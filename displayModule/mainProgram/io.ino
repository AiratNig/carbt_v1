#define LED_PIN				PA5
#define LED_PWM				OCR1B
#define BUZZER0				PA2
#define BUZZER1				PB2				
#define BTN0				PB0
#define BTN1				PB1
#define BTN2				PA7
#define BTN3				PA3

#define F_CPU 8000000UL


void ioInit() {
	DDRA &= ~((1<<BTN2)|(1<<BTN3));		//buttons 2 and 3 are inputs
	DDRA |= ((1<<BUZZER0)|(1<<LED_PIN));	//buzzer control 0 and LED pwn pin are outputs
	
	DDRB &= ~((1<<PB0)|(1<<PB1));		//set PB0 and PB1 as inputs
	DDRB |= (1<<BUZZER1);				//buzzer control 1 is an output
	
	//TCCR0A = (1<<COM0A1)|(1<<WGM00);  //pwm for pb2 oc0a, just an extra pwm output if needed later
	TCCR1A = (1<<COM1B1)|(1<<WGM10);  	//pwm for pa5 oc1b, the LCD backlight LED
}


//sets the backlight LED PWM brightness value, needs a value from 0 to 255
//0 is basically off, 255 is max brightness
void writeLED(uint8_t brightness) {
	LED_PWM = brightness;
}


//extracts the data recieved from the Pi, and sets the buzzer accordingly
void setBuzzer(uint8_t dataIn) {
	uint8_t mode = (dataIn & 0x80) >> 7;
	uint8_t tone = (dataIn & 0x60) >> 5;
	uint8_t duration = (dataIn & 0x1F) * 50;
	
	// for(char i = 0; i <= (dataIn & 0x1F); i++) {
		// writeBuzzer(1);
		// delay(100);
		// writeBuzzer(0);
		// delay(100);
	// }
	
	//check the buzzer operation mode first
	if(mode == 0) {									//sets the buzzer indefinitely (pi handles the duration)
		writeBuzzer(tone);							//writes the specified buzzer tone
		buzzerStartFlag = false;					//make sure these two vars are false, in case the Pi tried force stopping the buzzer
		buzzerRunning = false;
	}
	else {											//sets the buzzer for a specific duration handled by us
		buzzerTone = tone;
		buzzerDuration = duration;
		buzzerStartFlag = true;						//we got all the data out that we need, so start the buzzer now
	}
}


//runs the buzzer for a specified amount of time, call this continuously for good operation
void checkBuzzer() {
	if(buzzerStartFlag == true) {				//if the buzzer needs to be started
		buzzerStartFlag = false;				//we now know to get it going
		buzzerRunning = true;					//yeah
		buzzerStartTime = millis();				//get the current time, which is the time we started the buzzer
		writeBuzzer(buzzerTone);				//start the buzzer with the specified tone value
	}
	
	if(buzzerRunning == true) {					//if the buzzer should be running right now
		if((buzzerStartTime + buzzerDuration) <= millis()) {		//if it's time for the buzzer to stop running
			writeBuzzer(0);						//stop the buzzer now
			buzzerRunning = false;				//yep
		}
	}
}


//makes the buzzer play a specific tone
//0: off, 1: low, 2: med, 3: high
void writeBuzzer(uint8_t tone) {
	
	if(tone == 1) {					//sets the buzzer to the low predefined tone, only pin 0 is on
		PORTA |= (1<<BUZZER0);
		PORTB &= ~(1<<BUZZER1);
	}
	else if(tone == 2) {			//sets the buzzer to the medium predefined tone, both pins are on
		PORTA |= (1<<BUZZER0);
		PORTB |= (1<<BUZZER1);
	}
	else if(tone == 3) {			//sets the buzzer to the high predefined tone, only pin 1 is on
		PORTA &= ~(1<<BUZZER0);
		PORTB |= (1<<BUZZER1);
	}
	else {							//failsafe in case we get a bad value (or a 0), just turns the buzzer off
		PORTA &= ~(1<<BUZZER0);
		PORTB &= ~(1<<BUZZER1);
	}
}


//checks each button for any updates, run this very often
void updateButtons() {
	//uint8_t newBtn = (PINB & 0x03) | (PINA & 0x88);
	
	uint8_t newBtn = (PINB & ((1<<PB0)|(1<<PB1))) | (PINA & ((1<<BTN2)|(1<<BTN3)));
	
	if(newBtn > 0) {
		btnOut = newBtn;
	}
	//btnOut = (PINB & 0x3) | ((PINA & 0x3) << 6);		//get the current values of pb0-1 and pa0-1, then OR them
	//you will get a byte like xx0000xx
	//first two x's are the pina values, then pinb	
	//lcd.setCursor(0,0);
	//lcd.print(btnOut);
	
	//need to check if the last button was the same as this new one
	//since this new method auto resets itself by nature
	//basically if
	//the new value is 0
	//dont keep it and use the last value that was above 0 is possible
	//if reading is > 0x
	//then set it to the var
	//the var needs to be 0 by default and after comms
}