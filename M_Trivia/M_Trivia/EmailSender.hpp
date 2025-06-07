#pragma once
#include <string>

#define GMAIL_PASSWORD "kzse tous xxvt wabs" /**< Placeholder for Gmail app password. */
#define SMTP_SERVER "smtp://smtp.gmail.com:587" /**< Gmail SMTP server URL. */

/**
 * @struct upload_status
 * @brief Tracks the state of email content upload.
 */
struct upload_status {
    size_t bytes_read; /**< Number of bytes read from the email payload. */
} typedef upload_status;

/**
 * @class EmailSender
 * @brief Handles sending emails via Gmail's SMTP server using libcurl.
 *
 * This class provides a static function to send emails. It uses libcurl to establish a connection
 * with the Gmail SMTP server and handle email transmission. Note that the class cannot be instantiated.
 */
class EmailSender {
private:
    /**
     * @brief Deleted constructor to prevent instantiation.
     */
    EmailSender() = delete;

public:
    /**
     * @brief Sends an email using Gmail's SMTP server.
     *
     * This function establishes a connection to the Gmail SMTP server and sends an email
     * from the specified sender to the specified recipient.
     *
     * @param from Sender's email address.
     * @param to Recipient's email address.
     * @param subject The subject of the email.
     * @param body The body content of the email.
     * @throws std::runtime_error if email transmission fails.
     */
    static void sendEmail(const std::string& from, const std::string& to, const std::string& subject, const std::string& body);
    
private:
    static inline const char* payload_text = nullptr; /**< Pointer to the email payload text. */

    /**
     * @brief Reads email content and provides it to libcurl.
     *
     * This callback function is called by libcurl to fetch chunks of the email content during upload.
     *
     * @param ptr Pointer to the buffer to fill with email content.
     * @param size Size of each data element.
     * @param nmemb Number of elements.
     * @param userp Pointer to the upload_status structure for tracking progress.
     * @return Number of bytes actually written to the buffer.
     */
    static size_t payload_source(char* ptr, size_t size, size_t nmemb, void* userp);
    
};
