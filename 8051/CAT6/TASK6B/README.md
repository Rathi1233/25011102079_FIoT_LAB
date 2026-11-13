# TASK6B — UART Echo and Interrupt-Driven Reception

**Registration number:** 25011102079  
**Platform:** AT89S52 / 8051, Keil µVision C51  
**Faculty assessment:** CAT6

## Objective
UART Echo and Interrupt-Driven Reception. Follow the corresponding faculty CAT task sheet for detailed behavior and acceptance criteria.

## Supplied files
- C source: `main.c`
- Keil project: `TASKB_UART_Interrupt_Driven_Echo.uvproj`
- Keil startup: `STARTUP.A51`
- Compiled HEX: `Objects/8051.hex`

## Existing circuit / evidence images
![Existing supplied image](circuit.png)

## Build and verification
1. Open the supplied `.uvproj` / `.uvprojx` in Keil µVision.
2. Verify project source paths, target device, clock and pins.
3. Rebuild; enable HEX output and confirm **0 errors**.
4. Compare the behavior against the official CAT task sheet and test on the actual board.
