#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include <string>

class Player
{
public:
    // general
    std::string Forename;
    std::string Surname;
    std::string Nationality;
    std::string Birthday;
    int Height;
    int Weight;
    int Ranking;
    bool RightHanded;
    bool BothHanded;
    int AbilityClay;
    int AbilityHard;
    int AbilityGrass;
    int ServeAbility;
    int ReturnAbility;

    // constructor/destructor
    Player(std::string forename, std::string surname, std::string nationality, std::string birthday, int height, int weight, int ranking, bool right_handed, bool both_handed, int ability_clay, int ability_hard, int ability_grass, int serve_ability, int return_ability);

    void scored();
};

#endif
