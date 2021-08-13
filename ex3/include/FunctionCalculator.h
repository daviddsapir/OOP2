#pragma once

#include <vector>
#include <memory>
#include <string>
#include <iosfwd>
#include <optional>
#include <sstream>

#include <fstream>

class Function;

//--------------------- FunctionCalculator ---------------------
class FunctionCalculator
{
public:
    
    // C-tor
    FunctionCalculator(std::ostream& ostr);
    
    // Turns on the calculator.
    void run();

private:

    unsigned const int MIN_CAPACITY_FUNCS = 2;
    int max_functions = 4;
   
    // To read from the external file.
    std::ifstream m_file;

    // To hold the arguments for the current action.
    std::vector<std::string> m_arg;

    // evaluates the wanted equation
    void eval();
    
    // Insert a new Polynomial into the functions list. 
    void poly();
    
    // Insert a new log with base N into function
    // the functions list. 
    void log();
    
    // Delete an equation from the function list.
    void del();
    
    // Print calculator commands list. 
    void help();
    
    // Opens a file for reading.
    void read();
    
    // raises a flag to stop running the program.
    void exit();
    
    // Resizes the amount of functions 
    // in the functions list.
    void resize();

    template <typename FuncType>
    void binaryFunc()
    {
        if (auto f0 = readFunctionIndex(),
            f1 = readFunctionIndex(); f0 && f1)
        {
            m_functions.push_back(std::make_shared<FuncType>
                (m_functions[*f0], m_functions[*f1]));
        }
    }

    // Prints the function list.
    void printFunctions() const;

    // Reads input from keyboard.
    void readFromKeyboard(std::string&);

    // reads input from file.
    void readFromFile(std::string&);

    // sets string that hold the arguments into the 
    // vector m_arg that hold the arguemtns.
    void setLineArguments(const std::string&);

    // Handle error relate to a line in file.
    void fileHandlerErr(const std::string&);

    // Set the amount of max function is this program.
    void setMaxFunctions();

    // Clears the members that hold the data.
    void clearData();

    // Returns if a numbe is not natural number.
    bool isNotNaturalNum(const double) const;

    // Returns if a number is negative number.
    bool isNegativeNum(const double) const;

    // Returns if the user asks for valid reduce request of
    // the amount of function that can be hold in program.
    bool isValidReduceRequest(const int) const;

    void processInputStr();

    // enum to hold the available action.
    enum class Action
    {
        Invalid,
        Eval,
        Poly,
        Resize,
        Mul,
        Add,
        Comp,
        Log,
        Del,
        Read,
        Help,
        Exit,
    };


    // Returns if the action is an insertion action.
    bool isInsertAction(const Action& action) const;

    // Checks the validation of the current action.
    void validation(const Action& action) const;

    // Checks the capacity of the functions in this program.
    void capacityFuncsValidation(const Action& action) const;

    // Checks if the user entered only the action
    // name and did not added any more arguments.
    void noArgValidation() const;

    // Checks if the user delivered only one
    // argument for the action.
    void oneArgValidation() const;

    // Checks if the user delivered two argument
    // for the action.
    void twoArgValidation() const;

    // Checks the polynomial arguments validation. 
    void polyArgValidation() const;

    // Checks if the read function recived a file name.
    void readArgsValidation() const;

    // Check the validation of the arguments delivered
    // to an action.
    void argsValidation(const Action& action) const;

    // Reads and return the file name.
    std::string readFileName();

    struct ActionDetails
    {
        std::string command;
        std::string description;
        Action action;
    };

    using ActionMap = std::vector<ActionDetails>;
    using FunctionList = std::vector<std::shared_ptr<Function>>;

    const ActionMap m_actions;
    FunctionList m_functions;
    bool m_running = true;
    std::istringstream m_istr;
    std::ostream& m_ostr;

    // Reads and returns the function index.
    std::optional<int> readFunctionIndex();

    Action readAction();

    // Runs the desired action the user requested.
    void runAction(Action action);

    static ActionMap createActions();
    static FunctionList createFunctions();
};
