clear
T_f = 0.0547;
L_a = 0.024;
R_a = 69;
K_m = 1.38;
K_e = 0.00578;
D_fb = 1.35*10^(-4);
I_m = 0.0005;
D_ft = 0;


syms s;  
time = 0: 0.01: 10;
V_off =  ((T_f-D_ft) * (L_a*s+R_a))/K_m;
input = 10/s;
G = K_m/(K_e*K_m+(D_fb+I_m*s)*(R_a+L_a*s));
output_s = (input-V_off)*G;
output = ilaplace(output_s);
output_plot =subs(output,'t',time);
figure(1)
plot(time,output_plot)
title('Brushless DC motor');
xlabel('t [s]');
ylabel('\omega [rad/s]');