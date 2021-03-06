#include "circularvector.h"
#include <iostream>
using namespace std;

namespace tools {

template <typename T_Obj>
CircularVector<T_Obj>::CircularVector() : size_(0), cursor(0)
{
}

template <typename T_Obj>
CircularVector<T_Obj>::CircularVector(const quint32 &size) : size_(size), cursor(0)
{
}

template <typename T_Obj>
void CircularVector<T_Obj>::push_back(T_Obj obj) {

    if(this->size() < size_) {
        vector<T_Obj>::push_back(obj);
        ++cursor;
        return;
    }

    at(cursor) = obj;
    ++cursor;
}

template<typename T_Obj>
T_Obj &CircularVector<T_Obj>::at(const qint32 &adr) {
    return vector<T_Obj>::at(adr >= 0 ? adr%size_ : size_ - (-adr)%size_);
}

template<typename T_Obj>
quint32 CircularVector<T_Obj>::length(const qint32 &adrA, const qint32 &adrB) const
{
    qint32 pA, pB;

    adrA > 0 ? pA = adrA%size_ : pA = size_ - (-adrA)%size_;
    adrB > 0 ? pB = adrB%size_ : pB = size_ - (-adrB)%size_;

    return pA < pB ? pB - pA + 1: size_ - pA + pB + 1;
}

template<typename T_Obj>
void CircularVector<T_Obj>::setSize(const quint32 &size)
{
    size_ = size;
}

template<typename T_Obj>
typename vector<T_Obj>::value_type *CircularVector<T_Obj>::ptr(const qint32 &adr)
{
    return adr >= 0 ? vector<T_Obj>::data() + adr%size_ : vector<T_Obj>::data() + size_ - (-adr)%size_;
}

}
