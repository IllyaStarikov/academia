%
%  homework6.m
%  CS3200,  Intro Numerical Methods
%
%  Created by Illya Starikov on 10/26/16.
%  Copyright 2016. Illya Starikov. All rights reserved.
%

diary on;
clear;
tic;

figure('name',  'Least - Fit Regression');
hold on;

n = 11;
x = [6, 7, 11, 15, 17, 21, 23, 29, 29, 37, 39];
y = [29, 21, 29, 14, 21, 15, 7, 7, 13, 0, 3];

axis([0, 50, -10, 50]);
std_dev = std(y);

sumx = 0;
sumy = 0;
sumxy = 0;
sumx_square = 0;

for i = 1:n
  sumy = sumy + y(i);
  sumx = sumx + x(i);

  sumxy = sumxy + x(i) * y(i);
  sumx_square = sumx_square + x(i) * x(i);
  text(x(i), y(i), ' * ', 'FontSize', 12, 'color', 'b');
end

y_average = sumy/n;
x_average = sumx/n;

a1 = (n * sumxy - sumx * sumy)/(n * sumx_square - sumx * sumx);
a0 = y_average - a1 * x_average;

xplot = (0:1:100);
yplot = (0:1:100);

for i = 1:100
    yplot(i) = a1 * xplot(i) + a0;
end

st = 0;
sr = 0;

for i = 1:n
    st = st + (y(i) - y_average)^2;
    sr = sr + (y(i) - a1 * x(i) - a0)^2;
end

r = sqrt((st - sr)/st);

plot(xplot, yplot);
plot(xplot, yplot - std_dev);
plot(xplot, yplot + std_dev);

text(10, 10, ' * ', 'FontSize', 12, 'color', 'r');
title('Least - Fit Regression');
xlabel('x-axis');
ylabel('y-axis');

fprintf('\nLeast - Fit Regression\nBy Illya Starikov\n\n');
fprintf('Formula: %fx + %f\n', a1, a0);
fprintf('Standard Deviation: %f\n\n\n', std_dev);
display(datestr(clock));

diary off;
toc;
