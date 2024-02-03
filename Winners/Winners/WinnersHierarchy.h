#pragma once
#ifdef WINNERS_EXPORTS
#define WINNERS_API __declspec(dllexport)
#else
#define WINNERS_API __declspec(dllimport)
#endif //WINNERS_EXPORT

#include <string>
#include <vector>
#include <algorithm>
#include <map>


class WINNERS_API WinnersHierarchy
{
public:
	WinnersHierarchy();
	~WinnersHierarchy();

	void PopulateWinnersList(const std::string& name, int score);
	void ReadFile();
	void WriteInFile(const std::string& name, int score);


private:
	std::map <int, std::string> winnersList;

};

