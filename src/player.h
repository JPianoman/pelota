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
    int Weight;
    int Ranking;
    bool RightHanded;
    bool BothHanded;
    int Ability;
    int RankingPoints;

 
    // constructor/destructor
    Player(std::string name, int age, int height, int weight, int ranking, bool right_handed, bool both_handed, int ability, int ranking_points);

    void scored();
};

#endif
