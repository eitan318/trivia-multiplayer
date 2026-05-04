#include "EmailSender.hpp"
#include <curl/curl.h>
#include <iostream>


void EmailSender::sendEmail(const std::string& from, const std::string& to, const std::string& subject, const std::string& body)
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



size_t EmailSender::payload_source(char* ptr, size_t size, size_t nmemb, void* userp)
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