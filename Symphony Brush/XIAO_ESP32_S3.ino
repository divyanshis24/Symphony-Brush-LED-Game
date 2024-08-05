/*this is the code to be run on XiaoESP32S3, it takes the reading of the sensors, and send them using json to Nodemcu ESP8266*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include "MPU6050.h"
#include "Wire.h"
#include <ArduinoJson.h>

#define LED_BUILTIN 2
#define FREQUENCY_HZ        50
#define INTERVAL_MS         (1000 / (FREQUENCY_HZ + 1))
#define ACC_RANGE           1 // 0: -/+2G; 1: +/-4G

int maxAcX = -100000; // Initialize with a very small value
int minAcX = 100000; // Initialize with a very large value

// Convert factor g to m/s2 ==> [-32768, +32767] ==> [-2g, +2g]
#define CONVERT_G_TO_MS2    (9.81/(16384.0/(1.+ACC_RANGE))) 

#define S0 1
#define S1 2
#define S2 3
#define S3 4
#define sensorOut 43
#define color_sensor 44

// Stores frequency read by the photodiodes for the color sensor
int redFrequencyColor = 0;
int greenFrequencyColor = 0;
int blueFrequencyColor = 0;


// MPU6050 variables
MPU6050 imu;
int16_t ax, ay, az;

const char *ssid = "XIAO_ESP32S3";
const char *password = "password";

WiFiServer server(80);

unsigned long last_interval_ms = 0; // Declaration of last_interval_ms variable

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");

  Wire.begin();
  imu.initialize();
  delay(10);
  imu.setXAccelOffset(-4732);
  imu.setYAccelOffset(4703);
  imu.setZAccelOffset(8867);
  imu.setXGyroOffset(61);
  imu.setYGyroOffset(-73);
  imu.setZGyroOffset(35);
  imu.setFullScaleAccelRange(ACC_RANGE);

  // Setting the outputs for the color sensor
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(color_sensor, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20% for color sensor
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  digitalWrite(color_sensor, LOW);
}

void loop() {
  // Color Sensor Part
  // Setting RED (R) filtered photodiodes to be read
  if(digitalRead(color_sensor) == HIGH)
  {
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // Reading the output frequency for color sensor
  redFrequencyColor = pulseIn(sensorOut, LOW);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency for color sensor
  greenFrequencyColor = pulseIn(sensorOut, LOW);

  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency for color sensor
  blueFrequencyColor = pulseIn(sensorOut, LOW);
  }
  
  // IMU Sensor Part
  if (millis() > last_interval_ms + INTERVAL_MS) {
    last_interval_ms = millis();
    
    imu.getAcceleration(&ax, &ay, &az);
    

    float ax_m_s2 = ax * CONVERT_G_TO_MS2;
    float ay_m_s2 = ay * CONVERT_G_TO_MS2;
    float az_m_s2 = az * CONVERT_G_TO_MS2;

    // Print IMU data to serial
    Serial.print("Acceleration X: ");
    Serial.print(ax_m_s2); 
    Serial.print("\t");
    Serial.print("Acceleration Y: ");
    Serial.print(ay_m_s2); 
    Serial.print("\t");
    Serial.print("Acceleration Z: ");
    Serial.println(az_m_s2); 
  }

  // Serve webpage and upload data
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            // client.println("HTTP/1.1 200 OK");
            // client.println("Content-type:text/json");
            // client.println();
            // client.println("<!DOCTYPE html><html><head>");
            // client.println("<meta http-equiv=\"refresh\" content=\"0.5\">"); // Refresh every 5 seconds
            // client.println("<script>");
            // client.println("function refreshData() {");
            // client.println("var xhttp = new XMLHttpRequest();");
            // client.println("xhttp.onreadystatechange = function() {");
            // client.println("if (this.readyState == 4 && this.status == 200) {");
            // client.println("document.getElementById(\"data\").innerHTML = this.responseText;");
            // client.println("}");
            // client.println("};");
            // client.println("xhttp.open(\"GET\", \"/data\", true);");
            // client.println("xhttp.send();");
            // client.println("}");
            // client.println("setInterval(refreshData, 500);"); // Refresh every 5 seconds
            // client.println("</script>");
            // client.println("</head><body>");
            // client.println("Click <a href=\"/H\">here</a> to turn ON the LED.<br>");
            // client.println("Click <a href=\"/L\">here</a> to turn OFF the LED.<br>");
            // client.println("IMU Data:<br>");
            // client.println("Acceleration X: " + String(ax) + "<br>");
            // client.println("Acceleration Y: " + String(ay) + "<br>");
            // client.println("Acceleration Z: " + String(az) + "<br>");
            // client.println("<h1>Color Sensor Data:</h1>");
            // client.println("Red Frequency: " + String(redFrequencyColor) + "<br>");
            // client.println("Green Frequency: " + String(greenFrequencyColor) + "<br>");
            // client.println("Blue Frequency: " + String(blueFrequencyColor) + "<br>");
            // client.println("</body></html>");
            StaticJsonDocument<200> doc;
            doc["accx"]=ax;
            doc["accy"]=ay;
            doc["accz"]=az;
            doc["rf"]=redFrequencyColor;
            doc["gf"]=greenFrequencyColor;
            doc["bf"]=blueFrequencyColor;
            serializeJson(doc,client);
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
}