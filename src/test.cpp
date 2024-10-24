#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(S21MatrixTest, DefaultConstructor) {
  S21Matrix mat;
  EXPECT_EQ(mat.get_Row(), 3);
  EXPECT_EQ(mat.get_Col(), 3);
  EXPECT_DOUBLE_EQ(mat(0, 0), 0.0);
}

TEST(S21MatrixTest, ParamsConstructor_0) {
  S21Matrix mat(2, 2);
  EXPECT_EQ(mat.get_Row(), 2);
  EXPECT_EQ(mat.get_Col(), 2);
  EXPECT_DOUBLE_EQ(mat(0, 0), 0.0);
}

TEST(S21MatrixTest, ParamsConstructor_1) {
  EXPECT_THROW(S21Matrix mat(0, 2), std::invalid_argument);
}

TEST(S21MatrixTest, ParamsConstructor_2) {
  EXPECT_THROW(S21Matrix mat(1, -3), std::invalid_argument);
}

TEST(S21MatrixTest, CopyConstructor) {
  S21Matrix mat(2, 2);
  S21Matrix copy = S21Matrix(mat);
  EXPECT_EQ(copy.get_Row(), 2);
  EXPECT_EQ(copy.get_Col(), 2);
}

TEST(S21MatrixTest, MoveConstructor) {
  S21Matrix mat(2, 2);
  S21Matrix copy = std::move(mat);
  EXPECT_EQ(copy.get_Row(), 2);
  EXPECT_EQ(copy.get_Col(), 2);
}

TEST(S21MatrixTest, SetRows_0) {
  S21Matrix mat;
  mat.set_Row(2);
  EXPECT_EQ(mat.get_Row(), 2);
}

TEST(S21MatrixTest, SetRows_1) {
  S21Matrix mat;
  mat.set_Row(1);
  EXPECT_EQ(mat.get_Row(), 1);
}

TEST(S21MatrixTest, SetRows_2) {
  S21Matrix mat;
  EXPECT_THROW(mat.set_Row(0), std::invalid_argument);
}

TEST(S21MatrixTest, SetCols_0) {
  S21Matrix mat;
  mat.set_Col(2);
  EXPECT_EQ(mat.get_Col(), 2);
}

TEST(S21MatrixTest, SetCols_1) {
  S21Matrix mat;
  mat.set_Col(1);
  EXPECT_EQ(mat.get_Col(), 1);
}

TEST(S21MatrixTest, SetCols_2) {
  S21Matrix mat;
  EXPECT_THROW(mat.set_Col(0), std::invalid_argument);
}

TEST(S21MatrixTest, OperatorSet_0) {
  S21Matrix mat(2, 2);
  EXPECT_THROW(mat(-1, 1), std::out_of_range);
}

TEST(S21MatrixTest, OperatorSet_1) {
  S21Matrix mat(2, 2);
  EXPECT_THROW(mat(1, -1), std::out_of_range);
}

TEST(S21MatrixTest, OperatorSet_2) {
  S21Matrix mat(2, 2);
  mat(1, 1) = 5;
  EXPECT_DOUBLE_EQ(mat(1, 1), 5);
}

TEST(S21MatrixTest, Operator_Get_0) {
  const S21Matrix mat(2, 2);
  EXPECT_THROW(mat(-1, 1), std::out_of_range);
}

TEST(S21MatrixTest, Operator_Get_1) {
  const S21Matrix mat(2, 2);
  EXPECT_THROW(mat(1, -1), std::out_of_range);
}

TEST(S21MatrixTest, Operator_Get_2) {
  S21Matrix mat(2, 2);
  mat(1, 1) = 5;
  const S21Matrix constMat = mat;
  EXPECT_DOUBLE_EQ(constMat(1, 1), 5);
}

TEST(S21MatrixTest, MulNumber) {
  S21Matrix mat = {{0, 1}, {2, 3}};

  mat.MulNumber(2);
  EXPECT_DOUBLE_EQ(mat(0, 0), 0);
  EXPECT_DOUBLE_EQ(mat(0, 1), 2);
  EXPECT_DOUBLE_EQ(mat(1, 0), 4);
  EXPECT_DOUBLE_EQ(mat(1, 1), 6);
}

TEST(S21MatrixTest, EqMatrix_0) {
  S21Matrix mat1(2, 2);
  S21Matrix mat2(3, 3);
  EXPECT_FALSE(mat1.EqMatrix(mat2));
}

TEST(S21MatrixTest, EqMatrix_1) {
  S21Matrix mat1 = {{0, 1}, {2, 3}};

  S21Matrix mat2 = {{0, 1}, {2, 3}};

  EXPECT_TRUE(mat1.EqMatrix(mat2));
}

TEST(S21MatrixTest, EqMatrix_2) {
  S21Matrix mat1 = {{0, 1}, {2, 3}};

  S21Matrix mat2 = {{1, 1}, {2, 3}};

  EXPECT_FALSE(mat1.EqMatrix(mat2));
}

TEST(S21MatrixTest, Transpose) {
  S21Matrix mat1 = {{0, 1}, {2, 3}};

  S21Matrix mat2 = {{0, 2}, {1, 3}};

  S21Matrix mat3 = mat1.Transpose();

  EXPECT_TRUE(mat3.EqMatrix(mat2));
}

TEST(S21MatrixTest, SumMatrix_0) {
  S21Matrix mat1(2, 2);
  S21Matrix mat2(3, 3);
  EXPECT_THROW(mat1.SumMatrix(mat2), std::out_of_range);
}

TEST(S21MatrixTest, SumMatrix_1) {
  S21Matrix mat1 = {{0, 2}, {1, 3}};

  S21Matrix mat2 = {{3, 4}, {5, 6}};

  S21Matrix mat3 = {{3, 6}, {6, 9}};

  mat1.SumMatrix(mat2);

  EXPECT_TRUE(mat3.EqMatrix(mat1));
}

TEST(S21MatrixTest, SubMatrix_0) {
  S21Matrix mat1(2, 2);
  S21Matrix mat2(3, 3);
  EXPECT_THROW(mat1.SubMatrix(mat2), std::out_of_range);
}

TEST(S21MatrixTest, SubMatrix_1) {
  S21Matrix mat1 = {{0, 1}, {2, 3}};

  S21Matrix mat2 = {{3, 4}, {5, 6}};

  S21Matrix mat3 = {{-3, -3}, {-3, -3}};

  mat1.SubMatrix(mat2);

  EXPECT_TRUE(mat3.EqMatrix(mat1));
}

TEST(S21MatrixTest, MulMatrix_0) {
  S21Matrix mat1(2, 2);
  S21Matrix mat2(3, 2);
  EXPECT_THROW(mat1.MulMatrix(mat2), std::invalid_argument);
}

TEST(S21MatrixTest, MulMatrix_1) {
  S21Matrix mat1 = {{0, 1}, {2, 3}};

  S21Matrix mat2 = {{3, 4}, {5, 6}};

  S21Matrix mat3 = {{5, 6}, {21, 26}};

  mat1.MulMatrix(mat2);

  EXPECT_TRUE(mat3.EqMatrix(mat1));
}

TEST(S21MatrixTest, Minor_0) {
  S21Matrix mat1(2, 2);
  EXPECT_THROW(S21Matrix mat2 = mat1.Minor(2, 1), std::invalid_argument);
}

TEST(S21MatrixTest, Minor_1) {
  S21Matrix mat1(2, 2);
  EXPECT_THROW(S21Matrix mat2 = mat1.Minor(1, 2), std::invalid_argument);
}

TEST(S21MatrixTest, Minor_2) {
  S21Matrix mat1 = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};

  S21Matrix mat2 = {{0, 2}, {6, 8}};

  S21Matrix mat3 = mat1.Minor(1, 1);

  EXPECT_TRUE(mat3.EqMatrix(mat2));
}

TEST(S21MatrixTest, Determinant_0) {
  S21Matrix mat1(3, 2);
  EXPECT_THROW(mat1.Determinant(), std::invalid_argument);
}

TEST(S21MatrixTest, Determinant_1) {
  S21Matrix mat1 = {{0, 1}, {2, 3}};

  double det = mat1.Determinant();

  EXPECT_DOUBLE_EQ(det, -2);
}

TEST(MatrixDeterminant, MatrixDeterminantComputedOk) {
  S21Matrix m = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

  double determinant = m.Determinant();

  EXPECT_NEAR(determinant, 0.0, 1e-6);
}

TEST(S21MatrixTest, CalcComplements_0) {
  S21Matrix mat1(3, 2);
  EXPECT_THROW(S21Matrix mat2 = mat1.CalcComplements(), std::invalid_argument);
}

TEST(S21MatrixTest, CalcComplements_1) {
  S21Matrix mat1 = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};

  S21Matrix mat2 = {{-3, 6, -3}, {6, -12, 6}, {-3, 6, -3}};

  S21Matrix mat3 = mat1.CalcComplements();

  EXPECT_TRUE(mat3.EqMatrix(mat2));
}

TEST(S21MatrixTest, CalcComplements_2) {
  S21Matrix mat1(1, 1);

  S21Matrix mat2(1, 1);
  mat2(0, 0) = 1;

  S21Matrix mat3 = mat1.CalcComplements();

  EXPECT_TRUE(mat3.EqMatrix(mat2));
}

TEST(MatrixCalcComplements, ComplementsForNotSimpleMatrixCalculatedOk) {
  S21Matrix m(4, 4);
  m(0, 0) = 1.80377;
  m(0, 1) = 3.93870;
  m(0, 2) = 3.13429;
  m(0, 3) = 2.28155;
  m(1, 0) = 1.39307;
  m(1, 1) = 1.05586;
  m(1, 2) = 2.21357;
  m(1, 3) = 2.20440;
  m(2, 0) = 2.74323;
  m(2, 1) = 2.41325;
  m(2, 2) = 3.86805;
  m(2, 3) = 2.73013;
  m(3, 0) = 2.29065;
  m(3, 1) = 3.09765;
  m(3, 2) = 1.84139;
  m(3, 3) = 3.86339;

  S21Matrix complements = m.CalcComplements();

  S21Matrix matr(4, 4);
  matr(0, 0) = -8.0642664633;
  matr(0, 1) = 4.1987149757;
  matr(0, 2) = 3.1661056480;
  matr(0, 3) = -0.0941589509;
  matr(1, 0) = -19.1443430067;
  matr(1, 1) = -4.4198224214;
  matr(1, 2) = 8.7731760020;
  matr(1, 3) = 10.7131854857;
  matr(2, 0) = 15.1040957594;
  matr(2, 1) = -1.3457695400;
  matr(2, 2) = -1.9412358558;
  matr(2, 3) = -6.9511236616;
  matr(3, 0) = 5.0123523428;
  matr(3, 1) = 0.9933255993;
  matr(3, 2) = -5.5038169258;
  matr(3, 3) = 1.8833757880;

  EXPECT_TRUE(complements == matr);
}

TEST(MatrixCalcComplements, ComplementFor3x3MatrixCalculated) {
  S21Matrix matr = {{1, 2, 3}, {3, 2, 1}, {7, 5, 2}};

  S21Matrix complements = matr.CalcComplements();

  EXPECT_EQ(complements.get_Row(), 3);
  EXPECT_EQ(complements.get_Col(), 3);

  S21Matrix m = {{-1, 1, 1}, {11, -19, 9}, {-4, 8, -4}};

  EXPECT_TRUE(complements == m);
}

TEST(S21MatrixTest, Inverse_0) {
  S21Matrix mat1 = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};

  EXPECT_THROW(S21Matrix mat2 = mat1.InverseMatrix(), std::logic_error);
}

TEST(S21MatrixTest, Inverse_1) {
  S21Matrix mat1 = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};

  S21Matrix mat2 = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};

  S21Matrix mat3 = mat1.InverseMatrix();

  EXPECT_TRUE(mat3.EqMatrix(mat2));
}

TEST(S21MatrixTest, OperatorPlusEqual) {
  S21Matrix mat1 = {{0, 1}, {2, 3}};

  S21Matrix mat2 = {{3, 4}, {5, 6}};

  S21Matrix mat3 = {{3, 5}, {7, 9}};

  mat1 += mat2;

  EXPECT_TRUE(mat3.EqMatrix(mat1));
}

TEST(S21MatrixTest, OperatorMinuxEqual) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 3;
  mat2(0, 1) = 4;
  mat2(1, 0) = 5;
  mat2(1, 1) = 6;

  S21Matrix mat3(2, 2);
  mat3(0, 0) = -3;
  mat3(0, 1) = -3;
  mat3(1, 0) = -3;
  mat3(1, 1) = -3;

  mat1 -= mat2;

  EXPECT_TRUE(mat3.EqMatrix(mat1));
}

TEST(S21MatrixTest, OperatorMultEqNumber) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 0;
  mat2(0, 1) = 2;
  mat2(1, 0) = 4;
  mat2(1, 1) = 6;

  mat1 *= 2;

  EXPECT_TRUE(mat2.EqMatrix(mat1));
}

TEST(S21MatrixTest, OperatorMultEqMatrix) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 3;
  mat2(0, 1) = 4;
  mat2(1, 0) = 5;
  mat2(1, 1) = 6;

  S21Matrix mat3(2, 2);
  mat3(0, 0) = 5;
  mat3(0, 1) = 6;
  mat3(1, 0) = 21;
  mat3(1, 1) = 26;

  mat1 *= mat2;

  EXPECT_TRUE(mat3.EqMatrix(mat1));
}

TEST(S21MatrixTest, OperatorDoubleEq) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 0;
  mat2(0, 1) = 1;
  mat2(1, 0) = 2;
  mat2(1, 1) = 3;

  EXPECT_TRUE(mat1 == mat2);
}

TEST(S21MatrixTest, OperatorEq_0) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 4;
  mat2(0, 1) = 5;
  mat2(1, 0) = 6;
  mat2(1, 1) = 7;

  mat1 = mat2;

  EXPECT_TRUE(mat1 == mat2);
}

TEST(S21MatrixTest, OperatorEq_1) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 0;
  mat2(0, 1) = 1;
  mat2(1, 0) = 2;
  mat2(1, 1) = 3;

  mat2 = mat1;

  EXPECT_TRUE(mat1 == mat2);
}

TEST(S21MatrixTest, OperatorMultMatrix) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 3;
  mat2(0, 1) = 4;
  mat2(1, 0) = 5;
  mat2(1, 1) = 6;

  S21Matrix mat3(2, 2);
  mat3(0, 0) = 5;
  mat3(0, 1) = 6;
  mat3(1, 0) = 21;
  mat3(1, 1) = 26;

  S21Matrix mat4 = mat1 * mat2;

  EXPECT_TRUE(mat3 == mat4);
}

TEST(S21MatrixTest, OperatorMultNumber) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 0;
  mat2(0, 1) = 2;
  mat2(1, 0) = 4;
  mat2(1, 1) = 6;

  S21Matrix mat3 = mat1 * 2;
  S21Matrix mat4 = 2 * mat1;

  EXPECT_TRUE(mat2 == mat3);
  EXPECT_TRUE(mat2 == mat4);
}

TEST(S21MatrixTest, OperatorPlus) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 0;
  mat2(0, 1) = 2;
  mat2(1, 0) = 4;
  mat2(1, 1) = 6;

  S21Matrix mat3(2, 2);
  mat3(0, 0) = 0;
  mat3(0, 1) = 3;
  mat3(1, 0) = 6;
  mat3(1, 1) = 9;

  S21Matrix mat4 = mat1 + mat2;

  EXPECT_TRUE(mat3 == mat4);
}

TEST(S21MatrixTest, OperatorMinus) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 0;
  mat2(0, 1) = 2;
  mat2(1, 0) = 4;
  mat2(1, 1) = 6;

  S21Matrix mat3(2, 2);
  mat3(0, 0) = 0;
  mat3(0, 1) = -1;
  mat3(1, 0) = -2;
  mat3(1, 1) = -3;

  S21Matrix mat4 = mat1 - mat2;

  EXPECT_TRUE(mat3 == mat4);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}