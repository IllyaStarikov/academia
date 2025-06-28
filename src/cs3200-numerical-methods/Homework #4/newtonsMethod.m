%
%  newtonsMethod.m
%  CS3200, Intro Numerical Methods
%
%  Created by Illya Starikov on 9/16/16.
%  Copyright 2016. Illya Starikov. All rights reserved.
% 

function approximateRoot = newtonsMethod( x )
    approximateRoot = x - (originalFunction(x)/derivative(x));
end