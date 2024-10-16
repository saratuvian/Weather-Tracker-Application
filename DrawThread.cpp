#include "DrawThread.h"
#include "GuiMain.h"
#include "../../shared/ImGuiSrc/imgui.h"


void DrawAppWindow(void* common_ptr)
{
	auto common = (CommonObjects*)common_ptr; // Create pointer to the CommonObjects structure
	static char city_buff[200]; // Buffer to hold user input for the city name.

	ImGui::Begin("Connected!"); // Start a new window with the title "Connected!".
	ImGui::Text("Here you can find out about weather around the world"); // Displays a line of text in the ImGui window
	ImGui::Text("Enter City"); // Label text
	ImGui::SameLine(); // Place the input text field on the same line
	ImGui::InputText("##city", city_buff, sizeof(city_buff)); // Input text field
	ImGui::SameLine(); // Place the input text field on the same line

	if (ImGui::Button("Add")) // Creates a button labeled "Add".
	{
		common->dest_name = city_buff;
		common->start_download = true;
		// Clear the input buffer after pressing "Add"
		city_buff[0] = '\0'; // Set the first character of the buffer to null terminator
	}

	if (common->data_ready) // Checks if the data is ready
	{
		if (common->show_details.size() != common->weather_data.size()) {
			common->show_details.resize(common->weather_data.size(), false);
		}

		if (ImGui::BeginTable("Weather Data", 7)) // Start a table with 5 columns
		{
			ImGui::TableSetupColumn("City Name");
			ImGui::TableSetupColumn("Temperature (C)");
			ImGui::TableSetupColumn("Humidity (%)");
			ImGui::TableSetupColumn("pressure");
			ImGui::TableSetupColumn("Description", ImGuiTableColumnFlags_WidthFixed, 100.0f); // Column for the description and button
			ImGui::TableHeadersRow(); // Create the header row of the table with columns defined up.

			std::vector<int> rows_to_remove; // Temporary list to store rows to remove
			int row_index;

			for (row_index = 0; row_index < common->weather_data.size(); ++row_index) {

				auto& weather = common->weather_data[row_index];

				ImGui::TableNextRow(); // Move to the next row in the table.

				ImGui::TableSetColumnIndex(0); // Set the column index to the first column (City Name).
				ImGui::Text(weather.name.c_str()); // Display the city name.

				ImGui::TableSetColumnIndex(1); // Set the column index to the second column (Temperature).
				ImGui::Text("%.2f", weather.temp); // Display the temperature.

				ImGui::TableSetColumnIndex(2); // Set the column index to the third column (Humidity).
				ImGui::Text("%d", weather.humidity); // Display the humidity.

				ImGui::TableSetColumnIndex(3); // Set the column index to the fourth column (Wind Speed).
				ImGui::Text("%d", weather.pressure); // Display the wind speed.

				ImGui::TableSetColumnIndex(4); // Set the column index to the fifth column (Description).

				// Create a unique ID for the button based on the row index
				std::string button_id = common->show_details[row_index] ? "Hide" + std::to_string(row_index) : "Show" + std::to_string(row_index); // Unique ID


				if (ImGui::Button(button_id.c_str())) // Button with unique ID
				{
					if (common->show_details[row_index]) {
						common->show_details[row_index] = false; // Toggle visibility for this row
					}
					else
					{
						common->show_details[row_index] = true; // Show

					}
				}



				ImGui::TableSetColumnIndex(6); // Set the column index for the Remove button
				std::string button_id2 = "Remove" + std::to_string(row_index);
				if (ImGui::Button(button_id2.c_str())) {
					rows_to_remove.push_back(row_index); // Add row index to the removal list
				}


				// Display detailed information below the table
				if (common->show_details[row_index]) {
					ImGui::TableSetColumnIndex(5);
					ImGui::Text("Details for %s", weather.name.c_str());
					ImGui::Separator();
					ImGui::Text("Feels Like: %.2f", weather.feels_like);
					ImGui::Text("Low Temp: %.2f", weather.low_temp);
					ImGui::Text("High Temp: %.2f", weather.high_temp);
					ImGui::Text("Clouds: %s", weather.clouds.c_str());
					ImGui::Text("Humidity: %d%%", weather.humidity); //לחות
					ImGui::Text("Visibility: %d km", weather.visibility);
					ImGui::Text("Wind Speed: %d km/h", weather.wind_Speed);
					ImGui::Text("Sea Level: %d hPa", weather.sea_level);

				}

			}

			ImGui::EndTable();

			// Remove rows after the table iteration
			for (int i = rows_to_remove.size() - 1; i >= 0; i--) {
				int index = rows_to_remove[i];
				common->weather_data.erase(common->weather_data.begin() + index);
				common->show_details.erase(common->show_details.begin() + index);
			}

			common->start_download = false; // Reset the download flag
		}
	}

	ImGui::End();
}

// starts the GUI rendering loop for your application in a separate thread
void DrawThread::operator()(CommonObjects& common)
{
	// Start the GUI rendering loop
	GuiMain(DrawAppWindow, &common);
	common.exit_flag = true;
}
