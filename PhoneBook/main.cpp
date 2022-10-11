// PhoneBook.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "PhoneBookNote.h"
#include "PhoneBook.h"
int main()
{
	std::string fileName;
	std::cout << "Welcome to PhoneBook\nPlease enter File name:";
	std::cin >> fileName;
	PhoneBook book(fileName);
	if (!book.isValid())
		return 0;
	book.printList();
	std::cout << '\n';
	book.printValidations();
	std::string answer;
	PhoneBook::SortingOrder order;
	PhoneBookNote::SortCriteria criteria;
	std::cout << "Do you want to sort?\n(Y/N)\n";
	std::cin >> answer;
	if (answer == "n" || answer == "N")
		return 0;
	START_SORT:
	std::cout << "What criteria do you want to be sorted by\nname,surname,phone\nor type exit to exit\n";
	while(true)
	{ 
		std::cin >> answer;
		if (answer.compare("name") == 0)
		{
			criteria = PhoneBookNote::Name;
			break;
		}
		else if (answer.compare("surname") == 0)
		{
			criteria = PhoneBookNote::Surname;
			break;
		}
		else if (answer.compare("phone") == 0)
		{
			criteria = PhoneBookNote::Phone;
			break;
		}
		else if (answer.compare("exit") == 0)
			return 0;
		else
			std::cout << "please type one of 'name', 'surname' , 'phone' or 'exit'  without quotes \n";
	}
	std::cout << "Select order 1.Ascending 2.Descending\n";
	while (true)
	{
		std::cin >> answer;
		if (answer.compare("1") == 0)
		{
			order = PhoneBook::Ascending;
			break;
		}
		else if (answer.compare("2") == 0)
		{
			order = PhoneBook::Descending;
			break;
		}
		else if (answer.compare("exit") == 0)
			return 0;
		else
			std::cout << "please type one of '1', '2' or 'exit'  without quotes \n";
	}
	book.sort(criteria, order);
	book.printList();
	std::cout << "Doyou want to sort Again?";
	std::cin >> answer;
	if (answer == "n" || answer == "N")
		return 0;
	goto START_SORT;
	return 0;
}