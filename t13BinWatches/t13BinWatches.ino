/*
  Tech01 Digital Binary Clock
  https://github.com/techn0man1ac/ATtiny13BinaryWatches
  by Techn0man1ac Labs, 2022
*/

#define F_CPU 1200000UL
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/interrupt.h>


#define msPerCycleReal 560 // 

unsigned long MSec = 36900000; // 10:15
byte Minutes = 0;
byte Hours = 0;

byte Mode = 0;

bool ButtonPress = false;

ISR(WDT_vect) {
  ButtonPress = PINB & (1 << PINB4); // analog digitalRead(4);
  MSec += msPerCycleReal; // 500 ms per cycle

  if (MSec >= 43200000) { // 43200000 ms -> 43200 sec = 12h
    MSec = MSec - 43200000; // increment MSec value compensation -> 43199999 + 555 = 43200554
  }

  if (ButtonPress == true || Mode > 0 ) { // if (digitalRead(4) == HIGH){
    Mode = ShowTime(Mode);
  }

  WDTCR |= (1 << WDTIE);
}

int main() {
  ADCSRA &= ~(1 << ADEN); //Disable ADC
  ACSR = (1 << ACD); //Disable the analog comparator
  // Set up Port B as Input
  DDRB = 0b0000;
  wdt_reset();
  wdt_enable(WDTO_500MS);
  // Set watchdog timer in interrupt mode
  WDTCR |= (1 << WDTIE);
  sei(); // Enable global interrupts

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  while (1) {
    sleep_enable();
    sleep_cpu();
  }
  return 0;
}

byte ShowTime(byte currTm) {
  byte TempValue = 0;
  switch (currTm) { //Final state machine
    case 0:
      Hours = MSec / 3600000; // 3600 sec per hour

      if (Hours == 0) {
        TempValue = 15;
      } else {
        TempValue = Hours;
      }
      currTm = 1; // Next state
      break;

    case 1:
      Minutes = ((MSec / 60000) % 60 ) / 5; // 60 Seconds per minutes

      if (Minutes >= 55) {
        TempValue = 15;
      } else {
        TempValue = Minutes + 1; // " + 1" - 5 minutes in the future
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
