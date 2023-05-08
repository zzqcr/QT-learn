#ifndef ZVECTOR_H
#define ZVECTOR_H
#include <iostream>
template<typename  T>
class ZVector
{
public:
    ZVector();
    ZVector(int num);
    ~ZVector();
    void push_back(const T & value);
    void pop_back();
    int size() const;
    int capacity() const;




    // 运算符重载

    T& operator[](int i);

    template<typename  T1>
    friend std::ostream &operator<<(std::ostream &out,ZVector<T1> &V);

    template<typename  T1>
    friend ZVector<T1> &operator<<(ZVector<T1> &V,T1 value);

private:
    T* m_data;
    int m_size;  // 当前个数
    int m_capacity; // 最大容量

};
// 操作符重载
template<typename T>
T& ZVector<T>::operator[](int i)
{
    return m_data[i];
}

template<typename  T1>
ZVector<T1> &operator<<(ZVector<T1> &V,T1 value)
{
    V.push_back(value);
    return V;
}


template<typename  T>
std::ostream &operator<< (std::ostream &out,ZVector<T> &V)
{
    out<<"[";
    for(int i=0;i<V.size();i++){
        out<<V.m_data[i];
        if(i!= V.size()-1){
            out<<",";
        }
    }
    out<<"]"<<std::endl;
    return out;
}

// 函数实现
template<typename T>
ZVector<T>::ZVector() : m_data(nullptr),m_size(0),m_capacity(0)
{

}


template<typename T>
ZVector<T>::ZVector(int num) : m_data(new T [num]),m_size(0),m_capacity(num)
{
}

template<typename T>
ZVector<T>::~ZVector()
{
    if(m_data != nullptr){
        delete [] m_data;
    }
    m_size = 0;
    m_capacity =0;
}

template<typename T>
void ZVector<T>::push_back(const T &value)
{
    if(m_size < m_capacity){
        m_data[m_size] = value;
        m_size++;
        return;
    }
    // 扩容
    if(m_capacity ==0){
        m_capacity =1;
    }
    else {
        m_capacity*=2;
    }
    T* data = new T[m_capacity];
    // 转移数据
    for(int i=0;i< m_size;i++){
        data[i] = m_data[i];
    }
    // 删除原来数组
    if(m_data != nullptr){
        delete [] m_data;
        m_data = nullptr;
    }
    m_data = data;
    m_data[m_size] = value;
    m_size++;
}

template<typename T>
void ZVector<T>::pop_back()
{
    m_size--;
}

template<typename T>
int ZVector<T>::size() const
{
    return m_size;
}

template<typename T>
int ZVector<T>::capacity() const
{
    return m_capacity;
}


#endif // ZVECTOR_H
