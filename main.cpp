//by szymonna3 @ github

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct Player {
    int index;
    char sign;
    int wins = 0;
    int draws = 0;
    int losses = 0;
    int points = 0;
};

void readPlayersFile(std::vector<Player>& players) {
    std::ifstream file("players.txt");
    if (file.is_open()) {
        Player player;
        while (file >> player.index >> player.sign) {
            players.push_back(player);
        }
        file.close();
    } else {
        std::cout << "Unable to open players file." << std::endl;
    }
}

void readMatchResults(std::vector<Player>& players) {
    std::ifstream file("tictactoe.txt");
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            char result = line[0];
            bool allEqual = true;
            for (char c : line) {
                if (c != result && c != '.') {
                    allEqual = false;
                    break;
                }
            }
            if (!allEqual && result != '.') {
                char opponent = '.';
                for (char c : line) {
                    if (c != result && c != '.') {
                        opponent = c;
                        break;
                    }
                }
                for (Player& player : players) {
                    if (player.sign == result) {
                        player.points += 3;
                        player.wins++;
                    } else if (player.sign == opponent) {
                        player.losses++;
                    }
                }
            } else if (allEqual && result != '.') {
                for (Player& player : players) {
                    if (player.sign == result) {
                        player.points += 1;
                        player.draws++;
                    }
                }
            }
        }
        file.close();
    } else {
        std::cout << "Unable to open match results file." << std::endl;
    }
}


void showTable(std::vector<Player>& players) {
    std::sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
        return a.points > b.points;
    });

    std::cout << "Id\tSign\tWins\tDraws\tLosses\tPoints" << std::endl;
    for (const auto& player : players) {
        std::cout << player.index << "\t" << player.sign << "\t"
                  << player.wins << "\t" << player.draws << "\t"
                  << player.losses << "\t" << player.points << std::endl;
    }
}

void showResults() {
    std::ifstream file("tictactoe.txt");
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    } else {
        std::cout << "Unable to open match results file." << std::endl;
    }
}

void showPlayerStats(const std::vector<Player>& players) {
    int index;
    std::cout << "Enter player index: ";
    std::cin >> index;

    while (std::cin.fail()) {
        std::cout << "Invalid input. Please enter a number: ";
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> index;
    }

    auto it = std::find_if(players.begin(), players.end(),
                           [index](const Player& player) {
                               return player.index == index;
                           });
    if (it != players.end()) {
        std::cout << "Player stats for index " << index << ":" << std::endl;
        std::cout << "Sign: " << it->sign << std::endl;
        std::cout << "Wins: " << it->wins << std::endl;
        std::cout << "Draws: " << it->draws << std::endl;
        std::cout << "Losses: " << it->losses << std::endl;
        std::cout << "Points: " << it->points << std::endl;
    } else {
        std::cout << "Player with index " << index << " not found" << std::endl;
    }
}

int main() {
    std::vector<Player> players;

    readPlayersFile(players);
    readMatchResults(players);

    int choice;
    do {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Show table" << std::endl;
        std::cout << "2. Show results" << std::endl;
        std::cout << "3. Show player stats" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        while (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number: ";
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cin >> choice;
        }

        switch (choice) {
            case 1:
                showTable(players);
                break;
            case 2:
                showResults();
                break;
            case 3:
                showPlayerStats(players);
                break;
            case 4:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter a number from 1 to 4." << std::endl;
        }
    } while (choice != 4);

    return 0;
}
