#include <IRremote.h> // include the IRremote library
#include <EEPROM.h>
#define IR_RECEIVE_PIN 10   //IR receive pin
#define LED 6 // PWM Pin Out

int brightness[]={35,125, 86, 46, 78, 32, 15, 12, 75, 40, 93, 42, 17, 51, 88, 
74, 66, 125, 56, 15, 22, 17, 27, 13, 102, 79, 44, 39, 80, 118, 32, 24, 21, 
46, 23, 23, 14, 24, 11, 26, 23, 12, 16, 12, 27, 13, 28, 26, 11, 46, 26, 21, 
0, 0, 11, 15, 57, 21, 10, 42, 0, 9, 131, 16, 62, 96, 79, 80, 50, 12, 27, 0, 
36, 91, 75, 70, 70, 143, 64, 50, 74, 80, 107, 84, 84, 78, 89, 49, 46, 69, 32, 
71, 66, 33, 40, 42, 22, 50, 26, 41}; //database
int currentIndex =0; // define the number of current Index, used for stop loop
int intervals[] = { 1000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000,
 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000,
  5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000,
   5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000,
    5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000};//duration of the wind
boolean status = false;

void setup() {
  //TCCR2B = TCCR2B & 0b11111000 | 0x01;
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);//start the IR remote
  pinMode(LED, OUTPUT);
  Serial.println("IR start");  //show the program start
}

void loop() {
    
   // if (currentIndex >= sizeof(brightness)/ sizeof(int)){return;} //if the current index is out of the array, stop
    if(status){
      
      for(int i= 0; i<100;i++){    //Play the wind following array
        analogWrite(LED,brightness[i]);
        Serial.print("nowbrightness: ");
        Serial.println(brightness[i]);
        delay(intervals[i]);//duration of the wind
        //delay(500);
        currentIndex++;
    
        if(IrReceiver.decode()){ // Have we recieve the IR signal?
          translateIR();   
          Serial.print("button: ");
          Serial.println(IrReceiver.decodedIRData.command); // Show the code of the button which was pressed
        }
        if(!status){
          break;
        }  
      }
    }else if(IrReceiver.decode()){ // Have we recieve the IR signal?
          translateIR();   
          Serial.print("button: ");
          Serial.println(IrReceiver.decodedIRData.command); // Show the code of the button which was pressed
    }
}



void translateIR(){  // take action based on IR code received
  switch(IrReceiver.decodedIRData.command){
    case 9:  // press "+" LED brighter
    for(int i=0; i<100; i++){
      brightness[i] +=20;
      if(brightness[i] > 255 ){
        brightness[i] = 255;
      } 
    }
    delay(0);
    break;

    case 21:  //press "-", LED dimmer
    for(int i=0; i<100; i++){
      brightness[i] -=20;
      if(brightness[i] <= 0 ){
        brightness[i] = 0;
      }
    
    }
    delay(0);
    break;


    case 69:
    
    status = !status;
    analogWrite(LED,brightness[0]);
    delay(0);
    Serial.println("stop button pressed");
    break;

    default:
    Serial.println("other button  ");
   
  }     
  IrReceiver.resume();  //recieve the next value   
}
