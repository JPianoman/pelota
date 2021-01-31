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
    std::vector<Player*> Players;
    std::vector<Match*> Matches;
    int WinningSets;
    std::string Surface;
    bool OwnMatch = false;

    // constructor/destructor
    Tournament(std::string name, std::vector<Player*> players, int winning_sets, std::string surface);
    ~Tournament();

    void Init();
    Player getNextOpponent(Match *match);
private:
    int sortPlayersByRanking(Match *match);
    void ability(Match *match);
    void calculateNextRound();
    void calculateMatch(Match *match);
    bool winnerOfRallyA(Match *match);
    void changeService(Match *match);
    void saveGamesOfSet(Match *match);
    void tieBreak(Match *match);
    std::string printScore(Match *match);
    std::string printResult(Match *match);
    std::string toss(Match *match);
};

#endif
