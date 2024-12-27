#include "cachelab.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <getopt.h>

#define INSTR_LOAD 'I'
#define DATA_LOAD 'L'
#define DATA_STORE 'S'
#define DATA_MODIFY 'M'
typedef struct
{
    // I: instruction load
    // L: data load
    // S: data store
    // M: data modify
    char sType;
    unsigned long address;
    unsigned size;
} TraceLine;

typedef struct
{
    bool valid;
    unsigned long tag;
    int timestamp; // Most Recently referenced timestamp
} CacheLine;

// void printTraceLine(const TraceLine *trace, unsigned setID, unsigned rowID, unsigned tag, const char *status)
// {
//     printf("Type: %c, Address: 0x%x, Size: %u, SetID: %d, RowID: %d, Tag: %d, %s\n",
//            trace->sType, trace->address, trace->size,
//            setID, rowID, tag, status);
// }

void printVerbose(TraceLine* traceline, const char* status)
{
    printf("%c %lx,%d %s\n", traceline->sType, traceline->address, traceline->size, status);
}

void printUsage() {
    puts("Usage: ./csim [-hv] -s <num> -E <num> -b <num> -t <file>");
    puts("Options:");
    puts("  -h         Print this help message.");
    puts("  -v         Optional verbose flag.");
    puts("  -s <num>   Number of set index bits.");
    puts("  -E <num>   Number of lines per set.");
    puts("  -b <num>   Number of block offset bits.");
    puts("  -t <file>  Trace file.");
    puts("");
    puts("Examples:");
    puts("  linux>  ./csim -s 4 -E 1 -b 4 -t traces/yi.trace");
    puts("  linux>  ./csim -v -s 8 -E 2 -b 4 -t traces/yi.trace");
}

int main(int argc, char *argv[])
{
    // analysis the arguments
    unsigned nSetIndexbits = 0;
    unsigned nLinesPerSet = 0;
    unsigned nBlockBits = 0;
    bool verbose = false;
    const char *traceFilePath = NULL;
    int option;
    while ((option = getopt(argc, argv, "hvs:E:b:t:")) != -1)
    {
        switch (option)
        {
        case 'h':
            printUsage();
            exit(0);
            break;
        case 'v':
            verbose = true;
            break;
        case 's':
            nSetIndexbits = atoi(optarg);
            break;
        case 'E':
            nLinesPerSet = atoi(optarg);
            break;
        case 'b':
            nBlockBits = atoi(optarg);
            break;
        case 't':
            traceFilePath = optarg;
            break;
        default:
            printUsage();
            break;
        }
    }


    // // print information
    // printf("nSetIndexbits = %d\nnLinesPerSet = %d\nnBlockBits = %d\ntraceFilePath = %s\n",
    //        nSetIndexbits,
    //        nLinesPerSet,
    //        nBlockBits,
    //        traceFilePath);
    if (verbose);
    // Create the cache
    // 64-bit address: tag | setID | blockOffset
    unsigned nTagBits = 64 - nSetIndexbits - nBlockBits;
    unsigned nSet = pow(2, nSetIndexbits);
    // unsigned nBlock = pow(2, nBlockBits); // Do I need this value?

    // // print cache information
    // printf("nTagBits = %d\nnSet = %d\n", nTagBits, nSet);

    unsigned cacheSize = nSet * nLinesPerSet * sizeof(CacheLine);
    CacheLine *pCache = malloc(cacheSize);
    // Initialize the cache
    memset(pCache, 0, cacheSize);

    FILE *file = fopen(traceFilePath, "r");
    if (!file)
    {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    // count status
    unsigned nHit = 0;
    unsigned nMiss = 0;
    unsigned nEviction = 0;
    char line[256];
    int globalTimeStamp = -1;
    while (fgets(line, sizeof(line), file))
    {
        globalTimeStamp++;
        TraceLine trace;
        if (sscanf(line, " %c %lx,%u", &trace.sType, &trace.address, &trace.size) == 3)
        {
            // skip instruction load
            if (trace.sType == INSTR_LOAD)
            {
                continue;
            }
            unsigned setID = trace.address << nTagBits >> (nTagBits + nBlockBits);
            unsigned tag = trace.address >> (64 - nTagBits);

            // loop inside the set
            bool cacheHit = false;
            for (unsigned row = 0; row < nLinesPerSet; row++)
            {
                CacheLine cacheline = pCache[setID * nLinesPerSet + row];
                if (cacheline.valid && cacheline.tag == tag)
                {
                    // cache hit
                    cacheHit = true;
                    nHit++;
                    // Update timestamp
                    pCache[setID * nLinesPerSet + row].timestamp = globalTimeStamp;
                    const char* status;
                    if (trace.sType == DATA_MODIFY)
                    {
                        nHit++;
                        status = "hit hit";
                    }
                    else
                    {
                        status = "hit";
                    }
                    if (verbose)
                    {
                        // printTraceLine(&trace, setID, row, tag, status);
                        printVerbose(&trace, status);
                    }
                    break;
                }
            }
            if (cacheHit)
            {
                continue; // go to next traceline
            }

            // cache miss, search for empty cache line
            nMiss++;
            bool emptyRowFound = false;
            for (unsigned row = 0; row < nLinesPerSet; row++)
            {
                CacheLine cacheLine = pCache[setID * nLinesPerSet + row];
                if (cacheLine.valid == false)
                {
                    pCache[setID * nLinesPerSet + row].valid = true;
                    pCache[setID * nLinesPerSet + row].tag = tag;
                    pCache[setID * nLinesPerSet + row].timestamp = globalTimeStamp;
                    emptyRowFound = true;
                    const char* status;
                    // a data modify will always follow a 'write hit'
                    if (trace.sType == DATA_MODIFY)
                    {
                        status = "miss hit";
                        nHit++;
                    }
                    else
                    {
                        status = "miss";
                    }
                    if (verbose)
                    {
                        // printTraceLine(&trace, setID, row, tag, status);
                        printVerbose(&trace, status);
                    }
                    break;
                }
            }
            if (emptyRowFound)
            {
                continue; // go to next traceline
            }

            // cache miss, and no empty cache line available, need to evict
            nEviction++;
            unsigned lruRow = 0;
            unsigned lruTimeStamp = globalTimeStamp;
            for (unsigned row = 0; row < nLinesPerSet; row++)
            {
                CacheLine cacheLine = pCache[setID * nLinesPerSet + row];
                // each row should be valid
                if (cacheLine.valid == false)
                {
                    perror("Invalid cache status");
                    return EXIT_FAILURE;
                }
                if (cacheLine.timestamp < lruTimeStamp)
                {
                    lruTimeStamp = cacheLine.timestamp;
                    lruRow = row;
                }
            }
            // Evict & replace cacheline
            pCache[setID * nLinesPerSet + lruRow].tag = tag;
            pCache[setID * nLinesPerSet + lruRow].timestamp = globalTimeStamp;
            pCache[setID * nLinesPerSet + lruRow].valid = true;
            const char* status;
            if (trace.sType == DATA_MODIFY)
            {
                status = "miss eviction hit";
                nHit++;
            }
            else
            {
                status = "miss eviction";
            }
            if (verbose)
            {
                // printTraceLine(&trace, setID, lruRow, tag, status);
                printVerbose(&trace, status);
            }
        }
        else
        {
            fprintf(stderr, "Failed to parse line: %s", line);
        }
    }
    fclose(file);

    free(pCache);
    pCache = NULL;

    printSummary(nHit, nMiss, nEviction);
    return 0;
}
