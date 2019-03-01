
#include <IRremote.h>

int RECV_PIN = 11;


// buttons mapping 
const long poweron = 16617583;
const long go = 16625743;
const long one = 16611973;
const long two = 16605343;
const long three = 16621663;
const long four = 16638493;
const long timer = 16620133;
const long coolerB = 16632373;

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


void handleTimer(){


  while (irrecv.decode(&results)){
      long currentValue = results.value;
      Serial.println("in timer");
      Serial.println(currentValue);
      delay(500);


    irrecv.resume();
  }
  
}
void sleeper(int tm){

  delay(tm*1000*60);

  
  
}
void cooler(){

  while (1==1){
    delay(500);
        int ctime = 0;
        byte k=0;
        while(k==0){
          
          if(irrecv.decode(&results)){
            long currentValue = results.value;
            Serial.println("in cooler");
            Serial.println(currentValue);
            
          switch(currentValue){
            case one: ctime=1;
                      k=1;
                      break;
            case two: ctime=2;
                      k=1;
                      break;
            case three: ctime=3;
                        k=1;
                      break;
            case four: ctime=4;
                      k=1;
                      break;
            
          }
          irrecv.resume();

        }
        }
        while(1){
//          delay(100);
//          if(irrecv.decode(&results)){
//            long currentValue = results.value;
//            if(currentValue = poweron)
//            {
//              return;
//            }
//          }
//          irrecv.resume();
           Serial.println("in main cooler");
           Serial.println(ctime);
           digitalWrite(6,HIGH);
           sleeper(ctime);
           digitalWrite(6,LOW);
           sleeper(ctime);
        }
      }

   
  
}




void(* resetFunc) (void) = 0;

void loop()
{
  if (irrecv.decode(&results))
    {
      long currentValue = results.value;
      Serial.println(currentValue);
      if(currentValue == poweron){
        resetFunc();
      }
      else if(currentValue == timer){
        irrecv.resume();

        handleTimer();
      }
      else if(currentValue == coolerB){
        irrecv.resume();
        cooler();
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
