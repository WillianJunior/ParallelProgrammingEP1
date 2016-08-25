x = [10,100,1000,10000,100000];
ys = [31.709,22.178,19.511,19.437,22.662; 0.508,0.62,0.053,0.063,0.024];
yd = [44.078,21.531,19.25,19.239,22.469; 0.552,0.263,0.052,0.022,0.02];
yg = [18.913,18.932,18.914,18.9,20.688; 0.038,0.026,0.052,0.031,0.525];
ybase = [19.082,19.082,19.082,19.082,19.082; 0.126,0.126,0.126,0.126,0.126];

semilogx(x,ys(1,:));
hold on;
p1=errorbar(x,ys(1,:), ys(2,:), 'b');
xlabel('Chunk Size');
ylabel('Exec Time (secs)');
p2=errorbar(x,yd(1,:), yd(2,:), 'g');
p3=errorbar(x,yg(1,:), yd(2,:), 'r');
p4=errorbar(x,ybase(1,:), ybase(2,:), 'k');
legend([p1,p2,p3,p4], 'Static', 'Dynamic', 'Guided', 'Baseline');
title('Exec Time x Chunk Size for Primes < 500000')