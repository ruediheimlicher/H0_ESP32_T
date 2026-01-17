
#include <inttypes.h>
#include "main.h"
#include "display.h"
#include "text.h"

#include "defines.h"

//extern uint16_t currentexpoarray[5][513];

extern uint8_t                   kanalsettingarray[5][4][4];

extern  uint8_t                 curr_model; // aktuelles modell
extern  uint8_t                 speichermodel;
extern  uint8_t                 curr_funktion; // aktueller kanal
extern  uint8_t                 curr_aktion;
extern  uint8_t                 curr_wert;
extern  uint8_t                 curr_modus;

extern  uint8_t                 curr_setting; // aktuelles Setting fuer Modell
extern  uint8_t                 curr_screen; // aktueller screen
extern  uint8_t                 last_screen; // letzter screen

extern  uint8_t                 curr_page; // aktuelle page
extern  uint8_t                 curr_col; // aktuelle colonne

extern  uint8_t                 curr_cursorzeile; // aktuelle zeile des cursors
extern  uint8_t                 curr_cursorspalte; // aktuelle colonne des cursors
extern  uint8_t                 last_cursorzeile; // letzte zeile des cursors
extern  uint8_t                 last_cursorspalte; // letzte colonne des cursors

extern uint8_t                  curr_pfeil;

extern uint8_t                   curr_steuerstatus;

extern uint16_t                  blink_cursorpos;
extern uint8_t                   blinkstatus;
extern uint8_t                   calibstatus;

extern uint16_t                   batteriespannung;

extern uint16_t                  pressureint;
extern uint16_t                  temperaturint;
extern float                     pressurefloat;
extern float                     temperaturfloat;
extern float                     altitude;
extern uint16_t                  altitudeint;

extern float                     startaltitude;
extern uint16_t                  startaltitudeint;
extern uint16_t                  diffaltitudeint;




#define BLINKPFEILUP             0
#define BLINKPFEILDOWN           1

extern uint8_t                      calibstatus;

#define TAB0    2
#define TAB1    4
#define TAB3    8

#define cursortab0 2
#define cursortab1 26
#define cursortab2 46
#define cursortab3 54
#define cursortab4 66
#define cursortab5 78
#define cursortab6 90
#define cursortab7 100



//uint8_t cursortab[10] = {cursortab0,cursortab1,cursortab2,cursortab3,cursortab4,cursortab5,cursortab6,cursortab7,cursortab0,cursortab0};
//extern  uint16_t  cursorpos[8][8]; // Aktueller screen: werte fuer page und daraufliegende col fuer cursor (hex). geladen aus progmem

extern uint16_t   stopsekunde;
extern uint16_t   stopminute;
extern uint16_t   throttlecounter;
extern uint16_t    throttlesekunden;

#define itemtab0  10
#define itemtab1  34
#define itemtab2  50
#define itemtab3  62
#define itemtab4  74
#define itemtab5  88
#define itemtab6  110
#define itemtab7  118

  uint8_t itemtab[10] = {itemtab0,itemtab1,itemtab2,itemtab3,itemtab4,itemtab5,itemtab6,itemtab7,itemtab0,itemtab0};

//extern  uint16_t  posregister[8][8]; // Aktueller screen: werte fuer page und daraufliegende col fuer Menueintraege (hex). geladen aus progmem

#define  taby0    16
#define  taby1    24
#define  taby2    32
#define  taby3    40
#define  taby4    48
#define  taby5    56
#define  taby6    56
#define  taby7    56

  uint8_t taby[8] = {taby0,taby1,taby2,taby3,taby4,taby5,taby6,taby7};

#define menu0  24
#define menu1  40
#define menu2  56

#define menuh 20

extern float      UBatt;
extern uint16_t   batterieanzeige;

extern float      UFlyerBatt;
extern uint16_t   flyerbatterieanzeige;


//extern Signal data;





uint8_t charh = 0;
uint8_t balkenh = 50;
uint8_t balkenb = 5;
uint8_t balkenvh = 40;
 uint8_t balkenvb = 5;
 uint8_t balkenhh = 3;
 uint8_t balkenhb = 40;

//char menubuffer[20];
//char titelbuffer[20];


U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

void initDisplay()
{
  u8g2.begin();
  uint8_t c = 0;
}

/*
 void oled_fill(uint8_t x,uint8_t y,uint8_t l)
{
   //u8g2.setDrawColor(0);
   u8g2.drawBox(x,y-charh,l,charh+4);
   //u8g2.setDrawColor(1);
   u8g2.sendBuffer();
}



void oled_setInt(uint8_t x,uint8_t y, uint16_t data)
{
   u8g2.setCursor(x,y);
   u8g2.print(data);
   u8g2.sendBuffer();

}
*/
void oled_delete(uint8_t x,uint8_t y,uint8_t l)
{
   u8g2.setDrawColor(0);
   u8g2.drawBox(x,y-charh,l,charh+4);
   u8g2.setDrawColor(1);
   //u8g2.sendBuffer();
}

void oled_frame(uint8_t x,uint8_t y,uint8_t l)
{
   //u8g2.setDrawColor(0);
   u8g2.drawFrame(x,y-charh,l,charh+4);
   //u8g2.setDrawColor(1);
   u8g2.sendBuffer();
}
void oled_vertikalbalken(uint8_t x,uint8_t y, uint8_t b, uint8_t h)
{
   u8g2.drawFrame(x,y,b,h);


}

void oled_vertikalbalken_setwert(uint8_t x,uint8_t y, uint8_t b, uint8_t h,uint8_t wert)
{
  ////Serial.print(h);
  ////Serial.print("\t");
  ////Serial.print(wert);
  
  ////Serial.print("\n");
  uint8_t anzeige = map(wert-30,0,12,0,h); 
  
  u8g2.setDrawColor(0);
  u8g2.drawBox(x+1,y+1,b-2,h-2);
  u8g2.setDrawColor(1);
  //u8g2.drawBox(x+7,y+1,b-2,h-2);
  u8g2.drawHLine(x,y+h-wert,b);
  u8g2.drawHLine(x,y+h-wert-1,b);
  u8g2.drawHLine(x,y+h-wert+1,b);

}

void oled_batteriebalken_setwert(uint8_t x,uint8_t y, uint8_t b, uint8_t h,uint16_t wert)
{
 //uint8_t anzeige = map(wert-30,0,12,0,h); // Bereich 3-7.4V, 1.2V BATT 8.4V: 240   6.4V: 94   6.0: 65
 uint8_t min = map(2,0,12,0,h);
  uint8_t anzeige = wert;

  u8g2.setDrawColor(0);
  u8g2.drawBox(x+1,y+1,b-2,h-2);
  u8g2.setDrawColor(1);
 
  u8g2.drawBox(x+1,y+h-anzeige,b-2,anzeige);
  u8g2.setDrawColor(0);
  u8g2.drawHLine(x+1,y+h-min,b-2);
  u8g2.drawHLine(x+1,y+h-min-1,b-2);
  u8g2.setDrawColor(1);



}



void oled_setBatterieWert(uint8_t x,uint8_t y, uint8_t b, uint8_t h,float wert)
{
   u8g2.setFontDirection(3);
   u8g2.setFont(u8g2_font_t0_11_mr);  

   u8g2.setCursor(x,y);
   //u8g2.setDrawColor(0);
   u8g2.print(wert,1);
   u8g2.setDrawColor(1);
   u8g2.setFontDirection(0);

}

void oled_horizontalbalken(uint8_t x,uint8_t y, uint8_t b, uint8_t h)
{
   u8g2.drawFrame(x,y,b,h);
}
void oled_horizontalbalken_setwert(uint8_t x,uint8_t y, uint8_t b, uint8_t h,uint8_t wert)
{
  ////Serial.print(b);
  ////Serial.print("\t");
  ////Serial.print(wert);
  
  ////Serial.print("\n");
  

  u8g2.setDrawColor(0);
  u8g2.drawBox(x+1,y+1,b-2,h-2);

 

  u8g2.setDrawColor(1);
  //u8g2.drawBox(x+7,y+1,b-2,h-2);
  //return;
  u8g2.drawVLine(x+b-wert,y,h);
  //u8g2.drawHLine(x+b-wert-1,y,h);
  //u8g2.drawHLine(x+b-wert+1,y,h);

}

void resetRegister(void)
{
   uint8_t i=0,k=0;
   for(i=0;i<8;i++)
   {
      for (k=0;k<8;k++)
      {
         //posregister[i][k]=0xFFFF;
      }
   }
}


void setHomeScreen()
{
   
   u8g2.clear();
   u8g2.setFont(u8g2_font_t0_22_mr);  
   u8g2.setCursor(TAB0, 16);
   //u8g2.print(F("nRF24 T"));
   u8g2.setFont(u8g2_font_t0_15_mr);  
   //oled_vertikalbalken(BATTX,BATTY,BATTB,BATTH);
   //oled_vertikalbalken(FLYBATTX,FLYBATTY,FLYBATTB,FLYBATTH);

   u8g2.sendBuffer();
   

   updateHomeScreen();
}

void updateHomeScreen()
{
 
   
}
