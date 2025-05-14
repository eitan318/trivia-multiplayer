#pragma once 
#include <string>
#include <regex>

/**
 * @class RegexValidator
 * @brief A utility class for validating various types of input strings using regular expressions.
 *
 * This class provides static methods to validate common input fields, such as email addresses,
 * phone numbers, usernames, passwords, house addresses, and birth dates.
 */
class RegexValidator {
public:
    static constexpr std::string_view usernameRegexDescription = "None";
    static constexpr std::string_view emailRegexDescription = "_@_._";
    static constexpr std::string_view passwordRegexDescription = "8 + chars, include upper / lower letters, digit, special char.";
    static constexpr std::string_view houseAddressRegexDescription = "Street, Apt, City";
    static constexpr std::string_view phoneNumberRegexDescription = "0X(X)-XXXXXXX";
    static constexpr std::string_view birthDateRegexDescription = "DD.MM.YYYY or DD/MM/YYYY";

    /**
     * @brief Validates whether the input string is a valid email address.
     *
     * The validation uses a regular expression to check if the email format matches
     * the common pattern (e.g., `example@domain.com`).
     *
     * @param email The email address to validate.
     * @return `true` if the email is valid; otherwise, `false`.
     */
    static bool validEmail(const std::string& email);

    /**
     * @brief Validates whether the input string is a valid phone number.
     *
     * The validation ensures the phone number matches common formats, including country codes and digits.
     *
     * @param phoneNumber The phone number to validate.
     * @return `true` if the phone number is valid; otherwise, `false`.
     */
    static bool validPhoneNumber(const std::string& phoneNumber);

    /**
     * @brief Validates whether the input string is a valid username.
     *
     * The validation ensures the username meets specific criteria, such as length or allowed characters.
     *
     * @param username The username to validate.
     * @return `true` if the username is valid; otherwise, `false`.
     */
    static bool validUsername(const std::string& username);

    /**
     * @brief Validates whether the input string is a strong password.
     *
     * The validation ensures the password meets specific criteria, such as minimum length,
     * inclusion of uppercase, lowercase, numeric, and special characters.
     *
     * @param password The password to validate.
     * @return `true` if the password is strong; otherwise, `false`.
     */
    static bool validPassword(const std::string& password);

    /**
     * @brief Validates whether the input string is a valid house address.
     *
     * The validation ensures the address matches expected patterns (e.g., numbers, street names).
     *
     * @param houseAddress The house address to validate.
     * @return `true` if the house address is valid; otherwise, `false`.
     */
    static bool validHouseAddress(const std::string& houseAddress);

    /**
     * @brief Validates whether the input string is a valid birth date.
     *
     * The validation ensures the date is in an acceptable format (e.g., `YYYY-MM-DD` or similar).
     *
     * @param birthDate The birth date to validate.
     * @return `true` if the birth date is valid; otherwise, `false`.
     */
    static bool validBirthDate(const std::string& birthDate);
};
