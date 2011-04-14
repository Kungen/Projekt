% portefolio opgave 2
I = 0.39;    % inerti
b = 0.26;    % afstand mellem hjul
M = 12.2;     % samlet masse
h = 0.0885;    % afstand mellem massemidtpunkt og omdrejningspunkt
r = 0.1;    % radius af hjulene
R = 4.8;      % motorens indre modstand
km = 1.3;   % motorens mekaniske motorkonstant
N = 1;     % nedskalering på grund af motorens gearing
ke = 1.5;   % motorens elektriske motorkonstant
fm = 0.0005; % motorens viskose friktions konstant

k1 = (4*I - b^2*M + 4*h^2*M)*r^2*R;
k2 = 4*b^2*km*N^2;
k3 = (4*(I + h^2*M)*r^2 + b^2*(4*I*N^2 + M*r^2))*R;
k4 = b^2*4*N^2*(ke*km + fm*R);
 
num = {[k2*k3/(k3^2-k1^2) k2*k4/(k3^2-k1^2)] [k1*k2/(k3^2 - k1^2) 0]; 
       [k1*k2/(k3^2 - k1^2) 0] [k2*k3/(k3^2-k1^2) k2*k4/(k3^2-k1^2)]}; 
       %r/b*[(k1*k2-k2*k3)/(k3^2-k1^2) (-k2*k4/(k3^2-k1^2))] r/b*[(k2*k3-k1*k2)/(k3^2-k1^2) (k2*k4/(k3^2-k1^2))]};
   
den = {[1 2*k4*k3/(k3^2-k1^2) k4^2/(k3^2 - k1^2)] [1 2*k4*k3/(k3^2-k1^2) k4^2/(k3^2 - k1^2)]; 
       [1 2*k4*k3/(k3^2-k1^2) k4^2/(k3^2 - k1^2)] [1 2*k4*k3/(k3^2-k1^2) k4^2/(k3^2 - k1^2)]};
       %[1 2*k4*k3/(k3^2-k1^2) k4^2/(k3^2 - k1^2) 0] [1 2*k4*k3/(k3^2-k1^2) k4^2/(k3^2 - k1^2) 0]};
   
G = tf(num,den)
sys = canon(G,'modal');
step(G);
pole(G)
rank(obsv(sys.A, sys.C));
rank(ctrb(sys.A, sys.B));
p = [-10+10i -10-10i -20+10i -20-10i];
k = place(sys.A, sys.B, p);