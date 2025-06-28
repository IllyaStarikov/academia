%
%  homework7.m
%  CS3200,  Intro Numerical Methods
%
%  Created by Illya Starikov on 11/1/16.
%  Copyright 2016. Illya Starikov. All rights reserved.
%

tic

disp(datestr(clock))

title = 'Newton Plot vs Actual Plot';
xlabel = 'x values';
ylabel = 'y values';

x = 2.8;
xvalues = [1.6, 2, 2.5, 3.2, 4, 4.5];
yvalues = [2,8, 14, 15, 8, 2];

[coefficients] = interpolation(xvalues,yvalues);

p =  poly2sym(coefficients);
setup(-0.5, 6.5, -0.5, 20, xlabel, ylabel, title);

hold on
h = fplot(p,[1.6 4.5]);
set(h, 'LineWidth', 2);

hold on
g = plot(xvalues,yvalues,'-or');
set(g, 'LineWidth', 1);

grid on

legend([h,g], 'Degree 5', 'Linear');
y = double(subs(p,x));

toc
