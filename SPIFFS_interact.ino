#pragma once
#include <FS.h>
#include "Settings.h"
File file;
int bytesWritten;

// Read from SPIFFS: read string ReadSPIFFS(file name)
void ReadSPIFFS()
{
  
  file  = SPIFFS.open(SPIFFS_file_name, "r"); // Openning file from SPIFFS

  if (!file) // Cheking if file opened normaly
  {
    Serial.println("Failed to open file for reading");
    recv_str =  "-1";
  }

  while (file.available()) // Open while() loop while file is available
  {
    recv_str = file.readStringUntil('!'); // Read from file unti  l \n while file is available
  }

  file.close();
}

// Write string to SPIFFS: writed sucesefuly or not WriteSPIFFS(file name, writting string)
void WriteSPIFFS()
{
  file = SPIFFS.open(SPIFFS_file_name, "w"); // Openning file from SPIFFS

  if (!file) // Cheking if file opened normaly
  {
    Serial.println("Error opening file for writing");
    return;
  }

  bytesWritten = file.print(recv_str); // Write string in SPIFFS

  if (bytesWritten == 0) // Check if written sucesseful
  {
    Serial.println("File write failed");
    file.close();
    return;
  }

  file.close();
}
