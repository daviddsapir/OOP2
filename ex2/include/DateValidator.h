#pragma once
#include "Validator.h"
#include "Macros.h"
#include <time.h>


//--------------------- class DateValidator --------------------
template<class T>
class DateValidator:public Validator<T>
{
public:

	// C-tor
	DateValidator();

	// Checks if the input is valid.
	virtual bool isInputValid(T input) override;

private:

	// Returns the order date.
	void getOrderDate(int, int&, int&, int&) const;

	// Checks if the length of the date is valid.
	bool isValidLen(int) const;

	// overload - Checks if the order day is valid.
	bool isValidOrderDate(const int, const int) const;
	
	// Reutrns if the order day is valid.
	bool isValidDate(const int, const int, const int,
		const int, const int, const int) const;

	// Gets a date and checks if the date is valid
	bool isValidDate(const int) const;
	
	// Returns the current date.
	void getCurrentDate(int&, int&, int&) const;
};


//--------------- DateValidator C-tor ----------------
// Initializes the error message for this validator.
//----------------------------------------------------
template<class T>
inline DateValidator<T>::DateValidator()
{
	Validator<T>::setMsgError(DATE_MSG_EROOR);
}


//------------------ isInputValid --------------------
// Check if the date given did not passed.
//----------------------------------------------------
template<class T>
inline bool DateValidator<T>::isInputValid(T date)
{
	return isValidDate(date);
}


//--------------------- getOrderDate ----------------------
// Returns the order date.
// Inserts the order day, month and year into varaible.
//---------------------------------------------------------
template<class T>
inline void DateValidator<T>::getOrderDate(int date,
	int& orderDay, int& orderMonth, int& orderYear) const
{
	orderYear = date % YEAR_DIGIT_LEN;
	date /= YEAR_DIGIT_LEN;
	orderMonth = date % DAY_AND_MONTH_DIGIT_LEN;
	orderDay = date /= DAY_AND_MONTH_DIGIT_LEN;
}


//------------------------ isValidLen -----------------------
// Checks if the length of the date is valid.
// date must include 7 - 8 digits.
//-----------------------------------------------------------
template<class T>
inline bool DateValidator<T>::isValidLen(int date) const
{
	return (date / DATE_EIGHT_DIGIT_LEN == 0 ||
		date / DATE_SEVEN_DIGIT_LEN == 0);
}


//------------------------- isValidDate -----------------------
// overload - Checks if the order day is valid.
// auxillary function to check if the current stats are valid.
//-------------------------------------------------------------
template<class T>
inline bool DateValidator<T>::isValidOrderDate(const int d1,
	const int d2) const
{
	return (d1 >= d2);
}


//-------------------------- isValidDate -------------------------
// Reutrns if the order day is valid.
// The function checks if the order date is greater or equal to 
// the current date.
//----------------------------------------------------------------
template<class T>
inline bool DateValidator<T>::isValidDate(const int orderDay,
	const int orderMonth, const int orderYear, const int currDay,
	const int currMonth, const int currYear) const
{
	// Check if valid year.
	if (!isValidOrderDate(orderYear, currYear))
	{
		return false;
	}

	// Check if valid month.
	if (orderYear == currYear &&
		!isValidOrderDate(orderMonth, currMonth))
	{
		return false;
	}

	// Check if valid day.
	if (orderYear == currYear && 
		orderMonth == currMonth &&
		!isValidOrderDate(orderDay, currDay))
	{
		return false;
	}


	return true;
}


//-------------------- getCurrentDate -------------------
// Returns the current date.
//-------------------------------------------------------
template<class T>
inline void DateValidator<T>::getCurrentDate(int& Day,
	int& Month, int& Year) const
{
	time_t t = time(0);
	tm* ltm = localtime(&t);
	
	Year = 1900 + ltm->tm_year;
	Month = 1 + ltm->tm_mon;
	Day = ltm->tm_mday;
}


//------------------------- isValidDate ------------------------
// Returns if order day is valid.
// Gets the current date and the order date and compares between
// them.
// Checks if the the order date is greater or equal to the 
// current date.
//--------------------------------------------------------------
template<class T>
inline bool DateValidator<T>::isValidDate(const int date) const
{
	int currDay, currMonth, currYear,
		orderDay, orderMonth, orderYear;

	// check if valid date len.
	if (!isValidLen(date)) return false;

	// Gets the current date.
	getCurrentDate(currDay, currMonth, currYear);

	// gets the order day, month and year.
	getOrderDate(date, orderDay, orderMonth, orderYear);

	// Return if the date is valid.
	return  isValidDate(orderDay, orderMonth, orderYear,
		currDay, currMonth, currYear);
}


