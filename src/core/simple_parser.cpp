#include "simple_parser.h"


char parser_feedback[PARSER_FEEDBACK_SIZE];

char *M0(GCodeArgs_t &args)
{
    veh_state_t target;
    if(args.foundArg('S')){
        target.veh_spd_mm_s = atof(args.cmd + args.offset('S') + 1);
    }else{
        target.veh_spd_mm_s = 0;
    }

    if(args.foundArg('A')){
        target.veh_angV_rad_s = atof(args.cmd + args.offset('A') + 1);
    }else{
        target.veh_angV_rad_s = 0;
    }

    vehicle_laneBlazer->set_vehicleTarget(target, veh_cntrlType::SPD_ANGV);
    OK(parser_feedback);
}


char *M1(GCodeArgs_t &args)
{
    veh_state_t target;
    if(args.foundArg('L')){
        target.flw_angV_rad_s = atof(args.cmd + args.offset('L') + 1);
    }else{
        target.flw_angV_rad_s = 0;
    }

    if(args.foundArg('R')){
        target.frw_angV_rad_s = atof(args.cmd + args.offset('R') + 1);
    }else{
        target.frw_angV_rad_s = 0;
    }

    vehicle_laneBlazer->set_vehicleTarget(target, veh_cntrlType::WHEELSPEED);
    OK(parser_feedback);
}


char *M2(GCodeArgs_t &args)
{
    motor_power_t MOTPWR;
    if(args.foundArg('L')){
        MOTPWR.flw_MOT_power = atof(args.cmd + args.offset('L') + 1);
    }else{
        MOTPWR.flw_MOT_power = 0;
    }

    if(args.foundArg('R')){
        MOTPWR.frw_MOT_power = atof(args.cmd + args.offset('R') + 1);
    }else{
        MOTPWR.frw_MOT_power = 0;
    }

    if(args.foundArg('C')){
        MOTPWR.bcw_MOT_power = atof(args.cmd + args.offset('C') + 1);
    }else{
        MOTPWR.bcw_MOT_power = 0;
    }

    vehicle_laneBlazer->set_motorPower(MOTPWR);
    OK(parser_feedback);
}



char *G900(GCodeArgs_t &args)
{
    #if defined(DEBUG_) && ENABLED(DEBUG_PARSER)

        for(char c = 'A'; c <= 'Z'; c++){
            if(args.foundArg(c)){
                debug_out<char>("FOUND %c", c);
                debug_out<int>("AT %d", args.offset(c));
            }
        }

        for(char c = 'A'; c <= 'Z'; c++){
            if(args.foundArg(c)){
                debug_out<char*>("%s", args.cmd + args.offset(c));
            }
        }
    #endif
    OK(parser_feedback);
}

void simple_parser::reset()
{
    GCodeArgs.char_found = 0;
    GCodeArgs.count = 0;
}


char *simple_parser::parse(char *cmd)
{
    GCodeArgs.cmd = cmd;
    cmd = strtok(cmd, COMMAND_DELIMETER);
    char* currentArg;

    #if defined(DEBUG_PARSER) && ENABLED(DEBUG_PARSER)
        debug_out("CMD : %s " , cmd);
    #endif

    while((currentArg = strtok(NULL, COMMAND_DELIMETER)) != NULL && (GCodeArgs.count < GCODE_MAX_ARG_COUNT) ){
        char letter = currentArg[0];
        if(IS_VALID_LETTER(letter)){
            SBI32(GCodeArgs.char_found, LETTER_NUM(letter));   //Set bit corresponding to finding the letter
            GCodeArgs.char_offset[LETTER_NUM(letter)] = currentArg - GCodeArgs.cmd;
        }
        GCodeArgs.count++;
    }

    uint16_t cmdNum;
    if(strlen(cmd)>1){
        cmdNum = atoi(cmd+1);
    }else{
        cmdNum = 0xFFFF; //a value that wont trigger a command
    }

    switch(cmd[0]){
        case 'M':
            switch(cmdNum){
                case 0:
                    return M0(GCodeArgs);
                case 1:
                    return M1(GCodeArgs);
                case 2:
                    return M2(GCodeArgs);
                default:
                    strcpy(parser_feedback, "unk_M");
                    return parser_feedback;
            }
            break;
        case 'G':
            switch (cmdNum)
            {            
                case 900:
                    return G900(GCodeArgs);
                default:
                    strcpy(parser_feedback, "unk_G");
                    return parser_feedback;
            }
            break;

        default:
            strcpy(parser_feedback , "err");
            return parser_feedback;
    }
}
