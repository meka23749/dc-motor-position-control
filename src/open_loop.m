%% Open Loop Simulation
% DC Motor without controller — position grows unbounded

clc; clear; close all;

%% Load parameters
run('motor_params.m');

%% State space matrices
% States: x = [i, omega, theta]
A = [-R/L,   -Ke/L,  0;
      Kt/J,   -b/J,  0;
      0,       1,    0];

B = [1/L; 0; 0];
C = [0, 0, 1];
D = 0;

%% Step input
t = 0:0.01:Sim_Time;
U = ones(size(t));   % constant voltage input

%% Simulate
sys = ss(A, B, C, D);
[y, t_out] = lsim(sys, U, t);

%% Plot
figure;
plot(t_out, y, 'b', 'LineWidth', 1.5);
xlabel('Time (s)'); ylabel('Position theta (rad)');
title('Open Loop — No Controller'); grid on;
