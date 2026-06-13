%% PID Controller Simulation
% DC Motor Position Control — Closed Loop

clc; clear; close all;

%% Load parameters
run('motor_params.m');

%% State space matrices
A = [-R/L,   -Ke/L,  0;
      Kt/J,   -b/J,  0;
      0,       1,    0];

B = [1/L; 0; 0];
C = [0, 0, 1];
D = 0;

sys = ss(A, B, C, D);

%% PID configurations to compare
configs = [
  1,   1,    0;      % PI controller
  1,   0.5,  0.05;   % Optimized PID
];

labels = {'PI (Kp=1, Ki=1, Kd=0)', 'PID (Kp=1, Ki=0.5, Kd=0.05)'};
colors = {'r', 'g'};

t = 0:0.01:Sim_Time;

figure; hold on;

for k = 1:size(configs, 1)
    Kp = configs(k,1);
    Ki = configs(k,2);
    Kd = configs(k,3);

    %% Build closed-loop with PID
    C_pid = pid(Kp, Ki, Kd);
    sys_cl = feedback(C_pid * sys, 1);

    %% Step response
    [y, t_out] = step(sys_cl, t);
    plot(t_out, y, colors{k}, 'LineWidth', 1.5, 'DisplayName', labels{k});
end

%% Reference line
yline(theta_ref, 'k--', 'LineWidth', 1, 'DisplayName', 'Reference (1 rad)');

xlabel('Time (s)'); ylabel('Position theta (rad)');
title('Closed Loop — PID Position Control');
legend('Location', 'southeast'); grid on;
