# 🚌 IoT-Based BMTC Bus Tracking System

A real-time IoT-enabled bus tracking solution designed to monitor Bangalore Metropolitan Transport Corporation (BMTC) buses. The system uses GPS + GSM modules integrated with Arduino to send live bus coordinates to an online Excel/Google Sheet Script, which then updates and displays the live bus route on a map interface.

Passengers can view the bus location in real time, improving commuter convenience and reducing waiting time uncertainty.

![Project Overview](images/project-overview.png)
*Figure 1: Overall System Overview showing data flow from bus to end-user*

## 📌 Project Features

✅ Real-time bus location tracking  
✅ Arduino-based GPS + GSM data transmission  
✅ Live updates to Google Sheet/Excel Script  
✅ Public tracking map for passengers  
✅ Efficient & scalable for public transport fleets  

## 🛠️ Tech Stack

| Component | Description |
|-----------|-------------|
| Arduino | Microcontroller unit |
| GPS Module | Captures live bus coordinates |
| GSM Module | Sends location via cellular network |
| Open Maps API | Visual map display |
| Excel / Google Script | Stores + updates live location |

## 🔧 Hardware Components

- Arduino UNO / Nano
- GPS Module (NEO-6M)
- GSM Module (SIM800L / SIM900)
- Breadboard & jumper wires
- Power supply & SIM card

![Hardware Setup](images/hardware-setup.jpg)
*Figure 2: Hardware Components and Circuit Connection*

## 📊 System Architecture

![System Architecture](images/system-architecture.png)
*Figure 3: Detailed System Architecture with Data Flow*

## 🚀 Installation & Setup

### Hardware Setup
1. Connect GPS module to Arduino
2. Connect GSM module to Arduino
3. Assemble the circuit as per schematic
4. Insert active SIM card into GSM module

### Software Setup
```arduino
// Sample code snippet
#include <SoftwareSerial.h>
SoftwareSerial gps(10, 11); // RX, TX

void setup() {
  Serial.begin(9600);
  gps.begin(9600);
}
