#include <iostream>
#include <vector>
using namespace std;

struct Matrix :vector<vector<int> >//使用标准容器vector做基类，需#include语句
{
	Matrix(int x = 0, int y = 0, int z = 0)//初始化，默认为0行0列空矩阵
	{
		assign(x, vector<int>(y, z));
	}
	int h_size()const//常量说明不可省，否则编译无法通过
	{
		return size();
	}
	int l_size()const
	{
		return empty() ? 0 : front().size();//列数要考虑空矩阵的情况
	}	
};

Matrix GenUnitMatrix(int n)
{
	Matrix m(n, n, 0);
	for (int i = 0; i < m.size(); i++)
	{
		for (int j = 0; j < m[i].size(); j++)
		{
			if (i == j)
			{
				m[i][j] = 1;
				break;
			}
		}
	}
	return m;
}

ostream& operator<<(ostream& out, const Matrix &m)
{
	for (int i = 0; i < m.size(); i++)
	{
		for (int j = 0; j < m[i].size(); j++)
		{
			out << m[i][j] << " ";
		}
		out << endl;
	}
	return out;
}

istream& operator >> (istream&in, Matrix& m)
{
	for (int i = 0; i < m.size(); i++)
	{
		for (int j = 0; j < m[i].size(); j++)
		{
			in >> m[i][j];
		}
	}
	return in;
}

Matrix operator*(const Matrix &m, const Matrix &n)//常量引用避免拷贝
{
	if (m.l_size() != n.h_size())return Matrix();//非法运算返回空矩阵
	Matrix ans(m.h_size(), n.l_size());
	for (int i = 0; i != ans.h_size(); ++i)
		for (int j = 0; j != ans.l_size(); ++j)
			for (int k = 0; k != m.l_size(); ++k)
				ans[i][j] += m[i][k] * n[k][j];
	return ans;
}

Matrix Pow(const Matrix &m, int n)
{
	Matrix ans = GenUnitMatrix(m.size());
	Matrix base = m;
	while (n)
	{
		if (n & 1)
		{
			ans = ans * base;
		}
		base = base * base;
		n = n >> 1;
	}
	return ans;
}

int main()
{
	Matrix m(2, 2, 1);
	Matrix t = Pow(m,2);
	Matrix t1 = Pow(m, 3);
	cout << m;
	cout << t;
	cout << t1;
	int tt;
	cin >> tt;
	cout << tt;
	return 0;
}