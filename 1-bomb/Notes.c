// General-Purpose Registers
// RAX (Accumulator Register)
    // Historically used for arithmetic operations.
    // Often used to store return values from functions.
// RBX (Base Register)
    // Can be used as a base pointer for memory access.
    // Preserved across function calls (callee-saved).
// RCX (Counter Register)
    // Used as a loop counter in iteration operations.
    // Often used in string and memory operations.
// RDX (Data Register)
    // Used in input/output operations.
    // Often used to store the second return value in some calling conventions.
// RSI (Source Index)
    // Used as a source pointer in string and memory operations.
    // Often used to pass the second argument to functions.
// RDI (Destination Index)
    // Used as a destination pointer in string and memory operations.
    // Often used to pass the first argument to functions.
// RBP (Base Pointer)
    // Used to point to the base of the stack frame.
    // Preserved across function calls (callee-saved).
// RSP (Stack Pointer)
    // Points to the top of the stack.
    // Used to manage function call stacks.
// R8 to R15
    // Additional general-purpose registers introduced in x86-64.
    // Used to pass additional arguments to functions (R8 to R9).
// R10 and R11 are caller-saved, while R12 to R15 are callee-saved.

// the order of register to use for function arguments:
// di, si, dx, cx, 8, 9, ...

// bomb 4
func4(x, y, z)
{
    int ax = z;
    ax -= y

    int cx = ax;
    cx >>= 31;
    ax += cx;
    ax >>= 1;

    cx = ax + y;

    // 400fe4
    if (cx <= x)   
    {
        // 400ff2
        ax = 0;

        // 400ff9
        if (cx >= x)
        {
            // 401007
            return;
        }
        else
        {
            // 400ffb
            func4(x, cx + 1, z);
            ax = 1 + 2 * ax;
            return;
        }
    }

    else
    {
        // 400fe6
        func4(x, y, cx - 1);
        ax += ax;
        return ;
    }

}

// complete c version of func4
int func4(int x, int y, int z)
{
    int ax = z;
    ax -= y;

    int cx = ax;
    cx >>= 31;
    ax += cx;
    ax >>= 1;

    cx = ax + y;

    if (cx <= x)
    {
        if (cx >= x)
        {
            return 0;
        }
        else
        {
            return 2* func4(x, cx + 1, z) + 1;
        }
    }

    else
    {
        return 2 * func4(x, y, cx - 1);
    }
}

// Phase 5:
// input is a string with 6 letters.
// for each input char, take it's ASCII value, then and with 0xf.
//    for example, char 'i', ascii is 0x69, and with 0xf remains 0x9.
// Take the remianed value as index, search in an array: muduiersnfotvbyl
// Need to construct a string "flyers"
// the input should be "ionefg"

// Phase 6:
// input is six numbers
// each input x must be 1 <= x <= 6
// each input cannot be same as each other