%
%  interpolation.m
%  CS3200,  Intro Numerical Methods
%
%  Created by Illya Starikov on 11/1/16.
%  Copyright 2016. Illya Starikov. All rights reserved.
%

function [coefficients] = interpolation(xValues, yValues)

lengthOfX = length(xValues);
D = zeros(lengthOfX, lengthOfX);

D(:,1) = yValues';

for j = 2:lengthOfX,
  for k = j:lengthOfX,
      D(k, j) = (D(k, j-1) - D(k - 1,j - 1))/(xValues(k) - xValues(k - j + 1));
  end
end

coefficients = D(lengthOfX, lengthOfX);
for k=(lengthOfX - 1): - 1:1,
  coefficients = conv(coefficients, poly(xValues(k)));
  m = length(coefficients);
  coefficients(m) = coefficients(m) + D(k,k);
end

end
