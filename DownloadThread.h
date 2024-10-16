#pragma once
#include "CommonObject.h"

class DownloadThread
{
public:
    void operator()(CommonObjects& common); // Main function for downloading data.
    void SetUrl(std::string_view new_url);  // Sets the URL for the API request.
    //void SaveWeatherDataToFile(const CommonObjects& common, const std::string& filepath); // Saves recipes to a file.
private:
    std::string _download_url; // Stores the URL for downloading.
};
