#include "PhoneBookNote.h"
#include <iostream>
#include <ctype.h>
#include <string>
///some util functions
bool lessThanNames(const std::string left,const std::string right)
{
	size_t minLength = left.size() > right.size() ? right.size() : left.size();
	for (size_t i = 0; i < minLength; i++)
	{
		if (toupper(left.at(i)) > toupper(right.at(i)))
			return false;
		if (toupper(left.at(i)) < toupper(right.at(i)))
			return true;
	}
	return left.size() < right.size();
}
bool lessThanSurames(const std::string left, const std::string right)
{
	if (left.empty())
		return false;
	else if (!left.empty() && right.empty())
		return true;
	else
		return lessThanNames(left, right);
}
bool lessThanPhones( std::string phoneLeft, std::string phoneRight)
{
	short numLeft;
	short numRight;
	try {
		if (phoneLeft.size() > 3)
			phoneLeft = phoneLeft.substr(0, 3);
		if (phoneRight.size() > 3)
			phoneRight = phoneRight.substr(0, 3);
		if (phoneLeft.empty())
			numLeft = 0;
		else
			numLeft = std::stoi(phoneLeft);
		if (phoneRight.empty())
			numRight = 0;
		else
			numRight = std::stoi(phoneRight);
		return numRight - numLeft > 0;
	}
	catch(const std::exception& ex)
	{
		std::cout << ex.what() <<'\n';
		std::cout<<"Check Phone numbers before sorting\n";
		return false;
	}	

}
//////////////////////

PhoneBookNote::PhoneBookNote(std::string name, std::string surname, std::string separator, std::string phoneNumber)
:m_name{name}
,m_surname{surname}
,m_separator{separator}
,m_phoneNumber{phoneNumber}
,m_isValid{true}
,m_validationFlag{0}
{
	validate();
}
bool PhoneBookNote::validate()
{
	//if no Name invalid node
	if (m_name.empty()||m_name=="{name}")
	{
		m_validationFlag |= invalidNode;
	}
	///validate phoneNumber
	if (m_phoneNumber.size() != 9)
		m_validationFlag |= invalidPhone;
	else
	{
		for (size_t i = 0; i < m_phoneNumber.size(); i++)
		{
			if (!isdigit(m_phoneNumber.at(i)))
			{
				m_validationFlag |= invalidPhone;
				break;
			}
		}
	}
	//validate separator
	if (m_separator != "-" && m_separator !=".")
	{
		m_validationFlag |= inValidSeparator;
	}
	if (m_validationFlag != 0)
		m_isValid = false;
	return m_isValid;
}
std::string PhoneBookNote::stringToPrint()
{
	std::string output{""};
	output += m_name += " ";
	if (!m_surname.empty())
		output += m_surname += " ";
	output += m_separator += " ";
	output += m_phoneNumber;
	return output;
}
std::string PhoneBookNote::validStringToPrint()
{
	std::string output{ "" };
	short test{0};
	test = m_validationFlag & invalidNode;
	if (test)
		output += "InValid node. ";
	test=0;
	test = m_validationFlag & invalidPhone;
	if (test)
		output += "Phone should be with 9 digits. ";
	test = 0;
	test = m_validationFlag & inValidSeparator;
	if (test)
		output += "Separator should be '.' or '-'. ";
	return output;
}
bool PhoneBookNote::lessThan(PhoneBookNote other,SortCriteria criteria)const
{
	switch (criteria)
	{
	case PhoneBookNote::Name:
		return lessThanNames(m_name, other.getName());
	case PhoneBookNote::Surname:
		return lessThanSurames(m_surname, other.getSurname());
	case PhoneBookNote::Phone:
		return lessThanPhones(m_phoneNumber, other.getPhone());
	default:
		return false;
	}
}