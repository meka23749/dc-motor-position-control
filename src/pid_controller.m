%% PID Controller Simulation
% DC Motor Position Control — Auto-tuning with pidtune

clc; clear; close all;

%% Load parameters
run('motor_params.m');

%% Transfer function (position)
num = Kt;
den = conv([L R], [J b]) + [0 0 Kt*Ke];
den_pos = [den 0];
G = tf(num, den_pos);

%% Automatic PID tuning
[C_pid, info] = pidtune(G, 'PID');
fprintf('PID Parameters:\n');
fprintf('  Kp = %.4f\n', C_pid.Kp);
fprintf('  Ki = %.4f\n', C_pid.Ki);
fprintf('  Kd = %.4f\n', C_pid.Kd);

%% Closed-loop system
sys_cl = feedback(C_pid * G, 1);

%% Step response metrics
info = stepinfo(sys_cl);
fprintf('\nStep Response Metrics:\n');
fprintf('  Rise Time    : %.4f s\n', info.RiseTime);
fprintf('  Overshoot    : %.4f %%\n', info.Overshoot);
fprintf('  Settling Time: %.4f s\n', info.SettlingTime);

%% Plot
t = 0:0.01:10;
figure;
plot(t, step(sys_cl, t), 'b', 'LineWidth', 2, 'DisplayName', 'PID Auto-tuned');
yline(theta_ref, 'k--', 'LineWidth', 1, 'DisplayName', 'Reference (1 rad)');
xlabel('Time (s)'); ylabel('Position theta (rad)');
title('DC Motor Position Control — pidtune Auto-Tuning');
legend('Location', 'southeast'); grid on;
