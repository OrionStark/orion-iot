#include <dht11.h>

dht11 DHT11;

int digitalPIN = 4;
int blue_light = 9;
int red_light = 8;
int green_light = 10;

int pinSelectable[3] = {7, 6, 5}; // [s0, s1, s2]
int outputMap[8][3] = {
  {LOW, LOW, LOW}, // y0 DHT Sensor
  {LOW, LOW, HIGH}, // y1 Raindrop Sensor
  {LOW, HIGH, LOW}, // y2
  {LOW, HIGH, HIGH}, // y3
  {HIGH, LOW, LOW}, // y4
  {HIGH, LOW, HIGH}, // y5
  {HIGH, HIGH, LOW}, // y6
  {HIGH, HIGH, HIGH} // y7
};

void setup() {
  pinMode(pinSelectable[0], OUTPUT);
  pinMode(pinSelectable[1], OUTPUT);
  pinMode(pinSelectable[2], OUTPUT);

  pinMode(red_light, OUTPUT);
  pinMode(green_light, OUTPUT);
  pinMode(blue_light, OUTPUT);

  pinMode(digitalPIN, INPUT);

  Serial.begin(9600);
}

void loop() {
   setInputMap(0);
   int chk = DHT11.read(digitalPIN);

   Serial.print("Humidity (%): ");
   Serial.println((float)DHT11.humidity, 2);

   Serial.print("Temperature (C): ");
   Serial.print("Testing");
   Serial.println((float)DHT11.temperature, 2);

   setInputMap(1);
   int resultRain = digitalRead(digitalPIN);
   if ( resultRain == 0 ) {
      turnRGBLight(LOW, LOW, LOW);
      Serial.println("Rain detected");
   } else {
      turnRGBLight(LOW, HIGH, LOW);
      delay(500);
      turnRGBLight(LOW, LOW, HIGH);
   }

   delay(1000);
}

void turnRGBLight(int red, int green, int blue) {
  digitalWrite(red_light, red);
  digitalWrite(green_light, green);
  digitalWrite(blue_light, blue);
}

void setInputMap(int index) {
  int pinMap[3] = {outputMap[index]};
  for ( int i = 0; i < (sizeof(pinMap) / sizeof(*pinMap)); i++ ) {
    digitalWrite(pinSelectable[i], pinMap[i]);
  }
}
