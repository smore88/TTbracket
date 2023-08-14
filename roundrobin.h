#ifndef ROUNDROBIN_H
#define ROUNDROBIN_H

#include <string>
#include <vector>
#include <cmath>
#include <random>
#include <unordered_set>
#include <set>


using namespace std;

class RoundRobin {

public:

    RoundRobin(); // Constructor

    unordered_set<string> gatherPlayers(); // from a allplayers.txt file gather all the players and store them in a vector<string>
    unordered_set<string> players; // set to hold the players, this is the intial set we will pick 4 players that moves to round 1 and then remove those player from the set

    int getRound1RandomPlayerIndex(); // pick random player [0-16] that goes to round 2
    int getRound2RandomPlayerIndex(vector<string> players); // pick a random number from [0-15] for round 1

    vector<string> finalizeRound1Matches(); // pick 4 random players, and play them in 2 matches
    vector<string> printRound2Games(vector<string> players); // Each player plays one time there should be 8 matches

    vector<string> moveToRound2();

    void splitIntoConferences(vector<string> players);
    

private:

};

#endif // ROUNDROBIN_H