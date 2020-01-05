// **** INCLUDES *****
#include <LowPower.h>

int led = 13;//LED pin
// Use pin 2 as wake up pin
const int wakeUpPin = 2;
//
volatile byte state = LOW;
volatile String message = "ok";

void wakeUpInt()
{
    // Just a handler for the pin interrupt.
    // Ici on modifie le flag pour dire qu'une interruption a eu lieu -> 
    message = "alerte";
    Serial.print("Int\n");
    state = !state;
}

void wakeUpPeriod()
{
    // Ici on envoie le message via sigfox, que ce soit ok ou alerte.
    Serial.print("wakeUpPeriod\n");
}

void setup()
{
    Serial.begin(9600);
    Serial.print("setup\n");
    pinMode(led, OUTPUT); //set LED pin as output
    
    // Configure wake up pin as input.
    // This will consumes few uA of current.
    pinMode(wakeUpPin, INPUT);
}

void loop() 
{
    // Allow wake up pin to trigger interrupt on low.
    attachInterrupt(0, wakeUpInt, RISING);
        
    // Enter power down state with ADC and BOD module disabled.
    // Wake up when wake up pin is low.
    Serial.print("************power down\n");
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    
    // Disable external pin interrupt on wake up pin.
    detachInterrupt(0); 
    
    // Do something here
    // Example: Read sensor, data logging, data transmission.
    wakeUpPeriod();

    //Écrire l'état du flag sur la LED pour tester
    digitalWrite(led, state);
    Serial.print("digital\n");
    delay(1);
}
