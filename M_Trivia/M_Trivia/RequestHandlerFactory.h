#pragma once
#include "LoginManager.h"
#include "IDatabase.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include <memory>


class LoginRequestHandler;
class MenuRequestHandler;

/**
 * @class RequestHandlerFactory
 * @brief A factory class responsible for creating and managing instances of request handlers
 *        and accessing various managers such as LoginManager, RoomManager, and StatisticsManager.
 */
class RequestHandlerFactory {
public:
    /**
     * @brief Gets the singleton instance of RequestHandlerFactory.
     * @param database The database instance to be used across the managers.
     * @return A reference to the singleton instance of RequestHandlerFactory.
     */
    static RequestHandlerFactory& getInstance(IDatabase& database);

    /**
     * @brief Creates a new LoginRequestHandler.
     * @return A pointer to a newly created LoginRequestHandler.
     */
    std::unique_ptr<IRequestHandler> createLoginRequestHandler() const;

    /**
	 * @brief Creates a new MenuRequestHandler.
	 * @return A pointer to a newly created MenuRequestHandler.
	 */
    std::unique_ptr<IRequestHandler> createMenuRequestHandler(const LoggedUser& loggedUser) const;


    /**
     * @brief Gets a reference to the LoginManager.
     * @return A reference to the LoginManager instance.
     */
    LoginManager& getLoginManager() const;

    /**
     * @brief Gets a reference to the RoomManager.
     * @return A reference to the RoomManager instance.
     */
    RoomManager& getRoomManger() const;

    /**
     * @brief Gets a reference to the StatisticsManager.
     * @return A reference to the StatisticsManager instance.
     */
    StatisticsManager& getStatisticsManger() const;

private:
    RoomManager& m_roomManager; ///< The RoomManager instance used by the factory.
    IDatabase& m_database; ///< The database instance used across the managers.
    StatisticsManager& m_statisticsManager; ///< The StatisticsManager instance used by the factory.
    LoginManager& m_loginManager; ///< The LoginManager instance used by the factory.

    /**
     * @brief Private constructor for creating a RequestHandlerFactory instance.
     * @param database The database instance to initialize the managers.
     */
    RequestHandlerFactory(IDatabase& database);

    /**
     * @brief Deleted copy constructor to prevent copying of the factory.
     */
    RequestHandlerFactory(const RequestHandlerFactory&) = delete;

    ~RequestHandlerFactory() = default;

    /**
     * @brief Deleted assignment operator to prevent assignment of the factory.
     * @return A reference to the current instance.
     */
    RequestHandlerFactory& operator=(const RequestHandlerFactory&) = delete;
};
