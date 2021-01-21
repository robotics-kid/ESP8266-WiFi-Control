#pragma once
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#define DATA_PIN              D6
#define LEDS_TYPE             NEO_KHZ800                 // NEO_KHZ800 - SK6812, WS2812B, WS2812; NEO_KHZ400 - WS2811
#define MAX_BRIGHTNESS        250
#define COLOR_ORDER           NEO_GRBW               // NEO_GRB - WS2812B; NEO_GRBW - SK5812
#define WIDTH                 1
#define HEIGHT                37

#define APSSID                "FoViBaltLight_01"           // SSID of local WiFi Network
#define APPSK                 "qwertyuiop"       // Password of local WiFi Netdwork

#define MAX_CLIENTS           4                 // Maximum clients connection
#define PORT                  6295              // Port number
const char* ip =              "192.168.4.1";    // Local ip for AP
const char* sub =             "255.255.255.0";

const char root_previx[] =          "FoViBalTLight";  // root previx of protocol (root_previx:F:1:H:230..)
const size_t argsLen =        100;              // maximum recieve date length
const size_t argsPrevixLen =  4;
const char del[3] =           ":;";             // Default protocol value delimiter

const char SPIFFS_file_name[] =     "/effects.txt";

//Definition of led strip types
//==============================
#if WIDTH == 1
#define STRIP_TYPE  1                           // 1 - led strip; 2 - led matrix
#else
#define STRIP_TYPE  2
#endif

#if COLO_ORDER == NEO_RGBW or COLOR_ORDER == NEO_GRBW or COLOR_ORDER == NEO_GBRW or COLOR_ORDER == NEO_BRGW or COLOR_ORDER == NEO_BGRW or COLOR_ORDER == NEO_RBGW
#define LEDS_TYPE_S 1
#else
#define LEDS_TYPE_S 2
#endif

#define NUM_LEDS WIDTH*HEIGHT
//==============================

//Led constants

//Definition of different types
//==============================
struct handler {
  char handlerChar[argsPrevixLen];
  short handlerVal;
};


handler WiFiHandler[argsLen]; // Defining an array of handled values

char mSend[argsLen];  // Creating first mSend witch contain handshake: FoViBalTLight;STA:1
char preRecv[argsLen] = "FoViBalTLight;EFF:1;RED:255;GRN:0;BLU:0;WHT:0";
char recv_str[argsLen];
char toSPIFFS[argsLen];
char recv[argsLen];
//==============================

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, COLOR_ORDER + LEDS_TYPE);

//Defining WiFi types and variables
IPAddress local_IP;
IPAddress subnet;
bool err = local_IP.fromString(ip);
bool err2 = subnet.fromString(sub);
const char *ssid = APSSID;
const char *password = APPSK;

WiFiServer server(PORT); // Setting up server
WiFiClient serverClients[MAX_CLIENTS]; // Limit num of conected clients
WiFiClient client;
