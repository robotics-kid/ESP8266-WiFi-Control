#include "ArduinoJson.h"
#include "FS.h"

void setup() {

  Serial.begin(115200);
  Serial.println();

  bool success = SPIFFS.begin();

  if (success) {
    Serial.println("File system mounted with success");
  } else {
    Serial.println("Error mounting the file system");
    return;
  }

}

void loop() {

  File file2 = SPIFFS.open("/file.json", "r");

  if (!file2) {
    Serial.println("Failed to open file for reading");
    return;
  }
  /*
    Serial.println("File Content:");
    String recv;
    while (file2.available()) {

      recv += file2.readStringUntil('\n');


    }
    Serial.println(recv);

  */

  Serial.println("Parsing start: ");

  //char json[] = "{ \"company\": \"myComp\", \"contacts\": { \"phone\": \"25123682\", \"email\": \"robotics-kid@yandex.ru\" }, \"values\": [12, 34, 45, 56] }"; //Original message

  DynamicJsonDocument doc(768);                    //Memory pool
  DeserializationError error = deserializeJson(doc, file2);

  if (error) {   //Check for errors in parsing

    Serial.print("deserializeJson() failed with code ");
    Serial.println(error.c_str());
    delay(5000);
    return;

  }


  JsonObject leds_settings = doc["leds_settings"];
  int leds_settings_data_pin = leds_settings["data_pin"]; // 6

  Serial.println(leds_settings_data_pin);


  Serial.println();
  delay(5000);
  file2.close();
}
