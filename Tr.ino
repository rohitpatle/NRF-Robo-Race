#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const byte my_radio_pipe[6] = "00011"; //constant data-type to define radio frequency
RF24 radio(7,8);                      //(CE, CNF)
int arr[5];                            //integer data-type to store array
int X1;                                //integer data-type to store vaiables
int Y1;
int X2;
int Y2;
int Value;                             //integer data-type to store vaiables

void setup()
{
  Serial.begin(9600);                   //baud rate for serial monitor
  radio.begin();                        //to start wireless communication
  radio.setDataRate(RF24_250KBPS);      //communication frequency
  radio.openWritingPipe(my_radio_pipe); //setting address where we will send data
  radio.stopListening();                //end of the communication
  Value = 0;
  Serial.println("SETUP DONE");
}

void loop()
{
  X1 = map( analogRead(A0), 0, 1023, 0, 255); //mapping value of joystick to speed of motor according to arduino
  Y1 = map( analogRead(A1), 0, 1023, 0, 255);
  X2 = map( analogRead(A2), 0, 1023, 0, 255);
  Y2 = map( analogRead(A3), 0, 1023, 0, 255);
  arr[0] = X1;
  arr[1] = Y1;
  //arr[2] = X2;
  arr[3] = Y2;
  arr[4] = Value;
  //following are the statements to give conditions

  if (X1 > 130) {
    Value = 1;                //forward
  }
  else if (X1 < 121) {
    Value = 2;                //back
  }
  else if (Y2 > 133) {
    Value = 3;                //right
  }
  else if (Y2 < 123) {
    Value = 4;                //left
  }
  else {
    Value = 0;                //stop
  }

  Serial.print(Value);
  Serial.print("\t");
  Serial.print(X1);
  Serial.print("\t");
  Serial.print(Y1);
  Serial.print("\t");
  Serial.print(X2);
  Serial.print("\t");
  Serial.print(Y2);
  Serial.print("\t");
  Serial.println("");

  radio.write(&arr, sizeof(arr));              //we are sending this arrays to the receiver side
}
