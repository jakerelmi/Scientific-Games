#include "Header.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

#define STARTYEAR 1900
#define ENDYEAR 2000

using namespace std;

//////////////////////////////////////////////////////////////////////////////////
// Given a list of people with their birth and end years(all between 1900 and 2000) 
// find the year with the most number of people alive.

// Holds an indiviudals info
struct sPerson
{
	unsigned int unBirthYear;
	unsigned int unEndYear;
};

void SaveOutput(unsigned int unTotalPeople, unsigned int unMaxYear, unsigned int unMaxPeople, Vector<sPerson> &vec)
{

	string sCaption[] = { "Total people: ", "\nYear with most amount of people alive: ", "\nTotal amount of people alive that year: " };
	ofstream save("Output.txt", ios_base::out);
	if (save.is_open() && save.good())
	{
		save << sCaption[0] << unTotalPeople << '\n' << '\n';
		for (unsigned int i = 0; i < vec.size(); ++i) // Saves original info from list of people with their birth years/end years
			save << vec[i].unBirthYear << '-' << vec[i].unEndYear << '\n';
		save << sCaption[1] << unMaxYear;
		save << sCaption[2] << unMaxPeople;
		save.close();
	}
}

void MaxPeopleAlive(Vector<sPerson> &vec)
{

	unsigned int unAlive = 0; // Keep track of how many people are alive in a particular year
	unsigned int unMaxPeople = 0; // Keep track of year with most people alive altogether
	unsigned int unMaxYear = 0;

	/*
	// This code works too but not very optimized

	for (unsigned int i = STARTYEAR; i < ENDYEAR; ++i)
	{
	unAlive = 0; // Resets count at the start of every year

	// Check every person in the vector to see if they were alive for that year
	for (unsigned int j = 0; j < vec.size(); ++j)
	{
	// Is this person alive??
	if (vec[j].unBirthYear <= i && vec[j].unEndYear >= i)
	unAlive++;
	}

	if (unAlive > unMaxPeople)
	{
	unMaxPeople = unAlive;
	unMaxYear = i;
	}
	}*/

	// Map keeps track of how many people are born/die on what year
	map <unsigned int, unsigned int> birthYears;
	map <unsigned int, unsigned int> endYears;
	for (unsigned int i = 0; i < vec.size(); ++i)
	{
		++birthYears[vec[i].unBirthYear];
		++endYears[vec[i].unEndYear];
	}

	for (unsigned int i = STARTYEAR; i < ENDYEAR; ++i)
	{
		if (birthYears[i] > 0)
			unAlive += birthYears[i];

		if (endYears[i] > 0) // Makes sure to get decrement unAlive count if someone dies
			unAlive -= endYears[i];

		if (unAlive > unMaxPeople)
		{
			unMaxPeople = unAlive;
			unMaxYear = i; 
		}
	}

	// Display the max amout of people alive and the year
	cout << "Year with the most amount of people alive: " << unMaxYear;
	cout << "\nTotal amount of people alive that year: " << unMaxPeople << "\n\n\n\n";

	// Save output to .txt file
	SaveOutput(vec.size(), unMaxYear, unMaxPeople, vec);

}

int main()
{
	unsigned int unNumOfPeople = 10;

	// test values (max of 10)
	int nBirthYear[] = { 1900, 1982, 1982, 1971, 1995, 1982, 1982, 2000, 1991, 1992 };
	int nEndYear[] = { 1950, 2000, 2000, 1990, 2000, 1990, 2000, 2000, 2000, 2000 };
	Vector<sPerson> vPeople; // Using the data set I created in Header.h

	for (unsigned int i = 0; i < unNumOfPeople; ++i)
	{
		sPerson cPerson;
		cPerson.unBirthYear = nBirthYear[i];
		cPerson.unEndYear = nEndYear[i];
		vPeople.pushback(cPerson); // Store this person into vector
	}

	MaxPeopleAlive(vPeople);

	system("Pause");
	return 0;
}