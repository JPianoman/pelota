#ifndef MATCH_H
#define MATCH_H

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "player.h"

class Match
{
public:
    Player A;
    Player B;

   // match information
    bool ServeA;
    int PointsA;
    int GamesA;
    int SetsA;
    int GamesSet1A;
    int GamesSet2A;
    int GamesSet3A;
    int GamesSet4A;
    int GamesSet5A;

    int PointsB;
    int GamesB;
    int SetsB;
    int GamesSet1B;
    int GamesSet2B;
    int GamesSet3B;
    int GamesSet4B;
    int GamesSet5B;

    // constructor/destructor
    Match(Player a, Player b);

};

#endif
