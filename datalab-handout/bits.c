/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {

  // not this situation: both x and y are 1.
  // also not this situation: both x and y are 0.
  return ~(x & y) & ~(~y & ~x);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 0x80 << 24;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  // x: 01111111 11111111 11111111 11111111
  // y = x + 1
  // y + y == 0
  // exclude the case when y is zero.
  // when logical not (!) something, the result can only be 0 or 1.
  // so it is safe to bit-and (&) two things if they have "!".
  return !(x + 1 + x + 1) & !!(x + 1);
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  // 0xAA = 0b10101010
  int oddBitMask = 0xAA | (0xAA << 8) | (0xAA << 16) | (0xAA << 24);

  // check if all odd bits are set: x & oddBitMask == oddBitMask

  // check if two numbers are equal: if (a ^ b == 0)
  
  // check if a number is zero: if (!x))
  return !((x & oddBitMask) ^ oddBitMask); 
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  // To judge whether a number >= 0, check if greatest bit is 0.
  // condition 1: x - 0x30 >= 0
  int s1 = (x + (~0x30 + 1)) >> 31;   // if s1 is 0, the condition 1 succeed.
  
  // condition 2: 0x39 - x >= 0
  int s2 = (0x39 + (~x + 1)) >> 31;   // if s2 is 0, the condition 2 succeed.

  return (s1 + 1) & (s2 + 1);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int mask = ~!x + 1;
  // when x is 0, mask is 0xffffffff, ~mask = 0x00000000
  // when x is not 0, mask is 0x00000000, ~mask = 0xffffffff
  return (~mask & y) | (mask & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  // have to consider the sign of x and y.
  int diffSign = ((x ^ y) >> 31) & 1;
  int xSign = x >> 31 & 1;

  // if x and y have different sign, and xSign is 1, then x < 0, y > 0 => x < y.
  // in this case, return xSign.

  // else, consider condition: y - x >= 0
  int s = (y + (~x + 1)) >> 31;   // if s == 0, the condition succeed.
  return (diffSign & xSign) | (!diffSign & !s);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  int negX = ~x + 1;
  int combined = x | negX;    // combined is 0 only if x and negX is Zero.
                              // Then x must be zero.
  int signBit = combined >> 31;
  return signBit + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  // The input in always 32 bits.
  // The mission is to find out how many bits are enough to represent the input, i.e. remove redundant 1 or 0 prefix.
  // Example 1. x = 12:
  // input: 0000 0000 0000 0000 0000 0000 0000 1100
  // To represent 12 in two's complement, 01100 is enough. So 4 + 1 = 5 bits.

  // Example 2. x = -12:
  // input: 1111 1111 1111 1111 1111 1111 1111 0100
  // To represent -12 in two's complement, 10100 is enough. So 5 bits.
  // invert the input: 0000 0000 0000 0000 0000 0000 0000 1011
  // 4 bits to represent the inverted number. 4 + 1 = 5 is the answer.


  // Example 3. x = -5:
  // input: 1111 1111 1111 1111 1111 1111 1111 1011
  // To represent -5 in two's complement, 1011 is enough. So 4 bits.
  // inver the input: 0000 0000 0000 0000 0000 0000 0000 0100
  // 3 bits to represent the inverted number. 3 + 1 = 4 is the number.

  // Step 1. Get the absolute value of x.
  // determine the sign bit.
  int signBit = x >> 31;

  // if x is non-negative, then signBit is 0000 0000 0000 0000 0000 0000 0000 0000;    x ^ signBit = x;
  // if x is negative, then signBit is     1111 1111 1111 1111 1111 1111 1111 1111;    x ^ signBit = ~x;
  int InvX = (x ^ signBit);

  // Step 2. Determine the index of the left-most 1 of InvX.
  // Use binary search.
  int bits = 0;
  
  // Does any of left 16 bits have set? If yes, then the number needs at least 16 bits.
  int leftHasOne = !!(InvX >> 16 << 16);
  bits += leftHasOne << 4;  // "<< 4" means "* 16"

  // Take left 16 bits if they have 1, else take right 16 bits (just keep it unchanged, since left 16 bits are all zero).
  InvX = InvX >> (leftHasOne << 4);

  // Now InvX remains 16 bits.
  // Does any of left 8 bits have set?
  leftHasOne = !!(InvX >> 8 << 8);
  bits += leftHasOne << 3;
  InvX = InvX >> (leftHasOne << 3);

  // Now InvX remains 8 bits.
  // Does any of left 4 bits have set?
  leftHasOne = !!(InvX >> 4 << 4);
  bits += leftHasOne << 2;
  InvX = InvX >> (leftHasOne << 2);

  // Now InvX remians 4 bits.
  leftHasOne = !!(InvX >> 2 << 2);
  bits += leftHasOne << 1;
  InvX = InvX >> (leftHasOne << 1);

  // Now InvX remians 2 bits.
  leftHasOne = !!(InvX >> 1 << 1);
  bits += leftHasOne;
  InvX = InvX >> leftHasOne;

  // Now InvX has 1 bits.
  bits += InvX;

  // Step 3.
  return bits + 1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  int s = uf >> 31;
  // set sign bit to 0, and then shift right to get e.
  int mask31 = (1 << 31) - 1;  // 0x7fff ffff
  int e = (uf & mask31) >> 23;
  
  // get f part
  int mask23 = mask31 >> 8;  // 0x007f ffff
  int f = (uf & mask23);

  // NaN: e == 0xffff and f != 0
  // Infinity: e == 0xffff and f == 0
  if (!(e ^ 0xff))
  {
    return uf;
  }

  // zero: e == 0 and f == 0
  if (!e && !f)
  {
    return uf;
  }

  // denormalized: e == 0
  if (!e)
  {
    return (s << 31) | (((e << 23) | f) << 1);
  }

  // normalized
  return (s << 31) | (e + 1) << 23 | f;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  int INVALID = 1 << 31;

  int s = uf >> 31;
  // set sign bit to 0, and then shift right to get e.
  int mask31 = (0x80 << 24) - 1;  // 0x7fff ffff
  int e = (uf & mask31) >> 23;
  
  // get f part
  int mask23 = mask31 >> 8;  // 0x007f ffff
  int f = (uf & mask23);

  // forward declare variable to avoid dlc check error:
  int exp = 0;
  int n = 0;

  // NaN: e == 0xffff and f != 0
  // Infinity: e == 0xffff and f == 0
  if (!(e ^ 0xff))
  {
    return INVALID;
  }

    // zero: e == 0 and f == 0
  if (!e && !f)
  {
    return 0;
  }

  // denormalized: e == 0
  if (!e)
  {
    return 0;
  }

  // normalized
  // 1.xxx...xxx * pow(2, 30) will not overflow. (x * pow(2, n) == x << n)
  // 1.xxx...xxx * pow(2, 31) will overflow.
  // thus, e - 127 = exp must < 31.
  // if exp < 0, the number's absolute value is smaller than 1.

  // get exp
  exp = e - 127;  // exp: used in pow(2, exp)
  if (exp >= 31)
  {
    return INVALID;
  }
  
  if (exp < 0)
  {
    return 0;
  }

  // get the unsigned number
  n = 1 << exp | f >> (23 - exp);

  // check sign bit
  if (s)
  {
    n = ~n + 1;
  }

  return n;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  // sign: always positive.
  // no need to | sign bit.
  // int s = 0; 

  // 1. normalized: 0 < e < 255 => -127 < x < 128
  if ((-127 < x) && (x < 128))
  {
    int e = x + 127;
    return e << 23;
  }
  
  // 2. denormalized: e = 0, use f to extend
  else if (-149 <= x && x <= -127)
  {
    return 1 << (149 + x);
  }

  // 3. too small:
  else if (x < -149)
  {
    return 0;
  }

  // 4. too large:
  else
  {
    return 255 << 23;
  }
}
