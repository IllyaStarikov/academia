// Programmer: Illya Starikov                                Date: 10/14/15
// File: linkedlist.hpp                                      Class: CS1510A



#ifndef linkedlist_h
#define linkedlist_h

const std::string errorMessage = "!!-- ERROR : PANIC in LINKEDLIST.";
void printErrorMessage(const std::string explanation, const std::string functionName) {
    std::cout << errorMessage << functionName << "() - " << explanation << std::endl;
}

template <class T>
const LinkedList<T>&  LinkedList<T>::operator= (const LinkedList<T>& rhs) {
       if (this != &rhs) {
        LinkedList<T> *rightHandRunner = rhs.m_next;
        const LinkedList<T> *runner = this;
    
        clear();
        insert_front(rhs.m_data);
        
        while (rightHandRunner -> m_next != NULL) {
            insert(rightHandRunner -> m_data, runner -> m_next);
            rightHandRunner = rightHandRunner -> m_next;
            runner = runner -> m_next;
        }
    }
    
    return *this;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& rhs) {
    m_next = NULL;
    *this = rhs;
}

template <class T>
int LinkedList<T>::size() const {
    if (isEmpty()) {
        return 0;
    }
    
    int counter = 0;
    const LinkedList<T> *runner = this;
    
    while (runner -> m_next != NULL) {
        counter++;
        runner = runner -> m_next;
    }
    
    return counter;
}

template <class T>
bool LinkedList<T>::isEmpty() const {
    return (m_next == NULL);
}

template <class T>
LinkedList<T>* LinkedList<T>::getFirstPtr() {
    if (isEmpty()) {
        printErrorMessage("empty list", "getFirstPtr");
        return NULL;
    }

    return getAtPtr(0);
}

template <class T>
LinkedList<T>* LinkedList<T>::getLastPtr() {
    if (isEmpty()) {
        printErrorMessage("empty list", "getLastPtr");
        return NULL;
    }
    
    return getAtPtr(size() - 1);
}

template <class T>
LinkedList<T>* LinkedList<T>::getAtPtr(int i) {
    LinkedList<T> *runner = this;
    
    if (i > size() || i < 0) {
        printErrorMessage("invalid index", "getAtPtr");
        return NULL;
    }
    
    for (int j = 0; j < i; j++) {
        runner = runner -> m_next;
    }
    
    return runner;
}

template <class T>
void LinkedList<T>::clear() {
    if (isEmpty()) {
        return;
    } // if the list is empty, don't bother
    
    LinkedList<T> *temp = m_next;
    
    while  (temp != NULL) {
        // duplicate
        m_next = temp -> m_next;
        
        delete temp;
        temp = NULL;
        temp = m_next;
    }
}

template <class T>
void LinkedList<T>::insert_front(const T& x) {
    insert(x, this);
}

template <class T>
void LinkedList<T>::insert(const T& x, LinkedList<T>* pos) {
    LinkedList<T> *temp = new LinkedList<T>;
    
    temp -> m_data = pos -> m_data;
    temp -> m_next = pos -> m_next;
    
    pos -> m_next = temp;
    pos -> m_data = x;
}

template<class T>
bool LinkedList<T>::operator== (const LinkedList<T>& rhs) const {
    if (size() != rhs.size()) { return false; }
    
    if (m_data == rhs.m_data) {
        if (m_next == NULL) { return true; }
    }
    
    const LinkedList<T> *thisRunner = this;
    const LinkedList<T> *rightHandSideRunner = &rhs;
    
    
    while(thisRunner -> m_next != NULL) {
        if (thisRunner -> m_data != rightHandSideRunner -> m_data) {
            return false;
        }
        
        thisRunner = thisRunner -> m_next;
        rightHandSideRunner = rightHandSideRunner -> m_next;
    }
    
    return true;
}

template<class T>
void LinkedList<T>::remove(LinkedList<T>* pos) {
    LinkedList<T> *temp = pos -> m_next;
    
    pos -> m_data = temp -> m_data;
    pos -> m_next = temp -> m_next;
    
    delete temp;
    temp = NULL;
}

template<class T>
LinkedList<T>* LinkedList<T>::find(const T& x) {
    LinkedList<T> *runner = this;
    
    while (runner != NULL) {
        if (runner -> m_data == x) { return runner; }
        runner = runner -> m_next;
    }
    
    return NULL;
}

template<class T>
void LinkedList<T>::reverse() {
    LinkedList<T> reversedList;
    LinkedList<T> *runner = this;
    
    for (int i = 0; i < size(); i++) {
        reversedList.insert_front(runner -> m_data);
        runner = runner -> m_next;
    }
    
    *this = reversedList;
    reversedList.clear();
}

template <class T>
void LinkedList<T>::append(const LinkedList<T>& xlist) {
    const LinkedList<T> *xlistRunner = &xlist;
    
    for (int j = 0; j < xlist.size(); j++) {
        insert(xlistRunner -> m_data, getAtPtr(size()));
        xlistRunner = xlistRunner -> m_next;
    }
}

#endif /* linkedlist_h */
