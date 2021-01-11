#pragma once
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#define DATA_PIN              6
#define LEDS_TYPE             2                 // 1 - SK6812; 2 - WS2812B; 3 - WS2812; 4 - WS2811
#define MAX_BRIGHTNESS        250
#define COLOR_ORDER           GRB               // GRB - WS2812B
#define WIDTH                 1
#define HEIGHT                37

#define APSSID                "FoViBaltLight_01"           // SSID of local WiFi Network
#define APPSK                 "qwertyuiop"       // Password of local WiFi Netdwork

#define MAX_CLIENTS           4                 // Maximum clients connection
const uint16_t port =                    80;               // Port number
const char* ip =              "192.168.4.1";    // Local ip for AP
const char* sub =             "255.255.255.0";

const char root_previx[] =          "FoViBalTLight";  // root previx of protocol (root_previx:F:1:H:230..)
const size_t argsLen =        100;              // maximum recieve date length
const size_t argsPrevixLen =  4;
const char del[3] =           ":;";             // Default protocol value delimiter

const String SPIFFS_file_name =     "/effects.txt";

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
CRGBW ledsW[NUM_LEDS];
CRGB* ledsRGB = (CRGB*)&ledsW[0];               // For WHITE LEDS ONLY
CRGB leds[NUM_LEDS];                            // For all NONE WHITE LEDS

#if LEDS_TYPE == 2
  #define STRIP_NAME WS2812B
#elif LEDS_TYPE == 3
  #define STRIP_NAME WS2812
#elif LEDS_TYPE == 4
  #define STRIP_NAME WS2811
#endif

//Definition of different types
//==============================
struct handler {
  char handlerChar[argsPrevixLen];
  short handlerVal;
};

struct RGB_t {
  uint16_t r;
  uint16_t g;
  uint16_t b;
} rgb;

struct HSV_t {
  uint16_t h;
  uint16_t s;
  uint16_t v;
} hsv;


handler WiFiHandler[argsLen]; // Defining an array of handled values

String mSend = String(root_previx) + ";STA:1!"; // Creating first mSend witch contain handshake: FoViBalTLight;STA:1
String recv_str;
String preRecv = "FoViBalTLight;EFF:1;RED:255;GRN:0;BLU:0;WHT:0!";

char recv[argsLen];
char* token;
char buf[argsLen];

uint16_t i;
bool flag;
//==============================

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
