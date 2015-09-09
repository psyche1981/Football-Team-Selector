#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <random>
#include <vector>
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
		data.open("debuggery/DebugInfo.txt");

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
		for (auto& it = results.begin(); it != results.end(); it++)
		{						
			data << it->first << ": " << it->second << "\n";
		}
	}
	
private:
	std::string generateTeam()
	{
		data << "***" << "Team generated # " << genTeamCount << " ***\n";
		std::string team = "";
		static std::mt19937 randomEngine((unsigned int)time(nullptr));
		static std::uniform_int_distribution<int> roll(1, numTeams);
		bool picked = false;
		int teamPick;
		while (!picked)
		{
			teamPick = roll(randomEngine);
			data << "roll: " << teamPick << "\n";
			picked = true;
			for (auto& it = prevPicks.begin(), end = prevPicks.end(); it != end; it++)
			{
				if (*it == teamPick)
				{
					picked = false;
					continue;
				}
			}
		}
		prevPicks.push_back(teamPick);
		team = teamsMap[teamPick];
		data << "Team: " << team << "\n";
		teamsMap[teamPick].erase();
		genTeamCount++;
		data << "\n";
		return team;
	}

	int numTeams;
	int numPlayers;
	std::map<std::string, std::string> results;
	std::map<int, std::string> teamsMap;
	std::vector<int> prevPicks;
	std::ofstream data;
	int genTeamCount = 1;
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
