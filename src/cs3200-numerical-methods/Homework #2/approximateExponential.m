function approx = approximateExponential( x, expandedTo )

sumValue = 0
for i = [0:expandedTo]
    % of the form sum -x^i / k! for |x| < infinity
    sumValue = sumValue + power(x, i) / factorial(i)
end

approx = sumValue

end