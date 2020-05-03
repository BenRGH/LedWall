#include <WiFi.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>
#include <FastLED.h>
#include <analogWrite.h>

// ------------------------------ Wifi & MQTT stuff -------------------------------
const char* ssid = "";
const char* password = "";
IPAddress local_IP(192, 168, 0, 111);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
const char* mqtt_server = "192.168.0.26";
const char* mqtt_username = "";
const char* mqtt_password = "";
const int mqtt_port = 1883;
const char* ctrlTopic = "home/volume";

// -------------------------------- FastLED stuff --------------------------------
#define NUM_LEDS 150
#define DATA_PIN 5
#define WIFI_LED_PIN 4
#define BRIGHTNESSLIMIT          96
#define FRAMES_PER_SECOND  120
byte red = 0;
byte green = 0;
byte blue = 0;
byte brightness = 255;
CRGB leds[NUM_LEDS];
uint8_t thisHue = 0; // Starting hue value.
uint8_t deltaHue = 10; // hue change
uint8_t BeatsPerMinute = 120;

// ----------------------------------- Globals -----------------------------------
uint8_t gHue = 0;
int gCtrl[5] = {255,255,255,255,255}; // Brightness, Red, Green, Blue, Mode
enum effects {SOLID, RAINBOW, BPM};
effects effect = RAINBOW;


WiFiClient espClient;
PubSubClient client(espClient);


void setup() { 
  Serial.begin(115200);

  pinMode(WIFI_LED_PIN, OUTPUT);

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESSLIMIT);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 9500);

  setupWifi(); // Connects to wifi
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  
  Serial.println("Ready");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}


void loop() { 
  if (!client.connected()) {
    reconnect();
  }

  if (WiFi.status() != WL_CONNECTED) {
    delay(1);
    Serial.print("WIFI Disconnected. Attempting reconnection.");
    setupWifi();
    return;
  }

  client.loop();

  switch (effect) {
    case SOLID:
      solidEffect();
      break;
      
    case RAINBOW:
      rainbowEffect();
      break;
      
    case BPM:
      bpmEffect();
      break;
  }
  
  showLeds();
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
}
