/* 
   Setting the 8bits register of the chip ATMEGA328P U (Arduino Uno)
*/

//Output pin D
volatile uint8_t* _PIND = (volatile uint8_t*) 0x29;// pin status and config
volatile uint8_t* _DDRD = (volatile uint8_t*) 0x2A;// port direction
volatile uint8_t* _PORTD = (volatile uint8_t*) 0x2B;// pin set or reset

//Output pin B
volatile uint8_t* _PINB = (volatile uint8_t*) 0x23;// pin status and config
volatile uint8_t* _DDRB = (volatile uint8_t*) 0x24;// port direction
volatile uint8_t* _PORTB = (volatile uint8_t*) 0x25;// pin set or reset

//Interrupt REGISTER settings
volatile uint8_t* _SREG = (volatile uint8_t*) 0x5F;  // Global interupt
volatile uint8_t* _EICRA = (volatile uint8_t*) 0x69; // Raising or Falling edge or other
volatile uint8_t* _EIMSK = (volatile uint8_t*) 0x3D; // int0 or int1

volatile uint8_t flag = 0;

void setup() {

  Serial.begin(9600);

  // Set input button and pull-up mode.
  *_DDRD &= ~0x4; // set PD2 as an input.
  *_PORTD |= 0x4; // pullup mode (20k in series internal before switch).

  // Config interrupt.
  *_SREG |= 0x80; // enable globla interrupt always on by default (just for exemple).
  // Serial.println("SREG");
  // Serial.println(*_SREG, HEX);
  // delay(500);

  *_EICRA &= ~0xf;
  *_EICRA |= 0x3; // Interrupt in raising-edge mode.
  // Serial.println("EICRA");
  // Serial.println(*_EICRA, HEX);
  // delay(500);



  *_EIMSK |= 0x1; // int0 enabled on PD2.
  // Serial.println("EIMSK");
  // Serial.println(*_EIMSK, HEX);
  // delay(500);

  *_DDRB |= 0x20; //setp PB5 as an output.

  /*
     Some test Comments 2  
   */
}

void loop() {
  // Serial.println(*_PINB, HEX);

  delay(700);

}

// Poor debonce will be inprove not the subject of the study. 
ISR(INT0_vect) {
  if (flag < 5) {
    flag++;
  }
  if (flag >=3) {
    *_PORTB ^= 0x20;
    //Serial.println("Trigger");
    flag = 0;
  }
}
