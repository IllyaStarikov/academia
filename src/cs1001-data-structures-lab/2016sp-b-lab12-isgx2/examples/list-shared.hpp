// ~~~ Cell ~~~
template<class T>
Cell<T>::Cell(const T& t, shared_ptr<Cell<T> > n)
{
  elem = t;
  next = n;
}

template<class T>
Cell<T>::Cell(const Cell& c)
{
  elem = c.elem;

  if(c.next == NULL)
  {
    next = NULL;
  }
  else
  {
    next = shared_ptr<Cell<T> >(new Cell(*(c.next)));
  }
}

// ~~~ List ~~~

// Copy Constructor
template<class T>
List<T>::List(const List& l)
{
  if(!l.empty())
  {
    cell = shared_ptr<Cell<T> >(new Cell<T>(*(l.cell)));
  }
}

// Inserting stuff
template<class T>
void List<T>::prepend(const T& t)
{
  shared_ptr<Cell<T> > h(new Cell<T>(t, cell));
  cell = h;
}

template<class T>
void List<T>::append(const T& t)
{
  if(empty())
  {
    prepend(t);
  }
  else
  {
    shared_ptr<Cell<T> > it = cell;
    while(it->next != NULL)
    {
      it = it->next;
    }

    it->next = shared_ptr<Cell<T> >(new Cell<T>(t, NULL));
  }
}

template<class T>
void List<T>::extend(const List& l)
{
  if(empty())
  {
    cell = shared_ptr<Cell<T> >(new Cell<T>(*(l.cell)));
  }
  else
  {
    Cell<T>* it = cell;
    while(it->next != NULL)
    {
      it = it->next;
    }

    it->next = shared_ptr<Cell<T> >(new Cell<T>(*(l.cell)));
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

  cell = cell->next;
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

  if(cell->next != NULL)
  {
    l.cell = shared_ptr<Cell<T> >(new Cell<T>(*(cell->next)));
  }
  return l;
}

template<class T>
shared_ptr<Cell<T> > List<T>::iterator()
{
  return cell;
}

// Properties
template<class T>
unsigned int List<T>::length() const
{
  unsigned int len = 0;
  shared_ptr<Cell<T> > it = cell;

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

