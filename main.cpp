#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <set>

#include "roundrobin.h"

using namespace std;

// TESTCASES

int main() {
    // create the RounRobin object
    RoundRobin rb;

    // Test to make sure all the players are printed(should be 18 names no repeat)
    unordered_set<string> players = rb.gatherPlayers();
    // for(string player : players) {
    //     cout << player << " ";
    // }
    // cout << "\n";
    // cout << "\n";

    // Test to see who is in round1 should be 2 matches and 4 names, on top of that print the vector when those names are removed those will move to round 2 should be 14 names
    cout << "\n";
    vector<string> round2Matches = rb.finalizeRound1Matches();
    // cout << "\n";
    // for(string player : round2Matches) {
    //     cout << player << " ";
    // }
    cout << "\n";

    // Test to make sure that we have 8 matches. and that each player plays one time in round 2;
    cout << "ROUND 2 MATCHES(all NULLS will be replaced with round1 winners)" << "\n";
    vector<string> allRound2Matches = rb.printRound2Games(round2Matches);
    // for(string match : allRound2Matches) {
    //     cout << match << "\n";
    // }

    // Now split the round2 matches into EAST & WEST Conference
    rb.splitIntoConferences(allRound2Matches);



    
    
    
    // Test to check if the matches are printed correctly
    // rb.printRRGames(players);

    return 0;
}