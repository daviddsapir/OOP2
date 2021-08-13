#pragma once
#include "Validator.h"


//----------------- NotGreaterThanValidator -----------------
template<class T>
class NotGreaterThanValidator :public Validator<T>
{
public:

	// C-tor
	NotGreaterThanValidator(const int);

	// Virtual Function - Returns the input validation.
	virtual bool isInputValid(T) override;

private:

	// To hold the room size.
	const int m_capacity;
};


//--------------------- NotGreaterThanValidator C-tor -----------------------
template<class T>
inline NotGreaterThanValidator<T>::NotGreaterThanValidator(const int roomNum)
	:m_capacity(roomNum) 
{
	Validator<T>::setMsgError(NOT_GREATER_THAN_MSG_ERROR);
}


//------------------------ isInputValid ----------------------
// Returns the input validation.
// Checks if the input is less or equal to the max capacity.
//------------------------------------------------------------
template<class T>
inline bool NotGreaterThanValidator<T>::isInputValid(T input)
{
	return input <= m_capacity;
}