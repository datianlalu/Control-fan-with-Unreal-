#define sensorPin 2
#define relayPin 6

// Variable to store the time when last event happened
unsigned long lastEvent = 0;
unsigned long LastSpeedChange = 0;
double PWMfactor;
boolean relayState = false;    // Variable to store the state of relay
boolean IsFanOn = false;
int i=0;
int brightness[]={0,35,125,86,46,78,32,15,12,75,40,93,42,17,51,88,74,66,125,56,15,
                  22,17,27,13,102,79,44,39,80,118,32,24,21,46,23,23,14,24,11,26,
                  23,12,16,12,27,13,28,26,11,46,26,21,0,0,11,15,57,21,10,42,
                  0,9,131,16,62,96,79,80,50,12,27,0,36,91,75,70,70,143,64,50,
                  74,80,107,84,84,78,89,49,46,69,32,71,66,33,40,42,22,50,26,41};
int currentIndex =0;
int total_step = sizeof(brightness)/sizeof(brightness[0]);
int intervals[sizeof(brightness)];

void setup() {
  for(int i= 0; i<total_step;i++) {intervals[i]=1000;} //change 1000 to speed-shifting time
  pinMode(relayPin, OUTPUT);  // Set relay pin as an OUTPUT pin
  pinMode(sensorPin, INPUT);  // Set sensor pin as an INPUT
  for(int i= 0; i<total_step;i++) {intervals[i]=1000;}
  Serial.begin(9600);
  Serial.print("Connection ok. There are ");
  Serial.print(total_step);
  Serial.print(" steps.\n");
}

void loop() {
  int sensorData = digitalRead(sensorPin);
  int sensorDatatemp = analogRead(sensorPin);

  if (millis() - LastSpeedChange > intervals[i]){ // intervals[i] is the last time
      i++;
      i = i%total_step;
      LastSpeedChange = millis();
      Serial.print(i);
      Serial.print(", ");
      Serial.println(IsFanOn*brightness[i]);
  }
  if (sensorData == LOW) {
    if (millis() - lastEvent > 100) { // 100 is the time gap of the sound, need to find a good number
    
      Serial.println("Clap detected!");
      IsFanOn = !IsFanOn; //change the fan status, turn on or turn off.
    }
    lastEvent = millis();
  }
  PWMfactor = 4*brightness[i]; // Mapping from "brightness" to the PWM power, here a linear correlation is applied. 4* means enlarge the brightness 4 times.
  analogWrite(relayPin,IsFanOn*PWMfactor); //IsFanOn is the switch.
}
