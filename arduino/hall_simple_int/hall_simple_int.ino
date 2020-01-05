int led = 13;//LED pin
const byte interruptPin = 2; //sensor pin
int val; //numeric variable
volatile byte state = LOW;


void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT); //set LED pin as output
  pinMode(interruptPin, INPUT_PULLUP); //set sensor pin as interrupt pin
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING);
}

void loop()
{
  digitalWrite(led, state);
  delay(1);

}

void blink() {
  Serial.print("Interrupt\n");
  state = !state;
}
