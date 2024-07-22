#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_NeoPixel.h>
#include <math.h>

#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  420 // this is the 'maximum' pulse length count (out of 4096)
#define FREQUENCY 50
#define PIXELPIN 33
#define NUMPIXELS 33
#define BUTTON 27

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x43);
Adafruit_NeoPixel pixels(NUMPIXELS, PIXELPIN, NEO_GRB + NEO_KHZ800);

uint8_t thumb = 10;
uint8_t indexFinger = 11;
uint8_t middle = 9;
uint8_t ring = 6;
uint8_t pinky = 8;

int randMode;

int number3[17] = {0, 1, 2, 3, 4, 10, 14, 15, 16, 17, 18, 26, 28, 29, 30, 31, 32};
int number2[17] = {0, 1, 2, 3, 4, 10, 14, 15, 16, 17, 18, 22, 28, 29, 30, 31, 32};
int number1[5] = {4, 10, 18, 26, 32}; //HELP TOI QUEN CACH CODE DYNAMIC ARRAY 

const int buzzer = 5;
int buttonState = 0;
int flag = 0;

void home() {
  pwm.setPWM(thumb, 0, SERVOMIN);
  pwm.setPWM(indexFinger, 0, SERVOMAX);
  pwm.setPWM(middle, 0, SERVOMAX);
  pwm.setPWM(ring, 0, SERVOMAX);
  pwm.setPWM(pinky, 0, SERVOMIN);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);  // The int.osc. is closer to 27MHz  
  pwm.setPWMFreq(FREQUENCY);  // Analog servos run at ~50 Hz updates
  pixels.begin();
  home();
  pinMode (buzzer, OUTPUT);
  pinMode (BUTTON, INPUT_PULLUP);
  delay(10);
}

void buzzerBeep(){
  tone(buzzer, 500);
  delay(50);
  noTone(buzzer);
}

void loop() {
  // put your main code here, to run repeatedly:
  pixels.clear(); 
  randMode = random(1,4);
  buttonState = digitalRead(BUTTON);
  Serial.println(digitalRead(BUTTON));

  if (buttonState == 0 && flag ==0){
      pixels.clear();
      for (int i = 0; i < 17; i++){
        pixels.setPixelColor(number3[i], pixels.Color(255, 243, 0));
        pixels.show();
      }
      buzzerBeep();
      delay (900);
      pixels.clear();

    for (int i = 0; i < 17; i++){
      pixels.setPixelColor(number2[i], pixels.Color(255, 243, 0));
      pixels.show();
    }
    buzzerBeep();
    delay (900);
    pixels.clear();

    for (int i = 0; i < 5; i++){
      pixels.setPixelColor(number1[i], pixels.Color(255, 243, 0));
      pixels.show();
    }
      buzzerBeep();
      delay (900);
      pixels.clear();

  switch(randMode){
    case 1: //rock
      for (int i = SERVOMIN; i <= SERVOMAX; i++){
        pwm.setPWM(pinky, 0, i);
      }
      delay(10);
      for (int i = SERVOMIN; i <= SERVOMAX; i++){
        pwm.setPWM(ring, 0, i);
      }
      for (int i = SERVOMIN; i <= SERVOMAX; i++){
        pwm.setPWM(middle, 0, i);
      }
      for (int i = SERVOMIN; i <= SERVOMAX; i++){
        pwm.setPWM(indexFinger, 0, i);
      }
      delay(10);
      for (int i = SERVOMIN; i <= SERVOMAX; i++){
        pwm.setPWM(thumb, 0, i);
      }
      break;

    case 2: //paper
      pwm.setPWM(thumb, 0, SERVOMIN);
      pwm.setPWM(indexFinger, 0, SERVOMIN);
      pwm.setPWM(middle, 0, SERVOMIN);
      pwm.setPWM(ring, 0, SERVOMIN);
      pwm.setPWM(pinky, 0, SERVOMIN);
      break;

    case 3: //scissors
      for (int i = SERVOMIN; i <= SERVOMAX; i++){
        pwm.setPWM(pinky, 0, i);
      }
      delay(10);
      for (int i = SERVOMIN; i <= SERVOMAX; i++){
        pwm.setPWM(ring, 0, i);
      }
      pwm.setPWM(middle, 0, SERVOMIN);
      pwm.setPWM(indexFinger, 0, SERVOMIN);
      for (int i = SERVOMIN; i <= SERVOMAX; i++){
        pwm.setPWM(thumb, 0, i);
      }
      break;
    }
      flag = 1;
      delay (3000);
      home();
    }

    else{
      flag = 0;
    }

}
