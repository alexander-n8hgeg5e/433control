#define   TXPIN 6
#define IRTXPIN 9
#define MAXCODELEN 500
#define numberdatatype unsigned short
#define NODE_ID          1

#include <RFTransmitter.h>
RFTransmitter transmitter(TXPIN, NODE_ID);


numberdatatype code[MAXCODELEN];
numberdatatype a;

#define TMODE_RF 1
#define TMODE_IR 2
int transmit_mode=0;
int tx_state=0;
int ledState = LOW;
unsigned int interval;
unsigned short counter_thing_to_send = 0;
unsigned int  b1;
unsigned int  b2;
unsigned int  c;
unsigned char rr[1];
int r0a;
int r0b;
//int transmitting = 0;
int tccr0b;
int tccr0a;
int timsk0;


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
    		  if (code[i] == 0){break;}
              Serial.print(code[i]);
              Serial.print(" ");
              if ((i+1)%20 == 0 ){
              Serial.println();}
        }
              Serial.println();
        }

void setup_ir_pwm(){
	// output on pin PD3(uno pin 3) with alternate function OC2B

	// timer2 config
	#define OCIE2AV   0b0
	#define OCIE2BV   0b0
	#define TOIE2V    0b0
	#define  WGM2V  0b101 // count to OCR2A
	#define  COM2AV  0b00 // disconnected 
	#define  COM2BV  0b10 // connect output pin PD3 to OC2B
	#define   CS2V  0b001 // prescaler
	#define  FOC2AV   0b0
	#define  FOC2BV   0b0
	#define  OCR2AV   0b10000000 // count to half of 8bit
	#define  OCR2BV   0b10000000 // 50% duty cylce

	#define WGM20V (WGM2V & 0b1)
	#define WGM21V (WGM2V & 0b10)
	#define WGM22V (WGM2V & 0b100)
	 TCCR2A = 0 | ( COM2AV<< COM2A0)  | ( COM2BV<< COM2B0)  | ( WGM21V<< WGM21) | (WGM20V<<WGM20);
	 TCCR2B = 0 | ( FOC2AV<< FOC2A)   | ( FOC2BV<< FOC2B)   | ( WGM22V<< WGM22) | ( CS2V << CS20);
	TIMSK2  = 0 | (OCIE2AV<<OCIE2A)   | (OCIE2BV<<OCIE2B)   | (TOIE2V <<TOIE2);
     TCNT2  = 0; //timer counter
	//ASSR = (0<<EXCLK) & (0<<AS2); //asynchronous status register
	OCR2A = OCR2AV;
	OCR2B = OCR2BV;

	// pin config, enable pin as output
	DDRD |= (1 << 3);
	}

void disable_ir_pwm(){
	// timer2 config
	#define OCIE2AV0   0b0
	#define OCIE2BV0   0b0
	#define TOIE2V0    0b0
	#define  COM2AV0  0b00 // disconnect 
	#define  COM2BV0  0b00 // disconnect
	#define   CS2V0  0b000 // stop timer
	#define  FOC2AV0   0b0
	#define  FOC2BV0   0b0

	 TCCR2A = 0 | ( COM2AV0<< COM2A0)  | ( COM2BV0<< COM2B0)  | ( WGM21V<< WGM21) | (WGM20V<<WGM20);
	 TCCR2B = 0 | ( FOC2AV0<< FOC2A)   | ( FOC2BV0<< FOC2B)   | ( WGM22V<< WGM22) | ( CS2V0<< CS20);
	TIMSK2  = 0 | (OCIE2AV0<<OCIE2A)   | (OCIE2BV0<<OCIE2B)   | (TOIE2V0 <<TOIE2);
     TCNT2  = 0; //timer counter
	//ASSR = (0<<EXCLK) & (0<<AS2); //asynchronous status register
	OCR2A = OCR2AV;
	OCR2B = OCR2BV;

	// disable output mode for pin
	DDRD &= ~(1 << 3);
	}

/*
TCCR0A := timer counter control register 0A
TCCR0B := timer counter control register 0B
TIMSK0 := timer interrupt mask 0
		  This register has 3 output compare interupt enable bits.
TCNT0  := timer count 0
		  This is the counter value of timer 0.
*/

void enable_interrupt(){
    cli();
	#define OCIE0AV   0b1  //enable interrupt comperator A
	#define OCIE0BV   0b0
	#define TOIE0V    0b0
	#define  WGM0V  0b010
	#define  COM0AV  0b01 // toggle mode for pin oca0 aka pd6
	#define  COM0BV  0b00 // disconnected from pin
	#define   CS0V  0b101 // clocksource = io-clock/1024
	#define  FOC0AV   0b0
	#define  FOC0BV   0b0
	#define  OCR0AV   0b00000000
	#define  OCR0BV   0b00000000

	#define WGM00V (WGM0V & 0b1)
	#define WGM01V (WGM0V & 0b10)
	#define WGM02V (WGM0V & 0b100)
	 TCCR0A = 0 | ( COM0AV<< COM0A0)  | ( COM0BV<< COM0B0)  | ( WGM01V<< WGM01) | (WGM00V<<WGM00);
	 TCCR0B = 0 | ( FOC0AV<< FOC0A)   | ( FOC0BV<< FOC0B)   | ( WGM02V<< WGM02) | ( CS0V << CS00);
	TIMSK0  = 0 | (OCIE0AV<<OCIE0A)   | (OCIE0BV<<OCIE0B)   | (TOIE0V <<TOIE0);
     TCNT0  = 0; //timer counter
	OCR0A = OCR0AV;
	OCR0B = OCR0BV;
    sei();
        }

void disable_interrupt(){
    cli();
	#define OCIE0AV0   0b0
	#define OCIE0BV0   0b0
	#define TOIE0V0    0b0
	#define  COM0AV0  0b00 // disconnect 
	#define  COM0BV0  0b00 // disconnect
	#define   CS0V0  0b000 // stop timer
	#define  FOC0AV0   0b0
	#define  FOC0BV0   0b0
    // normal pin operation of pin OCA0 aka PD6
	TCCR0A = 0 | ( COM0AV0<< COM0A0)  | ( COM0BV0<< COM0B0)  | ( WGM01V<< WGM01) | (WGM00V<<WGM00);
	// disable interrupt
	TIMSK0 = 0b000;
    sei();
    }

void disable(){
	disable_interrupt();
	if (transmit_mode == TMODE_IR){
		disable_ir_pwm();
		}
	else if (transmit_mode == TMODE_RF){
    	digitalWrite(TXPIN, LOW);
		}
	}

ISR(TIMER0_COMPA_vect) {
    TCNT0  = 0;//first reset counter
	tx_state=~tx_state;
    if (code[counter_thing_to_send] == 0 && counter_thing_to_send%2==0){disable();return;}
    if (counter_thing_to_send > MAXCODELEN){disable();return;}
    OCR0A  = round((16.0 * (code[counter_thing_to_send])/1000));
    counter_thing_to_send++;
	/*
	if ( tx_state != 0 ){
		TCCR0A &= ~(0b1 << COM0A0);
		}
	else{
		TCCR0A |=  (0b1 << COM0A0);
		}
	*/
	if (transmit_mode == TMODE_IR){
		if ( tx_state != 0 ){
			TCCR2A |=  (0b1 << COM2B1);
			}
		else{
			TCCR2A &= ~(0b1 << COM2B1);
			}
		}
	}

void transmit_ir() {
	transmit_mode=2;
    counter_thing_to_send=0;
    ledState = LOW;
	setup_ir_pwm();
    enable_interrupt(); 
    while (0){ }
	}

void transmit_rf() {
	transmit_mode=TMODE_RF;
    counter_thing_to_send=0;
    pinMode(TXPIN, OUTPUT);
    digitalWrite(TXPIN, LOW);
    ledState = LOW;
    enable_interrupt();
    while (0){ }
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
                                       if (c==0xA0){
                                           return 0xA0;
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

void setup() {
	Serial.begin(500000);
	Serial.println("serial on");
        //Serial.println("code transmitter online. send code to serial. \n reset with 2 zero byte.");
        //Serial.println("maxcodelen= " + MAXCODELEN )
	//setup_ir_pwm();
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
			
			if (mode == 0xA0){
				Serial.println("transmitting ir...");
				transmit_ir();
			}
			else{
				Serial.println("transmitting 433Mhz rf...");
				transmit_rf();
			}
    }
	}


// vim: set foldlevel=0 foldmethod=indent foldnestmax=1 :
