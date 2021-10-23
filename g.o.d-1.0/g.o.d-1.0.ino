/*
  CREATED IN 2016 AND 2021
  BY ALEXGYVER 
  FINISHED JIGURDAS 
*/
#include <avr/sleep.h>            

volatile unsigned long lastshot;  
boolean trig_state;            
boolean flag;                  
boolean trigger;               
boolean mode;                  
byte del_shot = 10;             
byte n_shots=3;                

byte mode_pin = 12;            
byte trigger_pin = 2;          
byte solen_pin = 8;            
byte valve_pin = 3;            
boolean signal_shot = 1;       

void setup() {
  Serial.begin(9600);
  pinMode(mode_pin, INPUT_PULLUP);            
  pinMode(trigger_pin, INPUT_PULLUP);         
  pinMode(valve_pin, OUTPUT);                 
  digitalWrite(valve_pin, !signal_shot);      
  pinMode(solen_pin, OUTPUT);                 
  attachInterrupt(0, trigger_press, FALLING); 
}

void shot() { 
  digitalWrite(valve_pin, signal_shot);   
  delay(del_shot);                        
  digitalWrite(valve_pin, !signal_shot);  
  delay(10);                              
  digitalWrite(solen_pin, 1);             
  delay(40);                              
  digitalWrite(solen_pin, 0);             
  delay(40);                              
  lastshot = millis();                    
}

void loop() {
  trig_state = digitalRead(trigger_pin); 
  if (digitalRead(mode_pin) == 1) {     
    mode = 0;
  } else {
    mode = 1;
  }

  if (trig_state == 0 && mode == 0 && flag == 0) { 
    shot();
    flag = 1;                                      
  }

  if (trig_state == 1 && mode == 0 && flag == 1) { 
    flag = 0;  
  }

  if (trig_state == 0 && mode == 1 && flag == 0) { 
    for (int i=0; i<n_shots; i++) {
      shot();                                      
    }
  }

  // этот кусок даёт команду спать
  if (millis() - lastshot > 10000) {        
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);   
    sleep_mode();                          
  }
  // конец куска

  delay(1);       
}

void trigger_press() { 
                       
}
