%
%  homework3.m
%  CS3200, Intro Numerical Methods
%
%  Created by Illya Starikov on 9/10/16.
%  Copyright 2016. Illya Starikov. All rights reserved.
%

cleanup()
tic

%-------------------- Bisection Method --------------------%

figure('name', 'Bisection Method');
func = '0.7*x.^5-8*x.^4+44*x.^3-90*x.^2+82*x-25';

xl = zeros(1, 1000);
xu = zeros(1, 1000);
ea = zeros(1, 1000);
root = zeros(1, 1000);

xl(1) = 0.5;
xu(1) = 1.0;

tolerance = .1;
x = xl(1):.0001:xu(1);
y = closure(x);

hold on;
plot(x, y, 'r');
plot(x, x-x, 'b');

text(xu(1), 0, 'x', 'FontSize', 12, 'color', 'b');

xlabel('x-Values');
ylabel('Function Values');

titleString = sprintf('Bisection Method for %s \non interval [%f, %f] tolerance %f', func, xl(1), xu(1), tolerance);
title(titleString);

legend(func);

root(1) = (xl(1) + xu(1)) / 2.0;
i = 1;

display(datestr(clock));
fprintf('\nBisection Method for function %s', func);
fprintf('\nInitial Guesses: [%f , %f] \t Error Tolerance: %f',xl(1),xu(1), tolerance);
fprintf('\n____________________________________________________________________');

if(closure(xl(1)) * closure(xu(1)) <= 0)
    while(abs((xl(i) - xu(i)) / (xl(i) + xu(i))) > tolerance)
        i = i + 1;

        ea(i - 1) = 100 * (abs((xl(i - 1) - xu(i - 1)))/(xl(i - 1)+xu(i - 1)));
        root(i - 1) = (xl(i - 1) + xu(i - 1)) / 2;

        if (closure(xl(i - 1)) * closure(root(i - 1)) < 0)
            xu(i)=root(i - 1);
            xl(i)=xl(i - 1);
        else
            xl(i) = root(i - 1);
            xu(i) = xu(i - 1);
        end

        text(root(i - 1), closure(root(i - 1)), num2str(i - 1),'FontSize',12,'color','b');
        text(root(i - 1), 0, num2str(i - 1), 'FontSize', 12, 'color', 'b');
    end

    root(i) = (xl(i) + xu(i)) / 2.0;
    text(root(i), closure(root(i)), num2str(i), 'FontSize', 12, 'color', 'b');
    text(root(i), 0, num2str(i), 'FontSize', 12, 'color', 'b');

    fprintf('\nIterations \tRoot');
    fprintf('\n%d\t\t\t%f', i, root(i));
    fprintf('\n\t\t_____________________________________________________________________');
    fprintf('\n\t\tIteration\tAppRoot\t\tApproximateError\t[ -------Bracket------- ]');
    fprintf('\n\t\t_____________________________________________________________________\n');

    k = 1;

    fprintf('\t\t%u\t\t\t%f\t\t\t\t\t\t%f\t%f  \n', [k, root(k), xl(k), xu(k)]);
    for k = 2:i
        fprintf('\t\t%u\t\t\t%f\t\t%f\t\t%f\t%f  \n',[k, root(k), ea(k), xl(k), xu(k)]);
    end;

else
    fprintf('\nRoot not Bracketed \n');
end;

%-------------------- False Positives Method --------------------%

figure('name', 'False Position Method');
func = '0.7*x.^5-8*x.^4+44*x.^3-90*x.^2+82*x-25';

xl = zeros(1,100);
xu = zeros(1,100);
ea = zeros(1,100);
root = zeros(1,100);

xl(1) = 0.5;
xu(1) = 1.0;
tolerance = .02;

x = xl(1):.0001:xu(1);
y = closure(x);

hold on;
plot(x, y, 'r');
plot(x, x-x, 'b');

text(xu(1), 0, 'x', 'FontSize', 12, 'color', 'b');

xlabel('x-Values');
ylabel('Function Values');

titleString = sprintf('False Position Method for %s \non interval [%f, %f] tolerance %f', func, xl(1), xu(1), tolerance);

title(titleString);
legend(func);

display(datestr(clock));
fprintf('\nFalse Position Method for function %s', func);
fprintf('\nInitial Guesses: [%f , %f] \t Error Tolerance: %f', xl(1), xu(1), tolerance);
fprintf('\n____________________________________________________________________\n');

i = 1;

if(closure(xl(1)) * closure(xu(1)) <= 0)
    while(abs((xl(i) - xu(i)) / (xl(i) + xu(i))) > tolerance)
        tempx = [xl(i), xu(i)];
        tempy = [closure(xl(i)), closure(xu(i))];

        slope = (tempy(2) - tempy(1)) / (tempx(2) - tempx(1));

        root(i) = -1 * ((tempy(2) / slope) - tempx(2));

        plot(tempx, tempy, 'r');
        text(root(i), 0, num2str(i), 'FontSize', 12, 'color', 'b');
        text(root(i), closure(root(i)), num2str(i), 'FontSize', 12, 'color', 'b');

        if(closure(root(i)) > 0)
            xu(i + 1) = root(i);
            xl(i + 1) = xl(i);
        else
            xl(i + 1) = root(i);
            xu(i + 1) = xu(i);
        end

        i = i + 1;
    end

    fprintf('\nIterations \tRoot');
    fprintf('\n%d\t\t\t%f', i, root(i));
    fprintf('\n\t\t_____________________________________________________________________');
    fprintf('\n\t\tIteration\tAppRoot\t\tApproximateError\t[ -------Bracket------- ]');
    fprintf('\n\t\t_____________________________________________________________________\n');

    k = 1;

    fprintf('\t\t%u\t\t\t%f\t\t\t\t\t\t%f\t%f  \n', [k, root(k), xl(k), xu(k)]);
    for k = 2:i
        fprintf('\t\t%u\t\t\t%f\t\t%f\t\t%f\t%f  \n', [k, root(k), ea(k), xl(k), xu(k)]);
    end;

else
    fprintf('\nRoot not Bracketed \n');
end;

toc