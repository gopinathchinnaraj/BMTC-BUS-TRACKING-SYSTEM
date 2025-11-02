#include <WiFi.h>
#include <TinyGPSPlus.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// -------------------- CONFIGURATION --------------------
const char* WIFI_SSID = "MyGPS";
const char* WIFI_PASSWORD = "MyGPSPassword";
const char* GOOGLE_SCRIPT_URL = "";

// LCD and GPS setup
LiquidCrystal_I2C lcd(0x27, 16, 2);
HardwareSerial gpsSerial(2);
TinyGPSPlus gps;

// -------------------- SETUP FUNCTIONS --------------------
void connectToWiFi() {
  Serial.println("🔍 Scanning WiFi networks...");
  int n = WiFi.scanNetworks();
  for (int i = 0; i < n; ++i) {
    Serial.printf("%d: %s\n", i + 1, WiFi.SSID(i).c_str());
  }

  Serial.printf("🔗 Connecting to %s ...", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 20000) {
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ WiFi Connected!");
    lcd.clear();
    lcd.print("WiFi Connected");
  } else {
    Serial.println("\n❌ WiFi Failed!");
    lcd.clear();
    lcd.print("WiFi Failed");
  }

  delay(1500);
  lcd.clear();
}

void initLCD() {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
}

void initGPS() {
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);
  Serial.println("✅ GPS Serial Started (RX=16, TX=17)");
}


void sendToGoogleSheet(float lat, float lon) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("⚠️ WiFi Disconnected, retrying...");
    connectToWiFi();
    return;
  }

  HTTPClient http;
  String url = String(GOOGLE_SCRIPT_URL) + "?lat=" + String(lat, 6) + "&lon=" + String(lon, 6);

  Serial.println("📤 Sending Data: " + url);
  http.begin(url);
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    Serial.printf("✅ Sent Successfully [%d]\n", httpResponseCode);
  } else {
    Serial.printf("❌ HTTP Error: %s\n", http.errorToString(httpResponseCode).c_str());
  }

  http.end();
}

// -------------------- MAIN LOOP --------------------
void setup() {
  Serial.begin(115200);
  initLCD();
  initGPS();
  connectToWiFi();
  Serial.println("🚀 System Ready!");
}

void loop() {
  // Continuously read GPS data
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  // When GPS gives new location data
  if (gps.location.isUpdated()) {
    float lat = gps.location.lat();
    float lon = gps.location.lng();

    Serial.printf("📍 Latitude: %.6f | Longitude: %.6f\n", lat, lon);
    displayLocation(lat, lon);
    sendToGoogleSheet(lat, lon);
    delay(30000);  // send every 30 seconds
  }
}