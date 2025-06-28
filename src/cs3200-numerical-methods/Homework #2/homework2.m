delete outFile;
diary outFile;
tic;

% Constants 
numberOfIteration = 20;
exponent = 2;

trueValue = exp(exponent);
iteration = [0:1:20];

% Variables
method1 = []; % For exponent approximations
method2 = []; % For fraction approximations

trueRelativeError1 = [];
trueRelativeError2 = [];

approxRelativeError1 = [];
approxRelativeError2 =[];

for i = 0:20
    method1 = [method1; approximateExponential(exponent, i)];
    method2 = [method2; approximateFractional(exponent, i)];

    trueRelativeError1 = [trueRelativeError1; calculateRelativeError(method1(i + 1), trueValue)];
    trueRelativeError2 = [trueRelativeError2; calculateRelativeError(method2(i + 1), trueValue)];
  
    if i ~= 0
        approxRelativeError1 = [approxRelativeError1; calculateRelativeError(method1(i), method1(i + 1))];
        approxRelativeError2 = [approxRelativeError2; calculateRelativeError(method2(i), method2(i + 1))];
    else
        approxRelativeError1 = [approxRelativeError1; 0];
        approxRelativeError2 = [approxRelativeError2; 0];
    end
end

iteration = strread(num2str(iteration),'%s');

fprintf('Homework #2 by Illya Starikov on %s\n', datestr(clock));
fprintf('Method #1: 1 + x + x^2/2 + ...\n');
fprintf('Methods #2: 1/(1 - x + x^2/2 - ...\n');

fprintf('For x = %1f, actual value e^x = %f\n', exponent, trueValue);
t = table(method1, method2, trueRelativeError1, trueRelativeError2, approxRelativeError1, approxRelativeError2, 'RowNames', iteration)

fprintf('\n')
toc
