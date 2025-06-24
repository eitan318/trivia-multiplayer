#pragma once
#include "SqliteDatabase.hpp"
#include "QuestionRecord.hpp"

class AddAnswerManager 
{
public:
    /**
     * Gets the singleton instance of the AddAnswerManager.
     *
     * @param database Reference to the database used for managing game data.
     * @return A reference to the singleton instance of the AddAnswerManager.
     */
    static AddAnswerManager& getInstance(IDatabase& database);

    void addQuetion(QuestionRecord& question);
private:
    /**
    * Constructs a AddAnswerManager instance with a reference to the database.
    *
    * @param dataBase Reference to the database used for managing game data.
    */
    AddAnswerManager(IDatabase& dataBase);

    IDatabase& m_database;
};