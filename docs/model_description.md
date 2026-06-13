# DC Motor Position Control — Technical Description

## System Overview
A DC motor converts electrical energy into mechanical rotation.
The position control system uses a PID controller in a closed-loop configuration
to reach and maintain a desired angular position.

## Mathematical Model

### Electrical Equation
L * di/dt = V - (R*i + Ke * dtheta/dt)

### Mechanical Equation
J * d²theta/dt² = Kt*i - b * dtheta/dt

### PID Controller
u(t) = Kp*e(t) + Ki*integral(e(t)dt) + Kd*de(t)/dt

where e(t) = theta_ref - theta(t)

## Motor Parameters
| Parameter | Value  | Unit     | Description                  |
|-----------|--------|----------|------------------------------|
| R         | 1.0    | Ohm      | Armature resistance          |
| L         | 0.5    | H        | Armature inductance          |
| Kt        | 0.01   | Nm/A     | Motor torque constant        |
| Ke        | 0.01   | V·s/rad  | Back-EMF constant            |
| J         | 0.01   | kg·m²    | Rotor inertia                |
| b         | 0.1    | Nm·s/rad | Viscous friction coefficient |

## PID Tuning Results
| Configuration       | Overshoot | Settling Time | Steady-State Error |
|--------------------|-----------|---------------|--------------------|
| No controller      | —         | —             | infinite           |
| PI (1, 1, 0)       | ~10-20%   | ~1.5 s        | ≈ 0                |
| PID (1, 0.5, 0.05) | < 2%      | ~1 s          | ≈ 0                |

## Limitations
- Linear model — no saturation or nonlinearities
- No external load modeled
- Parameters manually tuned

## Next Steps
- Automatic PID tuning (MATLAB PID Tuner)
- LQR controller (state-space optimal control)
- Cascade control (current -> speed -> position)
- Embedded implementation on STM32 (Simulink Embedded Coder)
