#pragma once
#include "Validator.h"
#include "BaseField.h"
#include <iostream>


//------------------------ class Field -------------------------
template<class T>
class Field: public BaseField
{
public:

	// C-tor
	Field(const std::string);

	// Add validator.
	void addValidator( Validator<T>* validator);

	// Get field data content.
	const int getContent() const;

	// Show messege input and save input data.
	virtual void setData() override;

	// Check if the data is according to the validator.
	virtual bool isValid() override;

	// Update the validation of the field data.
	virtual void setFieldValidation(bool statues) override;

	// Print the field info with the data error if existed.
	virtual void printField(std::ostream&) override;

private:

	// Field data validator.
	Validator<T>* m_valid = nullptr;

	// Field input messege.
	const std::string m_inputMessege;

	// Stored data.
	T m_data;
};


//------------------------ Field C-tor -------------------------
template<class T>
Field<T>::Field(const std::string str) :m_inputMessege(str) {}


//----------------------- addValidator -------------------------
// Store existed validator which examin the data validation.
//--------------------------------------------------------------
template<class T>
inline void Field<T>::addValidator( Validator<T>* validator)
{
	m_valid = validator;
}


//----------------- getContent ----------------
// Returns field data content.
//---------------------------------------------
template<class T>
inline const int Field<T>::getContent() const
{
	return m_data;
}


//--------------------------- setData --------------------------
// Set new data if the last data is not according the validator.
//--------------------------------------------------------------
template<class T>
inline void Field<T>::setData()
{
	if (!m_valid->getValid()) 
	{
		std::cout << m_inputMessege << "\n";
		std::cin >> m_data;
	}
}


//----------------------------------------------------
//Check if the validator approve the data validation.
//----------------------------------------------------
template<class T>
inline bool Field<T>::isValid()
{
	return m_valid->isInputValid(m_data);
}


//------------------- setFieldValidation ----------------- 
// Update validation statues.
//--------------------------------------------------------
template<class T>
inline void Field<T>::setFieldValidation(bool statues)
{
	m_valid->setValid(statues);
}


//------------------------------ printField ------------------------------
// Print the field data stored, if there is an error, print it as well.
//------------------------------------------------------------------------
template<class T>
inline void Field<T>::printField(std::ostream& os)
{
	os << "---------------------------------------------------\n";
	os << m_inputMessege << " = " << m_data << "\t ";
	if (!m_valid->isInputValid(m_data)) std::cout << m_valid->getMsgErr();
	os << "\n";
	os << "---------------------------------------------------\n";
}
