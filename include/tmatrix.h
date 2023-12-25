// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;//размер вектора
  T* pMem;//указатель на массив элементов вектора
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {// конструктор по умолчанию, создется вектор размером 1 элем,
    if (sz == 0)//дальше в этом конструкторе происходит выделение динамической памяти для хр элем
      throw out_of_range("Vector size should be greater than zero");
    if (size > MAX_VECTOR_SIZE) throw "Size should be less";
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {// конструктор, принимающий указатель на массив элементов и создающий вектор на основе этого массива
    assert(arr != nullptr && "TDynamicVector vector requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {// Конструктор копирования, который создает копию существующего вектора и
      if (v.pMem == nullptr) {//выделяет новую динамическую память для хранения его элементов
          sz = 0;
          pMem = nullptr;
      }
      else {
          sz = v.sz;
          pMem = new T[sz];
          std::copy(v.pMem, v.pMem + sz, pMem);
      }
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = v.sz;
      pMem = nullptr;
      std::swap(pMem, v.pMem);
  }
  ~TDynamicVector()// деструктор для освобождения памяти
  {
      if(pMem != nullptr)
          delete[] pMem;

      pMem = nullptr;
      sz = 0;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v)
          return *this;
      if (sz != v.sz)
      {
          if (pMem != nullptr)
              delete[] pMem;
          sz = v.sz;
          pMem = new T[sz];
      }
      std::copy(v.pMem, v.pMem + v.sz, pMem);
      return *this;

  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this == &v)
          return *this;
      if (pMem != nullptr) {
          delete[] pMem;
          pMem = nullptr;
      }

      sz = v.sz;
      std::swap(pMem, v.pMem);

      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  //пример вектора вызов функции
  T& operator[](size_t ind)
  {
      if (ind > sz || ind < 0) throw "Index not in range";
      return pMem[ind];
  }
   const T& operator[](size_t ind) const
  {
      if (ind > sz || ind < 0) throw "Index not in range";
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind > sz || ind < 0) throw "Index not in range";
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind > sz || ind < 0) throw "Index not in range";
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) return false;
      for (int i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i]) return false;
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector result(sz);
      for (int i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] + val;
      }
      return result;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector result(sz);
      for (int i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] - val;
      }
      return result;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector result(sz);
      for (int i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] * val;
      }
      return result;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) throw "Error len vector";
      TDynamicVector result(sz);
      for (int i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] + v.pMem[i];
      }
      return result;

  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) throw "Error len vector";
      TDynamicVector result(sz);
      for (int i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] - v.pMem[i];
      }
      return result;
  }
  T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))S
  {
      if (sz != v.sz) throw "Error len vector";
      T result = T();
      for (int i = 0; i < sz; i++) {
          result += pMem[i] * v.pMem[i];
      }
      return result;
  }
  //друж функции имеют доступ к private и не явл членами класса
  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>//наследование конструкторов класса вектора
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if (s > MAX_MATRIX_SIZE) throw "So big";
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) return false;
      for (int i = 0; i < sz; i++) {
          if (pMem[i] != m.pMem[i]) return false;
      }
      return true;
  }
  size_t size() const noexcept { return sz; }
  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix result(sz);
      for (int i = 0; i < n; i++) {
          result.pMem[i] = pMem[i] * val;
      }
      return result;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.sz) throw "Error len";
      TDynamicVector<T> result(sz);
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; j++) {
              result[i] += pMem[i][j] * v[j];
          }
      }
      return result;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw "Error len";
      TDynamicMatrix result(sz);
      for (int i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] + m.pMem[i];
      }
      return result;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw "Error len";
      TDynamicMatrix result(sz);
      for (int i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] - m.pMem[i];
      }
      return result;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw "Error len";
      TDynamicMatrix result(sz);
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; j++) {
              for (int k = 0; k < sz; k++) {
                  result[i][j] += pMem[i][k] * m.pMem[k][j];
              }
          }
      }

      return result;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (int i = 0; i < v.sz; i++) {
          istr >> v.pMem[i];
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (int i = 0; i < v.sz; i++) {
          ostr << v.pMem[i] << endl;
      }
      return ostr;
  }
};

#endif
