# Weather Tracker Application

## Description
The Weather Tracker Application is a multi-threaded program designed to fetch and display current weather information from the OpenWeatherMap API. The application utilizes a graphical user interface (GUI) built with ImGui, allowing users to input city names, view weather data, and manage their selections.

## Features
- Multi-threaded architecture for downloading data and rendering the GUI concurrently.
- Real-time weather data fetching for specified cities.
- User-friendly interface to input city names and view weather details.
- Option to remove city data from the displayed list.
- Detailed weather information, including temperature, humidity, wind speed, and more.

## Files
- `GuiMain.h`: Contains declarations for the GUI rendering functions.
- `ConnectedApp.cpp`: Entry point for the application, initializes threads for downloading and drawing.
- `DrawThread.h/cpp`: Defines the drawing thread class responsible for rendering the GUI.
- `DownloadThread.h/cpp`: Implements the download thread class for fetching weather data from the API.
- `CommonObject.h`: Contains the shared data structures used for inter-thread communication.

## Requirements
- C++17 or later
- ImGui library for GUI rendering
- nlohmann/json for JSON parsing
- httplib for HTTP requests

## How to Build
1. Clone the repository.
2. Ensure all dependencies are available.
3. Compile the project using your preferred C++ compiler.

## Usage
1. Run the application.
2. Enter a city name in the input field and click "Add".
3. View current weather data for the added cities.
4. Use the "Remove" button to delete city entries from the list.

## License
This project is licensed under the MIT License.
