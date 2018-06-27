


#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "cold-storage-46213.firebaseio.com"
#define FIREBASE_AUTH "2sIPzwlSwxKDeXp6IwU5nZ8nB8B13vDmhUBO89iA"
#define WIFI_SSID "FIRST"
#define WIFI_PASSWORD "1234567890"

//------------------------------
const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data
float temperature= 0;
float hum=0;
boolean newData = false;

void setup() {
  Serial.begin(115200);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

void loop() {
  int i = 0;
  while (i == 0) {
    while (Serial.available() > 0) {

      int t = Serial.read();
      if(t==46)
      continue;
      if (t == 37) {
        i = 3;
        Firebase.pushFloat("Humidity", hum  );
        hum = 0;
        break;
      }
      hum *= 10;
      hum += (t - 48);
    }
  }
  i = 2;

  while (i == 2) {

    while (Serial.available() > 0) {

      int t = Serial.read();
      if(t==46)
      continue;
      if (t == 44) {
        i = 3;
        Firebase.pushFloat("Temperature", temperature/100);
        temperature = 0;
        break;
      }
      temperature *= 10;
      temperature += (t - 48);

    }



}

}




















