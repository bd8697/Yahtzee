#include "WinnersHierarchy.h"
#include <fstream>
#include <iostream>

std::ofstream fout;
std::ifstream fin;

WinnersHierarchy::WinnersHierarchy()
{
	ReadFile();
}

WinnersHierarchy::~WinnersHierarchy()
{
}

void WinnersHierarchy::PopulateWinnersList(const std::string& name, int score)
{
	winnersList[score] = name;
	WriteInFile(name,score);
}

void WinnersHierarchy::ReadFile()
{
	std::string name;
	int score;
	fin.open("Hierarchy.txt");
	int count = 0;
	if(fin.is_open()) {
		while (count <= 10)
		{
			fin >> name;
			fin >> score;
			winnersList[score] = name;
			count++;
		}
		fin.close();
	}
	
}

void WinnersHierarchy::WriteInFile(const std::string& name, int score)
{
	fout.open("Hierarchy.txt", std::ios::app);
	if (fout.is_open() ) {
		fout << name;
		fout << " ";
		fout << score << "\n";
		fout.close();
	}
	
	
}
