/*This is the code to be run on ESP8266, it receive sensor readings from xiaoEsp32S3 through wifi and manipulate them and display over Serial Monitor so that these values can be used by our actuator, i.e, Software Ableton*/

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char *ssid = "XIAO_ESP32S3";
const char *password = "password";
#define color_sensor 44
int Finalcolour = 0;

IPAddress serverIP(192, 168, 4, 1); // IP address of the web server
const int serverPort = 80; // HTTP port

void setup() {
  pinMode(color_sensor, OUTPUT);
  Serial.begin(115200);
  delay(10);
  StaticJsonDocument<200> doc;
  
  // Connect to Wi-Fi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  digitalWrite(color_sensor, LOW);
}

void loop() {
  int tone ;
  int colour;
  

  // Use WiFiClient class to create TCP connections
  WiFiClient client;

  // Make a HTTP request to a specific IP address and port
  if (client.connect(serverIP, serverPort)) {
    client.print("GET / HTTP/1.1\r\n");
    client.print("Host: "); // The HTTP Host header is optional when using an
    // IP address
    client.print(serverIP);
    client.print("\r\n");
    client.print("Connection: close\r\n\r\n");
  } else {
    Serial.println("Connection failed");
  }

  // Read the response
  while (client.connected()) {
    if (client.available()) {
      String line = client.readStringUntil('\r');
      
      // Serial.print(line);

      String data = line;

int accx,accy, accz, rf, gf, bf;

// Find the position of ":" after "accx" and extract the value after it
int accx_index = data.indexOf(":") + 1;
accx = abs(data.substring(accx_index, data.indexOf(",", accx_index)).toInt());

int accy_index = data.indexOf(":") + 2;
accy = abs(data.substring(accy_index, data.indexOf(",", accy_index)).toInt());

int accz_index = data.indexOf(":") + 3;
accz = abs(data.substring(accz_index, data.indexOf(",", accz_index)).toInt());

// Find the position of ":" after "rf" and extract the value after it
int rf_index = data.indexOf("rf") + 4;
rf = data.substring(rf_index, data.indexOf(",", rf_index)).toInt();

// Find the position of ":" after "gf" and extract the value after it
int gf_index = data.indexOf("gf") + 5;
gf = data.substring(gf_index, data.indexOf(",", gf_index)).toInt();

// Find the position of ":" after "bf" and extract the value after it
int bf_index = data.indexOf("bf") + 6;
bf = data.substring(bf_index, data.indexOf("}", bf_index)).toInt();
// Serial.println(accx);
// Serial.println(accy);
// Serial.println(accz);
// Serial.println(rf);
// Serial.println(gf);
// Serial.println(bf);

// Now you have the values stored in integers: accx, rf, gf, and bf

float tone = (abs(accx) + abs(accz))/3;

Serial.print("tone: ");
Serial.print(tone);
Serial.print("\n");

 // Classify color based on RGB values
 
 if (rf < 30 && gf < 30 && bf < 30) {
    colour=0;
  }  else {
    // Determine the least value color
    if (rf <= gf && rf <= bf) {
      colour=1;
    } else if (gf <= rf && gf <= bf) {
      colour=2;
    } else {
      colour=3;
    }
  }


 if(digitalRead(color_sensor) == HIGH)
 {Finalcolour=colour;}
 Serial.print("color: ");
 Serial.print(Finalcolour);

      // Serial.print(\n);
    }
  }

  // Close the connection
  client.stop();

  // Wait for some time before making the next request
  // delay(500);
}