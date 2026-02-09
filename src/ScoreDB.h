// -*- mode: c++; coding: utf-8 -*-

// Linthesia

#ifndef __SCORE_DB_H
#define __SCORE_DB_H

#include <sqlite3.h>
#include <string>
#include <vector>

struct SongScore {
    std::string song_path;
    int score;
    int max_streak;
    std::string grade;
    long long timestamp;
};

class ScoreDB {
public:
    ScoreDB();
    ~ScoreDB();

    bool Open(const std::string& db_path);
    void Close();

    void AddScore(const std::string& song_path, int score, int max_streak, const std::string& grade);
    SongScore GetBestScore(const std::string& song_path);

private:
    sqlite3* m_db;
    void CreateTable();
};

#endif // __SCORE_DB_H
