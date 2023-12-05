#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int rainFrame = 0; // 0 ~ 3

void initialiseGraphics(){
  static byte rain[] = {
    0b00000,
    0b11000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b01100,

    0b00000,
    0b01100,
    0b00000,
    0b00000,
    0b11000,
    0b00000,
    0b00000,
    0b00110,
    
    0b00000,
    0b00110,
    0b00000,
    0b00000,
    0b00110,
    0b00000,
    0b00000,
    0b00011,

    0b00000,
    0b00011,
    0b00000,
    0b00000,
    0b00001,
    0b00000,
    0b00000,
    0b00001
  };
  for (int i=0; i<4; i++){
    lcd.createChar(i+1, &rain[i*8]);
  }

  static byte characterA[8] = {
    0b00001,
    0b11010,
    0b11111,
    0b11001,
    0b00011,
    0b00110,
    0b00011,
    0b00001
  };
  lcd.createChar(5, characterA);

  static byte characterB_upper[8] = {
    0b00010,
    0b00010,
    0b11010,
    0b11111,
    0b11010,
    0b00001,
    0b00000,
    0b00000
  };
  lcd.createChar(6, characterB_upper);

  static byte characterB_lower[8] = {
    0b00000,
    0b00001,
    0b01111,
    0b11000,
    0b01111,
    0b00001,
    0b10000,
    0b00000
  };
  lcd.createChar(7, characterB_lower);

  static byte umbrella[8] = {
    0b00000,
    0b00100,
    0b01100,
    0b11111,
    0b01101,
    0b00101,
    0b00001,
    0b00010
  };
  lcd.createChar(8, umbrella);
}

void setup() {
  initialiseGraphics();
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  int br = analogRead(A1);

  // change the value according to the environment
  // Serial.println();
  // Serial.println(br);
  // Serial.println();

  if (br < 70){

    // rain + two characters

    lcd.setCursor(0, 0);
    for (int i=0; i<14; i++){
      lcd.write(rainFrame + 1);
    }
    lcd.write(8);
    lcd.write(5);

    lcd.setCursor(0, 1);
    for (int i=0; i<14; i++){
      lcd.write(rainFrame + 1);
    }
    lcd.write(6);
    lcd.write(7);

    // sound signal

    Serial.write(49);

  }
  else {

    // rain + one character

    lcd.setCursor(0, 0);
    for (int i=0; i<15; i++){
      lcd.write(rainFrame + 1);
    }
    lcd.write(5);

    lcd.setCursor(0, 1);
    for (int i=0; i<16; i++){
      lcd.write(rainFrame + 1);
    }

    // sound signal
    Serial.write(50);

  }
  
  rainFrame = (rainFrame + 1) % 4;
  delay(500);
}

/*
5v, ground를 브레드보드에 연결한다

왼쪽 -> 오른쪽 순서로
조도센서 : 5v, A1
저항 : A1, ground

가변저항 : 5v, lcd의 V0, ground

LCD :
GND - ground
VDD - 5v
V0 - 가변저항 가운데 뾰죡이
RS - 12
RW - ground
E - 11
D4 - 5
D5 - 4
D6 - 3
D7 - 2
BLA - 5V
BLK - ground

참고로 모든 연결은 브레드보드 가운데 줄 기준으로 같은 쪽에서 한다.
그리고 최종 작품을 생각해서 방향을 고려한다.
*/