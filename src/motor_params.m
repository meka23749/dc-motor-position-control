%% DC Motor Parameters
% Position Control — PID Design

%% Motor parameters
R = 1.0;        % Armature resistance (Ohm)
L = 0.5;        % Armature inductance (H)
Kt = 0.01;      % Motor torque constant (Nm/A)
Ke = 0.01;      % Back-EMF constant (V·s/rad)
J = 0.01;       % Rotor inertia (kg·m^2)
b = 0.1;        % Viscous friction coefficient (Nm·s/rad)

%% Simulation
Sim_Time = 5;   % Simulation duration (s)
theta_ref = 1;  % Reference position (rad)
