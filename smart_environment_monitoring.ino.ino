#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ------------------- CONFIG -------------------
#define DHTPIN 2
#define DHTTYPE DHT11

#define MQ135_PIN A0
#define LED_PIN 7
#define BUZZER_PIN 8

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// ------------------- OBJECTS -------------------
DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ------------------- GLOBAL VARIABLES -------------------
float temperature = 0;
float humidity = 0;
int gasValue = 0;
int gasThreshold = 700;

// Filtering
int gasBuffer[10];
int bufferIndex = 0;

// Timing (non-blocking)
unsigned long previousMillis = 0;
const long interval = 2000;  // 2 sec update

// ------------------- SETUP -------------------
void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  dht.begin();

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    while(true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  // Initialize buffer
  for(int i = 0; i < 10; i++) {
    gasBuffer[i] = 0;
  }
}

// ------------------- LOOP -------------------
void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    readSensors();
    processData();
    displayData();
    alertSystem();
  }
}

// ------------------- FUNCTIONS -------------------

// 🔹 Read Sensors
void readSensors() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  gasValue = analogRead(MQ135_PIN);

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" C | Humidity: ");
  Serial.print(humidity);
  Serial.print(" % | Gas: ");
  Serial.println(gasValue);
}

// 🔹 Process Data (Filtering)
void processData() {
  gasBuffer[bufferIndex] = gasValue;
  bufferIndex = (bufferIndex + 1) % 10;

  int sum = 0;
  for(int i = 0; i < 10; i++) {
    sum += gasBuffer[i];
  }

  gasValue = sum / 10;  // Moving average
}

// 🔹 Display Data
void displayData() {
  display.clearDisplay();

  display.setCursor(0,0);
  display.print("Temp: ");
  display.print(temperature);
  display.println(" C");

  display.print("Humidity: ");
  display.print(humidity);
  display.println(" %");

  display.print("Gas: ");
  display.println(gasValue);

  if(gasValue > gasThreshold) {
    display.println("ALERT: BAD AIR!");
  } else {
    display.println("Air Quality OK");
  }

  display.display();
}

// 🔹 Alert System
void alertSystem() {
  if(gasValue > gasThreshold) {
    digitalWrite(LED_PIN, HIGH);

    // Beep pattern instead of continuous
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);

  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }
}