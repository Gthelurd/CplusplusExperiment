#include<iostream>
#define N 4
#include<string>
#include<cmath>
class Matrix_4x4
{
private:
	double matrix[4][4];
public:
	//默认构造函数，初始化矩阵为单位阵
	Matrix_4x4()
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (i == j)
				{
					matrix[i][j] = 1;
				}
				else
				{
					matrix[i][j] = 0;
				}
			}
		}
	};

	//带参数构造函数，用一个4x4的二维数组初始化
	Matrix_4x4(double Mat[N][N])
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				matrix[i][j] = Mat[i][j];
			}
		}
	};

	//拷贝构造函数
	Matrix_4x4(const Matrix_4x4& D)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				matrix[i][j] = D.matrix[i][j];
			}
		}
	};

	//重载 = 运算符，参数为矩阵对象
	Matrix_4x4 operator=(Matrix_4x4 A);

	//重载 = 运算符，参数为一个4x4的二维数组
	Matrix_4x4 operator=(double Mat[N][N]);

	// 重载算术运算符 + - * 
	Matrix_4x4 operator+(Matrix_4x4& A);
	Matrix_4x4 operator-(Matrix_4x4& A);
	Matrix_4x4 operator*(const Matrix_4x4& A);

	// 重载 ^ 运算符为矩阵的i次幂（如果i为负数，如何处理？）
	Matrix_4x4 operator^(int n);

	// 重载 [ ] 运算符，实现双下标方式访问矩阵元素（该功能已经实现，无需自己写）
	const double* operator[] (const int i) const { return matrix[i]; }
	double* operator[] (const int i) { return matrix[i]; }

	// 重载输入<< 和输出 >>
	friend std::ostream& operator<< (std::ostream& out, const Matrix_4x4 D);
	friend std::istream& operator>> (std::istream& in, Matrix_4x4 D);

	// 重载逆与转置
	Matrix_4x4 inverse(); //矩阵求逆，不改变当前矩阵值，返回逆矩阵
	Matrix_4x4 transpose(); //矩阵转置，不改变当前矩阵值，返回转置矩阵

	// 行列式和代数余子式
	double determinant();
	Matrix_4x4 adjugate();

	bool operator==(const Matrix_4x4& other) const
	{
		return false;
	}
};


std::ostream& operator<< (std::ostream& out, const Matrix_4x4 D) {
	for (int i = 0; i < N; i++)
	{
		out << std::endl;
		for (int j = 0; j < N; j++)
		{
			out << D.matrix[i][j] << ' ';
		}
	}
	return out;
}

std::istream& operator>>(std::istream& in, Matrix_4x4 D)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			in >> D.matrix[i][j];
		}
	}
	return in;
}

Matrix_4x4 Matrix_4x4::operator=(Matrix_4x4 A)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			matrix[i][j] = A.matrix[i][j];
		}
	}
	return *this;
}
Matrix_4x4 Matrix_4x4::operator=(double Mat[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			matrix[i][j] = Mat[i][j];
		}
	}
	return *this;
}

Matrix_4x4 Matrix_4x4::operator+(Matrix_4x4& A)
{
	Matrix_4x4 temp = *this;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			temp.matrix[i][j] = A.matrix[i][j] + temp.matrix[i][j];
		}
	}
	return temp;
}

Matrix_4x4 Matrix_4x4::operator-(Matrix_4x4& A)
{
	Matrix_4x4 temp = *this;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			temp.matrix[i][j] = temp.matrix[i][j] - A.matrix[i][j];
		}
	}
	return temp;
}
Matrix_4x4 Matrix_4x4::operator*(const Matrix_4x4& A)
{
	Matrix_4x4 temp = *this;
	Matrix_4x4 answer;
	if (temp == answer)
	{
		return answer;
	}
	else
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				answer[i][j] = 0;
				for (int k = 0; k < N; k++)
				{
					answer.matrix[i][j] += temp.matrix[i][k] * A.matrix[k][j];
				}
			}
		}
		return answer;
	}
}

Matrix_4x4 Matrix_4x4::operator^(int n)
{
	Matrix_4x4 temp = *this;
	Matrix_4x4 answer;
	if (n > 0)
	{
		answer = temp * temp;
		for (int i = 1; i < n; i++)
		{
			answer = answer * temp;
		}
		return answer;
	}
	else if (n == 0)
	{
		return  answer;
	}
	else
	{
		answer = temp.inverse() * temp.inverse();
		for (int i = -1; i > n; i--)
		{
			answer = answer * temp.inverse();
		}
		return answer;
	}
}

Matrix_4x4 Matrix_4x4::inverse()
{
	Matrix_4x4 temp = *this;
	double det = temp.determinant();
	temp = temp.adjugate().transpose();
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			temp.matrix[i][j] /= det;
		}
	}
	return temp;
}

Matrix_4x4 Matrix_4x4::transpose()
{
	Matrix_4x4 temp;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			temp.matrix[j][i] = this->matrix[i][j];
		}
	}
	return temp;
}

double Matrix_4x4::determinant()
{
	Matrix_4x4 temp = *this;
	double det = 0;
	Matrix_4x4 adj;
	adj.matrix[0][0] = temp.matrix[1][1] * (temp.matrix[2][2] * temp.matrix[3][3] - temp.matrix[2][3] * temp.matrix[3][2]) -
		temp.matrix[1][2] * (temp.matrix[2][1] * temp.matrix[3][3] - temp.matrix[2][3] * temp.matrix[3][1]) +
		temp.matrix[1][3] * (temp.matrix[2][1] * temp.matrix[3][2] - temp.matrix[2][2] * temp.matrix[3][1]);

	adj.matrix[0][1] = -1 * (temp.matrix[1][0] * (temp.matrix[2][2] * temp.matrix[3][3] - temp.matrix[2][3] * temp.matrix[3][2]) -
		temp.matrix[1][2] * (temp.matrix[2][0] * temp.matrix[3][3] - temp.matrix[2][3] * temp.matrix[3][0]) +
		temp.matrix[1][3] * (temp.matrix[2][0] * temp.matrix[3][2] - temp.matrix[2][2] * temp.matrix[3][0]));
	adj.matrix[0][2] = temp.matrix[1][0] * (temp.matrix[2][1] * temp.matrix[3][3] - temp.matrix[2][3] * temp.matrix[3][1]) -
		temp.matrix[1][1] * (temp.matrix[2][0] * temp.matrix[3][3] - temp.matrix[2][3] * temp.matrix[3][0]) +
		temp.matrix[1][3] * (temp.matrix[2][0] * temp.matrix[3][1] - temp.matrix[2][1] * temp.matrix[3][0]);

	adj.matrix[0][3] = -1 * (temp.matrix[1][0] * (temp.matrix[2][1] * temp.matrix[3][2] - temp.matrix[2][2] * temp.matrix[3][1]) -
		temp.matrix[1][1] * (temp.matrix[2][0] * temp.matrix[3][2] - temp.matrix[2][2] * temp.matrix[3][0]) +
		temp.matrix[1][2] * (temp.matrix[2][0] * temp.matrix[3][1] - temp.matrix[2][1] * temp.matrix[3][0]));

	for (int i = 0; i < N; i++)
	{
		det += adj.matrix[0][i] * temp.matrix[0][i];
	}
	return det;
}

Matrix_4x4 Matrix_4x4::adjugate()
{
	Matrix_4x4 adj;
	Matrix_4x4 temp = *this;

	adj.matrix[0][0] = temp.matrix[1][1] * (temp.matrix[2][2] * temp.matrix[3][3] - temp.matrix[2][3] * temp.matrix[3][2]) -
		temp.matrix[1][2] * (temp.matrix[2][1] * temp.matrix[3][3] - temp.matrix[2][3] * temp.matrix[3][1]) +
		temp.matrix[1][3] * (temp.matrix[2][1] * temp.matrix[3][2] - temp.matrix[2][2] * temp.matrix[3][1]);

	adj.matrix[0][1] = -1 * (temp.matrix[1][0] * (temp.matrix[2][2] * temp.matrix[3][3] - temp.matrix[2][3] * temp.matrix[3][2]) -
		temp.matrix[1][2] * (temp.matrix[2][0] * temp.matrix[3][3] - temp.matrix[2][3] * temp.matrix[3][0]) +
		temp.matrix[1][3] * (temp.matrix[2][0] * temp.matrix[3][2] - temp.matrix[2][2] * temp.matrix[3][0]));
	adj.matrix[0][2] = temp.matrix[1][0] * (temp.matrix[2][1] * temp.matrix[3][3] - temp.matrix[2][3] * temp.matrix[3][1]) -
		temp.matrix[1][1] * (temp.matrix[2][0] * temp.matrix[3][3] - temp.matrix[2][3] * temp.matrix[3][0]) +
		temp.matrix[1][3] * (temp.matrix[2][0] * temp.matrix[3][1] - temp.matrix[2][1] * temp.matrix[3][0]);

	adj.matrix[0][3] = -1 * (temp.matrix[1][0] * (temp.matrix[2][1] * temp.matrix[3][2] - temp.matrix[2][2] * temp.matrix[3][1]) -
		temp.matrix[1][1] * (temp.matrix[2][0] * temp.matrix[3][2] - temp.matrix[2][2] * temp.matrix[3][0]) +
		temp.matrix[1][2] * (temp.matrix[2][0] * temp.matrix[3][1] - temp.matrix[2][1] * temp.matrix[3][0]));

	adj.matrix[1][0] = -1 * (temp.matrix[0][1] * (temp.matrix[2][2] * temp.matrix[3][3] - temp.matrix[2][3] * temp.matrix[3][2]) -
		temp.matrix[0][2] * (temp.matrix[2][1] * temp.matrix[3][3] - temp.matrix[2][3] * temp.matrix[3][1]) +
		temp.matrix[0][3] * (temp.matrix[2][1] * temp.matrix[3][2] - temp.matrix[2][2] * temp.matrix[3][1]));

	adj.matrix[1][1] = temp.matrix[0][0] * (temp.matrix[2][2] * temp.matrix[3][3] - temp.matrix[2][3] * temp.matrix[3][2]) -
		temp.matrix[0][2] * (temp.matrix[2][0] * temp.matrix[3][3] - temp.matrix[2][3] * temp.matrix[3][0]) +
		temp.matrix[0][3] * (temp.matrix[2][0] * temp.matrix[3][2] - temp.matrix[2][2] * temp.matrix[3][0]);

	adj.matrix[1][2] = -1 * (temp.matrix[0][0] * (temp.matrix[2][1] * temp.matrix[3][3] - temp.matrix[2][3] * temp.matrix[3][1]) -
		temp.matrix[0][1] * (temp.matrix[2][0] * temp.matrix[3][3] - temp.matrix[2][3] * temp.matrix[3][0]) +
		temp.matrix[0][3] * (temp.matrix[2][0] * temp.matrix[3][1] - temp.matrix[2][1] * temp.matrix[3][0]));

	adj.matrix[1][3] = temp.matrix[0][0] * (temp.matrix[2][1] * temp.matrix[3][2] - temp.matrix[2][2] * temp.matrix[3][1]) -
		temp.matrix[0][1] * (temp.matrix[2][0] * temp.matrix[3][2] - temp.matrix[2][2] * temp.matrix[3][0]) +
		temp.matrix[0][2] * (temp.matrix[2][0] * temp.matrix[3][1] - temp.matrix[2][1] * temp.matrix[3][0]);

	adj.matrix[2][0] = temp.matrix[0][1] * (temp.matrix[1][2] * temp.matrix[3][3] - temp.matrix[1][3] * temp.matrix[3][2]) -
		temp.matrix[0][2] * (temp.matrix[1][1] * temp.matrix[3][3] - temp.matrix[1][3] * temp.matrix[3][1]) +
		temp.matrix[0][3] * (temp.matrix[1][1] * temp.matrix[3][2] - temp.matrix[1][2] * temp.matrix[3][1]);

	adj.matrix[2][1] = -1 * (temp.matrix[0][0] * (temp.matrix[1][2] * temp.matrix[3][3] - temp.matrix[1][3] * temp.matrix[3][2]) -
		temp.matrix[0][2] * (temp.matrix[1][0] * temp.matrix[3][3] - temp.matrix[1][3] * temp.matrix[3][0]) +
		temp.matrix[0][3] * (temp.matrix[1][0] * temp.matrix[3][2] - temp.matrix[1][2] * temp.matrix[3][0]));

	adj.matrix[2][2] = temp.matrix[0][0] * (temp.matrix[1][1] * temp.matrix[3][3] - temp.matrix[1][3] * temp.matrix[3][1]) -
		temp.matrix[0][1] * (temp.matrix[1][0] * temp.matrix[3][3] - temp.matrix[1][3] * temp.matrix[3][0]) +
		temp.matrix[0][3] * (temp.matrix[1][0] * temp.matrix[3][1] - temp.matrix[1][1] * temp.matrix[3][0]);

	adj.matrix[2][3] = -1 * (temp.matrix[0][0] * (temp.matrix[1][1] * temp.matrix[3][2] - temp.matrix[1][2] * temp.matrix[3][1]) -
		temp.matrix[0][1] * (temp.matrix[1][0] * temp.matrix[3][2] - temp.matrix[1][2] * temp.matrix[3][0]) +
		temp.matrix[0][2] * (temp.matrix[1][0] * temp.matrix[3][1] - temp.matrix[1][1] * temp.matrix[3][0]));

	adj.matrix[3][0] = -1 * (temp.matrix[0][1] * (temp.matrix[1][2] * temp.matrix[2][3] - temp.matrix[1][3] * temp.matrix[2][2]) -
		temp.matrix[0][2] * (temp.matrix[1][1] * temp.matrix[2][3] - temp.matrix[1][3] * temp.matrix[2][1]) +
		temp.matrix[0][3] * (temp.matrix[1][1] * temp.matrix[2][2] - temp.matrix[1][2] * temp.matrix[2][1]));

	adj.matrix[3][1] = temp.matrix[0][0] * (temp.matrix[1][2] * temp.matrix[2][3] - temp.matrix[1][3] * temp.matrix[2][2]) -
		temp.matrix[0][2] * (temp.matrix[1][0] * temp.matrix[2][3] - temp.matrix[1][3] * temp.matrix[2][0]) +
		temp.matrix[0][3] * (temp.matrix[1][0] * temp.matrix[2][2] - temp.matrix[1][2] * temp.matrix[2][0]);

	adj.matrix[3][2] = -1 * (temp.matrix[0][0] * (temp.matrix[1][1] * temp.matrix[2][3] - temp.matrix[1][3] * temp.matrix[2][1]) -
		temp.matrix[0][1] * (temp.matrix[1][0] * temp.matrix[2][3] - temp.matrix[1][3] * temp.matrix[2][0]) +
		temp.matrix[0][3] * (temp.matrix[1][0] * temp.matrix[2][1] - temp.matrix[1][1] * temp.matrix[2][0]));

	adj.matrix[3][3] = temp.matrix[0][0] * (temp.matrix[1][1] * temp.matrix[2][2] - temp.matrix[1][2] * temp.matrix[2][1]) -
		temp.matrix[0][1] * (temp.matrix[1][0] * temp.matrix[2][2] - temp.matrix[1][2] * temp.matrix[2][0]) +
		temp.matrix[0][2] * (temp.matrix[1][0] * temp.matrix[2][1] - temp.matrix[1][1] * temp.matrix[2][0]);

	return adj;
}

int main(void)
{
	double m[4][4] = { {1,2,3,4},{8,6,8,9},{4,10,-4,12},{-13,14,45,28} };
	double mat[4][4] = { {1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16} };
	Matrix_4x4 a;
	Matrix_4x4 b(a);
	Matrix_4x4 c(m);
	Matrix_4x4 d;
	Matrix_4x4 e = m;
	Matrix_4x4 Mat = m;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			d[i][j] = m[i][j];
		}
	}

	//输入输出，下标重载完成。
	std::cout << "a: " << a << std::endl;
	std::cout << "b(a): " << b << std::endl;
	std::cout << "c(m): " << c << std::endl;
	std::cout << "d: " << d << std::endl;
	std::cout << "e=(double**)m: " << e << std::endl;

	//运算符重载完成。
	d = a + c;
	std::cout << "d=a+c: " << d << std::endl;
	d = d - a;
	std::cout << "d=d-a: " << d << std::endl;
	e = c * c;
	std::cout << "e=c*c: " << e << std::endl;
	d = a ^ 3;
	std::cout << "d=a^3: " << d << std::endl;
	
	//转置和求逆重载完成。
	d = d * d.inverse();
	std::cout << "d=d*d.inverse(): " << d << std::endl;
	d = c.transpose();
	std::cout << "d=c.transpose(): " << d << std::endl;
	Mat.determinant();
	std::cout << "Mat.determinant(): " << std::endl << Mat.determinant() << std::endl;
	Mat.adjugate().transpose();
	std::cout << "Mat.adjugate(): " << Mat.adjugate().transpose() << std::endl;
	/*
	使用python测试代码:
	* import numpy as np
	*
	* m = np.array([[1, 2, 3, 4],
	*               [8, 6, 8, 9],
	*               [4, 10, -4, 12],
	*               [-13, 14, 45, 28]])
	* 
	* adjugate_matrix = np.linalg.inv(m) * np.linalg.det(m)
	* determinant = np.linalg.det(m)
	* print("Adjugate matrix:\n", adjugate_matrix)
	* print("Determinant of the matrix:", determinant)
	* 
	输出结果:
	* Adjugate matrix:
	*  [[ -254.  -384.   144.    98.]
	*  [ 6208.  -944.  -652.  -304.]
	*  [  962.  -320.   120.   -86.]
	*  [-4768.   808.   200.   192.]]
	* Determinant of the matrix: -4023.9999999999977
	*/
	system("pause");
	return 0;
}


/*
1. Test case for default constructor:
   Matrix_4x4 a;
   // Verify that matrix 'a' is initialized as an identity matrix.

2. Test case for parameterized constructor:
   double mat[4][4] = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16} };
   Matrix_4x4 b(mat);
   // Verify that matrix 'b' is initialized with the provided values.

3. Test case for copy constructor:
   Matrix_4x4 c(b);
   // Verify that matrix 'c' is a copy of matrix 'b'.

4. Test case for assignment operator with another matrix:
   Matrix_4x4 d = c;
   // Verify that matrix 'd' is assigned the values of matrix 'c'.

5. Test case for assignment operator with a 2D array:
   double mat2[4][4] = { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} };
   Matrix_4x4 e;
   e = mat2;
   // Verify that matrix 'e' is assigned the values of the provided 2D array.

6. Test case for addition operator:
   Matrix_4x4 f = c + d;
   // Verify that matrix 'f' contains the element-wise addition of matrices 'c' and 'd'.

7. Test case for subtraction operator:
   Matrix_4x4 g = f - d;
   // Verify that matrix 'g' contains the element-wise subtraction of matrix 'd' from matrix 'f'.

8. Test case for multiplication operator:
   Matrix_4x4 h = c * d;
   // Verify that matrix 'h' contains the result of matrix multiplication between matrices 'c' and 'd'.

9. Test case for exponentiation operator:
   Matrix_4x4 i = c ^ 3;
   // Verify that matrix 'i' contains the result of matrix 'c' raised to the power of 3.

10. Test case for matrix inverse:
	Matrix_4x4 j = c.inverse();
	// Verify that matrix 'j' contains the inverse of matrix 'c'.

11. Test case for matrix transpose:
	Matrix_4x4 k = c.transpose();
	// Verify that matrix 'k' contains the transpose of matrix 'c'.

12. Test case for determinant calculation:
	double det = c.determinant();
	// Verify that 'det' contains the determinant of matrix 'c'.
*/