/*
 * CAT5 TASK5B.3 - Different Signal Types
 * AT89S52, 11.0592 MHz crystal, classic 12-clock 8051.
 * Output: P1.1 (connect to oscilloscope input through common ground).
 * Timer0 tick: approximately 50 us (reload FFD2).
 *
 * Demonstrates: square wave, variable-duty waveform, pulse train,
 * and burst signal. Each pattern is shown for approximately 2 seconds.
 * This is a demonstration implementation; verify timing on hardware.
 */
#include <REGX52.H>

sbit WAVE_OUT = P1^1;

volatile unsigned int tick_count = 0;
volatile unsigned int mode_ticks = 0;
volatile unsigned char waveform_mode = 0;
volatile unsigned char phase = 0;
volatile unsigned char burst_cycle = 0;

/* Timer0 interrupt every approximately 50 us at 11.0592 MHz.
 * Machine cycle = 12/11.0592 MHz = 1.08507 us.
 * 46 counts = 49.91 us; reload = 65536 - 46 = 0xFFD2.
 */
void timer0_isr(void) interrupt 1
{
    TH0 = 0xFF;
    TL0 = 0xD2;

    tick_count++;
    mode_ticks++;
    phase++;

    /* Change demonstration pattern every ~2 seconds (40000 ticks). */
    if (mode_ticks >= 40000) {
        mode_ticks = 0;
        waveform_mode++;
        if (waveform_mode >= 4) waveform_mode = 0;
        phase = 0;
        burst_cycle = 0;
        WAVE_OUT = 0;
    }

    switch (waveform_mode) {
        case 0: /* 1 kHz square wave: 20 ticks per period, 50% duty */
            if (phase >= 20) phase = 0;
            WAVE_OUT = (phase < 10) ? 1 : 0;
            break;

        case 1: /* Variable-duty waveform: 25% high, 75% low */
            if (phase >= 20) phase = 0;
            WAVE_OUT = (phase < 5) ? 1 : 0;
            break;

        case 2: /* Pulse train: short pulse once every 20 ticks */
            if (phase >= 20) phase = 0;
            WAVE_OUT = (phase == 0) ? 1 : 0;
            break;

        case 3: /* Burst: 10 cycles of 1 kHz followed by a silent gap */
            if (phase >= 200) {
                phase = 0;
                burst_cycle++;
                if (burst_cycle >= 5) burst_cycle = 0;
            }
            if (burst_cycle < 4) {
                WAVE_OUT = ((phase % 20) < 10) ? 1 : 0;
            } else {
                WAVE_OUT = 0;
            }
            break;
    }
}

void timer0_init(void)
{
    TMOD = (TMOD & 0xF0) | 0x01; /* Timer0, Mode 1, 16-bit */
    TH0 = 0xFF;
    TL0 = 0xD2;
    ET0 = 1;
    EA = 1;
    TR0 = 1;
}

void main(void)
{
    WAVE_OUT = 0;
    waveform_mode = 0;
    phase = 0;
    mode_ticks = 0;
    burst_cycle = 0;
    timer0_init();
    while (1) {
        /* Waveform generation is performed by the Timer0 ISR. */
    }
}
