#pragma once
#include "Validator.h"
#include "Macros.h"


//------------- class RangeValidator -------------
template<class T>
class RangeValidator: public Validator<T>
{
public:

	// C-tor
	RangeValidator(const int,const int);

	// Returns if the input is valid.
	virtual bool isInputValid(T) override;

private:

	// Holds the min and max valid ranges.
	const int m_maxRange, m_minRange;
};


//------------------- RangeValidator C-tor ------------------
template<class T>
inline RangeValidator<T>::RangeValidator(const int minRange,
	const int maxRange)
	:m_maxRange(maxRange),m_minRange(minRange)
{
	Validator<T>::setMsgError(RANGE_MSG_ERROR);
}


//------------------ isInputValid -------------------------
// Returns if the data is in the range given.
//---------------------------------------------------------
template<class T>
inline bool RangeValidator<T>::isInputValid(T input)
{
	return (input >= m_minRange && input <= m_maxRange);
}