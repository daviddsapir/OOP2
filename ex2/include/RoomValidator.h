#pragma once
#include "Field.h"
#include "FormValidator.h"


//-------------------- class RoomValidator ---------------------
class RoomValidator: public FormValidator
{
public:

	// C-tor
	RoomValidator(const std::string,  Field<int>*,
		 Field<int>*,  Field<int>*);

	// Returns the validation of the field.
	virtual bool isFieldsValid() override;

	// Sets the fields validation.
	virtual void setFieldsValidations(const bool) override;

private:

	// To hold the fields.
	Field<int>
		* m_familyRoomsField,
		* m_pairRoomsField,
		* m_totalPeopleField;
};
