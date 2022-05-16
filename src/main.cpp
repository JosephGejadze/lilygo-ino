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
void mqtt_reconnect();


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

  if(!WiFi.isConnected()) {
    Serial.println("Attempting to reconnect to WiFi");
    WiFi.reconnect();
  }

  if(!client.connected()) {
    mqtt_reconnect();
  }

  actuators.pump->auto_operate(sensors.get_soil_moisture());
  actuators.humi->auto_operate(sensors.get_air_humidity());
  actuators.vent_fan->auto_operate(sensors.get_co2_content());
  actuators.light->auto_operate();
  actuators.circ_fan->toggle();


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

void mqtt_reconnect() {
  Serial.print("Attempting MQTT connection...");
  if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD)) {
    Serial.println("connected");
  } else {
    Serial.print("failed, rc=");
    Serial.print(client.state());
  }
}


void callback(char* topic, byte* bytes, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0; i<length; i++) {
    Serial.print((char)bytes[i]);
  }
  Serial.println();

  char order_code[8] = {};
  char order_payload[8] = {};

  int delimiter_index = -1;


  // Parse the order into order code and payload
  for(int i=0; i<length; i++) {
    if(bytes[i] == '_') {
      delimiter_index = i;
    } else if(delimiter_index < 0 ) {
      order_code[i] = bytes[i];
    } else {
      order_payload[i - delimiter_index - 1] = bytes[i];
    }
  }

  Serial.print("order_code: ");
  Serial.println(atoi(order_code));
  Serial.print("order_payload: ");
  Serial.println(atoi(order_payload));

  ex_status status = execute_comm_order(atoi(order_code), atoi(order_payload));
  if(status == EX_SUCCESS) {
    Serial.print("Executed order ");
    for (int i=0; i<length; i++) {
      Serial.print((char)bytes[i]);
    }
    Serial.println();
  } else {
    Serial.print("Could not execute order ");
    for (int i=0; i<length; i++) {
      Serial.print((char)bytes[i]);
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

