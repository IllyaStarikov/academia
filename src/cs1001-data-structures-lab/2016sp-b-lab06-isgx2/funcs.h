#ifndef FUNCS_H
#define FUNCS_H

// The factorial function. 
// Pre: n! must fit inside an unsigned long
unsigned long factorial(unsigned long n);

// The combination function (aka 'n choose m').
// Pre: n must be >= m 
unsigned long combination(unsigned long n, unsigned long m);

#endif

