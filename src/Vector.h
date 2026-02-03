#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <climits>

template <typename T>
class Vector {
    private:
    T* arr;
    int size, capacity;

    void redefineCapacity();
    void checkBounds(int index);

    public:
    T& operator[](const int index);
    const T operator[] (const int index) const;
    Vector<T>& operator=(const Vector<T>& other);
    
    Vector();
    Vector(const Vector<T> &obj);
    ~Vector();

    T pop();
    T get(int index);

    int find(T element);
    int getSize();

    void push(T element);
    void remove(int index);
    void insert(int index, T element);
    void replace(int index, T element);
    Vector<T> map(T (*f)(T));
    Vector<T> filter(bool (*f)(T));
};

const int MIN_VECTOR_CAPACITY = 40;
const int SIZE_INCREMENT = 10;

template <typename T>
T& Vector<T>::operator[](const int index)
{
    checkBounds(index);
    return arr[index];
}

template <typename T>
const T Vector<T>::operator[](const int index) const 
{
    checkBounds(index);
    return arr[index];
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this != &other) { // Prevent self-assignment (v = v)
        delete[] arr;     // Clean up our old memory first

        size = other.size;
        capacity = other.capacity;
        arr = new T[capacity]; // Allocate new memory
        for (int i = 0; i < size; i++) {
            arr[i] = other.arr[i];
        }
    }
    return *this;
}

// private
template <typename T>
Vector<T>::Vector(): size(0), capacity(MIN_VECTOR_CAPACITY)
{
    arr = new T[capacity];
}

template <typename T>
inline Vector<T>::Vector(const Vector<T> &other)
{
    capacity = other.capacity;
    size = other.size;

    arr = new T[capacity];
    for (int i = 0; i < size; i++)
        arr[i] = other.arr[i];
}

template <typename T>
Vector<T>::~Vector()
{
    delete[] arr;
}

template <typename T>
void Vector<T>::redefineCapacity()
{
    if (capacity != size) return;

    int newCapacity = capacity + SIZE_INCREMENT;
    T* newArr = new T[newCapacity];

    for (int i = 0; i < size; i++)
        newArr[i] = arr[i];
    
    delete[] arr;
    arr = newArr;
    capacity = newCapacity;
}

template <typename T>
void Vector<T>::checkBounds(int index)
{
    if (index < 0 || index >= size)
        throw std::out_of_range("index is out of bounds");
}

// public
template <typename T>
T Vector<T>::pop()
{
    if (size == 0)
        throw std::out_of_range("tried to pop an empty vector");
    size--;
    return arr[size];
}

template <typename T>
T Vector<T>::get(int index)
{
    checkBounds(index);
    return arr[index];
}

// returns index of element in the vector. returns -1 if element is not found;
template <typename T>
int Vector<T>::find(T element)
{
    for (int i = 0; i < size; i++)
        if (element == arr[i]) return i;
    return -1;
}

// 
template <typename T>
int Vector<T>::getSize() 
{
    return size;
}

template <typename T>
void Vector<T>::push(T element)
{
    arr[size] = element;
    size++;

    redefineCapacity();
}

template <typename T>
void Vector<T>::remove(int index)
{
    checkBounds(index);
    size--;
    for (int i = index; i < size; i++)
        arr[i] = arr[i+1];
}


template <typename T>
void Vector<T>::insert(int index, T element)
{
    checkBounds(index);
    
    for (int i = size; i > index; i--)
        arr[i] = arr[i-1];
    arr[index] = element;
    size++;

    redefineCapacity();
}

template <typename T>
void Vector<T>::replace(int index, T element)
{
    checkBounds(index);
    arr[index] = element;
}

template <typename T>
Vector<T> Vector<T>::map(T (*func)(T))
{
    Vector<T> result;

    for (int i = 0; i < size; i++)
        result.push(func(arr[i]));
    
    return result;
}

template <typename T>
Vector<T> Vector<T>::filter(bool (*func)(T))
{
    Vector<T> result;

    for (int i = 0; i < size; i++) {
        if (func(arr[i]))
            result.push(arr[i]);
    }
    
    return result;
}


#endif