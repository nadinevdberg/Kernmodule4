#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

//this code is made copied from: http://educ8s.tv/arduino-nokia-5110-menu/
boolean backlight = true;
int contrast = 50;

int menuitem =1;
int page= 1;

volatile boolean up = false;
volatile boolean down = false;
volatile boolean middle = false;

int downButtonState = 0;
int upButtonState = 0;
int selectButtonState = 0;
int lastSelectButtonState = 0;
int lastUpButtonState = 0;

Adafruit_PCD8544 display = Adafruit_PCD8544(5,4,3)

void setup() {
 pinMode(0, INPUT_PULLUP);
 pinMode(1, INPUT_PULLUP);
 pinMode(2, INPUT_PULLUP);
 pinMode(7, OUTPUT);

 digitalWrite(7, LOW); // backlight ON

 Serial.begin(9600);

 display.begin();
 display.setContrast(contrast);
 display.clearDisplay();
 display.display();
}

void loop() {
  drawMenu();

  downButtonState=digitalRead(2);
  selectButtonState = digitalRead(1);
  upButtonState = digitalRead(0);

  checkIfDownButtonIsPressed();
  checkIfUpButtonIsPressed();
  checkIfSelectButtonIsPressed();

  if (up && page == 1){
    up = false;
    menuitem --;
    if(menuitem==0){
      menuitem = 3;
    }
  }else if (up && page == 2){
      up = false;
      contrast --;
      setContrast();
    }

    if (down && page == 1){
      down - false;
      menuitem++;
      if (menuitem=4){
        menuitem=1;
      }
    }else if(down&&page==2){
      down = false;
      contrast++;
      setContrast();
    }
  if (middle){
    middle = false;
    
    if (page == 1 && menuitem == 2)
    {
      if (blacklight)
      {
        backlight = false;
        turnBacklightOff();
      }
      else
      {backlight = true;
      turnBackLightOn();
    }
  }
  if(page == 1 && menuitem ==3){
    resetDefaults();
  }

  else if(page == 1 && menuitem ==1){
    page = 2;
  }
  else if (page == 2){
    page = 1;
  }
  }
}
