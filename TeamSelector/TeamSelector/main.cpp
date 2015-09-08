#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <random>
#include <ctime>

class InfoLoader
{
public:
	InfoLoader()
	{}

	int init(const std::string& TeamsFileName, const std::string& PlayersFileName)
	{
		numTeams = 0;
		numPlayers = 0;

		std::ifstream teams;
		teams.open(TeamsFileName);
		if (teams.fail())
		{
			std::cerr << "File: " << TeamsFileName.c_str() << " does not exist" << std::endl;
			return -1;
		}

		std::ifstream players;
		players.open(PlayersFileName);
		if (players.fail())
		{
			std::cerr << "File: " << PlayersFileName.c_str() << " does not exist" << std::endl;
			return -1;
		}

		std::string line;
		while (std::getline(teams, line))
		{
			numTeams++;
			teamsMap[numTeams] = line;
		}

		while (std::getline(players, line))
		{
			results[line] = generateTeam();
			numPlayers++;
		}

		teams.close();
		players.close();
		return 0;
	}

	void saveFile()
	{		
		data.open("Results.txt");
		for (auto& it = results.begin(); it != results.end(); it++)
		{						
			data << it->first << ": " << it->second << "\n";
		}
		
		data.close();
	}
	
private:
	std::string generateTeam()
	{
		std::string team = "";
		static std::mt19937 randomEngine((unsigned int)time(nullptr));
		static std::uniform_int_distribution<int> roll(1, numTeams);
		int teamPick = roll(randomEngine);
		numTeams--;
		team = teamsMap[teamPick];
		teamsMap[teamPick].erase();
		return team;
	}

	int numTeams;
	int numPlayers;
	std::map<std::string, std::string> results;
	std::map<int, std::string> teamsMap;
	std::ofstream data;
};

class Debuggery
{
public:

private:
};
	


int main(int argc, char** argv)
{
	InfoLoader info;
	if(info.init("Teams.txt", "Players.txt") == 0)
		info.saveFile();

	std::cout << "* Generating a completely fair set of results......            *" << std::endl;
	std::cin.get();
	return 0;
}
