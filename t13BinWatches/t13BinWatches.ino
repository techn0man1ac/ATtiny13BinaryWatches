/*
Tech01 Digital Binary Clock

Simple Binary Watches with 4 LED(1/5, 2/10, 4/20, 8/40), it mean 5 minute accuracy indicate.
It's project full open source(PCB and code).
https://github.com/techn0man1ac/ATtiny13BinaryWatches
By Tech01 labs 2023.

Fuses to defalt:
low_fuses=0x6A
high_fuses=0xFF
CPU Frequensy 1,2 MHz
*/

#define F_CPU 1200000UL // 1.2 MHz CPU mode(low_fuses=0x6A high_fuses=0xFF - defalt fuses)
#include <avr/io.h>
#include <avr/wdt.h> // Need for "wdt_..." macross
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/interrupt.h>


#define msPerCycleReal 563 // it's mean 500 ms in real life

unsigned long MSec = 33120000; // 06:00 (3600sec. per hour * 6)
byte Minutes = 0;
byte Hours = 0;

byte Mode = 0;

bool ButtonPress = false;

ISR(WDT_vect) {
  ButtonPress = PINB & (1 << PINB4); // analog digitalRead(4);
  MSec += msPerCycleReal; // 500 ms per cycle

  if (MSec >= 43200000) { // 43200000 ms -> 43200 sec = 12h
    MSec = MSec - 43200000; // increment MSec value compensation -> 43199999 + 555 = 43200554 -> 554
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

byte ShowTime(byte currState) {
  byte TempValue = 0;
  switch (currState) { //Final state machine
    case 0:
      Hours = MSec / 3600000; // 3600 sec per hour

      if (Hours == 0) {
        TempValue = 15;
      } else {
        TempValue = Hours;
      }
      currState = 1; // Next state
      break;

    case 1:
      Minutes = ((MSec / 60000) % 60 ) / 5; // 60 Seconds per minutes

      if (Minutes >= 55) {
        TempValue = 15;
      } else {
        TempValue = Minutes + 1; // " + 1" - 5 minutes in the future
      }
      currState = 2;
      break;

    case 2:
      TempValue = 0;
      currState = 0;
      break;

    default:
      return -1; // some wrong
      break;
  }

  PORTB = TempValue;
  return currState;
}
