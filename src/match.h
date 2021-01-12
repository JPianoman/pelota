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
    int GamesSetA [5] = {};
    int TiebreakPointsSetA [5] = {};

    int PointsB;
    int GamesB;
    int SetsB;
    int GamesSetB [5] = {};
    int TiebreakPointsSetB [5] = {};

    // constructor/destructor
    Match(Player a, Player b);

};

#endif
