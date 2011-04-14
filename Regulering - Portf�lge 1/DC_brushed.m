clear
T_f = 0.022;
L_a = 0.004;
R_a = 5.5;
K_m = 0.3365;
K_e = 0.514;
B_f = 0.00051;
I_m = 0.0005;

syms s;  
time = 0: 0.0001: .5;
V_off =  (T_f * (L_a*s+R_a))/K_m;
input = 10/s;
G = K_m/(K_e*K_m+(B_f+I_m*s)*(R_a+L_a*s));
output_s = (input-V_off)*G;
output = ilaplace(output_s);
output_plot =subs(output,'t',time);
figure(1)
plot(time,output_plot)
title('Brushed DC motor');
xlabel('t [s]');
ylabel('\omega [rad/s]');