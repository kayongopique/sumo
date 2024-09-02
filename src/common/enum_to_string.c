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

const char *line_to_string(line_e line)
{
    switch (line) {
    case LINE_NONE:
        return "NONE";
    case LINE_FRONT:
        return "FRONT";
    case LINE_BACK:
        return "BACK";
    case LINE_FRONT_LEFT:
        return "FRONT_LEFT";
    case LINE_BACK_LEFT:
        return "BACK_LEFT";
    case LINE_FRONT_RIGHT:
        return "FRONT_RIGHT";
    case LINE_BACK_RIGHT:
        return "BACK_RIGHT";
    case LINE_LEFT:
        return "LEFT";
    case LINE_RIGHT:
        return "RIGHT";
    case LINE_DIAGONAL_LEFT:
        return "DIAGONAL_LEFT";
    case LINE_DIAGONAL_RIGHT:
        return "DIAGONAL_RIGHT";
    }
    return "";
}

const char *enemy_pos_to_string(enemy_pos_e pos)
{
    switch (pos) {
    case ENEMY_POS_NONE:
        return "NONE";
    case ENEMY_POS_FRONT_LEFT:
        return "FRONT_LEFT";
    case ENEMY_POS_FRONT:
        return "FRONT";
    case ENEMY_POS_FRONT_RIGHT:
        return "FRONT_RIGHT";
    case ENEMY_POS_LEFT:
        return "LEFT";
    case ENEMY_POS_RIGHT:
        return "RIGHT";
    case ENEMY_POS_FRONT_AND_FRONT_LEFT:
        return "FRONT_AND_FRONT_LEFT";
    case ENEMY_POS_FRONT_AND_FRONT_RIGHT:
        return "FRONT_AND_FRONT_RIGHT";
    case ENEMY_POS_FRONT_ALL:
        return "FRONT_ALL";
    case ENEMY_POS_IMPOSSIBLE:
        return "IMPOSSIBLE";
    }
    return "";
}

const char *enemy_range_to_string(enemy_range_e range)
{
    switch (range) {
    case ENEMY_RANGE_NONE:
        return "NONE";
    case ENEMY_RANGE_CLOSE:
        return "CLOSE";
    case ENEMY_RANGE_MID:
        return "MID";
    case ENEMY_RANGE_FAR:
        return "FAR";
    }
    return "";
}

#endif