// Programmer: Illya Starikov                                Date: 10/07/15
// File: arraylist.hpp                                       Class: CS1510A

#ifndef arraylist_h
#define arraylist_h
void error(const std::string explanation) {
    std::cout << "!-- ERROR : PANIC in ARRAYLIST!!" << explanation << std:: endl;
}

template<typename T>
ArrayList<T>::~ArrayList() {
    m_size = 0;
    m_max = 0;
    
    delete []m_data;
    m_data = NULL;
}

template<typename T>
ArrayList<T>& ArrayList<T>:: operator=(const ArrayList<T>& rhs) {
    if (this != &rhs) {
        delete []m_data;
        m_data = NULL;
        m_data = new T [rhs.m_max];
        
        m_size = rhs.m_size;
        m_max = rhs.m_max;
        
        for (int i = 0; i < m_size; i++) {
            m_data[i] = rhs.m_data[i];
        }
    }
    return *this;
}

template<typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& cpy) {
    m_data = NULL;
    *this = cpy;
}

template<typename T>
int ArrayList<T>:: size() const {
    return m_size;
}

template<typename T>
const T& ArrayList<T>::first() const {
    if (m_size > 0) {
        return m_data[0];
    } else {
        error("Trying To Access Memory Outside of Scope.");
        return m_errobj;
    }
}

template <typename T>
T& ArrayList<T>::operator[](int i) {
    if (i > m_size) { error("Invalid Element Position (In [] Operator)"); }
    return (i < m_size) ? m_data[i]: m_errobj;
}

template <typename T>
const T& ArrayList<T>::operator[](int i) const {
    if (i > m_size) { error("Invalid Element Position (In [] Operator)"); }
    return (i < m_size) ? m_data[i]: m_errobj;
}

template<typename T>
int ArrayList<T>::find(const T& x) {
    const int numberToReturnIfVariableIsNotFound = -1;
    for (int i = 0; i < m_size; i++) {
        if (m_data[i] == x) {
            return i;
        }
    }
    return numberToReturnIfVariableIsNotFound;
}


template<typename T>
void ArrayList<T>::clear() {
    m_max = 0;
    m_size = 0;
    delete[] m_data;
    m_data = NULL;
}

template<typename T>
void ArrayList<T>::insert_back(const T& x) {
    insert(x, m_size);
}

template<typename T>
void ArrayList<T>::insert(const T& x, int i) {
    if (i < 0 || i > m_size) {
        error("Invalid Parameter [insert]");
        return;
    }
    
    if (m_size == m_max) {
        if (m_max == 0) { m_max = 2; }
        T* temporary = new T[m_max * 2];
        m_max *= 2;
        
        for (int j = 0; j < m_size; j++) {
            temporary[j] = m_data[j];
        }
        
        delete[] m_data;
        m_data = NULL;
        m_data = temporary;
    }
    
    for (int j = m_size; j > i; j--) {
        m_data[j] = m_data[j - 1];
    }
    
    m_data[i] = x;
    m_size++;
}

template<typename T>
void ArrayList<T>::remove(int i) {
    if (i < 0 || i > m_size) {
        error("Invalid Paraemeter [remove]");
        return;
    }
    
    for (int j = i; j < m_size; j++ ) {
        m_data[j] = m_data[j + 1];
    }
    
    m_size--;
    
    if (m_size * 4 < m_max) {
        T* temporary = new T[static_cast<int>(m_max / 2)];
        m_max = static_cast<int>(m_max / 2);
        
        for (int j = 0; j < m_size; j++) {
            temporary[j] = m_data[j];
        }
        
        delete []m_data;
        m_data = NULL;
        m_data = temporary;
    }
}

template<typename T>
void ArrayList<T>::swap(int i, int k) {
    if (i < 0 || i > m_size || k < 0 || k > m_size) {
        error("Invalid Parameters [swap]");
        return;
    }
    
    T temporary = m_data[i];
    m_data[i] = m_data[k];
    m_data[k] = temporary;
}

template<typename T>
void ArrayList<T>::append(const ArrayList<T>& alist) {
    if (this == &alist || m_size > m_max || m_size < 0 || alist.m_size > alist.m_max || alist.m_size < 0) {
        error("Trying To Access Memory Outside Of Scope");
        return;
    }
    
    T* temporary = new T [m_max + alist.m_max];
    
    for (int i = 0; i < m_size; i++) {
        temporary[i] = m_data[i];
    }
    
    for (int i = m_size; i < m_size + alist.m_size; i++) {
        temporary[i] = alist.m_data[i - m_size];
    }
    
    m_size += alist.m_size;
    m_max += alist.m_max;
    
    delete[] m_data;
    m_data = NULL;
    m_data = temporary;
}

template<typename T>
void ArrayList<T>::purge() {
    for (int i = 0; i < m_size; i ++) {
        for (int j = i + 1; j < m_size; j++) {
            if (m_data[i] == m_data[j]) {
                remove(j);
                j--;
            }
        }
    }
}

#endif /* arraylist_h */
