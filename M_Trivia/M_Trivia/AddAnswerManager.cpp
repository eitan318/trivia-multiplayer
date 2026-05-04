#include "AddAnswerManager.hpp"

AddAnswerManager& AddAnswerManager::getInstance(IDatabase& database)
{
	static AddAnswerManager instance(database);
	return instance;

}

GeneralResponseErrors AddAnswerManager::addQuetion(QuestionRecord& question)
{
	GeneralResponseErrors errors;
	if (this->m_database.addQuestionToDB(question)) 
	{
		return errors;
	}
	else 
	{
		return errors.generalError = "Error adding Question To Database";
	}
}

AddAnswerManager::AddAnswerManager(IDatabase& dataBase) : m_database(dataBase)
{
}
