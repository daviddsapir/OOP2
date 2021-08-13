#pragma once
#include <string>


// IDValidator conts
const int ID_NUM_OF_DIGITS = 9,

// DateValidator consts
DATE_EIGHT_DIGIT_LEN = 100000000,
DATE_SEVEN_DIGIT_LEN = 10000000,
YEAR_DIGIT_LEN = 10000,
DAY_AND_MONTH_DIGIT_LEN = 100;


// Message errors consts
const std::string
NO_DIGIT_MSG_ERROR = "Can't contain digits",
NOT_GREATER_THAN_MSG_ERROR = "The maximum is 10 rooms",
DATE_MSG_EROOR = "The date has already passed",
ID_MSG_ERROR = "Wrong control digit",
NON_NEGATIVE_MSG_ERROR = "Can't be negative",
RANGE_MSG_ERROR = "Out of range";