clear all;
% portefolio opgave 2
J  = 0.39;   % inerti
b  = 0.26;   % afstand mellem hjul
M  = 12.2;   % samlet masse
h  = -0.0885; % afstand mellem massemidtpunkt og omdrejningspunkt
r  = 0.1;    % radius af hjulene
R  = 4.8;    % motorens indre modstand
km = 1.3;    % motorens mekaniske motorkonstant
N  = 1;      % nedskalering p� grund af motorens gearing
ke = 1.5;    % motorens elektriske motorkonstant
fm = 0.0005; % motorens viskose friktions konstant

k1 = (4*J - b^2*M + 4*h^2*M)*r^2*R;
k2 = 4*b^2*N^2*km;
k3 = 4*b^2*N^2*(ke*km + fm*R);
k4 = (4*(J + h^2*M)*r^2 + b^2*(4*J*N^2 + M*r^2))*R;

A = 1/(k1^2 - k4^2)*[k3*k4 k1*k3; k1*k3 k3*k4]
B = 1/(k1^2 - k4^2)*[(-k2)*k4 (-k1)*k2; (-k1)*k2 (-k2)*k4]
C = [1 0; 0 1];
D = [0 0; 0 0];

sys = ss(A,B,C,D);
%G = tf(sys1);
%sys2 = canon(G,'modal')
%step(12*sys);
preal=pole(sys);
rank(obsv(sys.A, sys.C));
rank(ctrb(sys.A, sys.B));
p = [-20+3i -20-3i];
%K = place(sys.A, sys.B, p)
%L = place(sys.A, sys.B, p*4)
K = [35 10; 10 35]
L = 4 * K
