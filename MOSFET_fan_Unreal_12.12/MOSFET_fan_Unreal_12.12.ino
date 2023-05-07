#include <Arduino.h>
#include <Wire.h>
 
#include <DHT.h>
//add LCD library
#include <rgb_lcd.h>

//set digital pin8 as DHTPIN
#define DHTPIN 8
//set the sensor type as DHT 11
#define DHTTYPE DHT11

/*assign dht as the name of DHT sensor
  set the sensor pin as DHTPIN(pin2),
  set the sensor type as DHTTYPE(DHT11)
*/
DHT dht(DHTPIN, DHTTYPE);

//assign lcd as the name of rgb_lcd screen
rgb_lcd lcd;

int tempPin = 8;   // the output pin of Temperature sensor
int fan = 11;       // the pin where fan is
int heater = 3;    // buzzer pin
int temp;
int tempMin = 20;   // the temperature to start the fan
int tempMax = 30;   // the maximum temperature when fan is at 100%
int fanSpeed;
int fanLCD;
char inChar;
 
void setup() {
  Serial.begin(9600);//
  Serial.println(" Hi Fei ");//
  
  pinMode(fan, OUTPUT);
  pinMode(heater, OUTPUT);
  pinMode(tempPin, INPUT);
  pinMode(2,INPUT);


  //initialise the dht sensor
  dht.begin();
  //initialise the lcd screen;
  //set up the lcd's number of columns and rows:
  lcd.begin(16, 2);
  //wait for 2s
  delay(2000);

  lcd.setCursor(0,0);
  lcd.print(" WELCOME To VR ");
  lcd.setCursor(0,1);
  lcd.print(" Nature world ");
  delay(3000);
  lcd.clear();
  
}
 
void loop() {  

  
  int h = dht.readHumidity();
  //store the temperature value to t(in Celsius)
  int temp = dht.readTemperature();
  
  Serial.println("I'm working");
  delay(5000);
  
    while(Serial.available()){
    inChar=Serial.read();
    doStuff(); 

   fanLCD = map(temp, tempMin, tempMax, 0, 100);  // speed of fan to display on LCD
       Serial.println("higher than 10 degree");
       delay(2000);
       
  
   if(temp < tempMin) {   // if temp is lower than minimum temp
    fanSpeed = 0;      // fan is not spinning
    fanLCD = 0; 
    digitalWrite(fan, LOW);
    Serial.println("it's too cold to work");     
    delay(2000);  
   } 
   
   
   lcd.setCursor(0,0);
   lcd.print("T: ");
   lcd.setCursor(2,0);
   lcd.print(temp); // display the temperature
   lcd.write(223);
   lcd.print("C  ");

    lcd.setCursor(8, 0);
  //Print text Humidity: to the LCD
  lcd.print("H: ");
   lcd.setCursor(10,0);
   lcd.print(h); // display the temperature
   lcd.setCursor(12, 0);
  //Print sign % to the LCD
  lcd.print("%");
   
   lcd.setCursor(0,1); // move cursor to next line
   lcd.print("Fan Speed:");
   lcd.print(fanLCD); // display the fan speed
   lcd.print("%   ");
   delay(200);

   if(h > 60){
  Serial.println("OFF");  
  digitalWrite(2, LOW);    // atomization stopped
  }
  if(h <= 60) {
  Serial.println("ON");  
  digitalWrite(2, HIGH);   // atomize 
    }
      }
  delay (1);
}

 void doStuff(){
  if (inChar == '1'){
   
    Serial.println("Under shadow");
    delay(5000);
    digitalWrite(fan, HIGH);
    digitalWrite(heater, LOW);
    
    
  } else if (inChar == '0'){
    // Turn off LED and send 'bye' message
    Serial.println("under sun");
    delay(5000);
    digitalWrite(fan, HIGH);
    digitalWrite(heater, HIGH);
  }
}

int readTemp() {  // get the temperature and convert it to celsius
  temp = analogRead(tempPin);
  return temp * 0.48828125;
}
