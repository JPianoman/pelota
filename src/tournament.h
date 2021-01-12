#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "player.h"
#include "match.h"

class Tournament
{
public:
    std::string Name;
    std::vector<Player> Players;
    std::vector<Match> Matches;
    int WinningSets;

    // constructor/destructor
    Tournament(std::string name, std::vector<Player> players, int winning_sets);
    ~Tournament();

    void Init();
    Player getNextOpponent();
private:
    void calculateNextRound();
    void calculateMatch(Match match);
    bool winnerOfRallyA(Match match);
    void changeService(Match match);
    void saveGamesOfSet(Match match);
    void tieBreak(Match match);
    std::string toss(Match match);
};

#endif
