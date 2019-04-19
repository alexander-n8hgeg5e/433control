#define TXPIN 6
#define MAXCODELEN 500
#define numberdatatype unsigned short
#define NODE_ID          1

#include <RFTransmitter.h>
RFTransmitter transmitter(TXPIN, NODE_ID);


numberdatatype code[MAXCODELEN];
numberdatatype a;

int ledState = LOW;
unsigned int interval;
unsigned short counter_thing_to_send = 0;
unsigned int  b1;
unsigned int  b2;
unsigned int  c;
unsigned char rr[1];
int r0a;
int r0b;
int transmitting = 0;
int tccr0b;
int tccr0a;
int timsk0;

void setup() {
	Serial.begin(500000);
	Serial.println("serial on");
        pinMode(TXPIN, OUTPUT);
        //Serial.println("code transmitter online. send code to serial. \n reset with 2 zero byte.");
        //Serial.println("maxcodelen= " + MAXCODELEN );
}


numberdatatype read(){
        while (true){
             if (Serial.available() > 0) {
                    b1 = Serial.read();
                    break;
             }
        }
        while (true){
             if (Serial.available() > 0) {
                    b2 = Serial.read();
                    break;
             }
        }
        //Serial.print( b1 << 8 | b2);
        return b1 << 8 | b2;
}



void printcode(){
        for (int i = 0 ;i < int(MAXCODELEN); i++){
              Serial.print(code[i]);
              Serial.print(" ");
              if (i%20 == 0 ){
              Serial.println();}
        }
              Serial.println();
        }

void save_regs(){
          cli();
          //Serial.println( "save" );
          timsk0 = TIMSK0;
          tccr0a= TCCR0A;
          tccr0b= TCCR0B;
          //Serial.println( timsk0 );
          //Serial.println( tccr0a );
          //Serial.println( tccr0b );
          //Serial.println( TIMSK0 );
          //Serial.println( TCCR0A );
          //Serial.println( TCCR0B );
          sei();
        }

void restore_regs(){
          cli();
          //Serial.println( "restore" );
          TIMSK0 = timsk0;
          TCCR0A = tccr0a;
          TCCR0B = tccr0b;
          //Serial.println( TIMSK0 );
          //Serial.println( TCCR0A );
          //Serial.println( TCCR0B );
          sei();
        }
/*void print_regs(){
          cli();
          Serial.println( "regs:" );
          Serial.println( TIMSK0 );
          Serial.println( TCCR0A );
          Serial.println( TCCR0B );
          Serial.println( "regs>" );
          sei();
}
*/
void enable_interrupt(){
          cli();
          save_regs();
          TIMSK0 = 0 | (1 << OCIE0A);    //enable interrupt comperator A
          TCCR0A = 0 | (1 << COM0A0 );             // toggle pin oca0 aka pd6
          TCCR0B = 0 | (1 << CS02) | (1 << CS00); // clocksource = io-clock/1024
          TCNT0  = 0; //timer counter 0
          sei();
        }

void disable_interrupt(){
          cli();
          TCCR0A = 0;             // normal pin operation of pin oca0 aka pd6
          restore_regs();
          sei();
        }

ISR(TIMER0_COMPA_vect) {
         TCNT0  = 0;//first reset counter
         counter_thing_to_send++;
         if (code[counter_thing_to_send] == 0){disable_interrupt();}
         if (counter_thing_to_send > MAXCODELEN){disable_interrupt();}
         OCR0A = round((16 * code[counter_thing_to_send])/1000);
}


void transmit() {
          counter_thing_to_send=0;
          digitalWrite(TXPIN, LOW);
          ledState = LOW;
          enable_interrupt();
          //print_regs();
        
          while (transmitting){ }
          digitalWrite(TXPIN, LOW);
    }

int read_single_char(){
while (true){
      if (Serial.available() > 0){
           return Serial.read();}
}}

int wait_for_16bitFFFF(){
        while (true){
             if (Serial.available() > 0) {
                     c = Serial.read();
                     if (c == 0xFF){
                            while (true){
                                  if (Serial.available() > 0){
                                       c = Serial.read();
                                       if (c==0xFF){
                                           return 1;
                                       }
                                       if (c==0x7F){
                                           return 2;
                                       }
                                       else{
                                           break;
                                       }
                                  }
                            }
                     }
             }

        }
}


void loop() {
        //Serial.println("waiting for 0xFFFF ");
        if (wait_for_16bitFFFF() == 2){
                Serial.println("one-character-send-mode active");
                c = read_single_char();
                rr[0] = c;
                transmitter.send( rr , 1 );
                Serial.print("byte transmitted: ");
                Serial.println(rr[0]);
               }
        else{
        
        for (int i = 0 ;i < MAXCODELEN; i++){
	      a = read();
              if ( a == 0 ){
                           code[i]=0;
                           Serial.println("received double0. done capturing.");
                           break;
              }
              else{
                      code[i]=a;
              }
        }
        //Serial.println("here the code..");
        //printcode();
        Serial.println("transmitting...");
        transmit();
        }
}



