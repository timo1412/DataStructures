#include "Searcher.h"

#include <iostream>

void Searcher::startsWithString(string startString)
{
	int lengthStartString = startString.size();

	for (int i = 0 ; i < this->kraje.size(); i++)
	{
		string startStringCompare = this->kraje.at(i).getShortTitle().substr(0, lengthStartString);
		if (startStringCompare == startString)
		{
			this->result.push_back(this->kraje.at(i));
		}
	}
	cout << "============================UZEMNE CELKY KRAJOV========================================" << endl;
	this->printResult();
	this->result.clear();

	cout << "============================UZEMNE CELKY OKRESOV========================================" << endl;
	for (int i = 0; i < this->okresy.size(); i++)
	{
		string startStringCompare = this->okresy.at(i).getShortTitle().substr(0, lengthStartString);
		if (startStringCompare == startString)
		{
			this->result.push_back(this->okresy.at(i));
		}
	}
	this->printResult();
	this->result.clear();

	cout << "============================UZEMNE CELKY OBCI========================================" << endl;
	for (int i = 0; i < this->obce.size(); i++)
	{
		string startStringCompare = this->obce.at(i).getShortTitle().substr(0, lengthStartString);
		if (startStringCompare == startString)
		{
			this->result.push_back(this->obce.at(i));
		}
	}
	this->printResult();
	this->result.clear();
}

void Searcher::containsString(string containsString)
{
}

void Searcher::printResult()
{
	for (int i = 0; i < this->result.size();i++)
	{
		cout<< this->result.at(i).getNumber()<< " " << this->result.at(i).getCode()<< " " << this->result.at(i).getTitle() << " " << this->result.at(i).getMedTitle() << " " << this->result.at(i).getShortTitle() << " " << this->result.at(i).getNote() << endl;
	}
}
