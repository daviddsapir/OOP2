#pragma once
#include<string>


//------------------- class Validator -------------------
template <class T>
class Validator
{
public:

	// Returns the message error
	const std::string getMsgErr() const;

	// Sets the message error.
	void setMsgError(const std::string);

	// Returns if the input is valid.
	virtual bool isInputValid(T) = 0;

	// Sets the current status of the validator.
	virtual void setValid(bool);

	// Returns the current status of the validation.
	virtual bool getValid();

private:

	// To hold the message error.
	std::string m_msgError = " ";

	// To hold the correctness of the validator.
	bool isValid = false;
};


//---------------------- getMsgErr ------------------------
// Returns the message error.
//---------------------------------------------------------
template <class T>
inline const std::string Validator<T>::getMsgErr() const
{
	return m_msgError;
}


//--------------------- setMsgError -------------------------
// Sets the message error. 
//-----------------------------------------------------------
template <class T>
inline void Validator<T>::setMsgError(const std::string str)
{
	m_msgError = str;
}


//----------------- setValid ------------------
// Sets the current status of the validator.
//---------------------------------------------
template<class T>
inline void Validator<T>::setValid(bool valid)
{
	isValid = valid;
}


//-------------- getValid -------------
// Returns the current status of 
// the validation.
//-------------------------------------
template<class T>
inline bool Validator<T>::getValid()
{
	return isValid;
}
