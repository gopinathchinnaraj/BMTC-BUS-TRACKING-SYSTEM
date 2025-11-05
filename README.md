🚌 IoT-Based BMTC Bus Tracking System

A real-time IoT-enabled bus tracking solution designed to monitor Bangalore Metropolitan Transport Corporation (BMTC) buses. The system uses GPS + GSM modules integrated with Arduino to send live bus coordinates to an online Excel/Google Sheet Script, which then updates and displays the live bus route on a map interface.

Passengers can view the bus location in real time, improving commuter convenience and reducing waiting time uncertainty.

https://images/system_architecture.png
Overall system architecture and data flow diagram
📌 Project Features

✅ Real-time bus location tracking - Live GPS coordinates updated every 30 seconds
✅ Arduino-based GPS + GSM data transmission - Reliable hardware data collection
✅ Live updates to Google Sheet/Excel Script - Cloud-based data storage
✅ Public tracking map for passengers - User-friendly web interface
✅ Efficient & scalable for public transport fleets - Supports multiple buses simultaneously
🛠️ Tech Stack
Component	Description
Arduino Uno	Microcontroller unit for data processing
GPS Module (NEO-6M)	Captures live bus coordinates with satellite precision
GSM Module (SIM800L)	Sends location data via cellular network
Google Apps Script	Cloud script for data handling and API management
Google Sheets	Real-time database for location storage
Leaflet.js / OpenStreetMap	Visual map display for tracking interface
HTML/CSS/JavaScript	Frontend web interface for passengers
📊 System Overview
Hardware Setup

https://images/arduino_gps_gsm_setup.png
Arduino Uno with GPS and GSM modules connection diagram
Data Flow

https://images/data_flow_diagram.png
End-to-end data transmission from bus to passenger interface
Live Tracking Interface

https://images/live_tracking_map.png
Real-time bus tracking map showing current bus locations
🔧 Hardware Components
Component	Specification	Purpose
Arduino Uno	ATmega328P Microcontroller	Main processing unit
NEO-6M GPS Module	50 channels, -161 dBm sensitivity	Location coordinates
SIM800L GSM Module	Quad-band 850/900/1800/1900 MHz	Cellular data transmission
12V Power Supply	Vehicle battery compatible	Bus power integration
Antennas	GPS & GSM external antennas	Signal strength optimization
🚀 Installation & Setup
Hardware Setup
cpp

// Arduino Pin Configuration
#define GPS_RX_PIN 4
#define GPS_TX_PIN 3
#define GSM_RX_PIN 7
#define GSM_TX_PIN 8
#define POWER_PIN 9

Software Requirements
bash

# Required Libraries
Arduino IDE 2.0+
TinyGPS++ Library
SoftwareSerial Library
SIM800L Library

Google Apps Script Setup
javascript

function doPost(e) {
  var sheet = SpreadsheetApp.openById('SHEET_ID').getActiveSheet();
  var data = JSON.parse(e.postData.contents);
  sheet.appendRow([new Date(), data.busId, data.lat, data.lng, data.speed]);
  return ContentService.createTextOutput("Success");
}

