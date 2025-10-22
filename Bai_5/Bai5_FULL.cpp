#include <bits/stdc++.h>
using namespace std;

class MATRIX {
public:
    int m, n;
    double a[100][100];

    MATRIX() {
        m = n = 0;
    }

    MATRIX(int r, int c) {
        m = r;
        n = c;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                a[i][j] = 0;
    }

    MATRIX(int r, int c, bool I) {
        m = r;
        n = c;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if(I && i == j) a[i][j] = 1;
                else a[i][j] = 0;
    }

    friend istream &operator>>(istream &in, MATRIX &M) {
        for (int i = 0; i < M.m; i++) {
            for (int j = 0; j < M.n; j++) {
                cout << "a[" << i << "][" << j << "] = ";
                in >> M.a[i][j];
            }
        }
        return in;
    }

    friend ostream &operator<<(ostream &out, const MATRIX &M) {
        for (int i = 0; i < M.m; i++) {
            out << "[ ";
            for (int j = 0; j < M.n; j++) {
                out << setw(10) << M.a[i][j] << " ";
            }
            out << "]" << endl;
        }
        return out;
    }

    MATRIX operator*(const MATRIX &b) {
        MATRIX rs(m, b.n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < b.n; j++) {
                for (int k = 0; k < n; k++) {
                    rs.a[i][j] += a[i][k] * b.a[k][j];
                }
            }
        }
        return rs;
    }

    MATRIX operator*(double b) {
        MATRIX rs(m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                rs.a[i][j] = a[i][j] * b;
            }
        }
        return rs;
    }

    MATRIX operator+(const MATRIX &b) {
        MATRIX rs(m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                rs.a[i][j] = a[i][j] + b.a[i][j];
            }
        }
        return rs;
    }

    MATRIX operator-(const MATRIX &b) {
        MATRIX rs(m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                rs.a[i][j] = a[i][j] - b.a[i][j];
            }
        }
        return rs;
    }

    MATRIX operator-() {
        MATRIX rs(m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                rs.a[i][j] = -a[i][j];
            }
        }
        return rs;
    }

    friend double det_3_3(MATRIX M);
    friend double trace(MATRIX M);
    friend void FADDEEV_LEVERIER(MATRIX A);
};

double det_3_3(MATRIX M){
    if (M.m != 3 || M.n != 3) return 0;
    return M.a[0][0] * M.a[1][1] * M.a[2][2] + M.a[0][1] * M.a[1][2] * M.a[2][0] + M.a[1][0] * M.a[2][1] * M.a[0][2]
    - (M.a[0][2] * M.a[1][1] * M.a[2][0] + M.a[1][0] * M.a[0][1] * M.a[2][2] + M.a[2][1] * M.a[1][2] * M.a[0][0]);
}

double trace(MATRIX M){
    double rs = 0;
    if(M.m == M.n){
        for(int i = 0; i < M.m; i++) rs += M.a[i][i];
    }

    return rs;
}

void FADDEEV_LEVERIER(MATRIX A){
    cout << "\n\n -----FADDEEV_LEVERIER----";
    MATRIX I(A.n, A.n, true);
    MATRIX Yi = A;
    double Pi = 0;

    cout << endl << "Ki hieu lamda = k" << endl;
    cout << endl << "k^" << A.n;

    for(int i = 1; i <= A.n; i++){
        Pi = (1.0 / i) * trace(Yi);
        Yi = A * (Yi - I * Pi);
        cout << ((-Pi > 0) ? "+" : "") << -Pi;
        if (A.n - i > 0) cout << "k^" << (A.n - i);
    }

    cout << "\n----------------------\n";
}

void DANHILEPSKI(MATRIX A){
    cout << "\n\n -----DANHILEPSKI----";
    if(A.n != A.m) return;

    int k = A.n - 1;

    for(int i = 2; i <= A.n; i++){
        MATRIX _M(A.n, A.n, 1);
        MATRIX M(A.n, A.n, 1);
        for(int j = 0; j < A.n; j++){
            _M.a[A.n - i][j] = A.a[k][j];
            M.a[A.n - i][j] = (k - 1 == j ? 1 : -A.a[k][j]) / A.a[k][k - 1];
        }
        A = _M * A * M;
        k--;
    }

    cout << endl << "Ki hieu lamda = k" << endl;
    cout << endl << "k^" << A.n;

    for(int i = 0; i < A.n; i++){
        cout << ((-A.a[0][i] > 0) ? "+" : "") << -A.a[0][i];
        if (A.n - i - 1 > 0) cout << "k^" << (A.n - i - 1);
    }

    cout << "\n----------------------\n";
}


int main() {
    /* BO TEST
    2 1 0 1 3 1 0 1 2
    */

    MATRIX A(3, 3);

    cout << endl << "Ma tran A" << endl;
    cin >> A;

    FADDEEV_LEVERIER(A);
    DANHILEPSKI(A);
}
