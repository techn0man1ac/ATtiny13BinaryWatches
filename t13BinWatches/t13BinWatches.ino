/*
  Tech01 Digital Binary Clock
  https://www.tinkercad.com/things/b0rVxrV6jcl
  by Tech01 Labs, 2022
*/

#define F_CPU 1200000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

unsigned long Seconds = 0;
byte Minutes = 0;
byte Hours = 0;

byte Mode = 0;

bool ButtonPress = false;

ISR(WDT_vect) {
  ButtonPress = PINB & (1 << PINB4); // analog digitalRead(4);
  Seconds += 565; // 500 ms per cycle

  if (Seconds >= 86400000) { // 86400000 ms -> 86400 sec = 24h
    Seconds = 0;
    //PORTB = 15;
  }

  Minutes = (Seconds / 60000) % 60; // 60 Seconds per minutes
  Hours = (Seconds / 3600000) % 12; // 3600 sec per hour
  // if more less 12, Hours = 0 then to do hours -> 1

  if (ButtonPress == true || Mode > 0 ) { // if (digitalRead(4) == HIGH){
    Mode = ShowTime(Mode);
  }

}

void setup()
{
  ADCSRA &= ~(1 << ADEN); //Disable ADC
  ACSR = (1 << ACD); //Disable the analog comparator
  //DIDR0 = 0x3F; //Disable digital input buffers on all ADC0-ADC5 pins.
  // Set up Port B as Input
  DDRB = 0b0000; // usually not necessary but it will save current
  //PORTB = 15;
  
  //set timer to 1 sec
  // WDTCR |= (0 << WDP3) | (1 << WDP2) | (1 << WDP1) | (0 << WDP0);
  // set timer to 0.5s
  WDTCR |= (1<<WDP2) | (1<<WDP0);
  // set timer to 4 sec
  // WDTCR |= (1<<WDP3);

  // Set watchdog timer in interrupt mode
  WDTCR |= (1 << WDTIE);
  WDTCR |= (0 << WDE);
  sei(); // Enable global interrupts

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

void loop() {
  sleep_mode();   // go to sleep and wait for interrupt...
}

byte ShowTime(byte currTm) {
  byte TempValue = 0;
  switch (currTm) { //Final state machine
    case 0:
      if (Hours == 0) {
        TempValue = 15;
      } else {
        TempValue = Hours;
      }
      currTm = 1; // Next state
      break;

    case 1:
      if (Minutes > 55) {
        TempValue = 15;
      } else {
        TempValue = (Minutes / 5) + 1;
      }
      currTm = 2;
      break;

    case 2:
      TempValue = 0;
      currTm = 0;
      break;

    default:
      return -1; // some wrong
      break;
  }

  PORTB = TempValue;
  return currTm;
}
