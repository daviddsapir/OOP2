#include "FunctionCalculator.h"

#include <iostream>
#include "Macros.h"

int main()
{
    try { 
        FunctionCalculator(std::cout).run();
    }
    catch (...) { 
        std::cout << ERROR_IN_MAIN_MSG;
    }

    return EXIT_SUCCESS;
} 
