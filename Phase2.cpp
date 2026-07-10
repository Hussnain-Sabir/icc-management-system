#ifndef PHASE2_H
#define PHASE2_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

// ========================= MATCH CLASSES =========================
class Match
{
protected:
    int matchID;
    string team1;
    string team2;
    string venue;
    string date;
    string result;

public:
    Match()
    {
        matchID = 0;
        team1 = "Unknown";
        team2 = "Unknown";
        venue = "Unknown";
        date = "Unknown";
        result = "Not Played";
    }

    Match(int matchID, string team1, string team2, string venue, string date)
    {
        this->matchID = matchID;
        this->team1 = team1;
        this->team2 = team2;
        this->venue = venue;
        this->date = date;
        this->result = "Not Played";
    }

    virtual void playMatch() = 0;

    virtual void displayMatch() const
    {
        cout << "Match ID: " << matchID << endl;
        cout << "Team 1: " << team1 << endl;
        cout << "Team 2: " << team2 << endl;
        cout << "Venue: " << venue << endl;
        cout << "Date: " << date << endl;
        cout << "Result: " << result << endl;
    }

    virtual string toCSV() const
    {
        return to_string(matchID) + "," + team1 + "," + team2 + "," + venue + "," + date + "," + result;
    }

    string getResult() const { return result; }
    string getTeam1() const { return team1; }
    string getTeam2() const { return team2; }

    virtual ~Match() {}
};

// ---------------- T20 Match ----------------
class T20Match : public Match
{
private:
    int oversLimit;

public:
    T20Match() : Match() { oversLimit = 20; }
    T20Match(int matchID, string team1, string team2, string venue, string date) : Match(matchID, team1, team2, venue, date)
    {
        oversLimit = 20;
    }

    void playMatch() override
    {
        int team1Score = rand() % 101 + 120; // 120–220
        int team2Score = rand() % 101 + 120;

        if (team1Score > team2Score)
            result = team1;
        else if (team2Score > team1Score)
            result = team2;
        else
            result = "Match Drawn";
    }

    void displayMatch() const override
    {
        Match::displayMatch();
        cout << "Match Type: T20" << endl;
        cout << "Overs Limit: " << oversLimit << endl;
    }

    string toCSV() const override
    {
        return Match::toCSV() + ",T20";
    }
};

// ---------------- ODI Match ----------------
class ODIMatch : public Match
{
private:
    int oversLimit;

public:
    ODIMatch() : Match() { oversLimit = 50; }
    ODIMatch(int id, string t1, string t2, string v, string d) : Match(id, t1, t2, v, d)
    {
        oversLimit = 50;
    }

    void playMatch() override
    {
        int team1Score = rand() % 201 + 200; // 200–400
        int team2Score = rand() % 201 + 200;

        if (team1Score > team2Score)
            result = team1 + " won by " + to_string(team1Score - team2Score) + " runs";
        else if (team2Score > team1Score)
            result = team2 + " won by " + to_string(team2Score - team1Score) + " runs";
        else
            result = "Match tied";
    }

    void displayMatch() const override
    {
        cout << "[ODI Match]" << endl;
        Match::displayMatch();
        cout << "Overs Limit: " << oversLimit << endl;
    }

    string toCSV() const override
    {
        return "ODI," + Match::toCSV();
    }
};

// ========================= TOURNAMENT =========================
class Tournament
{
private:
    string tournamentName;
    vector<Match *> matches;

public:
    Tournament() { tournamentName = "Unnamed Tournament"; }
    Tournament(string name) { tournamentName = name; }

    void addMatch(Match *match)
    {
        matches.push_back(match);
    }

    void playTournament()
    {
        cout << "\n=== Playing Tournament: " << tournamentName << " ===\n";
        for (Match *m : matches)
            m->playMatch();
    }

    void displayTournament() const
    {
        cout << "\n=== Tournament Results: " << tournamentName << " ===\n";
        for (const Match *m : matches)
        {
            m->displayMatch();
            cout << "-------------------------\n";
        }
    }

    vector<Match *> getMatches() const { return matches; }

    ~Tournament()
    {
        for (Match *m : matches)
            delete m;
        matches.clear();
    }
};

// ========================= RANKING SYSTEM =========================
class RankingSystem
{
private:
    vector<string> teams;
    vector<int> points;

public:
    void addTeam(const string &teamName)
    {
        for (const string &t : teams)
        {
            if (t == teamName)
                return;
        }
        teams.push_back(teamName);
        points.push_back(0);
    }

    void updateFromMatch(const Match* match)
    {
        string result = match->getResult();
        for (size_t i = 0; i < teams.size(); ++i)
        {
            if (result.find(teams[i]) != string::npos)
            {
                points[i] += 2;
                break;
            }
        }
    }

    void displayRankings() const
    {
        cout << "\n=== Team Rankings ===\n";
        for (size_t i = 0; i < teams.size(); ++i)
            cout << teams[i] << " : " << points[i] << " points\n";
    }

    bool isTeam1Leading(const string &team1, const string &team2) const
    {
        int p1 = 0, p2 = 0;
        for (size_t i = 0; i < teams.size(); ++i)
        {
            if (teams[i] == team1)
                p1 = points[i];
            if (teams[i] == team2)
                p2 = points[i];
        }
        return p1 > p2;
    }
};

#endif
