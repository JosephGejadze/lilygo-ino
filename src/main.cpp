#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <mhz14a.h>
#include <SoftwareSerial.h>
#include <sensors.h>
#include <pump.h>
#include <fan.h>
#include <light.h>
#include <humi.h>
#include <PubSubClient.h>
#include "config.h"
#include "actuators/actuators.h"
#include "comm/comm.h"

// WiFi & MQTT clients
WiFiClient wifiClient;
PubSubClient client(wifiClient);
// Sensors
Adafruit_BME280 bme;
SoftwareSerial SerialCom(SS_RX, SS_TX);
MHZ14A mhz(&SerialCom);
Sensors sensors = Sensors();

// Actuators
actuators_t actuators;


void setup_wifi();
void setup_mqtt();
void printValues();
void gather_sensor_values();
void print_sensor_values();


void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Connect to WiFi
  setup_wifi();
  // Connect to broker
  setup_mqtt();

  // Power up sensors
  pinMode(POWER_CTRL, OUTPUT);
  digitalWrite(POWER_CTRL, 1);
  delay(1000);
  
  // Begin I2C communication
  Wire.begin(I2C_SDA, I2C_SCL);

  // Begin communication with BME280 sensor
  if(bme.begin(BME280_ADDRESS, &Wire)) {
    Serial.print("I2C device found at address 0x"); 
    Serial.println(BME280_ADDRESS, 16); 
  }
  else {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
  }

  // Initialize mhz14a sensor
  mhz.init();

  // Initialize actuators
  actuators = get_actuators();
  actuators.pump->init();
  actuators.humi->init();
  actuators.circ_fan->init();
  actuators.vent_fan->init();
  actuators.light->init();

}


void loop() { 
  
  gather_sensor_values();
  print_sensor_values();

  actuators.pump->auto_operate(sensors.get_soil_moisture());

  client.publish(MQTT_TOPIC, sensors.get_formatted_message());
  client.loop();

  delay(5000);
}

// utils

void setup_wifi() {

  WiFi.mode(WIFI_MODE_STA);
  Serial.print("Connect SSID: ");
  Serial.print(WIFI_SSID);
  Serial.print(" Password: ");
  Serial.println(WIFI_PASSWORD);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.println("WiFi connect fail!");
      delay(3000);
      esp_restart();
  }

  Serial.print("WiFi connect success! IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  // while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic","hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  // }
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0; i<length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  ex_status status = execute_comm_order((char*)payload);
  if(status == EX_SUCCESS) {
    Serial.print("Executed order ");
    for (int i=0; i<length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
  } else {
    Serial.print("Could not execute order ");
    for (int i=0; i<length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
  }
  Serial.println();
}

void setup_mqtt() {
  client.setServer(MQTT_IP, MQTT_PORT);
  client.setCallback(callback);
  
  while (!client.connected()) {
    // Attempt to connect

    if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD)) {
      client.subscribe("0");
      Serial.println("Sucessfully Connected to MQTT Broker.");
    }
    else {
      Serial.print("Failed with state ");
      Serial.print(client.state());
      Serial.println("");
      delay(2000);
    }
  }
}



void gather_sensor_values(){
  int temp;
  temp = bme.readTemperature();
  sensors.set_temperature(temp);

  temp = bme.readHumidity();
  sensors.set_air_humidity(temp);

  temp = analogRead(SOIL_PIN);
  temp = map(temp, SOIL_MIN, SOIL_MAX, 0, 100);
  sensors.set_soil_moisture(temp);

  temp = mhz.getCO2();
  sensors.set_co2_content(temp);
}

void print_sensor_values(){
  Serial.print("Temperature = ");
  Serial.print(sensors.get_temperature());
  Serial.println(" *C");

  Serial.print("Humidity = ");
  Serial.print(sensors.get_air_humidity());
  Serial.println(" %");

  Serial.print("Soil moisture = ");
  Serial.print(sensors.get_soil_moisture());
  Serial.println("%");

  Serial.print("CO2 = ");
  Serial.print(sensors.get_co2_content());
  Serial.println("ppm");

  Serial.println();
}

