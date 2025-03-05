#pragma once
#include "core.h"
#include "Config.h"
#include "core/delta_sys.h"



//May Implement Safe conversion helper functions later
//And String Validity checks (is a valid int,float etc representation)

#define PARSER_FEEDBACK_SIZE 12
#define GCODE_MAX_ARG_COUNT 26
#define LETTER_NUM(c)(c -'A')
#define IS_VALID_LETTER(c)(c <= 'Z' && c >= 'A')

#define OK(c) do{strcpy(c, "OK"); return c;}while(0)

struct GCodeArgs_t{
    char* cmd;
    uint32_t char_found;    // Store if the character was found
    int8_t char_offset[GCODE_MAX_ARG_COUNT];     // Store the character offset in the string
    int8_t count;           // Number of arguments

    bool foundArg(char c)
    {
        return BV32(char_found, LETTER_NUM(c));
    }
    inline int8_t __attribute__((always_inline)) offset(char c)
    {
        return char_offset[LETTER_NUM(c)];
    }
};

char* G0(GCodeArgs_t &args);
char* G1(GCodeArgs_t &args);
char* G2(GCodeArgs_t &args);
char* G3(GCodeArgs_t &args);
char* G4(GCodeArgs_t &args);
char* G5(GCodeArgs_t &args);
char* G6(GCodeArgs_t &args);
char* G7(GCodeArgs_t &args);
char* G8(GCodeArgs_t &args);
char* G9(GCodeArgs_t &args);
char* M0(GCodeArgs_t &args);
char* M1(GCodeArgs_t &args);
char* M2(GCodeArgs_t &args);
char* M3(GCodeArgs_t &args);
char* M4(GCodeArgs_t &args);
char* M5(GCodeArgs_t &args);
char* M6(GCodeArgs_t &args);
char* M7(GCodeArgs_t &args);
char* M8(GCodeArgs_t &args);
char* M9(GCodeArgs_t &args);

//parser debugging command
char* G900(GCodeArgs_t &args);

extern char parser_feedback[PARSER_FEEDBACK_SIZE];

class simple_parser{
    
    GCodeArgs_t GCodeArgs;
    public: 
    void reset();
    char* parse(char* cmd);
};