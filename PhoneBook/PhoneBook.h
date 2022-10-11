#pragma once
#include "PhoneBookNote.h"
#include <vector>
class PhoneBook
{
public:
	enum SortingOrder
	{
		Ascending,
		Descending
	};
	PhoneBook(std::string filename);
	void printList();
	void printValidations();
	void sort(PhoneBookNote::SortCriteria criteris,SortingOrder order = SortingOrder::Ascending);
	bool isValid() { return m_isValid; };
private:
	std::vector<PhoneBookNote> m_List;
	bool m_isValid;
};
