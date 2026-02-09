// -*- mode: c++; coding: utf-8 -*-

// Linthesia

#include "ScoreDB.h"
#include <iostream>
#include <ctime>

using namespace std;

ScoreDB::ScoreDB() : m_db(nullptr) {}

ScoreDB::~ScoreDB() {
    Close();
}

bool ScoreDB::Open(const std::string& db_path) {
    if (sqlite3_open(db_path.c_str(), &m_db)) {
        cerr << "Can't open database: " << sqlite3_errmsg(m_db) << endl;
        return false;
    }
    CreateTable();
    return true;
}

void ScoreDB::Close() {
    if (m_db) {
        sqlite3_close(m_db);
        m_db = nullptr;
    }
}

void ScoreDB::CreateTable() {
    if (!m_db) return;
    const char* sql = "CREATE TABLE IF NOT EXISTS song_scores ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "song_path TEXT NOT NULL, "
                      "score INTEGER NOT NULL, "
                      "max_streak INTEGER NOT NULL, "
                      "grade TEXT NOT NULL, "
                      "timestamp INTEGER NOT NULL);";
    char* errMsg = 0;
    if (sqlite3_exec(m_db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}

void ScoreDB::AddScore(const std::string& song_path, int score, int max_streak, const std::string& grade) {
    if (!m_db) return;

    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO song_scores (song_path, score, max_streak, grade, timestamp) VALUES (?, ?, ?, ?, ?);";

    if (sqlite3_prepare_v2(m_db, sql, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, song_path.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, score);
        sqlite3_bind_int(stmt, 3, max_streak);
        sqlite3_bind_text(stmt, 4, grade.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int64(stmt, 5, static_cast<long long>(time(nullptr)));

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

SongScore ScoreDB::GetBestScore(const std::string& song_path) {
    SongScore res = {song_path, 0, 0, "", 0};
    if (!m_db) return res;

    sqlite3_stmt* stmt;
    // Get best score based on score value
    const char* sql = "SELECT score, max_streak, grade, timestamp FROM song_scores WHERE song_path = ? ORDER BY score DESC LIMIT 1;";

    if (sqlite3_prepare_v2(m_db, sql, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, song_path.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            res.score = sqlite3_column_int(stmt, 0);
            res.max_streak = sqlite3_column_int(stmt, 1);
            res.grade = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            res.timestamp = sqlite3_column_int64(stmt, 3);
        }
        sqlite3_finalize(stmt);
    }
    return res;
}
