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
               return Serial.read(); // this func reads one byte at max
        }
    }
}

int wait_FFXX(){
        while (true){
             if (Serial.available() > 0) {
                     c = Serial.read();
                     if (c == 0xFF){
                            while (true){
                                  if (Serial.available() > 0){
                                       c = Serial.read();
                                       if (c==0xFF){
                                           return 0xFF;
                                       }
                                       if (c==0x7F){
                                           return 0x7F;
                                       }
                                       if (c==0x8F){
                                           return 0x8F;
                                       }
                                       if (c==0x9F){
                                           return 0x9F;
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

int get_iopin(int * write_pinnum, char c){
    /*
    digital pins 0,..,25 are enumerated with ascii strings a,..,z
    analog  pins A0,..,A9 are enumerated with ascii strings 0,..,9
    */
    if (c=='g'){return 1;}
    if ( ('0' <= c ) & ( c <= '9' ) ){
        *write_pinnum = c - 48;
        return 0;
    }
    else if ( ('a' <= c ) & ( c <= 'z') ){
        *write_pinnum = c - 97;
        return 0;
    }
    return 1;
}



void loop() {
        int mode;
        //Serial.println("waiting for 0xFFFF or 0xFF7F");
        mode=wait_FFXX();
        if (mode == 0x7F){
            Serial.println("one-character-send-mode active");
            c = read_single_char();
            rr[0] = c;
            transmitter.send( rr , 1 );
            Serial.print("byte transmitted: ");
            Serial.println(rr[0]);
               }
        else if (mode == 0x8F){
            Serial.print("gpio out ");
            c=read_single_char();
            int pin_num;
            if (get_iopin( &pin_num, c ) == 0 ){
               Serial.print("pin=");
               Serial.print(pin_num,DEC);
               Serial.print(" ");
               pinMode(pin_num,OUTPUT);
               c=read_single_char();
               Serial.print("write=");
               Serial.println( c && 1 , DEC);
               digitalWrite(pin_num, c && 1);
            }
            else{
                Serial.println("ERROR: wrong pin");
            }
        }
        else if (mode == 0x9F){
            Serial.print("gpio read ");
            c=read_single_char();
            int pin_num;
            if (get_iopin( &pin_num, c ) == 0 ){
                Serial.print("pin=");
                Serial.print(pin_num,DEC);
                Serial.print(' ');
                pinMode(pin_num,INPUT);
                Serial.print("read=");
                Serial.println( digitalRead(pin_num) , DEC);
            }
            else{
                Serial.println("ERROR: wrong pin");
            }
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



