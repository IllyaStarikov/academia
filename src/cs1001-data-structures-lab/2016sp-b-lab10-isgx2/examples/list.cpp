#include<iostream>
using namespace std;

class  List
{
  public:
    List(unsigned int num)
    {
      n = num;
      nxt = NULL;
    }

    ~List()
    {
      if(nxt)
        delete nxt;
    }

    unsigned int number()
    {
      return n;
    }

    List* next()
    {
      return nxt;
    }

    List* prepend(unsigned int num)
    {
      List* ret = new List(num);
      ret->nxt = this;
      return ret;
    }

  private:
    unsigned int n;
    List* nxt;
};

List* fibonnacci(unsigned long n)
{
  List* fib = new List(1);

  fib = fib->prepend(1);

  for(unsigned long i = 2; i <= n; i++)
  {
    fib = fib->prepend(fib->number() + fib->next()->number());
  }

  return fib;
}

int main()
{
  List* fib = fibonnacci(35);

  while(fib != NULL)
  {
    cout << fib->number() << endl;
    fib = fib->next();
  }

  delete fib;
  return 0;
}
