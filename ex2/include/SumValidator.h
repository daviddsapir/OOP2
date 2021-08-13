#pragma once
#include "Field.h"
#include "FormValidator.h"


//-------------------- class SumValidator ----------------------
class SumValidator: public FormValidator
{
public:

	// C-tor
	SumValidator(const std::string,  Field<int>*,
		 Field<int>*,  Field<int>*);

	// Returns fields validation.
	virtual bool isFieldsValid() override;

	// Sets fields validation
	virtual void setFieldsValidations(const bool) override;

private:

	// To hold the fields.
	Field<int>
		* m_totalFeild,
		* m_totalYoung,
		* m_totalAdults;
};


