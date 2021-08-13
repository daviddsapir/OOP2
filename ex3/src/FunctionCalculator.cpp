#include "FunctionCalculator.h"

#include <fstream>
#include "Macros.h"
#include <cmath>
#include <iostream>

#include "Sin.h"
#include "Ln.h"
#include "Poly.h"
#include "Mul.h"
#include "Add.h"
#include "Comp.h"
#include "Log.h"

#include <istream>
#include <ostream>
#include <iomanip>
#include <string>
#include <sstream>


// C-tor
FunctionCalculator::FunctionCalculator(std::ostream& ostr)
    : m_actions(createActions()), m_functions(createFunctions()),
    m_istr(std::string()), m_ostr(ostr)
{}


//---------------------------- run ------------------------------
// The main function that receives requests and performs the 
// operations of the calculator using auxiliary functions.
// The calculator will run until it's getting a request to exit.
//---------------------------------------------------------------
void FunctionCalculator::run()
{
    std::string fileName, line_str;

    setMaxFunctions();

    m_ostr << std::setprecision(2) << std::fixed;
    do
    {
        try 
        {
            // Clears the prev data to get a new one.
            clearData();

            m_ostr << '\n';

            // Print the available functions list.
            printFunctions();
            m_ostr << ENTER_COMMAND;

            // Check if an external file is open.
            if (m_file.is_open()) 
            {
                // The file is open ==> read from file.
                readFromFile(line_str);
            }
            else 
            {
                // The file is closed ==> read from keyboard.
                readFromKeyboard(line_str);
            }

            // Get a line from an external file or from 
            // the user and read the current line into 
            // the string line_str.
            setLineArguments(line_str);
            processInputStr();
        }
        catch (std::exception& e)
        {
            std::cerr << e.what();

            // If file is open handle line error.
            fileHandlerErr(line_str);
        }

    } while (m_running);
} 


//-------------------- eval ---------------------
// Evaluates the value of the requasted equation
//-----------------------------------------------
void FunctionCalculator::eval()
{
    if (auto i = readFunctionIndex(); i)
    {
        auto x = 0.;

        // Read a number form the user.
        if (!(m_istr >> x))
        {
            throw std::invalid_argument
            (INVALID_ARGUMENT + EXPECT_NUM);
        }

        auto sstr = std::ostringstream();
        sstr << std::setprecision(2) << std::fixed << x;
        m_ostr << m_functions[*i]->to_string(sstr.str())
            << " = "
            << (*m_functions[*i])(x)
            << '\n';
    }
} 


//----------------------------- poly --------------------------------
// Inserts and new Polynomial into the functions list.
// 
// function description:
// 1. Reads the desired power of the polynomial from the user and
// checks if the power of the polynomial is valid (the power of the
// polynomial should be Natural number).
// 2. Read the Polynomial coefficients (The coefficients should be
// real numbers).
//-------------------------------------------------------------------
void FunctionCalculator::poly()
{
    auto n = 0.;

    // Check the power of the polynomial.
    // The power of the polynomial should be Natural number.
    // ==> The number cannot be a letter, double or negative.
    if (!(m_istr >> n) || isNotNaturalNum(n) || isNegativeNum(n))
    {
        throw std::invalid_argument
        (INVALID_ARGUMENT + COEFFICIENTS_ERROR);
    }

    // Read the polynomial coefficients.
    auto coeffs = std::vector<double>((int)n);
    for (auto& coeff : coeffs)
    {
        if (!(m_istr >> coeff))
        {
            throw std::invalid_argument
            (INVALID_ARGUMENT + EXPECT_NUM);
        }
    }
    m_functions.push_back(std::make_shared<Poly>(coeffs));
} 


//------------------------------ log --------------------------------
// Insert a new log with base N into function the functions list.
//  
// function description:
// 1. Reads the log base from the user and check the validation
// of the base entered. The base should be a number greater than one.
// 2. Reads the function index that the log function is going to 
// work upon and push the new log function into the function list.
//-------------------------------------------------------------------
void FunctionCalculator::log()
{
    auto base = 0.;

    // Read the log base from the user and check the validation
    // of the base entered.
    if (!(m_istr >> base) || base < 1 || isNotNaturalNum(base))
    {
        throw std::invalid_argument(INVALID_ARGUMENT + LOG_BASE_ERR);
    }

    // Read the function index that the log function
    // is going to work upon and push the new log function
    // into the function list.
    if (auto f = readFunctionIndex(); f)
    {
        m_functions.push_back
        (std::make_shared<Log>((int)base, m_functions[*f]));
    }
} 


//---------------------- del -------------------------
// Deletes an equation from the function list.
//----------------------------------------------------
void FunctionCalculator::del()
{
    if (auto i = readFunctionIndex(); i)
    {
        m_functions.erase(m_functions.begin() + *i);
    }
} 


//---------------- help --------------------
// Print calculator commands list.
// Prints all the available commands and 
// how to use them.
//------------------------------------------
void FunctionCalculator::help()
{
    m_ostr << AVAILABLE_COMMANDS;
    for (const auto& action : m_actions)
    {
        m_ostr << "* " << action.command <<
            action.description << '\n';
    }
    m_ostr << '\n';
} 


//-------------------------- read ------------------------------
// Opens a file for reading.
// If file is already open, the read action will be ignored.
// If the opening of the file fails, ifstream exception will
// be thrown.
//--------------------------------------------------------------
void FunctionCalculator::read()
{
    if (!m_file.is_open()) {

        m_file.open(readFileName());
        if (!m_file.is_open())
        {
            throw std::ifstream::failure(CANNOT_OPEN_FILE_ERR);
        }
    }
    else 
    {
        m_ostr << FILE_ALREADY_OPEN;
    }
} 


//------------------ exit ----------------------
// Displays Goodbye to the user and raises 
// a flag that the program should stop running.
//----------------------------------------------
void FunctionCalculator::exit()
{
    m_ostr << "Goodbye!\n";
    m_running = false;
}


//-------------------------- resize ----------------------------
// Resizes the amount of functions in the functions list. 
// The resize will be done if the action is available.
//--------------------------------------------------------------
void FunctionCalculator::resize()
{
    int t_max_func = 0;

    // Read the size to resize to.
    if (!(m_istr >> t_max_func))
    {
        throw std::invalid_argument
        (INVALID_ARGUMENT + EXPECT_NATURAL_NUM);
    }
    
    //Check if max above current functions.
    if (t_max_func >= m_functions.size() && t_max_func <= 100)
    {
        max_functions = t_max_func;
    }
    else if (isValidReduceRequest(t_max_func))
    {
        auto c = char();

        m_ostr << DECREASE_FUNC_NUM;

        while (true)
        {
            std::cin >> c;
            std::cin.clear();
            std::cin.ignore();

            if (c == ACCEPT ||
                c == std::toupper(ACCEPT))
            {
                m_functions.resize(t_max_func);
                max_functions = t_max_func;
                break;
            }
            else if (c == DECLINE || c == std::toupper(DECLINE))
            {
                break;
            }
            else
            {
                std::cerr << WRONG_INPUT_ERROR;
            }
        }


        std::cin.clear();
    }
    else throw std::runtime_error(INVALID_SIZE);
} 


//------------------- printFunctions -------------------
// Prints the function list.
//------------------------------------------------------
void FunctionCalculator::printFunctions() const
{
    m_ostr << CURR_CAPACITY << m_functions.size()
        << MAX_CAPACITY << max_functions << "\n\n";

    m_ostr << "List of available gates:\n";

    for (decltype(m_functions.size()) i = 0;
        i < m_functions.size(); ++i)
    {
        m_ostr << i << ".\t" <<
            m_functions[i]->to_string("x") << '\n';
    }
    m_ostr << '\n';
} 


//----------------------- setLineArguments -----------------------
// Gets a line from an external file or from  the user and read 
// the current line into a string and pushes the arguments into
// a vector. (We use the vector m_args later to check the 
// validation of the input. i.e. with the vector we check the
// amount of argument passed for the current action.
//----------------------------------------------------------------
void FunctionCalculator::setLineArguments(const std::string& str)
{
    std::string buf;
    std::istringstream ss(str);

    while (ss >> buf)
        m_arg.push_back(buf);
}


//------------------- readFromKeyboard -------------------
// Reads input from keyboard. 
//---------------------------------------------------------
void FunctionCalculator::readFromKeyboard(std::string& str)
{
    std::getline(std::cin, str);
    m_istr.str(str);
} 


//-------------------- readFromFile --------------------
// reads input from file. 
//------------------------------------------------------
void FunctionCalculator::readFromFile(std::string& str)
{
    std::getline(m_file, str);
    if (m_file.eof())
        m_file.close();
    m_istr.str(str);
}


//------------------------- fileHandlerErr --------------------------
// Handle error relate to a line in file.
//-------------------------------------------------------------------
void FunctionCalculator::fileHandlerErr(const std::string& line_err)
{
    if (m_file.is_open()) 
    {
        char c;
        m_ostr << ERROR_IN_LINE << line_err;
        m_ostr << STOP_READING_FILE;
       
        while (true)
        {
            std::cin >> c;
            std::cin.clear();
            std::cin.ignore
            (std::numeric_limits<std::streamsize>::max(), '\n');
            if (c == ACCEPT || c == std::toupper(ACCEPT))
            {
                m_file.close();
                break;
            }
            else if (c == DECLINE || c == std::toupper(DECLINE))
            {
                break;
            }

            std::cout << WRONG_INPUT_ERROR;
        }

        std::cout << "\n";
        std::cin.clear();
    }
}


//----------------------- setMaxFunctions ----------------------
// Set the amount of max function is this program. 
//--------------------------------------------------------------
void FunctionCalculator::setMaxFunctions()
{
    m_ostr << INSERT_FUNC_NUM;

    while (1) 
    {
        try {

            // Read the amount of functions the user wants.
            if (!(std::cin >> max_functions))
            {
                throw std::ios_base::failure
                (INVALID_ARGUMENT + EXPECT_NUM);
            }

            // Print error message if the amount is not in range.
            if (max_functions < 2 || max_functions > 100) 
                m_ostr << WRONG_INPUT;
         
            else 
                break;
        }
        catch (std::ios_base::failure& e) {
            m_ostr << e.what() << "\n\n" + INSERT_FUNC_NUM;
            std::cin.clear();
            std::cin.ignore
            (std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::cin.clear();
    std::cin.get();
}


//---------------- capacityFuncsValidation ----------------
// Checks the capacity of the functions in this program.
// If the amount of functions is exceeded, an exception
// is thrown.
//---------------------------------------------------------
void FunctionCalculator::capacityFuncsValidation(
    const Action& action) const
{
    if (max_functions == m_functions.size() &&
        isInsertAction(action))
    {
        std::string error = (MAX_FUNC_ALLOWED +
            std::to_string(max_functions) + '\n');

        throw std::range_error(error);
    }
}


//------------------------- argsValidation ------------------------
// Check the validation of the arguments delivered to an action.
// 
// There are 5 types of validations:
// 1. noArgValidation - checks if the user entered only the action
//    name and did not added any more arguments.
// 2. oneArgValidation - checks if the user delivered only one 
//    argument for the action.
// 3. twoArgValidation - checks if the user delivered two argument
//    for the action.
// 4. polyArgValidation - Checks whether the amount of polynomial 
//    coefficients provided for the function corresponds to the 
//    power of the polynomial.
//-----------------------------------------------------------------
void FunctionCalculator::argsValidation(const Action& action) const
{
    switch (action) 
    {
        case Action::Help:    noArgValidation();    break;
        case Action::Exit:    noArgValidation();    break;

        case Action::Del:    oneArgValidation();    break;
        case Action::Resize: oneArgValidation();    break;

        case Action::Eval:   twoArgValidation();    break;
        case Action::Mul:    twoArgValidation();    break;
        case Action::Add:    twoArgValidation();    break;
        case Action::Comp:   twoArgValidation();    break;
        case Action::Log:    twoArgValidation();    break;

        case Action::Poly:  polyArgValidation();    break;
        case Action::Read: readArgsValidation();    break;
    }

    // Checks the total functions capacity.
    capacityFuncsValidation(action);
}


//--------------- getFileName ----------------
// Reads and return the file name.
//--------------------------------------------
std::string FunctionCalculator::readFileName() 
{
    std::string fileName;
    m_istr >> fileName;

    return fileName;
}


//----------- processInputStr --------------
// Reads action from the user and sends it 
// to the function runaction that:
// 1. Checks the validation of the input.
// 2. Links to the appropriate function to 
//    perform the operation.
//------------------------------------------
void FunctionCalculator::processInputStr()
{
    const auto action = readAction();
    runAction(action);
}


//------------------------ readFunctionIndex ------------------------
// Reads and returns the function index.
//-------------------------------------------------------------------
std::optional<int> FunctionCalculator::readFunctionIndex() 
{
    auto i = 0.;

    if (!(m_istr >> i) || isNegativeNum(i) || isNotNaturalNum(i))
    {
        throw std::invalid_argument
        (INVALID_ARGUMENT + EXPECT_NATURAL_NUM);
    }

    if ((int)i >= m_functions.size())
    {
        throw std::out_of_range
        (FUNC_NUM + std::to_string((int)i) + NOT_EXSIT);
    }

    return i;
}


//----------------------- readAction -----------------------
// Reads the desired actions the user want.
// 
// function description:
// 1. Reads wanted action from the user.
// 2. Checks if the action is found in the available
//    actions list.
//----------------------------------------------------------
FunctionCalculator::Action FunctionCalculator::readAction()
{
    // holds the string of the action.
    auto action = std::string();

    // Read wanted action from the user.
    if (!(m_istr >> action))
    {
        throw std::invalid_argument(INVALID_ARGUMENT);
    }

    // Check if the action is found in actions list.
    for (decltype(m_actions.size()) i = 0;
        i < m_actions.size(); ++i)
    {
        if (action == m_actions[i].command)
        {
            return m_actions[i].action;
        }
    }

    // The action wasn't found ==> 
    // return that the action is invalid.
    return Action::Invalid;
}


//------------------------- runAction --------------------------
// Run the desired action the user requested.
//--------------------------------------------------------------
void FunctionCalculator::runAction(Action action)
{
    validation(action);

    switch (action)
    {
        default:
            m_ostr << UNKNOWN_ENUM;
            break;

        case Action::Invalid: 
            throw std::invalid_argument(INVALID_ARGUMENT);
            break;

        case Action::Eval:   eval();              break;
        case Action::Poly:   poly();              break;
        case Action::Mul:    binaryFunc<Mul>();   break;
        case Action::Add:    binaryFunc<Add>();   break;
        case Action::Comp:   binaryFunc<Comp>();  break;
        case Action::Resize: resize();            break;
        case Action::Log:    log();               break;
        case Action::Del:    del();               break;
        case Action::Help:   help();              break;
        case Action::Read:   read();              break;
        case Action::Exit:   exit();              break;
    }
}


//----------------------------------- createActions -------------------------------------
FunctionCalculator::ActionMap FunctionCalculator::createActions()
{
    return ActionMap
    {
        {
            "eval",
            "(uate) num x - compute the result of function #num on x",
            Action::Eval
        },
        {
            "poly",
            "(nomial) N c_0 c_1 ... c_(N-1) - creates a polynomial with N coefficients",
            Action::Poly
        },
        {
            "mul",
            "(tiply) num1 num2 - Creates a function that is the multiplication of "
            "function #num1 and function #num2",
            Action::Mul
        },
        {
            "add",
            " num1 num2 - Creates a function that is the sum of function #num1 and "
            "function #num2",
            Action::Add
        },
        {
            "resize",
            " num1 - Resize maximum functions allowed in list"
            "function #num1",
            Action::Resize
        },
        {
            "comp",
            "(osite) num1 num2 - creates a function that is the composition of "
            "function #num1 and function #num2",
            Action::Comp
        },
        {
            "log",
            " N num - create a function that is the log_N of function #num",
            Action::Log
        },
        {
            "del",
            "(ete) num - delete function #num from the function list",
            Action::Del
        },
        {
            "read",
            " - read file name",
            Action::Read
        },
        {
            "help",
            " - print this command list",
            Action::Help
        },
        {
            "exit",
            " - exit the program",
            Action::Exit
        }
    };
}


//------------------------- createFunctions ---------------------------
// Creates the two intial functions.
//---------------------------------------------------------------------
FunctionCalculator::FunctionList FunctionCalculator::createFunctions()
{
    return FunctionList
    {
        std::make_shared<Sin>(),
        std::make_shared<Ln>()
    };
}


//-------------------- twoArgValidation -------------------
// Checks if the user delivered two argument
// for the action. 
//---------------------------------------------------------
void FunctionCalculator::twoArgValidation() const
{
    if (m_arg.size() != 3)
    {
        if (m_arg.size() < 3)
        {
            throw std::runtime_error(NOT_ENOUGH_ARG);
        }
        else if (m_arg.size() > 3)
        {
            throw std::runtime_error(TOO_MANY_ARG);
        }
    }
}


//--------------------- polyArgValidation ---------------------
// Checks the polynomial arguments validation.
// Chekcs if the amount of coefficients maches the polynomial
// power. 
//-------------------------------------------------------------
void FunctionCalculator::polyArgValidation() const
{
    if (floor(std::stod(m_arg[1])) - std::stod(m_arg[1]) < 0)
    {
    }
    else if (m_arg.size() < std::stod(m_arg[1]) + 2)
    {
        throw std::runtime_error(NOT_ENOUGH_ARG);
    }
    else if (m_arg.size() > std::stod(m_arg[1]) + 2)
    {
        throw std::runtime_error(TOO_MANY_ARG);
    }
}


//---------------- readArgsValidation ----------------
// Checks if the read function recived a file name. 
//----------------------------------------------------
void FunctionCalculator::readArgsValidation() const
{
    if (m_arg.size() == 1)
    {
        throw std::runtime_error("No file name");
    }
    else if (m_arg.size() != 2)
    {
        throw std::runtime_error(INVALID_ARGUMENT);
    }
}


//---------------- noArgValidation ----------------
// Checks if the user entered only the action
// name and did not added any more arguments.
//-------------------------------------------------
void FunctionCalculator::noArgValidation() const
{
    if (m_arg.size() != 1)
    {
        throw std::runtime_error(TOO_MANY_ARG);
    }
}


//------------------- oneArgValidation --------------------
// Checks if the user delivered only one
// argument for the action.
// If the amount of argument are not as expected an 
// appropriate exception is thrown.
//---------------------------------------------------------
void FunctionCalculator::oneArgValidation() const
{
    if (m_arg.size() != 2)
    {
        if (m_arg.size() > 2)
        {
            throw std::runtime_error(TOO_MANY_ARG);
        }
        else
        {
            throw std::runtime_error(NOT_ENOUGH_ARG);
        }
    }
}


//------------------------- isInsertAction --------------------------
// Returns if the action is an insertion action.
// The actions poly, log, mul, add, comp can add a function to the
// functions list.
//-------------------------------------------------------------------
bool FunctionCalculator::isInsertAction(const Action& action) const
{
    return (action == Action::Poly ||
        action == Action::Log ||
        action == Action::Mul ||
        action == Action::Add ||
        action == Action::Comp);
}


//-------------- clearData -----------------
// Clears the members that hold the data.
//------------------------------------------
void FunctionCalculator::clearData()
{
    m_arg.clear();
    m_istr.clear();
}


//---------------------- isNotNaturalNum -----------------------
// Returns if a numbe is not natural number.
//--------------------------------------------------------------
bool FunctionCalculator::isNotNaturalNum(const double n) const
{
    return (floor(n) - n) < 0;
}


//----------------------- isNegativeNum ------------------------
// Returns if a number is negative number.
//--------------------------------------------------------------
bool FunctionCalculator::isNegativeNum(const double n) const
{
    return n < 0;
}


//---------------- isValidReduceRequest -----------------
// Returns if the user asks for valid reduce request of
// the amount of function that can be hold in program.
//-------------------------------------------------------
bool FunctionCalculator::isValidReduceRequest(
    const int t_max_func) const
{
    return (t_max_func >= MIN_CAPACITY_FUNCS &&
        t_max_func <= MAX_FUNC_SIZE &&
        t_max_func < m_functions.size());
}


//------------------------- validation -------------------------
// Checks the validation of the current action.
// Calls the auxillary function argsValidation to Check the
// validation of the arguments delivered to an action.
//--------------------------------------------------------------
void FunctionCalculator::validation(const Action& action) const
{
    if (action == Action::Invalid)
    {
        throw std::invalid_argument(INVALID_ACTION);
    }
    else
    {
        argsValidation(action);
    }
}
