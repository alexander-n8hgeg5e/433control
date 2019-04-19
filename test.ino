void setup() {
  // put your setup code here, to run once:
 pinMode(2, OUTPUT);
}

void loop() {
  int pin = 2;
  // put your main code here, to run repeatedly:
digitalWrite(pin, HIGH);    // sets the digital pin 13 on
delay(1000);
digitalWrite(pin, LOW);       // sets the digital pin 13 on
delay(1000);  
}
