#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

String apiKey = "BRHOAUKHTTBHDA8Y";

#define SENSOR_PIN 34
#define LED_PIN 2

void setup() {

  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi Connected");
}

void loop() {

  int moisture = analogRead(SENSOR_PIN);

  Serial.print("Moisture: ");
  Serial.println(moisture);

  if (moisture > 3000) {

    digitalWrite(LED_PIN, HIGH);

    Serial.println("Soil Dry");

  } else {

    digitalWrite(LED_PIN, LOW);

    Serial.println("Soil Wet");
  }

  uploadData(moisture);

  delay(15000);
}

void uploadData(int value) {

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    String url =
    "http://api.thingspeak.com/update?api_key=" +
    apiKey +
    "&field1=" +
    String(value);

    http.begin(url);

    int code = http.GET();

    Serial.println(code);

    http.end();
  }
}