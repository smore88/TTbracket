#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <string>
#include <random>
#include <unordered_set>
#include <set>


#include "roundrobin.h"

using namespace std;

static const int COUNT = 1;

RoundRobin::RoundRobin() {
    // Default Constructor
}

unordered_set<string> RoundRobin::gatherPlayers() {
    // Puts the files contents in a stream playersFile;
    ifstream playersFile;
    playersFile.open("allplayers.txt");

    // Declare a string that holds the contents that we read from the stream
    string playerName;

    // Now read from the file
    if(playersFile.is_open()) {
        while(playersFile.good()) { // once we reach EOF this evaluates false exits loop
            playersFile >> playerName;
            players.insert(playerName);   
        }
    }
    return players;
}

int RoundRobin::getRound1RandomPlayerIndex() {
    // Initialize a random number generator
    random_device rd;
    mt19937 gen(rd());

    // Define the range for random numbers
    int minNumber = 0;
    int maxNumber = 17;

    // Create a uniform distribution
    std::uniform_int_distribution<int> distribution(minNumber, maxNumber);

    // Generate a random number
    int randomNumber = distribution(gen);

    return randomNumber;
}

vector<string> RoundRobin::finalizeRound1Matches() { // take the players set randomly get 1 player and move that player to round 2
    // convert that set we had to a vector since we want to access indexes
    vector<string> allPlayers;
    for(string player : players) {
        allPlayers.push_back(player);
    }

    unordered_map<string, int> round1Players;
    for(string player : allPlayers) {
        round1Players[player] = 0;
    }

    int numOfMatches = 2; // should be 2, test this
    int maxAttempts = 100;
    vector<string> pushedRound1Matches;
    for(int match = 1; match <= numOfMatches; match++) { // built so each player plays 1 game max
        
        // get the 1st player
        string player1Name;
        bool gotPlayer1 = false;
        int attempts1 = 0;
        while(!gotPlayer1 && attempts1 < maxAttempts) {
            int player1Index = getRound1RandomPlayerIndex(); // grab random index
            player1Name = allPlayers[player1Index]; // grab the random player name from the random index
            if(round1Players[player1Name] < 1) { // check if the player is in the map, if it is keep going, if not you gotPlayer1
                players.erase(player1Name);
                gotPlayer1 = true;
            }
            round1Players[player1Name]++;
            attempts1++;
        }

        // get the 2nd player
        string player2Name;
        bool gotPlayer2 = false;
        int attempts2 = 0;
        while(!gotPlayer2 && attempts2 < maxAttempts) {
            int player2Index = getRound1RandomPlayerIndex(); // grab random index
            player2Name = allPlayers[player2Index]; // grab the random player name from the random index
            if(round1Players[player2Name] < 1) { // check if the player is in the map, if it is keep going, if not you gotPlayer2
                players.erase(player2Name);
                gotPlayer2 = true;
            }
            round1Players[player2Name]++;
            attempts2++;
        }
        pushedRound1Matches.push_back("Match " + to_string(match) + " : " + player1Name + " vs " + player2Name);
    }

    cout << "ROUND 1 MATCHES(winners here will move to a bracket spot in round2)" << "\n";
    for(string match : pushedRound1Matches) {
        cout << match << "\n";
    }

    vector<string> round2Players;
    for(string player : players) {
        round2Players.push_back(player);
    }

    return round2Players;
}

int RoundRobin::getRound2RandomPlayerIndex(vector<string> players) {
    // Initialize a random number generator
    random_device rd;
    mt19937 gen(rd());

    // Define the range for random numbers
    int minNumber = 0;
    int maxNumber = players.size() - 1; // check this should be 13, test it, [0, 13]

    // Create a uniform distribution
    std::uniform_int_distribution<int> distribution(minNumber, maxNumber);

    // Generate a random number
    int randomNumber = distribution(gen);

    return randomNumber;
}

vector<string> RoundRobin::printRound2Games(vector<string> round2PlayerList) {

    unordered_map<string, int> visitedRound2Players;
    for(string player : round2PlayerList) {
        visitedRound2Players[player] = 0;
    }

    int numOfMatches = 6;
    int maxAttempts = 100;
    vector<string> printedRound2Matches;
    for(int match = 1; match <= numOfMatches; match++) { // built so each player plays 1 game max

        // get the first player
        string player1Name;
        bool gotPlayer1 = false;
        int attempts1 = 0;
        while(!gotPlayer1 && attempts1 < maxAttempts) {
            int player1Index = getRound2RandomPlayerIndex(round2PlayerList); // grab random index
            player1Name = round2PlayerList[player1Index]; // grab the random player name from the random index
            if(visitedRound2Players[player1Name] < 1) { // check if the player is in the set, if it is keep going, if not you gotPlayer1
                gotPlayer1 = true;
            }
            visitedRound2Players[player1Name]++; 
            attempts1++;
        }

        // get the 2nd player
        string player2Name;
        bool gotPlayer2 = false;
        int attempts2 = 0;
        while(!gotPlayer2 && attempts2 < maxAttempts) {
            int player2Index = getRound2RandomPlayerIndex(round2PlayerList); // grab random index
            player2Name = round2PlayerList[player2Index]; // grab the random player name from the random index
            if(visitedRound2Players[player2Name] < 1) { // check if the player is in the set, if it is keep going, if not you gotPlayer1
                gotPlayer2 = true;
            }
            visitedRound2Players[player2Name]++;  
            attempts2++;
        }

        printedRound2Matches.push_back("Match " + to_string(match) + " : " + player1Name + " vs " + player2Name);

    }

    int match = 7;
    for(auto pair : visitedRound2Players) {
        if(pair.second == 0) {
            printedRound2Matches.push_back("Match " + to_string(match) + " : " + pair.first + " vs " + "NULL");
            match++;
        }
    }

    return printedRound2Matches;

}

void RoundRobin::splitIntoConferences(vector<string> players) {
    vector<string> east;
    east.push_back(players[6]);
    for(int i = 0; i < 3; i++) {
        east.push_back(players[i]);
    }

    vector<string> west;
    west.push_back(players[7]);
    for(int i = 3; i < 6; i++) {
        west.push_back(players[i]);
    }

    cout << "EAST DIVISION" << "\n";
    for(string match : east) {
        cout << match << "\n";
    }
    cout << "\n";

    cout << "WEST DIVISION" << "\n";
    for(string match : west) {
        cout << match << "\n";
    }
    cout << "\n";
}