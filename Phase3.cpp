#ifndef PHASE3_H
#define PHASE3_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // for sort
#include "Phase1.h" // CricketBoard
#include "Phase2.h" // Tournament, RankingSystem

using namespace std;

// ====================== ICC Class ======================
class ICC {
private:
    string iccName;
    vector<CricketBoard> boards;
    vector<Tournament> tournaments;
    RankingSystem ranking;

public:
    ICC() : iccName("Unknown ICC") {}
    ICC(string name) : iccName(name) {}
    ~ICC() {}

    string getICCName() const { return iccName; }
    void setICCName(const string& name) { iccName = name; }

    // Board Management
    void addBoard(const CricketBoard& board) { boards.push_back(board); }
    void displayBoards() const {
        cout << "\n--- ICC Boards ---\n";
        for (const auto& board : boards) {
            board.displayAllTeams();
        }
    }
    CricketBoard* getBoardByName(const string& name) {
        for (auto& board : boards)
            if (board.getBoardName() == name)
                return &board;
        return nullptr;
    }

    // Tournament Management
    void addTournament(const Tournament& t) { tournaments.push_back(t); }
    void displayTournaments() const {
        cout << "\n--- ICC Tournaments ---\n";
        for (const auto& t : tournaments)
            t.displayTournament();
    }
    void playAllTournaments() {
        for (auto& t : tournaments)
            t.playTournament();
    }

    // Ranking Management
    void updateRankingsFromTournament(const Tournament& t) {
        for (const auto& match : t.getMatches())
            ranking.updateFromMatch(match);
    }
    void displayRankings() const { ranking.displayRankings(); }

    void displayInfo() const {
        cout << "\n=== ICC Information ===\n";
        cout << "ICC Name: " << iccName << "\n";
        cout << "Total Boards: " << boards.size() << "\n";
        cout << "Total Tournaments: " << tournaments.size() << "\n";
        cout << "Rankings Summary:\n";
        displayRankings();
    }
};

// ====================== Venue Class ======================
class Venue {
private:
    string venueName;
    string location;
    int capacity;

public:
    Venue() : venueName("Unknown Venue"), location("Unknown Location"), capacity(0) {}
    Venue(string vName, string loc, int cap) : venueName(vName), location(loc), capacity(cap) {}
    ~Venue() {}

    string getVenueName() const { return venueName; }
    void setVenueName(const string& name) { venueName = name; }

    string getLocation() const { return location; }
    void setLocation(const string& loc) { location = loc; }

    int getCapacity() const { return capacity; }
    void setCapacity(int cap) { capacity = cap; }

    void displayInfo() const {
        cout << "\nVenue Name: " << venueName
             << "\nLocation: " << location
             << "\nCapacity: " << capacity << "\n";
    }

    string toCSV() const {
        return venueName + "," + location + "," + to_string(capacity);
    }

    void fromCSV(const string& line) {
        // simple CSV parsing
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        venueName = line.substr(0, pos1);
        location = line.substr(pos1 + 1, pos2 - pos1 - 1);
        capacity = stoi(line.substr(pos2 + 1));
    }
};

// ====================== Statistics Class ======================
class Statistics {
public:
    // top scorer / best bowler statistics
    static void displayTopScorer(const vector<Player>& players) {
        if(players.empty()){cout<<"No players available.\n";return;}
        const Player* top = &players[0];
        for(const auto& p : players)
            if(p.getRuns() > top->getRuns())
                top = &p;
        cout << "\nTop Scorer: " << top->getName() << " | Runs: " << top->getRuns() << "\n";
    }

    static void displayBestBowler(const vector<Player>& players) {
        if(players.empty()){cout<<"No players available.\n";return;}
        const Player* top = &players[0];
        for(const auto& p : players)
            if(p.getWickets() > top->getWickets())
                top = &p;
        cout << "Best Bowler: " << top->getName() << " | Wickets: " << top->getWickets() << "\n";
    }

    static void displayTeamWinRatio(const Team& team) {
        int matches = team.getMatchesPlayed();
        int wins = team.getMatchesWon();
        double ratio = matches > 0 ? (double)wins / matches * 100 : 0;
        cout << "Team: " << team.getTeamName() << " | Win Ratio: " << ratio << "%\n";
    }
};

// ====================== Template List<T> ======================
template <typename T>
class List {
private:
    vector<T> items;

public:
    void add(const T& item) { items.push_back(item); }
    void remove(int index) {
        if(index >= 0 && index < items.size()) items.erase(items.begin() + index);
    }
    T& get(int index) { return items.at(index); }
    int size() const { return items.size(); }
    void display() const {
        for(const auto& item : items)
            item.displayInfo(); // assumes T has displayInfo()
    }
};

// ====================== Coach Class ======================
class Coach : public Person {
private:
    string teamName;
    int experience; // in years

public:
    Coach() : teamName("Unknown"), experience(0) {}
    Coach(string n, int a, string nat, string tName, int exp)
        : Person(n,a,nat), teamName(tName), experience(exp) {}

    void displayInfo() const override {
        cout << "\nCoach Name: " << name
             << "\nAge: " << age
             << "\nNationality: " << nationality
             << "\nTeam: " << teamName
             << "\nExperience: " << experience << " years\n";
    }
};

// ====================== Umpire Class ======================
class Umpire : public Person {
private:
    int matchesOfficiated;
    string qualification;

public:
    Umpire() : matchesOfficiated(0), qualification("Unknown") {}
    Umpire(string n, int a, string nat, int matches, string qual)
        : Person(n,a,nat), matchesOfficiated(matches), qualification(qual) {}

    void displayInfo() const override {
        cout << "\nUmpire Name: " << name
             << "\nAge: " << age
             << "\nNationality: " << nationality
             << "\nMatches Officiated: " << matchesOfficiated
             << "\nQualification: " << qualification << "\n";
    }
};

#endif
