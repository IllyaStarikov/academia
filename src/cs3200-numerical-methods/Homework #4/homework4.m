%
%  homework4.m
%  CS3200, Intro Numerical Methods
%
%  Created by Illya Starikov on 9/16/16.
%  Copyright 2016. Illya Starikov. All rights reserved.
% 

% Constants
initialGuess = 4.520;
iterationBound = 50;

% Variables
root = [newtonsMethod(initialGuess)];
functionValues = [originalFunction(initialGuess)]
derivativeValues = [derivative(initialGuess)]
i = 1;

while (originalFunction(root(i)) ~= 0)
    root = [root; newtonsMethod(root(i))];
    functionValues = [functionValues; originalFunction(root(i))];
    derivativeValues = [derivativeValues; derivative(root(i))];
    i = i + 1
end


fprintf('---------------------------------------------------------------------\n');
fprintf('Iteration\t AppRoot\t f(x)\t\t\t df(x)\t \n');
fprintf('---------------------------------------------------------------------\n');

for j=1:i
    fprintf('%d\t\t %d\t %d\t\t %d\t\n', j, root(i), functionValues(i), derivativeValues(i));
end


figure('name', 'Newton Method');
title('NewtonRaphson For y = 0.5*x^3 - 4*x^2 + 5.5*x - 1')

x = initialGuess-10:.1:root(i)+9;
y = arrayfun(@originalFunction, x);

hold on;

xlabel('Approximate Function Values');
ylabel('Approximate Root Values');

plot(x, y, 'r');
plot(x, 0, 'b');

for j=1:i
    text(root(j), 0, num2str(j), 'FontSize', 12, 'color', 'b');
end