#ifndef MATCH_H
#define MATCH_H

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "player.h"

class Match
{
public:
    Player *A;
    Player *B;

   // match information
    std::string liveScore;

    bool ServeA;
    int AbilityA;
    int PointsA;
    int GamesA;
    int SetsA;
    int GamesSetA [5] = { 0, 0, 0, 0, 0 };
    int TiebreakPointsSetA [5] = { -1, -1, -1, -1, -1 };

    int AbilityB;
    int PointsB;
    int GamesB;
    int SetsB;
    int GamesSetB [5] = { 0, 0, 0, 0, 0 };
    int TiebreakPointsSetB [5] = { -1, -1, -1, -1, -1 };

    // constructor/destructor
    Match(Player *a, Player *b);

};

#endif
