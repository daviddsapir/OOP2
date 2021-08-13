==========================================================================

           OOP2 - ex3
=================================
by: David Sapir & Shimson Polak 
id: David - 208917351
    Shimson - 315605642 


			Calculator with exceptions.
==========================================================================

  			Description
                     =================	
The Program is a calculator of functions 
as given in ex1 but with exceptions that deal with
unwanted inputs were given by the user. On each invalid input given
a message will be shown accordingly to the error of the input.

Each input will be given as a line which each line should contain the 
operation and exact following input as described in ex1.

The program can as well get commands from an external file with 'read' <file_name>.
If the file does not exist error would be shown to the user.
Each line in the file should contain an operation same as described before, 
but the command 'read' would be ignored, as the file is already open.
If a line in the file does not meet the requirements, the user asked to
continue with the reading, or stop and close the file.

Also, the program as a limit of the number of function can be inserted in the list,
The User can decide the maximum function he wants to have in the list, at the 
start of the program, while the values can be between 2 and 100.

To change in the middle of the run the size, the user can use the command:
resize <num1>
If the size is given, is below some functions that existed in the list, 
the userwould be noted that it will delete the last functions above
 the size given and he should confirm it.

==========================================================================

                       	   Design
                      =================
We used the existed files given by the instructor,
 with some changes to fit the exceptions.

The 'run' function in the FunctionCalculator.cpp catch only the std::exception
because all the exceptions thrown have the same treatment.The exceptions goes
to the same try catch block,except the exception on the intilize size
given by the user.

The input from the file and the keyboard handled in the same way by
checking each line given.

=======================================================================

                         Included files
                        =================
We added "Macros.h" to hold the consts used in the program.
'resources' diractory been added to store the input file added for the 'read'
command.
=====================================================================

                           Data Structure
                          =================
=====================================================================

                        Algorithms worth mention:
                      =============================
=====================================================================

			    Known bugs
      		        ===================
=====================================================================

			    Comments
=====================================================================
1.The command read is not allowed if wriiten in the input file.

2.On messeages such as decreasing existed  functions 
or to continue reading the file if encounter a line with error,
the user will be asked to insert the respond 'y'-yes or 'n'-no accordingly
to the message.If given wrong answer, the user will be asked again.

3.Each input is read by a line, therefore the user need the whole requasted command
with the value,(the same for keyboard and file input)

4.An input.txt file example is included in the files.
Some error will be shown on porpuse for the exception examples.

5.exit command written in the input file, will close the program.