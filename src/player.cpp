#include "player.h"

Player::Player(std::string forename, std::string surname, std::string nationality, std::string birthday, int height, int weight, int ranking, bool right_handed, bool both_handed, int ability_clay, int ability_hard, int ability_grass, int serve_ability, int return_ability)
: Forename(forename), Surname(surname), Nationality(nationality), Birthday(birthday), Height(height), Weight(weight), Ranking(ranking), RightHanded(right_handed), BothHanded(both_handed), AbilityClay(ability_clay), AbilityHard(ability_hard), AbilityGrass(ability_grass), ServeAbility(serve_ability), ReturnAbility(return_ability)
{

}
