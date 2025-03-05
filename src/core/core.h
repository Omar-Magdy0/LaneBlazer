#pragma once
#include <stdint.h>



#define SBI32(reg, bit) ((reg) |= (1U << (bit)))  // Set Bit
#define CBI32(reg, bit) ((reg) &= ~(1U << (bit))) // Clear Bit
#define BV32(reg, bit) ((reg) & (1U << (bit))) //get bit value

#ifndef SBI
    #define SBI(reg, bit) ((reg) |= (1U << (bit)))
#endif
#ifndef CBI
    #define CBI(reg, bit) ((reg) &= ~(1U << (bit)))
#endif
#ifndef BV
    #define BV(reg, bit) ((reg) & (1U << (bit)))
#endif


#define ENABLED(x) ((x)==1)
#define DISABLED(x) ((x)==0)
#define CONF_ENABLE 1
#define CONF_DISABLE 0
#define FREQ_TO_PTIME(F)(1.0/F)
#define PTIME_TO_FREQ(PT)(1.0/PT)

#define SIGN(n)((n>0)?1:((n<0)?-1:0))
#define SIGN_NBIAS(n)((n<=0)?-1:1)
#define SIGN_PBIAS(n)((n>=0)?1:-1)
#define POSITIVE 1
#define NEGATIVE -1
#define ZERO 0

