#pragma once
#include <iostream>
#include <string>
#include <curl/curl.h>

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
    static void sendEmail(const std::string& from, const std::string& to, const std::string& subject, const std::string& body)
    {
        std::string from_addr = "<" + from + ">";
        std::string to_addr = "<" + to + ">";
        std::string from_mail = "Trivia Game Authenticator " + from_addr;
        std::string to_mail = "Receiver " + to_addr;

        std::string payload_str =
            "To: " + to_mail + "\r\n"
            "From: " + from_mail + "\r\n"
            "Subject: " + subject + "\r\n"
            "\r\n"
            + body + "\r\n";

        payload_text = payload_str.c_str();

        CURL* curl;
        CURLcode res = CURLE_OK;
        struct curl_slist* recipients = NULL;
        struct upload_status upload_ctx = { 0 };

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, SMTP_SERVER);
            curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
            curl_easy_setopt(curl, CURLOPT_USERNAME, from.c_str());
            curl_easy_setopt(curl, CURLOPT_PASSWORD, GMAIL_PASSWORD);
            curl_easy_setopt(curl, CURLOPT_MAIL_FROM, from_addr.c_str());

            recipients = curl_slist_append(recipients, to_addr.c_str());
            curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

            curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
            curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
            curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

            res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                throw std::runtime_error(std::string("curl_easy_perform() failed: ") + curl_easy_strerror(res));
            }

            curl_slist_free_all(recipients);
            curl_easy_cleanup(curl);
        }
    }

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
    static size_t payload_source(char* ptr, size_t size, size_t nmemb, void* userp)
    {
        struct upload_status* upload_ctx = (struct upload_status*)userp;
        const char* data;
        size_t room = size * nmemb;

        if ((size == 0) || (nmemb == 0) || ((size * nmemb) < 1)) {
            return 0;
        }

        data = &payload_text[upload_ctx->bytes_read];

        if (data) {
            size_t len = strlen(data);
            if (room < len)
                len = room;
            memcpy(ptr, data, len);
            upload_ctx->bytes_read += len;

            return len;
        }

        return 0;
    }
};
