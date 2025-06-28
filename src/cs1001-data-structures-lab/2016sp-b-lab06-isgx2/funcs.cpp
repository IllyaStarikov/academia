unsigned long factorial(unsigned long n)
{
    if(n < 2)
    {
        return 1;
    }

    return n * factorial(n - 1);
}

unsigned long combination(unsigned long n, unsigned long m)
{
	unsigned long nFactorial = factorial(n);
	unsigned long kFactorial = factorial(m);
	unsigned long nkFactorial = factorial(n-m);
	
	return nFactorial / (kFactorial * nkFactorial);
}
