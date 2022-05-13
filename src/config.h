// Connection macros
#define WIFI_SSID               "e.chm"     //"IKOIKO"
#define WIFI_PASSWORD           "qeti7777"  //"irinka2005"
#define MQTT_IP                 "167.99.217.27"
#define MQTT_PORT               (3004)
#define MQTT_CLIENT_ID          "100"
#define MQTT_TOPIC              "0"
#define MQTT_USER               ""
#define MQTT_PASSWORD           ""

// Pin assignments
#define I2C_SDA                 (25)
#define I2C_SCL                 (26)
#define POWER_CTRL              (4)
#define SALT_PIN                (34)    // not used
#define SOIL_PIN                (32)
#define SS_RX                   (13)
#define SS_TX                   (12)
#define PUMP_PIN                (19)
#define CIRC_PIN                (15)
#define HUMID_POWER             (27)
#define HUMID_EN                (14)
#define VENT_PIN                (23)
#define LIGHT_PIN               (17)
#define FREE_PIN_5              (5)
// pins 36-39 don't work :(

// Constants
#define SOIL_MIN                (3562)
#define SOIL_MAX                (1420)

// Thresholds
#define SOIL_THRESHOLD          (40)