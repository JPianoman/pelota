#include "tournament.h"

#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <string>

Tournament::Tournament(std::string name, std::vector<Player> players, int winning_sets)
: Name(name), Players(players), WinningSets(winning_sets)
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

// should return the Opponent for the next match
Player Tournament::getNextOpponent()
{
    //TODO
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
        calculateMatch(Matches[1]);
}

// should calculate result of the next match
void Tournament::calculateMatch(Match match)
{
    toss(match);
    match.PointsA = match.GamesA = match.SetsA = match.PointsB = match.GamesB = match.SetsB = 0;
//TODO string score
    while (match.PointsA < 50 && match.PointsB < 50)
    {
        if (winnerOfRallyA(match) == true)
        {
            if (match.PointsA == 0 || match.PointsA == 15)
                match.PointsA += 15;
            else if (match.PointsA == 30)
                match.PointsA += 10;
            else if (match.PointsA == 40 && match.PointsB < 40)
            {
                match.GamesA++;
                match.PointsA = match.PointsB = 0;
                changeService(match);
            }
        }
        else
        {
            if (match.PointsB == 0 || match.PointsB == 15)
                match.PointsB += 15;
            else if (match.PointsB == 30)
                match.PointsB += 10;
            else if (match.PointsB == 40 && match.PointsA < 40)
            {
                match.GamesB++;
                match.PointsB = match.PointsA = 0;
                changeService(match);
            }
        }
//TODO string score
        if (match.PointsA == match.PointsB == 40)
        {
            if (winnerOfRallyA(match) == true)
                match.PointsA += 5;
            else
                match.PointsB += 5;
//TODO string score
        }

        if (match.PointsA == 45 || match.PointsB == 45)
        {
            if (winnerOfRallyA(match) == true)
            {
                if (match.PointsA == 45)
                {
                    match.GamesA++;
                    match.PointsA = match.PointsB = 0;
                    changeService(match);
//TODO string score
                }
                else
                    match.PointsA = match.PointsB = 40;
            }
            else
            {
                if (match.PointsA == 45)
                    match.PointsA = match.PointsB = 40;
                else
                {
                    match.GamesB++;
                    match.PointsA = match.PointsB = 0;
                    changeService(match);
//TODO string score
                }
            }
        }
        if (match.GamesA >= 6 && match.GamesB < 6 && (match.GamesA - match.GamesB >= 2))
        {
            match.SetsA++;
            saveGamesOfSet(match);
            match.PointsA = match.PointsB = match.GamesA = match.GamesB = 0;
        }
        else if (match.GamesB >= 6 && match.GamesA < 6 && match.GamesB - match.GamesA >= 2)
        {
            match.SetsB++,
            saveGamesOfSet(match);
            match.PointsA = match.PointsB = match.GamesA = match.GamesB = 0;
        }
        else if (match.GamesA == match.GamesB == 6)
            tieBreak(match);

        if (match.SetsA == WinningSets)
        {
            std::cout << match.A.Name + " has won!" << std::endl;
            match.PointsA = 60;
        }
    }
exit (EXIT_SUCCESS);
}

bool Tournament::winnerOfRallyA(Match match)  //TODO should return whether Player A wins the rally (t/f)
{
//    srand (time(NULL));
  //  int x = rand() % /*//*/ + 1
    //if ((x /**/ /**/ && match.A.Serve == true) || (x /**/ /**/ && match.A.Serve == false))
        return true;
    //else
      //  return false;
}

void Tournament::saveGamesOfSet(Match match)
{
    switch(match.SetsA + match.SetsB)
    {
        case 1:
            match.GamesSetA [1] = match.GamesA;
            match.GamesSetB [1] = match.GamesB;
            break;
        case 2:
            match.GamesSetA [2] = match.GamesA;
            match.GamesSetB [2] = match.GamesB;
            break;
        case 3:
            match.GamesSetA [3] = match.GamesA;
            match.GamesSetB [3] = match.GamesB;
            break;
    }
    if (WinningSets == 5)
    {
        switch(match.SetsA + match.SetsB)
        {
            case 4:
                match.GamesSetA [4] = match.GamesA;
                match.GamesSetB [4] = match.GamesB;
                break;
            case 5:
                match.GamesSetA [5] = match.GamesA;
                match.GamesSetB [5] = match.GamesB;
                break;
        }
    }
}

void Tournament::changeService(Match match)
{
    if (match.ServeA == true)
        match.ServeA = false;
    else
        match.ServeA = true;
}

void Tournament::tieBreak(Match match)
{
    while (match.GamesA == match.GamesB == 6)
    {
        /**if (winnerOfRallyA == true)
            match.PointsA++;
        else
            match.PointsB++;*/
//TODO string score
        if ((match.PointsA + match.PointsB) % 2 == 1)
            changeService(match);

        if ((match.PointsA - match.PointsB >= 2 && match.PointsA >= 7) || (match.PointsB - match.PointsA >= 2 && match.PointsB >= 7))
        {
            if (match.PointsA > match.PointsB)
            {
                match.GamesA++;
                match.SetsA++;
            }
            else
            {
                match.GamesB++;
                match.SetsB++;
            }
            changeService(match);
            saveGamesOfSet(match);
            switch (match.SetsA + match.SetsB)
            {
                case 1:
                    match.TiebreakPointsSetA [1] = match.PointsA;
                    match.TiebreakPointsSetB [1] = match.PointsB;
                    break;
                case 2:
                    match.TiebreakPointsSetA [2] = match.PointsA;
                    match.TiebreakPointsSetB [2] = match.PointsB;
                    break;
                case 3:
                    match.TiebreakPointsSetA [3] = match.PointsA;
                    match.TiebreakPointsSetB [3] = match.PointsB;
                    break;
            }
            if (WinningSets == 5)
            {
                switch (match.SetsA + match.SetsB)
                {
                    case 4:
                        match.TiebreakPointsSetA [4] = match.PointsA;
                        match.TiebreakPointsSetB [4] = match.PointsB;
                        break;
                    case 5:
                        match.TiebreakPointsSetA [5] = match.PointsA;
                        match.TiebreakPointsSetB [5] = match.PointsB;
                        break;
                }
            }
            match.PointsA = match.PointsB = match.GamesA = match.GamesB = 0;
        }
    }
//TODO score method
}

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
