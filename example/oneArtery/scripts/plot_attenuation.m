clear;
close all;

L=350;
nu=1e-2;         % kinematic  viscocity of the blood  cm/s
Kr=40*nu*pi;

h=2e-1;         % thickness of the vessel;
E=3/4*1.7e4;           % elatisity modulus;
rho=0.1050;

R0=1.470;
A_ref=pi*R0.^2;

t_final = 4; 
dt=4e-5;
timeSteps = floor(t_final/dt);
tt=linspace(0,t_final,timeSteps);

anly=exp(-0.5*Kr./A_ref.*(tt-0.2));

Q_hist=csvread('../data/histQ.csv');

h1=figure;
curveH=plot(Q_hist(:,1),Q_hist(:,2),'r',Q_hist(:,1),Q_hist(:,3),Q_hist(:,1),Q_hist(:,4),Q_hist(:,1),Q_hist(:,5),tt, anly,'c');    % 
xlabel('time(s)');
ylabel('Flux');

%legend(curveH([1 6 11 16]),'Taylor-Galerkin','MUSCL','MacCormack','DG'); %
%print(h1, '-depsc', '../figures/attenuation.eps'); % myplot.eps
%!epstopdf ../figures/attenuation.eps;