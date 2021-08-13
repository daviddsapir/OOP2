#include <string>


//-------------------- Operations --------------------

// The operations symbol
const std::string
ADDITION = " + ",
MULT = " * ";

// The operations the user can use.
const std::string
EXIT = "exit",
EVAL = "eval",
POLY = "poly",
ADD = "add",
MUL = "mul",
COMP = "comp",
LOG = "log",
DEL = "del",
HELP = "help",
INSTRUCTION = "Following is the list of the calculator's available commands:\n\
eval(uate) num x - Evaluates function #num on x\n\
poly(nomial) N c0 c1 ... cN - 1 - Creates a polynomial with N coefficients\n\
mul(tiply) num1 num2 - Creates a function that is the multiplication of\n\
function #num1 and function #num2\n\
add num1 num2 - Creates a function that is the sum of function #num1 and\n\
function #num2\n\
comp(osite) num1 num2 - Creates a function that is the composition of\n\
function #num1 and function #num2\n\
log N num - Creates a function that computes log N of function #num\n\
del(ete) num - Deletes function #num from function list\n\
help - Prints this help screen\n\
exit - Exits the program\n\n";