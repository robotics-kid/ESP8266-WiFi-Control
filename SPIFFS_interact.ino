#pragma once
#include <FS.h>
#include "Settings.h"

File file;

// Read from SPIFFS: read string ReadSPIFFS(file name)
void ReadSPIFFS()
{

  memset(recv_str, '\0', sizeof(char) * argsLen);
  file  = SPIFFS.open(SPIFFS_file_name, "r"); // Openning file from SPIFFS

  if (!file) // Cheking if file opened normaly
  {
    Serial.println("Failed to open file for reading");
    strcpy(recv_str, "-1");
  }

  
  if (file.available()) // Open while() loop while file is available
  {
    file.readString().toCharArray(recv_str, argsLen); // Read from file unti  l \n while file is available
  }


  file.close();
}

// Write string to SPIFFS: writed sucesefuly or not WriteSPIFFS(file name, writting string)
void WriteSPIFFS(char recv_str[])
{

  file = SPIFFS.open(SPIFFS_file_name, "w"); // Openning file from SPIFFS

  if (!file) // Cheking if file opened normaly
  {
    Serial.println("Error opening file for writing");
    return;
  }
  uint16_t i = strlen(recv_str);
  uint16_t bytesWritten = file.write(recv_str, argsLen);

  if (bytesWritten == 0) // Check if written sucesseful
  {
    Serial.println("File write failed");
    file.close();
    return;
  }

  file.close();
}
