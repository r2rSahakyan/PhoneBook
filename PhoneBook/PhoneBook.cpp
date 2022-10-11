#include "PhoneBook.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
PhoneBook::PhoneBook(std::string filename)
{
	std::ifstream fileStream; 
	fileStream.open(filename);
	if (fileStream.is_open())
	{

		std::string buffer;
		while (fileStream)
		{
			std::getline(fileStream, buffer);
			if (buffer.empty())
				break;
			std::vector<std::string> separated;
			size_t lastPos{ 0 };
			std::string token;
			while ((lastPos = buffer.find(' ')) != std::string::npos) {
				token = buffer.substr(0, lastPos);
				separated.push_back(token);
				buffer.erase(0, lastPos + 1);
			}
			separated.push_back(buffer);
			if (separated.size() == 4)
			{
				PhoneBookNote note{ separated.at(0), separated.at(1), separated.at(2), separated.at(3) };
				m_List.push_back(note);
			}
			else if (separated.size() == 3)
			{
				PhoneBookNote note{ separated.at(0), "", separated.at(1), separated.at(2) };
				m_List.push_back(note);
			}
			else
			{
				PhoneBookNote note("{name}","{surname}","{separator}","{phoneNumber}");
				m_List.push_back(note);
			}
			buffer.clear();
		}
		m_isValid = true;
	}
	else {
		std::cout << "Couldn't open file\n";
		m_isValid = false;
	}
}
void PhoneBook::printList()
{
	std::cout << "File Structure" << '\n';
	for (size_t i = 0; i < m_List.size(); i++)
	{
		std::cout << m_List.at(i).stringToPrint()<<'\n';
	}
}
void PhoneBook::printValidations()
{
	std::cout << "Validations:" << '\n';
	for (size_t i = 0; i < m_List.size(); i++)
	{
		if(!m_List.at(i).isValid())
			std::cout << "line "<<i+1<<" " << m_List.at(i).validStringToPrint() << '\n';
	}
}
void PhoneBook::sort(PhoneBookNote::SortCriteria criteria,SortingOrder order)
{
	std::sort(m_List.begin(), m_List.end(), [criteria](PhoneBookNote left, PhoneBookNote right) { return left.lessThan(right, criteria); });
	if (order == Descending)
		std::reverse(m_List.begin(), m_List.end());
}