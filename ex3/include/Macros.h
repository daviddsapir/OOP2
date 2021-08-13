#pragma once

#include <string>

const std::string
UNKNOWN_ENUM = "\nUnknown enum entry used!\n",

ENTER_COMMAND = "Enter command ('help' for the list of available commands): ",

AVAILABLE_COMMANDS = "The available commands are:\n",

INVALID_ARGUMENT = "\nInvalid argument: ",

INVALID_ACTION = "\nInvalid action\n",

ERROR_IN_MAIN_MSG = "\nError in program.\n",

EXPECT_NATURAL_NUM = "Expecting Natural number.\n",

EXPECT_NUM = "Expecting number.\n",

EXPECT_STRING = "Expecting String.\n",

TOO_MANY_ARG = "\nToo many arguments...\n",

NOT_ENOUGH_ARG = "\nNot enough arguments...\n",

LOG_BASE_ERR = "Expecting Natural number greater than 1.\n",

DECREASE_FUNC_NUM = "Sure you wnat to reduce the list?'y'-yes 'n'-no ",

INSERT_FUNC_NUM = "Insert max functions requasted (between 2 and 100): ", 

WRONG_INPUT_ERROR = "Wrong input. \nPlease Try again: ",

INVALID_SIZE = "Size given is invalid",

STOP_READING_FILE = "\nStop reading from file? Press 'y' for yes 'n' for no: ",

ERROR_IN_LINE = "Error in line: ",

CURR_CAPACITY = "Current capacity: ",

MAX_CAPACITY = "\nMax capacity: ",

COEFFICIENTS_ERROR = "Expecting natural number for num of coefficents.\n",

MAX_FUNC_ALLOWED = "\nError: Max functions allowed: ",

FUNC_NUM = "\nFunction #",

NOT_EXSIT = " doesn't exist\n",

WRONG_INPUT = "Wrong input try again...",

// File errors
CANNOT_OPEN_FILE_ERR = "\nCannot open file.\n",

FILE_ALREADY_OPEN = "\nFile already open.\n";


// Max amount of function available.
const int MAX_FUNC_SIZE = 100;


const char
ACCEPT = 'y',
DECLINE = 'n';