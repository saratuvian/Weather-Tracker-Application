#pragma once
#include <atomic>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

// Structure for storing weather data
struct WeatherData {
    std::string name;
    float temp;
    int humidity;
    int pressure;
    std::string clouds;
    int visibility;
    int wind_Speed;
    int sea_level;
    float feels_like;
    float low_temp;
    float high_temp;
};

// Main common object structure for synchronization between threads and storing data
struct CommonObjects {
    std::atomic_bool start_download = false; // Flag to start download
    std::atomic_bool data_ready = false;     // Flag to mark that data is ready
    std::atomic_bool exit_flag = false;     // flag to signal exit window
    std::string dest_name; // Stores the destination name for the url from which the data will be downloaded
    std::vector<WeatherData> weather_data;   // Vector to store multiple weather data points
    int selected_index; // Add this member to keep track of selected row
    std::vector<bool> show_details; // Vector to store the visibility state for each row
};
