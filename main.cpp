#include <iostream>
#include <curl/curl.h>

// Callback function to write response data
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response)
{
    size_t totalSize = size * nmemb;
    response->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

int main()
{
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create a CURL handle
    CURL* curl = curl_easy_init();
    if (curl)
    {
        // Set the URL to the API endpoint
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.example.com/endpoint");

        // Set the callback function to handle the response
        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the request
        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK)
        {
            // Request successful, print the response
            std::cout << "Response: " << response << std::endl;
        }
        else
        {
            // Request failed, print the error
            std::cerr << "Request failed: " << curl_easy_strerror(res) << std::endl;
        }

        // Clean up
        curl_easy_cleanup(curl);
    }

    // Clean up libcurl
    curl_global_cleanup();

    return 0;
}