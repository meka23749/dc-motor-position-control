# DC Motor Position Control in MATLAB/Simulink

PID controller design for precise DC motor position control.
Comparison of open-loop vs closed-loop behavior with step response analysis.

## Project Overview
- Mathematical modeling of a DC motor (electrical + mechanical equations)
- Open-loop simulation (no controller)
- PI controller (Kp=1, Ki=1, Kd=0) — analysis of overshoot
- Optimized PID controller (Kp=1, Ki=0.5, Kd=0.05) — stable, fast response

## Results
| Configuration   | Overshoot | Settling Time | Steady-State Error |
|----------------|-----------|---------------|--------------------|
| No controller  | —         | —             | infinite           |
| PI (1, 1, 0)   | ~10-20%   | ~1.5 s        | ≈ 0                |
| PID (1, 0.5, 0.05) | < 2%  | ~1 s          | ≈ 0                |

## Structure
- src/        MATLAB scripts
- docs/       Technical documentation
- results/    Simulation plots

## Requirements
- MATLAB R2021a or later
- Simulink
- Control System Toolbox

## Author
Steve Meka
