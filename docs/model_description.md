# DC Motor Position Control — Technical Description

## Workflow
Mathematical Model → pidtune Auto-Tuning → Simulink → Embedded Coder → SIL Validation → STM32 ready

## Mathematical Model

### Transfer Function (Position)
G(s) = Kt / [(Ls + R)(Js + b) + Kt*Ke] * 1/s

### Electrical Equation
L * di/dt = V - (R*i + Ke * dtheta/dt)

### Mechanical Equation
J * d²theta/dt² = Kt*i - b * dtheta/dt

## Motor Parameters
| Parameter | Value | Unit     | Description          |
|-----------|-------|----------|----------------------|
| R         | 1.0   | Ohm      | Armature resistance  |
| L         | 0.5   | H        | Armature inductance  |
| Kt        | 0.01  | Nm/A     | Torque constant      |
| Ke        | 0.01  | V.s/rad  | Back-EMF constant    |
| J         | 0.01  | kg.m2    | Rotor inertia        |
| b         | 0.1   | Nm.s/rad | Viscous friction     |

## PID Auto-Tuning Results (pidtune)
| Parameter | Value |
|-----------|-------|
| Kp        | 43.42 |
| Ki        | 14.31 |
| Kd        | 18.95 |

## Step Response Metrics
| Metric            | Value  |
|-------------------|--------|
| Rise Time         | 0.36 s |
| Overshoot         | 9.62 % |
| Settling Time     | 4.61 s |
| Steady-State Error| ≈ 0    |

## Embedded Coder Configuration
- Target: ERT (Embedded Real-Time)
- Solver: Fixed-step, ode4
- Step size: 0.001 s (1 kHz)
- Generated code: embedded/dc_motor_pid.c

## SIL Validation
- Normal Simulation vs SIL: curves identical
- C code validated and STM32 ready

## Limitations
- Linear model — no saturation or nonlinearities
- No external load modeled
- No temperature dependency

## Next Steps
- HIL with real STM32 hardware
- LQR controller (state-space optimal control)
- Cascade control (current -> speed -> position)
- AUTOSAR integration
