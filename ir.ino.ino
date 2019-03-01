
#include <IRremote.h>

int RECV_PIN = 11;


// buttons mapping 
const long poweron = 16617583;
const long go = 16625743;
const long one = 16611973;
const long two = 16605343;
const long three = 16621663;
const long four = 16638493;
const timer = 16620133;

byte r1 = 0;
byte r2 = 0;
byte r3 = 0;
byte r4 = 0;



IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{

  // relay pins
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}










void loop()
{
  if (irrecv.decode(&results))
    {
      long currentValue = results.value;
      Serial.println(currentValue);
      if(currentValue == poweron){
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        r1 = 0;
        r2 = 0;
        r3 = 0;
        r4 = 0;
      }
      else if(currentValue == timer){
        handleTimer();
      }
      else{

      switch(currentValue){

          case one : if(r1 == 0){
                      digitalWrite(6, HIGH);
                      r1=1;
                      }
                     else{
                      digitalWrite(6, LOW);
                      r1=0;
                      
                     }
                     break;

           case two : if(r2 == 0){
                      digitalWrite(7, HIGH);
                      r2=1;
                      }
                     else{
                      digitalWrite(7, LOW);
                      r2=0;
                      
                     }
                     break;
                     
           case three : if(r3 == 0){
                        digitalWrite(8, HIGH);
                        r3=1;
                      }
                      else{
                        digitalWrite(8, LOW);
                        r3=0;
                      
                     }
                     break;
           case four : if(r4 == 0){
                        digitalWrite(9, HIGH);
                        r4=1;
                      }
                      else{
                        digitalWrite(9, LOW);
                        r4=0;
                      
                     }
                     break;

          default :Serial.println("ERROR KEY");
                    
    

        
        }
      }

      
     
     irrecv.resume(); // Receive the next value
     
    }
}
