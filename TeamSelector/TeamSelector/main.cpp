#include <iostream>
#include <fstream>

class InfoLoader
{
public:
	InfoLoader(const std::string& TeamsFileName, const std::string& PlayersFileName)
	{
		numTeams = 0;
		numPlayers = 0;

		std::ifstream teams(TeamsFileName);
		if (teams.fail())
		{
			std::cerr << "File: " << TeamsFileName.c_str() << " does not exist" << std::endl;
			std::exit(-1);
		}

		std::ifstream players(PlayersFileName);
		if (players.fail())
		{
			std::cerr << "File: " << PlayersFileName.c_str() << " does not exist" << std::endl;
			std::exit(-1);
		}


		//TODO read in the data from each file
		//TODO choose the best container for the teams and the players

	}


	int numTeams;
	int numPlayers;
};


int main(int argc, char** argv)
{
	std::cout << "Working" << std::endl;
	std::cout << "Please enter the file name (including extension) of the file containing the list of teams" << std::endl;

	char* s = new char[100];
	std::cin >> s;
	std::string teamFileName = s;
	
	std::cout << "Please enter the file name (including extension) of" <<
		" the file containing the list of Sports Blackjack players" << std::endl;
	std::cin >> s;
	std::string playersFileName = s;

	InfoLoader info(teamFileName, playersFileName);
	std::cout << "Number of Teams = " << info.numTeams <<
		", Number of Players = " << info.numPlayers << std::endl;

	return 0;
}
