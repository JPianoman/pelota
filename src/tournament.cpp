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
    toss(match);
    if (Name.compare("GRANDSLAM") == 0 || Name.compare("ATP1000") == 0)
        int winningSets = 3;
    else if (Name.compare("ATP500") == 0 || Name.compare("ATP250") == 0)
        int winningSets = 2;

    while (match.PointsA < 50 && match.PointsB < 50)
    {
    /*    if (winnerOfRallyA(match) == true)
        {*/
            if (match.PointsA == 0 || match.PointsA == 15)
                match.PointsA += 15;
            else if (match.PointsA == 30)
                match.PointsA += 10;
            else if (match.PointsA == 40 && match.PointsB < 40)
            {
                match.GamesA++;
                match.PointsA = match.PointsB = 0;
            }
    }
}
/*
bool Tournament::winnerOfRallyA(Match match)  //TODO
{
    srand (time(NULL));
    int x = rand() % 18 + 1
    if ((x /**/ /**/ /*&& match.A.Serve == true) || (x /**/ /**/ /*&& match.A.Serve == false))
        return true;
    else
        return false;
}
*/
std::string Tournament::toss(Match match)
{
    std::string toss_string;
    srand (time(NULL));
    int toss_value = rand() % 4;
    switch (toss_value)
    {
        case 0:
            match.ServeA = true;
            toss_string = match.A.Name + " has won the toss and has chosen to serve";
            break;
        case 1:
            match.ServeA = false;
            toss_string = match.A.Name + " has won the toss and has chosen to receive";
            break;
        case 2:
            match.ServeA = false;
            toss_string = match.B.Name + " has won the toss and has chosen to serve";
            break;
        case 3:
            match.ServeA = true;
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
