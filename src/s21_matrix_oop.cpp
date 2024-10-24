#include "s21_matrix_oop.h"

double** S21Matrix::allocate(const int rows_, const int cols_) {
  double** matrix = new double*[rows_];
  if (matrix == nullptr) {
    throw std::bad_alloc();
  }
  int x = 0;
  try {
    for (int i = 0; i < rows_; ++i) {
      matrix[i] = new double[cols_];
      if (matrix[i] == nullptr) {
        x = i;
        throw std::bad_alloc();
      }
      for (int j = 0; j < cols_; ++j) {
        matrix[i][j] = 0;
      }
    }
  } catch (const std::exception& err) {
    for (int i = 0; i < x; ++i) {
      if (matrix[i] != nullptr) {
        delete[] matrix[i];
      }
    }
    delete[] matrix;
    throw;
  }
  return matrix;
}

S21Matrix::S21Matrix() {
  rows_ = 3;
  cols_ = 3;
  matrix_ = allocate(rows_, cols_);
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 1 || cols < 1) {
    throw std::invalid_argument("Invalid argument");
  }
  matrix_ = allocate(rows_, cols_);
}

S21Matrix::S21Matrix(const S21Matrix& o) : rows_(o.rows_), cols_(o.cols_) {
  matrix_ = allocate(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = o.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& o) {
  rows_ = o.rows_;
  cols_ = o.cols_;
  matrix_ = o.matrix_;
  o.matrix_ = nullptr;
  o.rows_ = 0;
  o.cols_ = 0;
}

void S21Matrix::destructor(S21Matrix& o) {
  if (o.matrix_ == nullptr) return;
  for (int i = 0; i < o.rows_; ++i) {
    delete[] o.matrix_[i];
  }
  delete[] o.matrix_;
}

S21Matrix::~S21Matrix() {
  if (matrix_) {
    destructor(*this);
  }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) noexcept {
  if ((rows_ != other.rows_) || (cols_ != other.cols_)) {
    return false;
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > ESP) {
        return false;
      }
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& o) {
  if (rows_ != o.rows_ || cols_ != o.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = matrix_[i][j] + o.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& o) {
  if (rows_ != o.rows_ || cols_ != o.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = matrix_[i][j] - o.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument("MulMatrix: cannot multiply matrices");
  }
  double** res = allocate(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int x = 0; x < rows_; x++) {
        res[i][j] += matrix_[i][x] * other.matrix_[x][j];
      }
    }
  }
  destructor(*this);
  matrix_ = res;
}

S21Matrix S21Matrix::Transpose() noexcept {
  S21Matrix res(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      res.matrix_[i][j] = matrix_[j][i];
    }
  }
  return res;
}

S21Matrix S21Matrix::Minor(const int i, const int j) {
  if (rows_ != cols_) {
    throw std::invalid_argument("Minor: the matrix is ​​not square");
  }
  if (i < 0 || i > rows_ - 1) {
    throw std::invalid_argument("Minor: i argument out of range");
  }
  if (j < 0 || j > cols_ - 1) {
    throw std::invalid_argument("Minor: j argument out of range");
  }
  int c = 0;
  int r = 0;
  int flag = 0;
  S21Matrix res(rows_ - 1, cols_ - 1);
  for (int x = 0; x < rows_; x++) {
    for (int y = 0; y < cols_; y++) {
      if (x != i && y != j) {
        res.matrix_[r][c] = matrix_[x][y];
        c++;
        flag = 1;
      }
    }
    if (flag) {
      r++;
      flag = 0;
      c = 0;
    }
  }
  return res;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Determinant: the matrix is ​​not square");
  }
  double res = 0;
  if (rows_ == 1) {
    return matrix_[0][0];
  } else {
    for (int i = 0; i != rows_; ++i) {
      S21Matrix minor = this->Minor(i, 0);
      res += minor.Determinant() * pow(-1, i) * matrix_[i][0];
    }
  }
  return res;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "CalcComplements: the matrix is ​​not square");
  }
  S21Matrix res(rows_, cols_);
  if (rows_ == 1) {
    res.matrix_[0][0] = 1;
  } else {
    S21Matrix matr(rows_ - 1, cols_ - 1);
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matr = this->Minor(i, j);
        res.matrix_[i][j] = matr.Determinant() * pow(-1, i + j);
      }
    }
  }

  return res;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = this->Determinant();
  double one = 1;
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "InverseMatrix: the matrix is ​​not square");
  }
  if (!det) {
    throw std::logic_error("InverseMatrix: determinant is zero");
  }
  S21Matrix result(rows_, cols_);
  S21Matrix temp = *this;
  temp = this->CalcComplements();
  result = temp.Transpose();
  result.MulNumber(one / det);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& o) noexcept { return EqMatrix(o); }

S21Matrix& S21Matrix::operator=(const S21Matrix& o) {
  if (this == &o) {
    return *this;
  }
  destructor(*this);
  rows_ = o.rows_;
  cols_ = o.cols_;
  matrix_ = allocate(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = o.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& o) {
  S21Matrix res(*this);
  res.SumMatrix(o);
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& o) {
  S21Matrix res(*this);
  res.SubMatrix(o);
  return res;
}

S21Matrix S21Matrix::operator*(const double& num) {
  S21Matrix res(*this);
  res.MulNumber(num);
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix& o) {
  S21Matrix res(*this);
  res.MulMatrix(o);
  return res;
}

S21Matrix operator*(const double& num, const S21Matrix& other) {
  S21Matrix res(other);
  res *= num;
  return res;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& o) {
  this->SumMatrix(o);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& o) {
  this->SubMatrix(o);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& o) {
  this->MulMatrix(o);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double& num) {
  this->MulNumber(num);
  return *this;
}

double& S21Matrix::operator()(int row, int col) {
  if (row < 0 || row > rows_ - 1) {
    throw std::out_of_range("Incorrect input, row is out of range");
  }
  if (col < 0 || col > cols_ - 1) {
    throw std::out_of_range("Incorrect input, col is out of range");
  }
  double& x = matrix_[row][col];
  return x;
}

double S21Matrix::operator()(const int row, const int col) const {
  if (row < 0 || row > rows_ - 1) {
    throw std::out_of_range("Incorrect input, row is out of range");
  }
  if (col < 0 || col > cols_ - 1) {
    throw std::out_of_range("Incorrect input, col is out of range");
  }
  return matrix_[row][col];
}

int S21Matrix::get_Row() const { return rows_; }

int S21Matrix::get_Col() const { return cols_; }

void S21Matrix::set_Row(int const x) {
  if (x < 0) {
    throw std::invalid_argument("set_Row: Invalid argument x");
  }
  S21Matrix mat(x, cols_);
  for (int i = 0; i < x; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (i >= rows_)
        mat.matrix_[i][j] = 0;
      else
        mat.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = mat;
}

void S21Matrix::set_Col(int const y) {
  if (y < 0) {
    throw std::invalid_argument("set_Row: Invalid argument y");
  }
  S21Matrix mat(rows_, y);
  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != y; ++j) {
      if (j >= cols_)
        mat.matrix_[i][j] = 0;
      else
        mat.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = mat;
}

S21Matrix::S21Matrix(
    std::initializer_list<std::initializer_list<double>> init) {
  rows_ = init.size();
  cols_ = rows_ > 0 ? init.begin()->size() : 0;
  matrix_ = allocate(rows_, cols_);
  int x = 0;
  for (auto i = init.begin(); i != init.end(); ++i) {
    int y = 0;
    for (auto j = (*i).begin(); j != (*i).end(); ++j) {
      matrix_[x][y] = *j;
      y++;
    }
    x++;
  }
}