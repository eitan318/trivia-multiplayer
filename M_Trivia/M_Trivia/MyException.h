#pragma once
#include <exception>
#include <string>

/**
 * @class MyException
 * @brief A custom exception class for handling application-specific errors.
 */
class MyException : public std::exception
{
public:
    /**
     * @brief Constructs a new MyException with a specific error message.
     *
     * @param message The error message associated with this exception.
     */
    MyException(const std::string& message) : m_message(message) {}

    /**
     * @brief Default destructor for MyException.
     *
     * Ensures proper cleanup of resources. This destructor is marked as noexcept.
     */
    virtual ~MyException() noexcept = default;

    /**
     * @brief Retrieves the error message associated with the exception.
     *
     * @return A C-style string containing the error message.
     */
    virtual const char* what() const noexcept override { return m_message.c_str(); }

protected:
    /// The error message associated with the exception.
    std::string m_message;
};
