/*
  Tech01 Digital Binary Clock By Serhii Trush for MIT License
  https://github.com/techn0man1ac/ATtiny13BinaryWatches

  Simple Binary Watches with 4 LED(1/5, 2/10, 4/20, 8/40), it mean 5 minute accuracy indicate.
  It's project full open source(PCB and code).

  By Tech01 labs 2022.

  Fuses to defalt:
  low_fuses=0x6A
  high_fuses=0xFF
  CPU Frequensy 1,2 MHz
*/

#define F_CPU 1200000UL  // 1.2 MHz CPU mode(low_fuses=0x6A high_fuses=0xFF - defalt fuses)
#include <avr/io.h>
#include <avr/wdt.h>  // Need for "wdt_..." macross
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/interrupt.h>


#define msPerCycleReal 560  // it's mean 500 ms in real life

volatile unsigned long MSec = 33120000;  // 09:15 (3600sec. per hour * 6)
uint8_t Minutes = 0;
uint8_t Hours = 0;

uint8_t Mode = 0;

ISR(WDT_vect) {            // code iteration time is 200 nS
  MSec += msPerCycleReal;  // 500 ms per cycle

  if (MSec >= 43200000) {    // 43200000 ms -> 43200 sec = 12h
    MSec = MSec - 43200000;  // increment MSec value compensation -> 43199999 + 555 = 43200554 -> 554
  }

  if (PINB & (1 << PINB4) || Mode > 0) {  // if (digitalRead(4) == HIGH)
    Mode = ShowTime(Mode);                // Show time on LED in binary format
  }

  WDTCR |= (1 << WDTIE);
}

int main() {
  ADCSRA &= ~(1 << ADEN);  //Disable ADC
  ACSR = (1 << ACD);       //Disable the analog comparator
  // Set up Port B as Input
  DDRB = 0b01111;  // Use 470 ohm resistor per LED
  wdt_reset();
  wdt_enable(WDTO_500MS);  // Set watchdog timer to trigger every 500 ms
  WDTCR |= (1 << WDTIE);   // Set watchdog timer in interrupt mode
  sei();                   // Enable global interrupts

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  while (1) {
    sleep_enable();
    sleep_cpu();
  }
  return 0;
}

uint8_t ShowTime(uint8_t currState) {
  uint8_t LEDValue = 0;
  switch (currState) {  //Final state machine
    case 0:
      if (!MSec) {  // protect divide by zero(if MSec not = 0), thanks ChatGPT
        Hours = 0;
      } else {
        Hours = MSec / 3600000;  // 3600 sec per hour
      }

      if (Hours == 0) {
        LEDValue = 12;  // 
      } else {
        LEDValue = Hours;
      }
      DDRB = 0b1111; // Turn on ouptuts

      currState = 1;  // Next state
      break;

    case 1:
      if (!MSec) {  // protect divide by zero, thanks ChatGPT
        Minutes = 0;
      } else {
        Minutes = ((MSec / 60000) % 60) / 5;  // 60 Seconds per minutes(5 min to discrete)
      }

      LEDValue = Minutes;

      currState = 2;
      break;

    case 2:
      LEDValue = 0;
      DDRB = 0b0000; // Turn off outputs(Hi-Z state) for low consumption
      currState = 0;
      break;

    default:
      return -1;  // some wrong
  }

  PORTB = LEDValue;  // Set Port B to LEDValue
  return currState;
}
