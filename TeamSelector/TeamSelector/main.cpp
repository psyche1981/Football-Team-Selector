#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <random>
#include <ctime>
#include <vector>

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
		std::ofstream data;
		data.open("Results.txt");
		for (auto& it = results.begin(); it != results.end(); it++)
		{			
			data << it->first << ": " << it->second << "\n";
		}
		data.close();

		for (auto& it = prevPicks.begin(), end = prevPicks.end(); it != end; it++)
		{			
			std::cout << *it << std::endl;
		}
	}
	
private:
	std::string generateTeam()
	{
		std::string team = "";
		static std::mt19937 randomEngine((unsigned int)time(nullptr));
		static std::uniform_int_distribution<int> roll(1, numTeams);		
		int teamPick = roll(randomEngine);

		bool picked = false;
		for (auto& it = prevPicks.begin(), end = prevPicks.end(); it != end; it++)
		{
			if (*it == teamPick)
				picked = true;
		}
		if (!picked)
		{
			prevPicks.push_back(teamPick);
			team = teamsMap[teamPick];
			teamsMap[teamPick].erase();
		}
		else
		{
			generateTeam();
		}		
		return team;
	}

	int numTeams;
	int numPlayers;
	std::map<std::string, std::string> results;
	std::map<int, std::string> teamsMap;
	std::vector<int> prevPicks;
};
	


int main(int argc, char** argv)
{
	char* s = new char[100];

	std::cout << "****************************************************************" << std::endl;
	std::cout << "*                   Random Football Team Selector              *" << std::endl;
	std::cout << "*                                                              *" << std::endl;
	std::cout << "* Please make sure there are two .txt files in the same        *" << std::endl;
	std::cout << "* directory as the executable, one containing sports teams     *" << std::endl; 
	std::cout << "* and the other containing the names of people in the round.   *" << std::endl;
	std::cout << "*                                                              *" << std::endl;
	std::cout << "*                     ---------------------------              *" << std::endl;
	std::cout << "*           Enter the file name of the list of teams           *" << std::endl;
	std::cout << "*          ";
	std::cin >> s;
	std::string teamFileName = s;
	std::cout << std::endl;
	std::cout << "*                     ---------------------------              *" << std::endl;
	std::cout << "* Enter the file name of the list of Sports Blackjack players  *" << std::endl;
	std::cout << "*          ";
	std::cin >> s;
	std::string playersFileName = s;
	std::cout << std::endl;
	InfoLoader info;
	if(info.init(teamFileName, playersFileName) == 0)
		info.saveFile();

	std::cout << "* Generating a completely fair set of results......            *" << std::endl;
	std::cin >> s;
	delete[] s;
	return 0;
}
