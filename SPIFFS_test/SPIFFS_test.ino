#include <FS.h>

void setup() {

  Serial.begin(115200);
  delay(1000);
  Serial.println();

  bool success = SPIFFS.begin();

  if (success) {
    Serial.println("File system mounted with success");
  } else {
    Serial.println("Error mounting the file system");
    return;
  }
  char writeS[] = "FoViBalTLight;EFF:2;WHT:500";
  Write(writeS);
  Read();
}

void loop() {}

String Read() {

  File file2 = SPIFFS.open("/file.txt", "r");

  if (!file2) {
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.println("File Content:");
  String recv;
  while (file2.available()) {

    Serial.write(file2.read());
    
    
  }

  file2.close();

}

void Write(const char* writeS) {
  File file = SPIFFS.open("/file.txt", "w");

  if (!file) {
    Serial.println("Error opening file for writing");
    return;
  }

  //int bytesWritten = file.print("FoViBalTLight;EFF:1;RED:255;GRN:0;BLU:0;WHT:0");
  int bytesWritten = file.print(writeS);

  if (bytesWritten == 0) {
    Serial.println("File write failed");
    return;
  }

  file.close();
}
