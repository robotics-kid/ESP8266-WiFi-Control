#pragma once
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#define DATA_PIN              D6
#define LEDS_TYPE             NEO_KHZ800                 // 1 - SK6812; 2 - WS2812B; 3 - WS2812; 4 - WS2811
#define MAX_BRIGHTNESS        250
#define COLOR_ORDER           NEO_RGBW               // GRB - WS2812B
#define WIDTH                 1
#define HEIGHT                37

#define APSSID                "FoViBaltLight_01"           // SSID of local WiFi Network
#define APPSK                 "qwertyuiop"       // Password of local WiFi Netdwork

#define MAX_CLIENTS           4                 // Maximum clients connection
int port =                    80;               // Port number
const char* ip =              "192.168.4.1";    // Local ip for AP
const char* sub =             "255.255.255.0";

char root_previx[] =          "FoViBalTLight";  // root previx of protocol (root_previx:F:1:H:230..)
const size_t argsLen =        100;              // maximum recieve date length
const size_t argsPrevixLen =  4;
const char del[3] =           ":;";             // Default protocol value delimiter

String SPIFFS_file_name =     "/effects.txt";

//Definition of led strip types
//==============================
#if WIDTH == 1
#define STRIP_TYPE  1                           // 1 - led strip; 2 - led matrix
#else
#define STRIP_TYPE  2
#endif

#define NUM_LEDS WIDTH*HEIGHT
//==============================

//Led constants

//Definition of different types
//==============================
struct handler {
  char handlerChar[argsPrevixLen];
  int handlerVal;
};


handler WiFiHandler[argsLen]; // Defining an array of handled values

String mSend = String(root_previx) + ";STA:1!"; // Creating first mSend witch contain handshake: FoViBalTLight;STA:1
String preRecv = "FoViBalTLight;EFF:1;RED:255;GRN:0;BLU:0;WHT:0!";
char recv[argsLen];
String recv_str;
char *token;
int i;
char buf[argsLen];
bool flag;
//==============================

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, COLOR_ORDER + LEDS_TYPE);

//Defining WiFi types and variables
IPAddress local_IP;
IPAddress subnet;
bool err = local_IP.fromString(ip);
bool err2 = subnet.fromString(sub);
const char *ssid = APSSID;
const char *password = APPSK;

WiFiServer server(port); // Setting up server
WiFiClient serverClients[MAX_CLIENTS]; // Limit num of conected clients
WiFiClient client;
