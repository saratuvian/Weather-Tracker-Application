#include "DownloadThread.h"
#define CPPHTTPLIB_OPENSSL_SUPPORT // Enables HTTPS support for the httplib library, allowing secure API requests.
#include "httplib.h"
#include "nlohmann/json.hpp" // Includes the JSON library used for parsing the JSON response from the API.


void DownloadThread::operator()(CommonObjects& common) // Download thread's main operation.
{
    std::string apiKey = "e2802f3c467f4e01c9f3924be649c3de";
    while (!common.exit_flag) // Loop until exit flag is set
    {
        if (common.start_download) // Check if download is requested
        {

            std::string url = "http://api.openweathermap.org/data/2.5/weather?q=" + common.dest_name + "&appid=" + apiKey;

            httplib::Client cli("http://api.openweathermap.org"); // Creates an HTTP client for the base URL.

            auto res = cli.Get(url.c_str()); // Sends a GET request to the /weather endpoint to retrieve the data.

            if (res->status == 200) // Checks if the request was successful (HTTP status code 200).
            {
                auto json_data = nlohmann::json::parse(res->body); // Parses the JSON response body into a JSON object.
                WeatherData weather;
                weather.name = json_data["name"].get<std::string>();
                weather.temp = json_data["main"]["temp"].get<float>() - 273.15;
                weather.humidity = json_data["main"]["humidity"].get<int>();
                weather.pressure = json_data["main"]["pressure"].get<int>();
                weather.clouds = json_data["weather"][0]["description"].get<std::string>();
                weather.feels_like = json_data["main"]["feels_like"].get<float>() - 273.15;
                weather.sea_level = json_data["main"]["sea_level"].get<int>();
                weather.visibility = json_data["visibility"].get<int>() / 1000;
                weather.wind_Speed = json_data["wind"]["speed"].get<float>();
                weather.low_temp = json_data["main"]["temp_min"].get<float>() - 273.15;
                weather.high_temp = json_data["main"]["temp_max"].get<float>() - 273.15;
                common.weather_data.push_back(weather);
                common.data_ready = true;
            }

            common.start_download = false; // Reset the download flag after processing
        }
    }
}


void DownloadThread::SetUrl(std::string_view new_url) // Function to set the URL for the API request.
{
    _download_url = new_url; // Assigns the new URL to the _download_url member variable.
}

