#include <Arduino.h>
#include <esp_now.h>
#include "esp_system.h"
#include "esp_wifi.h"
#include <WiFi.h>
#include <Wire.h>
#include "main.h"
#include "display.h"

#include "settings.h"


#include <driver/adc.h>
#include "elapsedMillis.h"
#include <Ticker.h> 

//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>
#include <U8g2lib.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDR 0x3C
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0,U8X8_PIN_NONE);

//#define LED_BUILTIN 5
#define NUM_SERVOS 4

#define MAX_TICKS 2010 // Maxwert ms fur Impulslaenge
#define MIN_TICKS 990  // Minwert ms fuer Impulslaenge

#define JOYSTICK_B 
#define MAX_ADC 3310 // Max wert vom ADC
#define MIN_ADC 2150 // Min wert vom ADC

#define NULLBAND 10 // nichts tun bei kleineren Kanalwerten

#define START_TON 0
#define LICHT_ON 1

#define ESPOK 0

#define SENDINTERVALL 20


// put function declarations here:
int myFunction(int, int);
uint8_t mac[6] = {0x34, 0x85, 0x18, 0x05, 0xEC, 0x28};

canal_struct canaldata;

canal_struct indata;

esp_now_peer_info_t peerInfo;



elapsedMicros sincelastbeepA;

elapsedMillis sincelastseccond;
elapsedMillis sinceimpulsstart;

// debounce
Ticker debouncetimer;
elapsedMillis debouncemillis;
#define MAX_CHECKS 10
#define AVERAGE 8

uint8_t DebouncedState;
uint8_t lastDebouncedState;
uint8_t debouncestatus;
uint8_t averagecounter = 0;
uint16_t lxmittelwertarray[AVERAGE];
uint16_t lymittelwertarray[AVERAGE];

uint16_t lxmittel = 0;
uint16_t lymittel = 0;

float speedfilterfaktor = 0.8;
uint16_t speedA = 0;
uint16_t speedB = 0;

uint8_t propfaktorx = 1.0;
uint8_t propfaktory = 1.0;
uint8_t State[MAX_CHECKS];
uint8_t Index = 0;

uint16_t loopcounter = 0;

uint8_t broadcastAddressArray[8][6] = 
{{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
{0x44, 0x17, 0x93, 0x14, 0xF7, 0x17}, // ESP8266 D1 MINI
{0x48, 0x3F, 0xDA, 0xA4, 0x36, 0x57}, // RobotStepper
{0x8c, 0xaa, 0xb5, 0x7b, 0xa3, 0x28}, // WMOS MINI,
{0x44, 0x17, 0x93, 0x14, 0xF6, 0x6F},
{0x34,0x85,0x18,0x05,0xEC,0x28}, // seedstudio XIAO 32
{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};
uint8_t peerpos = 1; // geladener peer

uint8_t   adcstatus=0;
//#define ADC_OK  0
#define ADC_END 1

uint8_t   servostatus=0;
uint8_t   programmstatus = 0;
uint8_t   tastaturstatus = 0;
uint8_t   buttonstatus = 0;
uint8_t   tonindex = 0;

int ledintervall = 200;
elapsedMillis ledmillis;

unsigned char char_x;
unsigned char char_y;
uint16_t   stopsekunde;
 uint16_t   stopminute;
 uint16_t   throttlecounter;
 uint16_t    throttlesekunden;

// put function declarations here:

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) 
{
  char macStr[18];
  Serial.printf("Packet sent\n");
  // Copies the sender mac address to a string
  //snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
  //         mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
 // Serial.print(macStr);
 // Serial.print(" send status:\t");
 // Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

//callback function that will be executed when data is received
// Callback when data is received
// 

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&indata, incomingData, sizeof(canaldata));
  Serial.print("Bytes received: ");
  //Serial.println(len);
  //Serial.printf("indata x: %d y. %d\n", indata.x, indata.y);
 
}


void setup() 
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("setup");

  //pinMode(LED_BUILTIN, OUTPUT); 

  Wire.begin(6,7);   // ESP32 I2C Pins
  delay(100);
 
  u8g2.begin();              // Display initialisieren
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(0, 12, "H0_ESP_T");
  u8g2.sendBuffer();
  delay(100);

  esp_read_mac(mac, ESP_MAC_WIFI_STA);
  //Serial.printf("Base/WiFi STA MAC:\n{0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X}\n",  mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);


  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() 
{
  if (ledmillis > ledintervall)
  {
    ledmillis = 0;
    loopcounter++;
    //Serial.println(loopcounter);
  } // if ledmillis
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}