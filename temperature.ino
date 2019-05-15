#include <LiquidCrystal.h>
#include <SimpleDHT.h>

// DHT22 pinout
int outDHT22 = 6;

// LCD pinout (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
SimpleDHT22 dht22(outDHT22);

// custom characters
byte heart[8] = {
  0b00000, 0b01010,
  0b11111, 0b11111,
  0b11111, 0b01110,
  0b00100, 0b00000
};

void setup() {
  // create characters
  lcd.createChar(1, heart);

  // Begin serial output
  Serial.begin(9600);

  lcd.begin(16,2);
  //lcd.write(1);

  // LED pin mode
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  // DHT22 read
  Serial.println("=============");
  Serial.println("Sampling the air around you...");

  float temp = 0;
  float humidity = 0;
  int error = SimpleDHTErrSuccess;
  if ((error = dht22.read2(&temp, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("DHT22 read failed. error = ");
    Serial.println(error);
    delay(2000);
    return;
  }

  // Serial print (for debugging lulz)
  Serial.print("Sample OK: ");
  Serial.print((float)temp);
  Serial.print(" *C, ");
  Serial.print((float)humidity);
  Serial.println(" RH%");

  // LCD print
  // write temp
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp:");
  lcd.setCursor(6,0);
  lcd.print(temp);
  lcd.setCursor(11,0);
  lcd.print("*C");

  // write humidity
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.setCursor(10,1);
  lcd.print(humidity);
  lcd.setCursor(14,1);
  lcd.print("%");

  // LED
  if (temp < 30) {
    digitalWrite(2, HIGH);
  }
  else {
    digitalWrite(2, LOW);
  }

  delay(2500);
}
