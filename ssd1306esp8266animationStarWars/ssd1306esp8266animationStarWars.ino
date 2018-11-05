//oled demo with long animation.

#include <Wire.h>
#include "SSD1306Wire.h"
#include <FS.h>
#include <ESP8266WiFi.h>
#include <user_interface.h>

//remember to check your oled's address
SSD1306Wire  display(0x3c, D2, D1);

//add here you file
const char image[] = "/tahtiensotasprite106x64.MONO";  //896 tahtiensota starwars in finnish
char pathto[30];
//here precise byte amount for frame
unsigned char kuvabuf[976];
int frames = 1008;  // remember 0 frame
//frame specs
int imagewid = 106;
int imagehig = 64;
int imagewidpl = 0;
int imagehigpl = 0;
int framebytes = 896;
// sprite = animation mode if 0 will load one image every time so it work also
//with single files
int sprite = 1;
int delayBetween = 0;

int s; //file size

File f;
void setup() {
  WiFi.mode(WIFI_OFF);
  system_update_cpu_freq(160);
  // put your setup code here, to run once:
  //Wire.setClock(400000L); does not work here oled library will change it
  display.init();
  display.flipScreenVertically();

  //to check that code gets here
  display.clear();
  display.drawString(0, 0, "Hello world: ");
  display.display();
  delay(500);
  
  Serial.begin(115200);

  if (!SPIFFS.begin()) {
    Serial.println("Failed to mount file system");
  }
  
  Serial.println("Mounted");
  display.clear();
  display.display();
}

void loop() {
  // put your main code here, to run repeatedly:
  //if it sprite
  if(sprite)  {
    //sprintf(pathto, image, e);
    f = SPIFFS.open(image, "r");
    if(f){
    s = f.size();
    Serial.printf("Sprite file Opened , Size=%d\r\n", s);
    }
    Serial.println("might have failed to load");
  }

  //start play
  for(int e = 0; e < frames + 1; e++){
    //one frame in file load
    if(sprite == 0){
      sprintf(pathto, image, e);
      f = SPIFFS.open(pathto, "r");
    }
    if (f) {
      s = f.size();
      Serial.printf("File Opened , Size=%d\r\n", s);
      if(sprite == 0){
        for(int i = 0; i < s ; i++){
          kuvabuf[i]= f.read();
        }
      }
      //reads frame from sprite file. File pointer leaves to next byte
      if(sprite == 1){
        for(int i = 0; i < framebytes ; i++){
          kuvabuf[i]= f.read();
        }
      }
      //closes current file if not sprite
      if (sprite == 0) f.close();
      //f.close();
      display.clear();
      Serial.println("displaying...");
      //displays your image. You can convert this code to other oled libraries
      //if you use input variables right!
      display.drawXbm(imagewidpl, imagehigpl, imagewid, imagehig, kuvabuf);
      display.display();
    }
    delay(delayBetween);
  }
}
