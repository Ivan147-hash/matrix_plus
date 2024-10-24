#ifndef __S21_MATRIX_OOP_H__
#define __S21_MATRIX_OOP_H__

#include <cmath>
#include <exception>
#include <iostream>
#include <stdexcept>

#define ESP 10E-7

class S21Matrix {
 public:
  // constructors
  S21Matrix();                    // default constructor
  S21Matrix(int rows, int cols);  // parameterized constructor
  S21Matrix(const S21Matrix& o);  // copy cnstructor  конструктор копирования
  S21Matrix(S21Matrix&& o);  // move cnstructor  переместить конструктор
  S21Matrix(std::initializer_list<std::initializer_list<double>> init_list);
  ~S21Matrix();  // destructor

  // methods
  bool EqMatrix(const S21Matrix& other) noexcept;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() noexcept;
  S21Matrix Minor(const int i, const int j);
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // operators
  S21Matrix operator+(const S21Matrix& o);
  S21Matrix operator-(const S21Matrix& o);
  S21Matrix operator*(const S21Matrix& o);
  S21Matrix operator*(const double& num);
  friend S21Matrix operator*(const double& num, const S21Matrix& other);
  bool operator==(const S21Matrix& o) noexcept;
  S21Matrix& operator=(const S21Matrix& o);
  S21Matrix& operator+=(const S21Matrix& o);
  S21Matrix& operator-=(const S21Matrix& o);
  S21Matrix& operator*=(const S21Matrix& o);
  S21Matrix& operator*=(const double& num);
  double& operator()(const int row, const int col);
  double operator()(const int row, const int col) const;

  // Accessors/mutators
  int get_Row() const;
  int get_Col() const;
  void set_Row(int const x);
  void set_Col(int const y);

  // other methods
  double** allocate(const int rows_, const int cols_);
  void destructor(S21Matrix& o);

 private:
  // атрибуты
  int rows_, cols_;  // rows and columns attributes  нижнее подчеркивание в
                     // конце / private идет в конце класса
  double** matrix_;  // указатель на память, где будет размещена матрица
};

#endif
