#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include <string>

class Player
{
public:
    // general
    std::string Name;
    int Age;
    int Height;
    int Ranking;
    bool RightHanded;
    int Ability;
    int RankingPoints;

    // match information
    bool InMatch;
    bool Serve;
    int Points;
    int Games;
    int Sets;
    int GamesSet1;
    int GamesSet2;
    int GamesSet3;
    int GamesSet4;
    int GamesSet5;

    // constructor/destructor
    Player(std::string name, int age, int height, int ranking, bool right_handed, int ability, int ranking_points);

    void scored();
};

#endif
