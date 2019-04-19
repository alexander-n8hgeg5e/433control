
const int pin = 2;
const long LIMIT = 1000000;
const int BIT_PER_BLOCK = 512;
unsigned int data[BIT_PER_BLOCK];
boolean code[BIT_PER_BLOCK];
int codelen =0;
int i;
unsigned long a;
void setup(){
	Serial.begin(19200);
	pinMode(pin, INPUT);}
    
    	boolean pinlow(){
    		if (digitalRead(pin) == LOW){
                	delayMicroseconds(33);
                     		if (digitalRead(pin) == LOW){
                            		return true;}}
    				else{return false;}}
    
    boolean pinhigh(){
    if (digitalRead(pin) == HIGH){
                delayMicroseconds(33);
                     if (digitalRead(pin) == HIGH){
                            return true;}}
    			 else{return false;}}

    void loop() {
      for(int i = 0 ; i < BIT_PER_BLOCK; i++) {
      	data[i]=0xFFFF;
      }
      boolean done = false;
     boolean started=false;
      for(int i = 0 ; i < BIT_PER_BLOCK/2 ; i++) {
      	while(not started){
	  	if (pinlow() == true){a=micros();started=true;}}
        while(true){
		if ((micros() - a) > LIMIT){
			Serial.println("limit pinlow reached");
                        done=true;
			data[i*2]=0xFFFE;
			break;}
		if (pinhigh() == true){
			data[i*2] = micros() - a ; a = micros();break;}}
        while(true){
		if ((micros() - a) > LIMIT){
			Serial.println("limit pinhigh reached");
			data[i*2]=0xFFFE;
                        done=true;
			break;}
		if (pinlow() == true){
			data[i*2+1] = micros() - a ; a = micros();break;}}
        if (done){break;}}

	Serial.println("results:");
        for(i = 0 ; i < BIT_PER_BLOCK ; i++){
		if ((data[i] != 0xFFFF) and (data [i] != 0xFFFE) ){
	 		Serial.println(data[i]);}
		if (data[i] == 0xFFFE){
	 		Serial.println("some limit was reached here");}}}
