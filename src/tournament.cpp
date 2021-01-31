#include "tournament.h"

#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <algorithm>
#include <vector>

Tournament::Tournament(std::string name, std::vector<Player*> players, int winning_sets, std::string surface)
: Name(name), Players(players), WinningSets(winning_sets), Surface(surface)
{
    Init();
}

void Tournament::Init()
{
    // Init match plan      //TODO

    Match *m = new Match(Players[0], Players[1]);
    Matches.push_back(m);

    m = new Match(Players[2], Players[3]);
    Matches.push_back(m);

    m = new Match(Players[4], Players[5]);
    Matches.push_back(m);

    m = new Match(Players[6], Players[7]);
    Matches.push_back(m);

    m = new Match(Players[8], Players[9]);
    Matches.push_back(m);

    calculateNextRound();
}

int Tournament::sortPlayersByRanking(Match *match)   //TODO
{
    int x = sizeof(Players) / sizeof(Players[0]);
    return 0;
}

// should return the Opponent for the next match
Player Tournament::getNextOpponent(Match *match)
{
    //TODO
}

// should calculate all results of the next round
void Tournament::calculateNextRound()
{
    std::string liveScore;
    for (int i = 0; i < Matches.size(); i++)
    {
        if (this->OwnMatch == true)
            break;
        calculateMatch(Matches[i]);
    }
}

// should calculate result of the next match
void Tournament::calculateMatch(Match *match)
{
    ability(match);
    sortPlayersByRanking(match);
    match->liveScore.append(toss(match));
    match->PointsA = match->GamesA = match->SetsA = match->PointsB = match->GamesB = match->SetsB = 0;
    match->liveScore.append(printScore(match));
    while (match->PointsA < 50 && match->PointsB < 50)
    {
        if (winnerOfRallyA(match) == true)
        {
            if (match->PointsA == 0 || match->PointsA == 15)
                match->PointsA += 15;
            else if (match->PointsA == 30)
                match->PointsA += 10;
            else if (match->PointsA == 40 && match->PointsB < 40)
            {
                match->GamesA++;
                match->PointsA = match->PointsB = 0;
                changeService(match);
            }
        }
        else
        {
            if (match->PointsB == 0 || match->PointsB == 15)
                match->PointsB += 15;
            else if (match->PointsB == 30)
                match->PointsB += 10;
            else if (match->PointsB == 40 && match->PointsA < 40)
            {
                match->GamesB++;
                match->PointsB = match->PointsA = 0;
                changeService(match);
            }
        }
        match->liveScore.append(printScore(match));
        if (match->PointsA == 40 && match->PointsB == 40)
        {
            if (winnerOfRallyA(match) == true)
                match->PointsA += 5;
            else
                match->PointsB += 5;
            match->liveScore.append(printScore(match));
        }

        if (match->PointsA == 45 || match->PointsB == 45)
        {
            if (winnerOfRallyA(match) == true)
            {
                if (match->PointsA == 45)
                {
                    match->GamesA++;
                    match->PointsA = match->PointsB = 0;
                    changeService(match);
                    match->liveScore.append(printScore(match));
                }
                else
                    match->PointsA = match->PointsB = 40;
            }
            else
            {
                if (match->PointsA == 45)
                    match->PointsA = match->PointsB = 40;
                else
                {
                    match->GamesB++;
                    match->PointsA = match->PointsB = 0;
                    changeService(match);
                    match->liveScore.append(printScore(match));
                }
            }
        }
        if (match->GamesA >= 6 && match->GamesB < 6 && (match->GamesA - match->GamesB >= 2))
        {
            match->SetsA++;
            saveGamesOfSet(match);
            match->PointsA = match->PointsB = match->GamesA = match->GamesB = 0;
        }
        else if (match->GamesB >= 6 && match->GamesA < 6 && (match->GamesB - match->GamesA >= 2))
        {
            match->SetsB++,
            saveGamesOfSet(match);
            match->PointsA = match->PointsB = match->GamesA = match->GamesB = 0;
        }
        if (match->GamesA == 6 && match->GamesB == 6)
            tieBreak(match);

        if (match->SetsA == WinningSets || match->SetsB == WinningSets)
        {
            int length = 0;
            char winner [128];
            match->liveScore.append(printScore(match));
            if (match->SetsA > match->SetsB)
                length += sprintf(winner + length, "%s %s has won against %s %s!\n", match->A->Forename.c_str(), match->A->Surname.c_str(), match->A->Forename.c_str(), match->B->Surname.c_str());
            else
                length += sprintf(winner + length, "%s %s has won against %s %s!\n", match->B->Forename.c_str(), match->B->Surname.c_str(), match->A->Forename.c_str() match->B->Surname.c_str(),);
            match->liveScore.append(winner);
            match->liveScore.append(printResult(match));
            std::cout << match->liveScore << std::endl;
            match->PointsA = 60;
        }
    }
}

void Tournament::ability(Match *match)
{
    if (Surface.compare("clay") == 0)
    {
        match->AbilityA = match->A->AbilityClay;
        match->AbilityB = match->B->AbilityClay;
    }
    else if (Surface.compare("hard") == 0)
    {
        match->AbilityA = match->A->AbilityHard;
        match->AbilityB = match->B->AbilityHard;
    }
    else if (Surface.compare("grass") == 0)
    {
        match->AbilityA = match->A->AbilityGrass;
        match->AbilityB = match->B->AbilityGrass;
    }
}

bool Tournament::winnerOfRallyA(Match *match)
{
    srand (time(NULL));
    int x = rand() % 42 + 1;
    int y = rand() % 42 + 1;
    if (match->AbilityA - match->AbilityB >= 42)
    {
        x = rand() % ((match->AbilityA - match->AbilityB) + 5) + 1;
        y = rand() % ((match->AbilityA - match->AbilityB) + 5) + 1;
    }
    else if (match->AbilityB - match->AbilityA >= 42)
    {
        x = rand() % ((match->AbilityB - match->AbilityA) + 5) + 1;
        y = rand() % ((match->AbilityB - match->AbilityA) + 5) + 1;
    }
    int p_a = x + match->AbilityA;
    int p_b = y + match->AbilityB;
    if (match->ServeA == true)
    {
        p_a += match->A->ServeAbility;
        p_b += match->B->ReturnAbility;
    }
    else
    {
        p_b += match->B->ServeAbility;
        p_a += match->A->ReturnAbility;
    }
    if (p_a >= p_b)
        return true;
    else
        return false;
}

void Tournament::saveGamesOfSet(Match *match)
{
    switch(match->SetsA + match->SetsB)
    {
        case 1:
            match->GamesSetA[0] = match->GamesA;
            match->GamesSetB[0] = match->GamesB;
            break;
        case 2:
            match->GamesSetA[1] = match->GamesA;
            match->GamesSetB[1] = match->GamesB;
            break;
        case 3:
            match->GamesSetA[2] = match->GamesA;
            match->GamesSetB[2] = match->GamesB;
            break;
    }

    if (WinningSets == 3)
    {
        switch(match->SetsA + match->SetsB)
        {
            case 4:
                match->GamesSetA[3] = match->GamesA;
                match->GamesSetB[3] = match->GamesB;
                break;
            case 5:
                match->GamesSetA[4] = match->GamesA;
                match->GamesSetB[4] = match->GamesB;
                break;
        }
    }
}

void Tournament::changeService(Match *match)
{
   match->ServeA ? match->ServeA = false : match->ServeA = true;
}

void Tournament::tieBreak(Match *match)
{
    while (match->GamesA == 6 && match->GamesB == 6)
    {
        if (winnerOfRallyA(match) == true)
            match->PointsA++;
        else
            match->PointsB++;
    match->liveScore.append(printScore(match));

        if ((match->PointsA + match->PointsB) % 2 == 1)
            changeService(match);

        if ((match->PointsA - match->PointsB >= 2 && match->PointsA >= 7) || (match->PointsB - match->PointsA >= 2 && match->PointsB >= 7))
        {
            if (match->PointsA > match->PointsB)
            {
                match->GamesA++;
                match->SetsA++;
            }
            else
            {
                match->GamesB++;
                match->SetsB++;
            }
            changeService(match);
            saveGamesOfSet(match);
            switch (match->SetsA + match->SetsB)
            {
                case 1:
                    match->TiebreakPointsSetA [0] = match->PointsA;
                    match->TiebreakPointsSetB [0] = match->PointsB;
                    break;
                case 2:
                    match->TiebreakPointsSetA [1] = match->PointsA;
                    match->TiebreakPointsSetB [1] = match->PointsB;
                    break;
                case 3:
                    match->TiebreakPointsSetA [2] = match->PointsA;
                    match->TiebreakPointsSetB [2] = match->PointsB;
                    break;
            }
            if (WinningSets == 5)
            {
                switch (match->SetsA + match->SetsB)
                {
                    case 4:
                        match->TiebreakPointsSetA [3] = match->PointsA;
                        match->TiebreakPointsSetB [3] = match->PointsB;
                        break;
                    case 5:
                        match->TiebreakPointsSetA [4] = match->PointsA;
                        match->TiebreakPointsSetB [4] = match->PointsB;
                        break;
                }
            }
            match->PointsA = match->PointsB = match->GamesA = match->GamesB = 0;
        }
    }
    match->liveScore.append(printScore(match));

}

std::string Tournament::toss(Match *match)
{
    std::string toss_string;
    srand (time(NULL));
    int toss_value = rand() % 4;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    switch (toss_value)
    {
        case 0:
            match->ServeA = true;
            toss_string = match->A->Surname + " has won the toss and has chosen to serve\n";
            break;
        case 1:
            match->ServeA = false;
            toss_string = match->A->Surname + " has won the toss and has chosen to receive\n";
            break;
        case 2:
            match->ServeA = false;
            toss_string = match->B->Surname + " has won the toss and has chosen to serve\n";
            break;
        case 3:
            match->ServeA = true;
            toss_string = match->B->Surname + " has won the toss and has chosen to receive\n";
            break;
    }
    return toss_string;
}

std::string Tournament::printScore(Match *match)
{
    int length = 0;
    char score [100000];
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    if (match->ServeA == true)
        length += sprintf(score + length, "-");
    else
        length += sprintf(score + length, " ");
    length += sprintf(score + length, "%14s   ", match->A->Surname.c_str());
    length += sprintf(score + length,  "%d%d%d", match->GamesSetA[0], match->GamesSetA[1], match->GamesSetA[2]);
    if (WinningSets == 3)
        length += sprintf(score + length, "%d%d   ", match->GamesSetA[3], match->GamesSetA[4]);
    else
        length += sprintf(score + length, "   ");
    length += sprintf(score + length, "%d   ", match->GamesA);
    if (match->PointsA == 45)
        length += sprintf(score + length, "Ad");
    else
        length += sprintf(score + length, "%2d", match->PointsA);
    length += sprintf(score + length, "\n");

    if (match->ServeA == false)
        length += sprintf(score + length, "-");
    else
        length += sprintf(score + length, " ");
    length += sprintf(score + length, "%14s   ", match->B->Surname.c_str());
    length += sprintf(score + length, "%d%d%d", match->GamesSetB[0], match->GamesSetB[1], match->GamesSetB[2]);
    if (WinningSets == 3)
        length += sprintf(score + length, "%d%d   ", match->GamesSetB[3], match->GamesSetB[4]);
    else
        length += sprintf(score + length, "   ");
    length += sprintf(score + length, "%d   ", match->GamesB);
    if (match->PointsB == 45)
        length += sprintf(score + length, "Ad");
    else
        length += sprintf(score + length, "%2d", match->PointsB);
    length += sprintf(score + length, "\n\n");
    return score;
}

std::string Tournament::printResult(Match *match)
{
    int length = 0;
    char result [100];
    length += sprintf(result + length, "    ");
    if (match->SetsA == WinningSets)
    {
        for (int i = 0; i < 5; i++)
        {
            if (match->TiebreakPointsSetA[i] > 0)
                length += sprintf(result + length, "(%d)", match->TiebreakPointsSetA[i]);
            if (match->GamesSetA[i] != match->GamesSetB[i])
                length += sprintf(result + length, "%d:%d", match->GamesSetA[i], match->GamesSetB[i]);
            if (match->TiebreakPointsSetB[i] > 0)
                length += sprintf(result + length, "(%d)", match->TiebreakPointsSetB[i]);
            length += sprintf(result + length, " ");
        }
    }
    else
    {
        for (int i = 0; i < 5; i++)
        {
            if (match->TiebreakPointsSetB[i] > 0)
                length += sprintf(result + length, "(%d)", match->TiebreakPointsSetB[i]);
            if (match->GamesSetB[i] != match->GamesSetA[i])
                length += sprintf(result + length, "%d:%d", match->GamesSetB[i], match->GamesSetA[i]);
            if (match->TiebreakPointsSetA[i] > 0)
                length += sprintf(result + length, "(%d)", match->TiebreakPointsSetA[i]);
            length += sprintf(result + length, " ");
        }
    }
    length += sprintf(result + length, "\n\n");
    return result;
}
