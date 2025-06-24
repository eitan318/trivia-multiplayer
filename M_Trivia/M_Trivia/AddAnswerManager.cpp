#include "AddAnswerManager.hpp"

AddAnswerManager& AddAnswerManager::getInstance(IDatabase& database)
{
	static AddAnswerManager instance(database);
	return instance;

}

void AddAnswerManager::addQuetion() 
{

}

AddAnswerManager::AddAnswerManager(IDatabase& dataBase) : m_database(dataBase)
{
}
