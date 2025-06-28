// ~~~ Cell ~~~
template<class T>
Cell<T>::Cell(T& t, Cell<T>* n)
{
  elem = t;
  next = n;
}

template<class T>
Cell<T>::Cell(Cell& c)
{
  elem = c.elem;

  if(c.next == NULL)
  {
    next = NULL;
  }
  else
  {
    c.next = new Cell<T>(*(c.next));
  }
}

// ~~~ List ~~~
// Constructor
template<class T>
List<T>::List()
{
  cell = NULL;
}

// Copy Constructor
template<class T>
List<T>::List(const List& l)
{
  if(l.empty())
  {
    cell = NULL;
  }
  else
  {
    cell = new Cell<T>(*(l.cell));
  }
}

// Destructor
template<class T>
List<T>::~List()
{
  Cell<T>* it = cell;
  Cell<T>* toDelete = NULL;

  while(it != NULL)
  {
    toDelete = it;
    it = it->next;
    delete toDelete;
  }
}

// Inserting stuff
template<class T>
void List<T>::prepend(T& t)
{
  Cell<T>* h = new Cell<T>(t, cell);
  cell = h;
}

template<class T>
void List<T>::append(T& t)
{
  if(empty())
  {
    prepend(t);
  }
  else
  {
    Cell<T>* it = cell;
    while(it->next != NULL)
    {
      it = it->next;
    }

    it->next = new Cell<T>(t, NULL);
  }
}

template<class T>
void List<T>::extend(const List& l)
{
  if(empty())
  {
    cell = new Cell<T>(*(l.cell));
  }
  else
  {
    Cell<T>* it = cell;
    while(it->next != NULL)
    {
      it = it->next;
    }

    it->next = new Cell<T>(*(l.cell));
  }
}

// Removing stuff
template<class T>
void List<T>::pop()
{
  if(empty())
  {
    throw out_of_range("empty list");
  }

  Cell<T>* next = cell->next;
  delete cell;
  cell = next;
}

// Accessors
template<class T>
T& List<T>::head()
{
  if(empty())
  {
    throw out_of_range("empty list");
  }

  return cell->elem;
}

template<class T>
List<T> List<T>::tail()
{
  if(empty())
  {
    throw out_of_range("empty list");
  }

  List<T> l;

  if(cell->next == NULL)
  {
    return l;
  }
  else
  {
    l.cell = new Cell<T>(*(cell->next));
  }
}

template<class T>
Cell<T>* List<T>::iterator()
{
  return cell;
}

// Properties
template<class T>
unsigned int List<T>::length() const
{
  unsigned int len = 0;
  Cell<T>* it = cell;

  while(it != NULL)
  {
    len++;
    it = it->next;
  }

  return len;
}

template<class T>
bool List<T>::empty() const
{
  return cell == NULL;
}

