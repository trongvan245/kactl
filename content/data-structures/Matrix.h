/**
 * Author: Ulf Lundstrom
 * Date: 2009-08-03
 * License: CC0
 * Source: My head
 * Description: Basic operations on square matrices.
 * Usage: Matrix<int, 3> A;
 *  A.d = {{{{1,2,3}}, {{4,5,6}}, {{7,8,9}}}};
 *  vector<int> vec = {1,2,3};
 *  vec = (A^N) * vec;
 * Status: tested
 */
#pragma once

template<class T, int N> struct Matrix {
	typedef Matrix M;
	array<array<T, N>, N> d{};
	M operator*(const M& m) const {
		M a;
		rep(i,0,N) rep(j,0,N)
			rep(k,0,N) a.d[i][j] += d[i][k]*m.d[k][j];
		return a;
	}
	vector<T> operator*(const vector<T>& vec) const {
		vector<T> ret(N);
		rep(i,0,N) rep(j,0,N) ret[i] += d[i][j] * vec[j];
		return ret;
	}
	M operator^(ll p) const {
		assert(p >= 0);
		M a, b(*this);
		rep(i,0,N) a.d[i][i] = 1;
		while (p) {
			if (p&1) a = a*b;
			b = b*b;
			p >>= 1;
		}
		return a;
	}
};



using type = int; // Kiểu dữ liệu các phần tử của ma trận

struct Matrix {
    vector <vector <type> > data;

    // Số lượng hàng của ma trận
    int row() const { return data.size(); }

    // Số lượng hàng của ma trận
    int col() const { return data[0].size(); }

    auto & operator [] (int i) { return data[i]; }

    const auto & operator[] (int i) const { return data[i]; }

    Matrix() = default;

    Matrix(int r, int c): data(r, vector <type> (c)) { }

    Matrix(const vector <vector <type> > &d): data(d) {

        // Kiểm tra các hàng có cùng size không và size có lớn hơn 0 hay không
        // Tuy nhiên không thực sự cần thiết, ta có thể bỏ các dòng  đi
         assert(d.size());
         int size = d[0].size();
         assert(size);
         for (auto x : d) assert(x.size() == size);
    }

    // In ra ma trận.
    friend ostream & operator << (ostream &out, const Matrix &d) {
        for (auto x : d.data) {
            for (auto y : x) out << y << ' ';
            out << '\n';
        }
        return out;
    }

    // Ma trận đơn  vị
    static Matrix identity(long long n) {
        Matrix a = Matrix(n, n);
        while (n--) a[n][n] = 1;
        return a;
    }

    // Nhân ma trận
    Matrix operator * (const Matrix &b) {
        Matrix a = *this;

        // Kiểm tra điều kiện nhân ma trận
        assert(a.col() == b.row());

        Matrix c(a.row(), b.col());
        for (int i = 0; i < a.row(); ++i)
            for (int j = 0; j < b.col(); ++j)
                for (int k = 0; k < a.col(); ++k)
                    c[i][j] += a[i][k] * b[k][j];
        return c;
    }

    // Lũy thừa ma trận
    Matrix pow(long long exp) {

        // Kiểm tra điều kiện lũy thừa ma trận (là ma trận vuông)
        assert(row() == col());

        Matrix base = *this, ans = identity(row());
        for (; exp > 0; exp >>= 1, base = base * base)
            if (exp & 1) ans = ans * base;
        return ans;
    }
};

int main(){
    Matrix a({
        {1, 2},
        {3, 4}
    });

    Matrix b({
        {0, 10, 100},
        {1,  1,  10}
    });

    cout << a * b << '\n';
    // 2 12 120
    // 4 34 340

    cout << a.pow(3) << '\n';
    // 37 54
    // 81 118

    b = a;
    cout << b << '\n';
    // 1 2
    // 3 4

    b = Matrix::identity(3);
    cout << b << '\n';
    // 1 0 0
    // 0 1 0
    // 0 0 1

    b = Matrix(2, 3);
    cout << b << '\n';
    // 0 0 0
    // 0 0 0

    Matrix c(3, 2);
    cout << c << '\n';
    // 0 0
    // 0 0
    // 0 0
}