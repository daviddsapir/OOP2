==========================================================================

           OOP2 - ex2
=================================
by: David Sapir & Shimson Polak 
id: David - 208917351
    Shimson - 315605642 


			Functions Calculator.
==========================================================================

  			Description
                     =================	
Hotel Form that is filled by the user to order vacation.
The hotel has 20 rooms,10 are for 2 people each and 10 for 5 people each.
The program will check first if the fields input are corrects and than will
check if the data of are match.

The requiremnts for each field, are the following:

	Name: Name witout digits.

	Id  : Correct personal id with control digit.

	Birth : Year of birth that is reprasant age between 18 and 120.

	Start vactaion date: Date by DDMMYYYY format and it wasnt passed.

	Num of nighs: Positive number of requasted days to sleep.

	Num of people: Not negative number of people suppose to come.

	Num of pair rooms: The number is not above the avaible number of pair rooms.

	Num of family rooms: The number is not above the avaible number of family rooms

	Num of children and adults : Not negative number of adults and children.

Besides the required input data validation, the program will check:
1.Number of people is match to the young and adults numbers.
2.Number of people is match to the pair and family rooms capacity.

On each uncorrect input a messege will be shown and the user will be asked
to fix the data.
==========================================================================

                       	   Design
                      =================
Form
==========
Role: Manage the form of the hotel the user suppose to fill a
	nd prints the error acoordingly.
      The form hold vector of fields to recive the data from the user 
	and validators to check the info match accordingly.

BaseField
========
Role: A base class of template class Field which allowing Form
	to store differents types Field in a vector.

Field
========
Role: Template class which store the T type data and validator.
      The Field check the data according the validator given.

Validator
===
Role: Base Template class of differents types of validator which
	check the data validation given by Field class.

	The class below inherit from Validator:

	NonDigitValidator
	===
	Role: Check if the given data does not contain numbers.

	IDValidator
	===
	Role: Check if the id given is correct according the
	 'Control Digits' check.

	NonNegativeValidator
	===
	Role: Check if the given data is not a negative value.

	NotGreaterThanValidator
	===
	Role: Check if the given data is not above ROOMS_NUM.

	RangeValidator
	===
	Role: Check if the given data is between the values been 
	MIN_AGE and MAX_AGE.
	
	DateValidator
	===
	Role: Check if the given data is according ddmmyyyy format
	and the date is not before the current date..
	


FormValidator
=====
Role: Base class of Form validators (which check the data info)
	to store diffents types of validators in the same vector.

	The class below inherit from FormValidator

	RoomValidator
	========
	Role: Store pointers of Fields which hold the number of 
	total people,Pair rooms and Family rooms requasted
	Validate the numbers of total people match the Pair and Family rooms 
	capacity.


	SumValidator
	========
	Role: Store pointers of Fields which hold the number of 
	total people,adults and young.
	Validate the numbers of total people match the young and adults given.

=======================================================================

                         Included files
                        =================
1) BaseField.h - Abstract and base class of Form.

2) Form.h/cpp	- Class of the hotel form.

3) Field.h - Class of the Form field

4) Validator.h - Abstract and base class of  the differents validators.

5) DateValidator.h - Date validator.

6) IDValidator.h/cpp - Id validator.

7) NoDigitValidator.h/cpp - Validate the data has no digits.

8) NonNegativeValidator.h - Validate the data is not a negative value.

9) NotGreaterThanValidator.h - Validate the data is not above ROOMS_NUM.

10) RangeValidator.h - Validate data  between MIN_AGE and MAX_AGE.

11) FormValidator.h/cpp - Abstract and base class of Form validators.

12) SumValidator.h/cpp - Validator of total people match total adults and youngs.

13) RoomValidator.h/cpp - Validator of total people match pair and family rooms capacity.

14) Macros.h - Hold the consts used in the program.

6 source + 14 header = 20 files in total.

main.cpp was given.
=====================================================================

                           Data Structure
                          =================
=====================================================================

                        Algorithms worth mention:
                      =============================
1.Check digit- validate the Id number by multiplying the even position 
digits by 2 and sum all the digits and mod by 10, if the value is 0
the id is correct else not correct.

=====================================================================

			    Known bugs
      		        ===================
=====================================================================

			    Comments
=====================================================================
1.The program will checks by levels the inputs validations:
 	1.All the field are correct values.
	2.Total people number is equel to number of adults and youngs.
	3.Total people number is equel to number of pair and family rooms capacity.
if the total people doesnt match one of the form validator,the user will be asked to insert
again the values of the required unmatch fields.

2.On each validator errors messege will be shown accordingly if the data given wasnt
good

3.ctime libary used to extract today date and compare it with user input date