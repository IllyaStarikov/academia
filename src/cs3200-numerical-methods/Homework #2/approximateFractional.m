function approx = approximateFractional( x, expandedTo )

sumValue = 0
for i = [0:expandedTo]
    % exact same as approximate exponential, but x is positive
    % and 1/sumValue
    sumValue = sumValue + power(-x, i) / factorial(i)
end

approx = 1/sumValue

end