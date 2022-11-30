#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const byte address[6] = "00011";//constant data-type to receive radio frequency
RF24 radio(8,7);               //(CE, CNF)
int arr[5];                     //integer data-type to store array
int X1;                         //integer data-type to store vaiables
int Y1;
int X2;
int Y2;
int Value;                      //integer data-type to store vaiables
const int IN1 = 3;              //constant data-type to define the pin number of motors
const int IN2 = 4;
const int IN3 = 5;
const int IN4 = 6;
const int ENa = 9;
const int ENb = 10;
int Hspeed=255;
int Lspeed=100;

void setup() 
{
  Serial.begin(9600);               //baud rate for serial monitor
  radio.begin();                    //to start wireless communication
  radio.setDataRate(RF24_250KBPS);  //communication frequency
  radio.openReadingPipe(0,address); //setting address where we will send data
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();           //end of the communication
  Serial.println("SETUP DONE");  
  
  pinMode(IN1,OUTPUT);    //left motor front
  pinMode(IN2,OUTPUT);    //left motor back
  pinMode(IN3,OUTPUT);    //right motor front
  pinMode(IN4,OUTPUT);    //right motor back  
}

void loop()
{
  if (radio.available())          //if we are receiving signals then
  { 
    radio.read(&arr, sizeof(arr));//we are receiving this arrays from the transmiter side
    X1=arr[0];                    //take this variable from this array
    Y1=arr[1];
    X2=arr[2];
    Y2=arr[3];
    Value=arr[4];               //take this variable from this array
    Serial.print(Value);
    Serial.print("\t");
    Serial.print(X1);
    Serial.print("\t");
    Serial.print(Y1);
    Serial.print("\t");
    Serial.print(X2);
    Serial.print("\t");
    Serial.print(Y2);
    Serial.println("");
    
    switch(Value)    //according to the variable received from transmiter it will switch to that case below
    {                //making cases for all the below functions
      
      case 1:        //forward
        Forward();
      break;
      case 2:        //back
        Back();
      break;
      case 3:        //right
        Right(); 
      break;
      case 4:        //left
        Left();
      break;
      default:       //stop
        Stop();
      break;
    }
  }
}

void Forward()                //declaring function
{
 X1= map(X1,127,255,0,255);   //mapping value of joystick to speed of motor according to arduino
 digitalWrite(IN1,HIGH);      //motor direction
 digitalWrite(IN3,HIGH);      //motor direction
 analogWrite(ENa,X1);         //motor speed
 analogWrite(ENb,X1);         //motor speed
 Serial.println("Forward");
}


void Back()
{
 X1= map(X1,127,0,0,255);
 digitalWrite(IN2,HIGH);      
 digitalWrite(IN4,HIGH);      
 analogWrite(ENa,X1);         
 analogWrite(ENb,X1);         
 Serial.println("Back");
}

void Left()
{
 digitalWrite(IN1,HIGH);
 digitalWrite(IN3,LOW);      
 analogWrite(ENa,255);       
 Serial.println("Left");
}

void Right()
{
 digitalWrite(IN3,HIGH);
 digitalWrite(IN2,LOW);      
 analogWrite(ENb,255);         
 Serial.println("Right");
}

void Stop()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  Serial.println("Stop");
}
