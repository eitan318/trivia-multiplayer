#include "AddAnswerManager.hpp"

AddAnswerManager& AddAnswerManager::getInstance(IDatabase& database)
{
	static AddAnswerManager instance(database);
	return instance;

}

void AddAnswerManager::addQuetion(QuestionRecord& question) 
{
	this->m_database.addQuestionToDB(question);
}

AddAnswerManager::AddAnswerManager(IDatabase& dataBase) : m_database(dataBase)
{
}
