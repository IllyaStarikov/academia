#include<iostream>
using namespace std;

class List
{
  public:
    // Constructor
    List(int v)
    {
      val = v;
      nxt = NULL;
    }

    // Copy Constructor
    List(const List& copy)
    {
      val = copy.value();
      nxt = NULL;

      List* copy_iter = copy.next();
      List* this_iter = this;

      while(copy_iter)
      {
        this_iter->nxt = new List(copy_iter->value());
        this_iter = this_iter->next();
        copy_iter = copy_iter->next();
      }
    }

    // Destructor
    ~List()
    {
      if(nxt)
      {
        delete nxt;
      }

    }

    // Append a new node to the linked list
    void append(int v)
    {
      List* l = last();

      l->nxt = new List(v);
    }

    // Append a linked list to the end of this list
    void extend(List* e)
    {
      List* l = last();
      List* ext = new List(*e); // Prevent circular links

      l->nxt = ext;
    }

    // Print out the list
    void print() const
    {
      const List* iter = this;
      while(iter)
      {
        cout << iter->value() << endl;
        iter = iter->next();
      }
    }


    // Getters

    int value() const
    {
      return val;
    }

    List* next() const
    {
      return nxt;
    }

  private:
    // Get the last item in the linked list
    List* last()
    {
      List* l = this;
      while(l->next() != NULL)
      {
        l = l->next();
      }

      return l;
    }

    int val;
    List* nxt;
};

int main()
{
  List nums(0);
  const int max_val = 5;

  // Add some numbers to the list
  for(unsigned int i = 1; i <= max_val; i++)
  {
    nums.append(i);
  }

  cout << "The list: " << endl;
  nums.print();


  // Double the list
  List* nums_copy = new List(nums);

  cout << "The list, doubled: " << endl;
  nums.extend(nums_copy);
  nums.print();
  
  delete nums_copy;
  return 0;
}
