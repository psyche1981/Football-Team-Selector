#include <iostream>
#include <fstream>
#include <string>

class InfoLoader
{
public:
	InfoLoader(const std::string& TeamsFileName, const std::string& PlayersFileName)
	{
		numTeams = 0;
		numPlayers = 0;

		std::ifstream teams;
		teams.open(TeamsFileName);
		if (teams.fail())
		{
			std::cerr << "File: " << TeamsFileName.c_str() << " does not exist" << std::endl;
			system("PAUSE");
		}

		std::ifstream players;
		players.open(PlayersFileName);
		if (players.fail())
		{
			std::cerr << "File: " << PlayersFileName.c_str() << " does not exist" << std::endl;
			system("PAUSE");
		}

		//TODO read in the data from each file
		std::string line;
		while (std::getline(teams, line))
		{
			numTeams++;
		}

		while (std::getline(players, line))
		{
			numPlayers++;
		}
		//TODO choose the best container for the teams and the players

	}


	int numTeams;
	int numPlayers;
};


int main(int argc, char** argv)
{
	std::cout << "Please make sure there are two .txt files int he same directory as the executable. "<<
		std::endl << "One containing Teams and the other containing the names of the people in the round." << std::endl <<
	"Enter the file name (including extension) of the file containing the list of teams" << std::endl;

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

	std::cin >> s;
	return 0;
}
