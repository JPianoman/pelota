#include "tournament.h"

#include <time.h>
#include <stdlib.h> 
#include <iostream>
#include <string>

Tournament::Tournament(std::string name, std::vector<Player> players)
: Name(name), Players(players)
{
    Init();
}

void Tournament::Init()
{
    // Init match plan

    // create new match
    Match *m = new Match(Players[0], Players[1]);
    // add match to list
    Matches.push_back(*m);
    
    m = new Match(Players[2], Players[3]);
    Matches.push_back(*m);

    calculateNextRound();
}

// should calculate all results of the next round
void Tournament::calculateNextRound()
{
    /*for (int i = 0; i < Matches.length(); i++)
    {
        if (ownMatch == true)
            break;
        calculateMatch(Matches[i]);
    }*/
        calculateMatch(Matches[0]);
}

// should calculate result of the next match
void Tournament::calculateMatch(Match match)
{
//    toss(match);
    std::cout << toss(match) << std::endl;
//    points();
}

std::string Tournament::toss(Match match)
{
    std::string toss_string;
    srand (time(NULL));
    int toss_value = rand() % 4;
    switch (toss_value)
    {
        case 0:
            match.A.Serve = true;
            toss_string = match.A.Name + " has won the toss and has chosen to serve";
            break;
        case 1:
            match.A.Serve = false;
            toss_string = match.A.Name + " has won the toss and has chosen to receive";
            break;
        case 2:
            match.B.Serve = false;
            toss_string = match.B.Name + " has won the toss and has chosen to serve";
            break;
        case 3:
            match.B.Serve = true;
            toss_string = match.B.Name + " has won the toss and has chosen to receive";
            break;
    }
    return toss_string;
}

// should return the Opponent for the next match
Player Tournament::getNextOpponent()
{
    //TODO
}
























