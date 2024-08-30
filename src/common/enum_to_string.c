#include "enum_to_string.h"

#ifndef DISABLE_ENUM_STRINGS
const char *ir_remote_cmd_to_string(ir_cmd_e cmd)
{
    switch (cmd) {
    case IR_CMD_0:
        return "0";
    case IR_CMD_1:
        return "1";
    case IR_CMD_2:
        return "2";
    case IR_CMD_3:
        return "3";
    case IR_CMD_4:
        return "4";
    case IR_CMD_5:
        return "5";
    case IR_CMD_6:
        return "6";
    case IR_CMD_7:
        return "7";
    case IR_CMD_8:
        return "8";
    case IR_CMD_9:
        return "9";
    case IR_CMD_STAR:
        return "STAR";
    case IR_CMD_HASH:
        return "HASH";
    case IR_CMD_UP:
        return "UP";
    case IR_CMD_DOWN:
        return "DOWN";
    case IR_CMD_LEFT:
        return "LEFT";
    case IR_CMD_RIGHT:
        return "RIGHT";
    case IR_CMD_OK:
        return "OK";
    case IR_CMD_NONE:
        return "NONE";
    }
    return "";
}

#endif