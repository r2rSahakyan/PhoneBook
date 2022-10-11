#pragma once
#include <string>
class PhoneBookNote
{
	enum  ValidFlags
	{
		invalidPhone = 1,
		inValidSeparator = 2,
		invalidNode = 4
	};

public:
	enum SortCriteria
	{
		Name = 0,
		Surname,
		Phone,
	};
	PhoneBookNote(std::string name = "", std::string surname = "", std::string separator = "", std::string phoneNumber = "");
	bool validate();
	inline short getValidationFlags() { return m_validationFlag; };
	inline bool isValid() { return m_isValid; };
	inline std::string getName(){return m_name;};
	inline std::string getSurname() { return m_surname; };
	inline std::string getPhone() { return m_phoneNumber; };
	std::string stringToPrint();
	std::string validStringToPrint();
	bool lessThan(PhoneBookNote,SortCriteria)const;
private:
	std::string m_name;
	std::string m_surname;
	std::string m_phoneNumber;
	std::string m_separator;
	bool m_isValid;
	short m_validationFlag;///0=valid,001=invalid phone, 010=invalid separator, 100=invalide node;
};