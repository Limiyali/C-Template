#include <iostream>
#include <memory>

using std::cout;
using std::endl;

// template <typename T, size_t n> class SquareMatrix {
// public:
//   void invert() { cout << typeid(T).name() << " size:" << n << endl; }
// };

// template <typename T> class SquareMatrixBase {
// protected:
//   void invert(size_t size) {
//     cout << typeid(T).name() << " size:" << size << endl;
//   }
// };

// template <typename T, size_t n>
// class SquareMatrix : private SquareMatrixBase<T> {
// private:
//   using SquareMatrixBase<T>::invert;

// public:
//   void invert() { this->invert(n); }
// };

template <typename T> class SquareMatrixBase {
protected:
  SquareMatrixBase(size_t n, T *data) : size(n), pData(data) {}
  void invert() { cout << typeid(T).name() << " size:" << size << endl; }

private:
  size_t size;
  T *pData;
};

template <typename T, size_t n>
class SquareMatrix : private SquareMatrixBase<T> {
public:
  SquareMatrix() : SquareMatrixBase<T>(n, data.get()) {
    // data.reset(new T[25]);
  }
  using SquareMatrixBase<T>::invert;

private:
  T data[n * n];
  // std::shared_ptr<T> data;
};

int main() {
  SquareMatrix<int, 5> a;
  SquareMatrix<double, 3> b;
  a.invert();
  b.invert();
  return 0;
}