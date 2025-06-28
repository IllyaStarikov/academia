%
%  setup.m
%  CS3200,  Intro Numerical Methods
%
%  Created by Illya Starikov on 11/1/16.
%  Copyright 2016. Illya Starikov. All rights reserved.
%


function [] = setup(xLeft, xRight, yLeft, yRight,xLabel,yLabel,title)

axis([xm xM ym yM]);

line ([xLeft xRight],[0 0]);
line ([0 0],[yLeft yRight]);

xlabel(xLabel);
ylabel(yLabel);

title(title);

% set(gcf, 'name','Newton Interpolation\nIllya Starikov');

text(xM,0,'X')
text(0,yM,'Y')
