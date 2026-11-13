# TASK5C – Stepper Motor Speed and Direction Control (Optional)

## Objective
Use the AT89S52 Timer0 interrupt as a time base to advance a four-step motor sequence. The step interval controls motor speed, and the sequence order determines direction.

## Files
- `main.c` – Timer0-based step timing and four-step output sequence.
- `STARTUP.A51` – Keil C51 startup file.
- `TASK5C_Stepper_Motor_Control.uvproj` – Keil µVision project configured for AT89S52.
- `Objects/8051.hex` – HEX output supplied with the reference project.
- `circuit.png` – Circuit diagram.


## Operation
The example uses P1.0–P1.3 for the four driver inputs. The example step intervals are 100 ms (slow), 50 ms (medium), and 10 ms (fast). Reverse the sequence order to reverse rotation.

## Hardware note
Do not connect a stepper motor directly to AT89S52 GPIO pins. Use a suitable motor driver (such as ULN2003 for a compatible unipolar motor), an appropriate external motor supply, and a common ground. Confirm the motor and driver pinout before wiring.

## Build and verification
Open the `.uvproj` file in Keil µVision with the C51 toolchain and build the project. The included HEX is the HEX supplied with the reference project; rebuild it locally after confirming the target hardware and toolchain.
