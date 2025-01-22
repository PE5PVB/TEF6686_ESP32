#include "logbook.h"
#include "language.h"
#include "constants.h"
#include <EEPROM.h>
#include "language.h"

void handleRoot() {
  fs::File file = SPIFFS.open("/logbook.csv", "r");
  if (!file) {
    webserver.send(500, "text/plain", "Failed to open logbook");
    return;
  }

  String html = "<!DOCTYPE html><html lang=\"en\"><head>";
  html += "<meta charset=\"UTF-8\">";
  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";

  // Add CSS styling
  html += "<style>";
  html += "body {background-color: rgb(32, 34, 40); color: white; font-family: 'Arial', sans-serif;}";
  html += "h1 {text-align: center; margin-top: 20px;font-size: 32px;}";
  html += "img {display: block; margin: 0 auto; max-width: 100%; height: auto; padding-top: 20px; cursor: pointer;}";
  html += "table {width: 90%; max-width: 1500px; margin: 0 auto; border-radius: 15px; overflow: auto; padding: 20px; background-color: #2e5049; border: 0; border-collapse: separate !important; border-spacing: 0;}";
  html += "thead th {font-size: 18px; cursor: pointer; position: relative; user-select: none; background-color: #3c7f6a;}";
  html += "th, td {padding: 10px; text-align: center;}";
  html += "thead th:first-child, tbody th:first-child {border-radius: 15px 0 0 15px;}";
  html += "thead th:nth-last-of-type(1), tbody th:nth-last-of-type(1) {border-radius: 0 15px 15px 0;}";
  html += "tbody td:nth-child(3) {font-weight: 700;}";
  html += "tbody td:nth-child(4) {color: #5bd6ab;}";
  html += "tbody td:nth-child(5) {color: #ddd;}";
  html += "tbody td:nth-child(11) {color: #5bd6ab;font-weight: bold;}";
  html += "thead th:nth-child(1) {width: 12%;} thead th:nth-child(2) {width: 5%;} thead th:nth-child(3) {width: 10%;} thead th:nth-child(4) {width: 5%;} thead th:nth-child(5) {width: 10%;} thead th:nth-child(6) {width: 5%;} thead th:nth-child(6) {width: 5%;}";
  html += "button {background-color: #4db691;font-family: 'Arial', sans-serif;border: 0;padding: 15px 20px;font-size: 14px;text-transform: uppercase;cursor: pointer;border-radius: 15px;font-weight: bold;color: rgb(32, 34, 40);display: block;margin: 20px auto;transition: 0.3s ease background-color;}";
  html += "button:hover {background-color: #5bd6ab;}";
  html += ".go-to-bottom {position: fixed;bottom: 30px;right: 30px;z-index: 100;}";
  html += ".sort-icon {position: absolute;right: 10px;top: 50%;transform: translateY(-50%);color: #ccc;}";
  html += "@media (max-width: 768px) {table {width: 100%;}th, td {font-size: 14px;padding: 8px;}}";
  html += "a { text-decoration:none };";
  html += "</style>";
  html += "</head><body>";

  // Add logo as a clickable link
  html += "<a href=\"https://fmdx.org/\" target=\"_blank\">";
  html += "<img src=\"/logo.png\" alt=\"FMDX website\">";
  html += "</a>";

  html += "<h1>" + String(myLanguage[language][286]) + "</h1>";
  html += "<button onclick=\"window.location.href='/downloadCSV'\">" + String(myLanguage[language][287]) + "</button>";
  html += "<button class=\"go-to-bottom\" onclick=\" window.scrollTo(0, document.body.scrollHeight);\">" + String(myLanguage[language][289]) + "</button>";

  // Sorting function with icons
  html += "<script>";
  html += "function sortTable(columnIndex) {";
  html += "var table = document.getElementById('logbookTable');";
  html += "var rows = Array.from(table.rows).slice(1);";
  html += "var isAscending = table.rows[0].cells[columnIndex].classList.toggle('asc');";
  html += "Array.from(table.rows[0].cells).forEach((th, index) => {";
  html += "if (index !== columnIndex) th.classList.remove('asc', 'desc');});";
  html += "rows.sort((a, b) => {";
  html += "var cellA = a.cells[columnIndex].textContent.trim();";
  html += "var cellB = b.cells[columnIndex].textContent.trim();";
  html += "return isAscending ? cellA.localeCompare(cellB) : cellB.localeCompare(cellA);});";
  html += "rows.forEach(row => table.appendChild(row));";
  html += "updateSortIcons(columnIndex, isAscending);}";

  // Function to update the sort icons
  html += "function updateSortIcons(columnIndex, isAscending) {";
  html += "document.querySelectorAll('th').forEach((th, index) => {";
  html += "th.querySelector('.sort-icon').textContent = '';";
  html += "if (index === columnIndex) {";
  html += "th.querySelector('.sort-icon').textContent = isAscending ? '▲' : '▼';}});}";
  html += "</script>";

  html += "<table id=\"logbookTable\"><thead>";

  String header = "";
  if (file.available()) {
    header = file.readStringUntil('\n');
    html += "<tr>";
    int startIndex = 0;
    int columnIndex = 0;

    // Generate table headers with sorting functionality
    while (startIndex < header.length()) {
      int endIndex = header.indexOf(',', startIndex);
      if (endIndex == -1) endIndex = header.length();
      String column = header.substring(startIndex, endIndex);

      // Add clickable headers for sorting
      html += "<th onclick=\"sortTable(" + String(columnIndex) + ")\">" + column;
      html += "<span class=\"sort-icon\"></span></th>";  // Sorting icon placeholder

      startIndex = endIndex + 1;
      columnIndex++;
    }
    html += "<th></th></tr><thead><tbody>";
  }

  bool hasData = false;
  int piCodeIndex = -1, frequencyIndex = -1;

  // Identify column indices for PI code and Frequency
  int startIndex = 0, columnIndex = 0;
  while (startIndex < header.length()) {
    int endIndex = header.indexOf(',', startIndex);
    if (endIndex == -1) endIndex = header.length();
    String column = header.substring(startIndex, endIndex);

    if (column.equalsIgnoreCase("PI")) piCodeIndex = columnIndex;
    if (column.equalsIgnoreCase("Frequency")) frequencyIndex = columnIndex;

    startIndex = endIndex + 1;
    columnIndex++;
  }

  if (file.available()) hasData = true;

  if (logcounter < 130) {
    // Generate rows
    while (file.available()) {
      String line = file.readStringUntil('\n');
      if (line.length() > 0) {
        html += "<tr>";

        String piCode = "", frequency = "";
        startIndex = 0, columnIndex = 0;

        while (startIndex < line.length()) {
          int endIndex = line.indexOf(',', startIndex);
          if (endIndex == -1) endIndex = line.length();
          String cell = line.substring(startIndex, endIndex);

          // Extract PI code and Frequency
          if (columnIndex == piCodeIndex) piCode = cell;
          if (columnIndex == frequencyIndex) frequency = cell;

          html += "<td>" + cell + "</td>";
          startIndex = endIndex + 1;
          columnIndex++;
        }

        // Remove " MHz" from Frequency
        frequency.replace(" MHz", "");

        // Make row clickable
        html += "<td><a href =\"https://maps.fmdx.org/#qth=&freq=" + frequency + "&findPi=" + piCode + "\"target=\"_blank\">🌐</a></td>";
        html += "</tr>";
      }
    }

    file.close();
  } else {
    html += "<tr><td colspan=\"100%\" style=\"text-align: center; color: red;\">" + String(myLanguage[language][300]) + "</td></tr>";
  }

  if (!hasData) {
    html += "<tr><td colspan=\"100%\" style=\"text-align: center; color: red;\">" + String(myLanguage[language][288]) + "</td></tr>";
  }

  html += "</table>";
  html += "</body></html>";

  webserver.send(200, "text/html", html);
}

void handleDownloadCSV() {
  // Attempt to open the CSV file from SPIFFS in read mode
  fs::File file = SPIFFS.open("/logbook.csv", "r");

  // Check if the file was successfully opened
  if (!file) {
    // If the file could not be opened, send an error response
    webserver.send(500, "text/plain", "Failed to open logbook for download");
    return;  // Exit the function if the file cannot be opened
  }

  // Set the headers to specify that the response will be a CSV file for download
  webserver.sendHeader("Content-Type", "text/csv");  // Set MIME type for CSV files
  webserver.sendHeader("Content-Disposition", "attachment; filename=logbook.csv");  // Suggests the file name for download

  // Stream the CSV file content directly to the browser
  webserver.streamFile(file, "text/csv");

  // Close the file after streaming the content to release resources
  file.close();
}

bool handleCreateNewLogbook() {
  // Check if the file "logbook.csv" already exists
  if (SPIFFS.exists("/logbook.csv")) {
    // If it exists, delete the file
    if (!SPIFFS.remove("/logbook.csv")) {
      // Return false if the file could not be deleted
      return false;
    }
  }

  // Create a new "logbook.csv" file in write mode
  fs::File file = SPIFFS.open("/logbook.csv", "w");

  // Check if the file was successfully created
  if (!file) {
    // Return false if file creation fails
    return false;
  }

  // Write the header to the new CSV file
  String header = "Date,Time,Frequency,PI,Signal,Stereo,TA,TP,PTY,ECC,PS\n";
  file.print(header); // Ensure that the header is written properly

  // Make sure the data is written before closing the file
  file.flush(); // Ensure that everything is written to the file
  file.close(); // Close the file after writing


  logcounter = 0; // Reset logcounter
  EEPROM.writeUInt(EE_UINT16_LOGCOUNTER, logcounter);
  EEPROM.commit();
  // Return true if the function runs without problems
  return true;
}

byte addRowToCSV() {
  // Ensure there is at least 150 bytes of free space in SPIFFS before proceeding
  if (SPIFFS.totalBytes() - SPIFFS.usedBytes() < 150) {
    return 2;  // Return 2 if insufficient free space is available
  }

  // Open the "logbook.csv" file in append mode
  fs::File file = SPIFFS.open("/logbook.csv", "a");

  // Check if the file could not be opened
  if (!file) {
    return 1;  // Return 1 if the file cannot be opened
  }

  // Fetch the current date and time
  char currentDateTime[32] = "-,-";
  String dateTimeString = getCurrentDateTime();
  if (!dateTimeString.isEmpty()) {
    strncpy(currentDateTime, dateTimeString.c_str(), sizeof(currentDateTime) - 1);
  }

  // Prepare the frequency in a formatted string
  int freqInt = (band == BAND_OIRT) ? (int)frequency_OIRT : (int)frequency;
  int adjustedFreq = freqInt + (band != BAND_OIRT ? ConverterSet * 100 : 0);
  char frequencyFormatted[16];
  snprintf(frequencyFormatted, sizeof(frequencyFormatted), "%d.%02d MHz",
           adjustedFreq / 100, adjustedFreq % 100);

  // Calculate signal strength based on the selected unit
  int SStatusPrint = 0;
  if (unit == 0) SStatusPrint = SStatus;  // dBμV
  else if (unit == 1) SStatusPrint = ((SStatus * 100) + 10875) / 100;  // dBf
  else if (unit == 2) SStatusPrint = round((float(SStatus) / 10.0 - 10.0 * log10(75) - 90.0) * 10.0);  // dBm

  char signal[16];
  snprintf(signal, sizeof(signal), "%d.%d %s",
           SStatusPrint / 10, abs(SStatusPrint % 10),
           (unit == 0) ? "dBμV" : (unit == 1) ? "dBf" : "dBm");

  // Replace commas in the station name to avoid CSV conflicts
  char stationName[64] = "";
  strncpy(stationName, radio.rds.stationName.c_str(), sizeof(stationName) - 1);
  for (size_t i = 0; i < strlen(stationName); i++) {
    if (stationName[i] == ',') {
      stationName[i] = ' ';
    }
  }

  // Handle ECC, PTY, TA, TP, and Stereo flag
  char ECC[4] = "--";
  if (radio.rds.hasECC) {
    snprintf(ECC, sizeof(ECC), "%02X", radio.rds.ECC);  // Format ECC as uppercase 2-digit hex
  }

  const char *TA = radio.rds.hasTA ? "•" : " ";
  const char *TP = radio.rds.hasTP ? "•" : " ";
  const char *Stereo = radio.getStereoStatus() ? "•" : " ";
  char pty[4];
  snprintf(pty, sizeof(pty), "%d", radio.rds.stationTypeCode);

  // Extract the first 4 characters of `picode`
  char piCode[5] = "0000";  // Initialize with a default value
  if (strlen(radio.rds.picode) >= 4) {
    strncpy(piCode, radio.rds.picode, 4);  // Copy the first 4 characters
    piCode[4] = '\0';  // Ensure null termination
  }

  // Construct the CSV row data
  char row[256];
  snprintf(row, sizeof(row), "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
           currentDateTime, frequencyFormatted, piCode,
           signal, Stereo, TA, TP, pty, ECC,
           stationName[0] != '\0' ? stationName : "");

  // Write the row to the file and close it
  if (file.print(row)) {
    file.close();  // Successfully wrote to the file
    logcounter++;
    EEPROM.writeUInt(EE_UINT16_LOGCOUNTER, logcounter);
    EEPROM.commit();
    return 0;  // Return 0 to indicate success
  } else {
    file.close();  // Close the file if writing fails
    return 1;  // Return 1 to indicate failure
  }
}

String getCurrentDateTime() {
  // Check if the RTC has been set
  if (!rtcset) {
    return "-,-";  // Return placeholder when the RTC is not set
  }

  // Use the ESP32's time functions to retrieve the current time
  struct tm timeInfo;
  if (!getLocalTime(&timeInfo)) {
    return "-,-";  // Return placeholder if local time is unavailable
  }

  // Adjust timeInfo using the GMT offset
  time_t currentEpoch = mktime(&timeInfo);  // Convert struct tm to time_t format

  // Calculate GMT offset
  currentEpoch += (NTPupdated ? NTPoffset * 3600 : radio.rds.offset); // Apply GMT offset if NTPupdated, else RDS offset

  // Apply DST adjustment if NTPupdated and autoDST are true
  if (NTPupdated && autoDST) {
    struct tm tempTimeInfo;
    localtime_r(&currentEpoch, &tempTimeInfo); // Convert to struct tm for DST calculation
    if (isDST(mktime(&tempTimeInfo))) { // Check if DST is in effect
      currentEpoch += 3600; // Add 1-hour DST offset
    }
  }

  // Convert adjusted time back to struct tm format
  localtime_r(&currentEpoch, &timeInfo);

  // Buffer for formatted date-time string
  char buf[20];

  if (clockampm) {
    // USA format: MM/DD/YYYY, HH:MM:SS AM/PM
    strftime(buf, sizeof(buf), "%m/%d/%Y", &timeInfo);  // Format as MM/DD/YYYY

    // Format time in 12-hour format with AM/PM
    int hour = timeInfo.tm_hour;
    String ampm = (hour >= 12) ? "PM" : "AM";  // Determine AM or PM
    if (hour == 0) hour = 12;  // Convert 0 hour to 12 AM
    else if (hour > 12) hour -= 12;  // Convert to 12-hour format for PM

    String timeWithAMPM = String(hour) + ":" + (timeInfo.tm_min < 10 ? "0" : "") + String(timeInfo.tm_min) + ":" + (timeInfo.tm_sec < 10 ? "0" : "") + String(timeInfo.tm_sec) + " " + ampm;

    // Return the final formatted date and time for the USA region
    return String(buf) + "," + timeWithAMPM;
  } else {
    // European format: DD-MM-YYYY, HH:MM:SS
    strftime(buf, sizeof(buf), "%d-%m-%Y", &timeInfo);  // Format as DD-MM-YYYY
    String timeEuropean = String(timeInfo.tm_hour) + ":" + (timeInfo.tm_min < 10 ? "0" : "") + String(timeInfo.tm_min) + ":" + (timeInfo.tm_sec < 10 ? "0" : "") + String(timeInfo.tm_sec); // Format time with leading zero if needed
    return String(buf) + "," + timeEuropean;
  }
}

bool isDST(time_t t) {
  struct tm timeInfo;
  localtime_r(&t, &timeInfo); // Convert time_t to struct tm

  int month = timeInfo.tm_mon + 1; // tm_mon is 0-based, so add 1
  int day = timeInfo.tm_mday;     // tm_mday is the day of the month
  int hour = timeInfo.tm_hour;    // tm_hour is the hour of the day
  int weekday = timeInfo.tm_wday; // tm_wday is the day of the week (0 = Sunday)

  // DST starts last Sunday in March at 2:00 AM
  if (month == 3) {
    int lastSunday = 31 - ((weekday + 31 - day) % 7);
    if (day > lastSunday || (day == lastSunday && hour >= 2)) {
      return true;
    }
  }

  // DST ends last Sunday in October at 3:00 AM
  if (month == 10) {
    int lastSunday = 31 - ((weekday + 31 - day) % 7);
    if (day < lastSunday || (day == lastSunday && hour < 3)) {
      return false;
    }
  }

  // DST is active from April to September
  if (month > 3 && month < 10) {
    return true;
  }

  return false;
}

void handleLogo() {
  fs::File file = SPIFFS.open("/logo.png", "r");
  if (!file) {
    webserver.send(404, "text/plain", "Logo not found");
    return;
  }
  webserver.streamFile(file, "image/png");
  file.close();
}

void printLogbookCSV() {
  // Attempt to open the CSV file stored in SPIFFS
  fs::File file = SPIFFS.open("/logbook.csv", "r");

  // Check if the file was successfully opened
  if (!file) {
    Serial.println("Failed to open logbook!");
    return;
  }

  // Print a message indicating the start of the file content
  Serial.println("===== Start of logbook.csv =====");

  // Read and print the contents of the file line by line
  while (file.available()) {
    String line = file.readStringUntil('\n');  // Read one line at a time
    Serial.println(line);  // Print the line to the Serial Monitor
  }

  // Close the file after reading
  file.close();

  // Print a message indicating the end of the file content
  Serial.println("===== End of logbook.csv =====");
}