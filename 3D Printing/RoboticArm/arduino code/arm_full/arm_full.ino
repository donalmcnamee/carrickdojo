/*
Very simple control of a robotic arm (using servos). Direct control of joint/servo positions using
buttons and a potentiometer. One servo controls base rotation, two move the lowest joint, one moves the middle joint,
one moves the upper joint, and one opens/closes the gripper.


created 4/18/2014
*/

#include <Servo.h>
Servo base;
Servo lower1;
Servo lower2;
Servo mid;
Servo upper;
Servo grip;
                    
const int pot = A0;        // define pot as pin A0
const int button1 = 7;     // define buttons
const int button2 = 6;
const int button3 = 5;
const int button4 = 4;
const int button5 = 3;
const int button6 = 2;
const int button7 = A3;
const int button8 = A4;

int potState;
int potStatePrev;
int buttonState1;
int buttonState2;             // the current reading from the input pin
int buttonState3;
int buttonState4;
int buttonState5;
int buttonState6;
int buttonState7;
int buttonState8;

int posB = 0;
int posL = 90;               // positions for each joint
int posM = 90;
int posU = 90;
int posG = 120;

int num = 0;

const int Delay = 10; // ms delay for servo motions

//-----------------------------------------------------------------------------------------

void setup() {
  Serial.begin(9600);
  
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(button5, INPUT);
  pinMode(button6, INPUT);
  pinMode(button7, INPUT);
  pinMode(button8, INPUT);
  
  base.attach(8, 771, 1798);     // setup servo connections - probably need custom values for each servo
  lower1.attach(9, 600, 2100);
  lower2.attach(10, 600, 2100);
  mid.attach(11, 600, 2100);
  upper.attach(12, 600, 2100);
  grip.attach(13, 600, 2400);
  
  base.write(posB);         // set all servos to start at "mid" positions 
  lower1.write(posL);
  lower2.write(180-posL);
  mid.write(posM);
  upper.write(posU);
  grip.write(posG);
  
  potState = analogRead(pot);
  potStatePrev = potState;

}

//-----------------------------------------------------------------------------------------
/*
void knobServoControl(Servo servo, int potState, int potStatePrev, int pos){
  if (potState != potStatePrev){
    pos = map(potState, 0, 1023, 0, 179); 
    servo.write(pos); }
  delay(Delay); 
}

void singleServoControl(Servo servo, int buttonStateD, int buttonStateU, int pos){
  if (buttonStateU == HIGH){
        pos += 1; // increase position of servo
        if (pos > 175){ pos = 175;} // bound "pos" variable to keep from drifting at ends
        servo.write(pos); // write new position
        delay(Delay); // wait      
    }
  if (buttonStateD == HIGH){
        pos -= 1; 
        if (pos < 2){ pos = 2;}
        servo.write(pos); 
        delay(Delay);       
    } 
}


void dualServoControl(Servo servo1, Servo servo2, int buttonStateD, int buttonStateU, int pos){
  if (buttonStateU == HIGH){
        pos += 1; 
        if (pos > 175){ pos = 175;} 
        servo1.write(pos); 
        servo2.write(180-pos);
        delay(Delay); //wait      
    }
  if (buttonStateD == HIGH){
        pos -= 1; //increase position of servo
        if (pos < 2){ pos = 2;}
        servo1.write(pos); //write new position
        servo2.write(180-pos);
        delay(Delay); //wait      
    } 
}
*/

//-----------------------------------------------------------------------------------------

void loop(){
  potState = analogRead(pot); 
  int buttonState1 = digitalRead(button1);    
  int buttonState2 = digitalRead(button2);   
  int buttonState3 = digitalRead(button3);    
  int buttonState4 = digitalRead(button4);
  int buttonState5 = digitalRead(button5);    
  int buttonState6 = digitalRead(button6); 
  int buttonState7 = digitalRead(button7);
  int buttonState8 = digitalRead(button8);
 
  //knobServoControl(base, potState, potStatePrev, posB); // move base
  //dualServoControl(lower1, lower2, buttonState1, buttonState2, posL); // move lower joint
  //singleServoControl(mid, buttonState3, buttonState4, posM); // move middle joint
  //singleServoControl(upper, buttonState5, buttonState6, posU); // move upper joint
  //singleServoControl(grip, buttonState7, buttonState8, posG); // move gripper
  
  //base
  if (buttonState1 == LOW && buttonState2 == LOW && buttonState3 == LOW && buttonState4 == LOW && buttonState5 == LOW && buttonState6 == LOW && buttonState7 == LOW && buttonState8 == LOW){

    posB = map(potState, 0, 1024, 0, 179); 
    //Serial.print("Writing to the base servo ");
   num=posB;
    //Serial.println(posB);
    base.write(posB); 
    delay(Delay); 
    
  }
  
  
  //lower
    if (buttonState1 == HIGH){
        Serial.println("Button 1 high");
        posL += 1; // increase position of servo
        if (posL > 175){ posL = 175;} // bounds "pos" variable to prevent drifting at limits
        lower1.write(posL); // write new position
        lower2.write(180-posL);
        delay(Delay); // wait      
    }
  if (buttonState2 == HIGH){
        Serial.println("Button 2 high");
        posL -= 1; // decrease position of servo
        if (posL < 4){ posL = 4;}
        lower1.write(posL); 
        lower2.write(180-posL);
        delay(Delay);      
    }
  
  //mid
      if (buttonState3 == HIGH){
        Serial.println("Button 3 high");
        posM += 1; 
        if (posM > 180){ posM = 180;} 
        mid.write(posM);
        delay(Delay);    
    }
      if (buttonState4 == HIGH){
        Serial.println("Button 4 high");
        posM -= 1; 
        if (posM < 0){ posM = 0;}
        mid.write(posM); 
        delay(Delay);     
    }

  //upper
        if (buttonState5 == HIGH){
        Serial.println("Button 5 high");
        posU += 1; 
        if (posU > 180){ posU = 180;} 
        upper.write(posU); 
        delay(Delay);       
    }
      if (buttonState6 == HIGH){
        Serial.println("Button 6 high");
        posU -= 1; 
        if (posU < 0){ posU = 0;}
        upper.write(posU); 
        delay(Delay);      
    }

  //gripper
      if (buttonState7 == HIGH){
        Serial.println("Button 7 high");
        posG += 1; 
        if (posG > 90){ posG = 90;} 
        grip.write(posG); 
        delay(Delay);       
    }
      if (buttonState8 == HIGH){
        Serial.println("Button 8 high");
        posG -= 1; 
        if (posG < 0){ posG = 0;}
        grip.write(posG); 
        delay(Delay);     
    }
  
  
  
  
  
  
  
  
  
  
  potStatePrev = potState;
}


// CHECK FOR LAG IN SERVO RESPONSIVENESS
// COULD ALSO DO A SWITCH CASE WITH BUTTON STATES -- MIGHT BE MORE RESPONSIVE
