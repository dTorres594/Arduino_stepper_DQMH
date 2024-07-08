#include "Adafruit_MotorShield_DTA.h"

const int INIT = 1;
const int MOVE = 2;
const unsigned char STOP = 'S';
const unsigned char GET_POS = 'G';
const unsigned char READ = 'R';
const unsigned char LASER = 'L';
const unsigned char ENDSTOP = 'E';
const unsigned char INFO = 'I';
const unsigned char HOME = 'H';
const int endStop1Pin = 18;  // 18 on MEGA, 2 on UNO
const int endStop2Pin = 19;   // 19 on MEGA, 3 on UNO
const int laserOutPin = 2;
const int sensorPin = A10;  //Change to A0 on Uno, A10 on MEGA
unsigned long wait_ms;
volatile unsigned int ES1 = 0, ES2 = 0;  // Status of the end-stops
unsigned int endStop1, endStop2;         // Digital value of end-stop inputs
unsigned char Home = 0;                  // Flag to indicate if in home position

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_StepperMotor *motor1;
Adafruit_StepperMotor *motor2;

unsigned int dataAtPort[] = {0,  //[0] Shield action. 0: Init; 1: Move; Miscellaneous commands
                              0,    //[1] On init: steps per rev motor1; on move: direction motor 1 FORWARD=1 BACKWARD=2
                              0,    //[2] On init: steps per rev motor2; on move: direction motor 2
                              0,    //[3] On init: rpm MSB motor1; on move: total steps MSB motor1
                              0,    //[4] On init: rpm LSB motor1; on move: total steps LSB motor1
                              0,    //[5] On init: rpm MSB motor2; On move: total steps MSB motor2
                              0,    //[6] On init: rpm LSB motor2; On move: total steps LSB motor2
                              0,    //[7] On move: step style motor 1
                              0};   //[8] On move: step style motor 2 
String dataAtPortStr;

void setup() {
  Serial.begin(115200);           // set up Serial library at 115200 bps
  while (!Serial) {
    Serial.println("Starting...");
  }
  Serial.println("Serial connected");
  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Shield connected");
  Serial.flush();

  pinMode(endStop1Pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(endStop1Pin),endStop1Changed,CHANGE);
  //attachInterrupt(digitalPinToInterrupt(endStop1Pin),endStop1Reached,RISING);
  //attachInterrupt(digitalPinToInterrupt(endStop1Pin),endStop1Free,FALLING);
  pinMode(endStop2Pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(endStop2Pin),endStop2Changed,CHANGE);
  //attachInterrupt(digitalPinToInterrupt(endStop2Pin),endStop2Reached,RISING);
  //attachInterrupt(digitalPinToInterrupt(endStop2Pin),endStop2Free,FALLING);
  pinMode(laserOutPin, OUTPUT);
}

void loop() {
  int str_len;
  unsigned int LSB_motor1 = 0, MSB_motor1 = 0, LSB_motor2 = 0, MSB_motor2 = 0;
  uint32_t totalStepsMotor1 = 0, totalStepsMotor2 = 0, maxSteps = 0;
  long int factor1, factor2;
  long int LCM;
  unsigned int positionMotor1 = 0, positionMotor2 = 0;   
  int directionMotor1, directionMotor2, stepStyleMotor1, stepStyleMotor2;
  int instruction[] = {0, 0};
  uint32_t delay_motor1, delay_motor2, wait_us = 0;
  String positionStr;
  int sensor_in = 0;
  double sensor_voltage = 0;

  if (Serial.available() > 0) { // Only run routines if there's information at the port
    for (int i = 0; i < 9; i++){
      dataAtPort[i] = Serial.read();
      delay(30);
      //Serial.println(dataAtPort[i]);
    }           

    if (dataAtPort[0] == INIT) { // Initialization routine
      motor1 = AFMS.getStepper(dataAtPort[1], 1);
      motor2 = AFMS.getStepper(dataAtPort[2], 2);
      delay_motor1 = motor1->setSpeed((dataAtPort[3]-1)*256 + dataAtPort[4]-1);
      //Serial.println((dataAtPort[3]-1)*256 + dataAtPort[4]-1);
      delay_motor2 = motor2->setSpeed((dataAtPort[5]-1)*256 + dataAtPort[6]-1);
      //Serial.println((dataAtPort[5]-1)*256 + dataAtPort[6]-1);
      //Serial.print("M1: " + (String)delay_motor1 + " M2: " + (String)delay_motor2 + "\n");
      delay(80);
      wait_us = (delay_motor1 <= delay_motor2) ? delay_motor1 : delay_motor2;
      wait_ms = (unsigned long)wait_us / 1000L;
      //wait_ms = 60e3L/(dataAtPort[1]*dataAtPort[3]);
      //Serial.print("Microseconds: " + (String)wait_us + "\n");
      Serial.println("Motors ready. Standing by.");
    } // End of initialization

    else if (dataAtPort[0] == LASER) {  // Send PWM value to laser
      Serial.println("PWM: " + (String)dataAtPort[1]);
      analogWrite(laserOutPin, dataAtPort[1]);          
    }

    else if (dataAtPort[0] == READ) {
      sensor_in = analogRead(sensorPin);
      sensor_voltage = (double)sensor_in / 1024;
      Serial.print("Sen");
      Serial.println(sensor_voltage, 6);
    }

    else if (dataAtPort[0] == ENDSTOP){
      endStop1 = digitalRead(endStop1Pin);
      endStop2 = digitalRead(endStop2Pin);
      Serial.println("ES" + (String)endStop1 + "," + (String)endStop2);
    }

    else if (dataAtPort[0] == HOME){  // Home routine
      Serial.println("Homing");
      delay(30);
      //int dir1 = dataAtPort[1];
      //int dir2 = dataAtPort[2];
      
      directionMotor1 = dataAtPort[1];
      stepStyleMotor1 = DOUBLE;
      directionMotor2 = dataAtPort[2];
      stepStyleMotor2 = DOUBLE;

      ES1 = digitalRead(endStop1Pin);
      ES2 = digitalRead(endStop2Pin);

      for (int current_step = 1; current_step <= 180000; current_step++) {
        if (Serial.available()) { // See if new commands are available at the port
            instruction[0] = Serial.read();

            if (instruction[0] == STOP) { // Check if a stop has been received
              Serial.println("Stop sent");
              break;
            }

            else if (instruction[0] == INFO) { // Get all info on position, sensor and endstop status
              positionStr = "Pos" + (String)positionMotor1 + "," + (String)positionMotor2;              
              positionMotor1 = 0; positionMotor2 = 0;

              sensor_in = analogRead(sensorPin);
              sensor_voltage = (double)sensor_in / 1024;          
              
              Serial.print(positionStr + "Sen");
              Serial.print(sensor_voltage, 6);
              Serial.println("ES" + (String)ES1 + "," + (String)ES2);
            }
        }
        
        //endStop1 = digitalRead(endStop1Pin);
        //endStop2 = digitalRead(endStop2Pin);
        //Serial.println("ES" + (String)endStop1 + "," + (String)endStop2);
        if (!ES1){         
          motor1->onestep(directionMotor1, stepStyleMotor1);
          positionMotor1++;
        }
        if (!ES2){
          motor2->onestep(directionMotor2, stepStyleMotor2);
          positionMotor2++;
        }
        if (ES1 && ES2){
          Serial.println("Home");
          delay(30);
          break;
        }
        //delay(1);
        delayMicroseconds(200);
      }  // End of home for      
    } // End of home routine

    else if (dataAtPort[0] == MOVE) { // Move routine
      // Get all necessary values from buffer
      Serial.println("Moving motors"); 
      Serial.println("Ready"); Serial.flush();
      directionMotor1 = dataAtPort[1];
      directionMotor2 = dataAtPort[2];

      MSB_motor1 = (dataAtPort[3] - 1) * 256; //1 has been added to MSB to avoid null char, decrease by 1
      LSB_motor1 = dataAtPort[4] - 1;
      totalStepsMotor1 = MSB_motor1 + LSB_motor1;

      /*Serial.print("MSB: ");
      Serial.println(MSB_motor1);
      Serial.print("LSB: ");
      Serial.println(LSB_motor1);
      Serial.print("Total steps motor 1: ");
      Serial.println(totalStepsMotor1);*/

      MSB_motor2 = (dataAtPort[5] - 1) * 256; // 1 has been added to MSB to avoid null char, decrease by 1
      LSB_motor2 = dataAtPort[6] - 1;
      totalStepsMotor2 = MSB_motor2 + LSB_motor2;

      /*Serial.print("MSB: ");
      Serial.println(MSB_motor2);
      Serial.print("LSB: ");
      Serial.println(LSB_motor2);
      Serial.print("Total steps motor 2: ");
      Serial.println(totalStepsMotor2)*/

      //maxSteps = (totalStepsMotor1 >= totalStepsMotor2) ? totalStepsMotor1 : totalStepsMotor2;
      //maxSteps = totalStepsMotor1*totalStepsMotor2;
      if (totalStepsMotor1 == 0){
        factor1 = totalStepsMotor2;
        factor2 = 1;
        maxSteps = totalStepsMotor2;
      }
      else if (totalStepsMotor2 == 0){
        factor1 = 1;
        factor2 = totalStepsMotor1;
        maxSteps = totalStepsMotor1;
      }
      else {
        maxSteps = lcm(totalStepsMotor1, totalStepsMotor2);
        factor1 = maxSteps / totalStepsMotor1;
        factor2 = maxSteps / totalStepsMotor2;
      }
      //Serial.println("Steps :" + (String)maxSteps + "f1: " + (String)factor1 + ", f2: " + (String)factor2);

      stepStyleMotor1 = dataAtPort[7];
      stepStyleMotor2 = dataAtPort[8];      

      for (int current_step = 1; current_step <= maxSteps; current_step++) { // Start moving

        if (current_step >= 20) { Home = 0; }  // Release Home flag

        if ((current_step % factor1) == 0 ||
            (current_step % factor2) == 0) {  // At least one motor has to take a step

          if (Serial.available()) { // See if new commands are available at the port
            instruction[0] = Serial.read();

            if (instruction[0] == STOP) { // Check if a stop has been received
              Serial.println("Stop sent");
              break;
            }
            else if (instruction[0] == GET_POS) { // Get position called
              positionStr = "Pos" + (String)positionMotor1 + "," + (String)positionMotor2;
              Serial.println(positionStr);
              positionMotor1 = 0; positionMotor2 = 0;
            }
            else if (instruction[0] == READ) { // Read analog pin
              sensor_in = analogRead(sensorPin);
              sensor_voltage = (double)sensor_in / 1024;
              Serial.print("Sen");
              Serial.println(sensor_voltage, 6);
            }   

            else if (instruction[0] == ENDSTOP){ // Get end-stop status
              endStop1 = digitalRead(endStop1Pin);
              endStop2 = digitalRead(endStop2Pin);
              Serial.println("ES" + (String)endStop1 + "," + (String)endStop2);
            }
            
            else if (instruction[0] == INFO) { // Get all info on position, sensor and endstop status
              positionStr = "Pos" + (String)positionMotor1 + "," + (String)positionMotor2;              
              positionMotor1 = 0; positionMotor2 = 0;

              sensor_in = analogRead(sensorPin);
              sensor_voltage = (double)sensor_in / 1024;          
              
              Serial.print(positionStr + "Sen");
              Serial.print(sensor_voltage, 6);
              Serial.println("ES" + (String)ES1 + "," + (String)ES2);
            }
          } // End of Serial.available within for loop.

          if (totalStepsMotor1 != 0 && (current_step % factor1) == 0) { // Motor 1 takes a step
            motor1->onestep(directionMotor1, stepStyleMotor1);
            positionMotor1++;            
          }

          if (totalStepsMotor2 != 0 && (current_step % factor2) == 0) { // Motor 2 takes a step
            motor2->onestep(directionMotor2, stepStyleMotor2);
            positionMotor2++;            
          }          

          /*if (ES1 && ES2 && !Home){  // If both end-stops are active, stop movement.
            Home = 1;
            ES1 = ES2 = 0;
            Serial.println("Home");
            //break;
          } */
          //delay(wait_ms);
          delayMicroseconds(wait_us);  // Unstable
        }
      } // End for
      delay(50);  // Allow for serial port to empty
      
      positionStr = "Pos" + (String)positionMotor1 + "," + (String)positionMotor2;
     
      Serial.print(positionStr + "Sen");
      Serial.print(sensor_voltage, 6);
      Serial.println("ES" + (String)ES1 + "," + (String)ES2);      
      
      delay(50);
      motor1->release();
      motor2->release();
      Serial.println("fin"); Serial.flush();            
    } // End of movement routine
  }  // End of data available at port
} // End of loop

// Recursive function to return gcd of a and b
long int gcd(int a, int b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

// Function to return LCM of two numbers
long int lcm(int a, int b) {
  return (a / gcd(a, b)) * b;
}

// Interruption routines for End-stops
void endStop1Changed(){
  endStop1 = digitalRead(endStop1Pin);
  if (endStop1){
    endStop1Reached();
  } else {
    endStop1Free();
  }
}

void endStop2Changed(){
  endStop2 = digitalRead(endStop2Pin);
  if (endStop2){
    endStop2Reached();
  } else {
    endStop2Free();
  }
}

void endStop1Reached(){
  if (!bounced()){
    ES1 = 1;    
  }
}

void endStop2Reached(){
  if (!bounced()){
    ES2 = 1;    
  }
}

void endStop1Free(){
  if (!bounced()){
    ES1 = 0;
  }
}

void endStop2Free(){
  if (!bounced()){
    ES2 = 0;
  }
}

// Debounce end-stop switches
unsigned char bounced(){
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if((interrupt_time - last_interrupt_time) > 15){
    last_interrupt_time = interrupt_time;
    return 0;    
  }
  last_interrupt_time = interrupt_time;
  return 1;
}
