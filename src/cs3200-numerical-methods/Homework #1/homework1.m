%
%  homework-1.m
%  CS3200, Intro Numerical Methods
%
%  Created by Illya Starikov on 8/28/16.
%  Copyright 2016. Illya Starikov. All rights reserved.
%

% delete xyz else it will append the current session to the existing diary
delete xyz  % diary will continue with the current diary

diary xyz 
display(datestr(clock)); % display today's date

tic % begin the timer 

clf % clear current figure
close all

figure('name', 'Homework #1 by Illya Starikov', 'numbertitle','off');%,'color','b');
hold on
x=-pi/2+.002:.01:pi/2-.002;
y = sin(x);
plot(x,y,'b','linewidth',1); % plot functions separately

set(gca,'fontname','Trebuchet MS'); % set default font

y=tan(x);
plot(x,y,'r');

sx='x-values in radians'; % label for x-axis
sy='y-values in standard units'; % label for y-axis
st={'Display of';' sin(x) and tan(x)'};

xlabel(sx, 'color','b')
ylabel(sy, 'color','b')
title(st)
legend('sin','tan');
axis([-2 2 -3 3])

toc % end timer

diary off