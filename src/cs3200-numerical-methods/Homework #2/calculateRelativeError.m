function error = calculateRelativeError( approximateValue, trueValue )
    error = abs(trueValue - approximateValue)/trueValue;
    error = error * 100
end

