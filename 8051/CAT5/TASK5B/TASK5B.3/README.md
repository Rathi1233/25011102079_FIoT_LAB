# CAT5 – TASK5B.3: Different Signal Types

**Registration number:** 25011102079  
**Controller:** AT89S52 (classic 12-clock 8051)  
**Clock assumption:** 11.0592 MHz  
**Output pin:** P1.1

## Objective
Generate simple waveforms after establishing timer-based signal generation: square wave, variable-duty waveform, pulse train, and burst signal. These are the four signal examples shown in the supplied CAT5 task sheet.

## Implementation
`main.c` uses Timer0 Mode 1 and an approximately 50 µs interrupt tick (reload `0xFFD2`). The interrupt service routine cycles through four waveform modes, changing the demonstration mode approximately every two seconds.

| Mode | Pattern |
|---|---|
| 1 | 1 kHz square wave, approximately 50% duty |
| 2 | 1 kHz variable-duty waveform, approximately 25% high |
| 3 | Short pulse once every 20 timer ticks |
| 4 | Burst of square-wave cycles followed by a silent interval |

## Pin / test setup
- Observe P1.1 using an oscilloscope or logic analyser.
- Connect instrument ground to the 8051 board ground.
- Use the board's actual oscillator frequency; the reload calculation assumes 11.0592 MHz.

## Build
1. Open `TASK5B.3_Different_Signal_Types.uvproj` in Keil µVision (C51).
2. Confirm the target is AT89S52 and the oscillator setting matches the board.
3. Build the target (F7), enable HEX output, and check for zero errors.
4. Measure the output on P1.1 and compare the observed waveforms with the task sheet.

