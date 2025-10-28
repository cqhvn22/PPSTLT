/* cqhvn */

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

    MATRIX operator*(MATRIX &b) {
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

    MATRIX operator+(MATRIX &b) {
        MATRIX rs(m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                rs.a[i][j] = a[i][j] + b.a[i][j];
            }
        }
        return rs;
    }

    MATRIX operator-(MATRIX &b) {
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
    friend double chuan(MATRIX M);
    friend void bienDoi(MATRIX &A, MATRIX &B);
};

double det_3_3(MATRIX M){
    if (M.m != 3 || M.n != 3) return 0;
    return M.a[0][0] * M.a[1][1] * M.a[2][2] + M.a[0][1] * M.a[1][2] * M.a[2][0] + M.a[1][0] * M.a[2][1] * M.a[0][2]
    - (M.a[0][2] * M.a[1][1] * M.a[2][0] + M.a[1][0] * M.a[0][1] * M.a[2][2] + M.a[2][1] * M.a[1][2] * M.a[0][0]);
}

double chuan(MATRIX M){
    double MAX = 0;
    for(int i = 0; i < M.m; i++){
        double r = 0;
        for(int j = 0; j < M.n; j++){
            r += fabs(M.a[i][j]);
        }
        if(r > MAX) MAX = r;
    }

    return MAX;
}

void bienDoi(MATRIX &A, MATRIX &B){
    for(int i = 0; i < A.m; i++){
        B.a[i][0] /= A.a[i][i];
        for(int j = 0; j < A.n; j++){
            if(i != j){
                A.a[i][j] /= -A.a[i][i];
            }
        }
    }
    for(int i = 0; i < A.m; i++){
        A.a[i][i] = 0;
    }
}

void LAP_DON(MATRIX &A, MATRIX &B, double e){
    MATRIX X1(3, 1), X0 = B;
    double delta;
    int i = 1;

    cout << left << setw(5) << "n" << setw(40) << "Xn" << "delta" << endl;
    cout << string(60, '-') << endl;

    do {
        X1 = A * X0 + B;
        delta = (chuan(A) / (1 - chuan(A))) * chuan(X1 - X0);
        cout << left << setw(5) << i++;

        cout << "[";
        for (int j = 0; j < 3; j++) {
            cout << setw(10) << X1.a[j][0];
            if (j < 2) cout << ",";
        }
        cout << " ]";

        cout << setw(10) << "" << delta << endl;

        X0 = X1;
    } while (delta > e);

    cout << X1;
}

void LAP_JACOBI(MATRIX &A, MATRIX &B, double e){
    MATRIX X1(3, 1), X0 = X1;
    double delta;
    int i = 0;

    bienDoi(A, B);

    cout << setw(5) << "k" << setw(10) << "x1(k)" << setw(10) << "x2(k)" << setw(10) << "x3(k)" << setw(20) << "||x(k)-x(k-1)||oo" << endl;
    cout << string(60, '-') << endl;
    cout << setw(5) << i++ << setw(10) << 0 << setw(10) << 0 << setw(10) << 0 << setw(20) << "" << endl;

    do {
        X1 = A * X0 + B;
        delta = chuan(X1 - X0);
        cout << setw(5) << i++ << setw(10) << X0.a[0][0] << setw(10) << X0.a[1][0] << setw(10) << X0.a[2][0] << setw(20) << delta << endl;
        X0 = X1;
    } while(delta > e);
}

void LAP_GAUSS_SEIDEL(MATRIX &A, MATRIX &B, double e){
    MATRIX X1(3, 1), X0 = X1;
    double delta;
    int i = 0;

    bienDoi(A, B);

    cout << setw(5) << "k" << setw(10) << "x1(k)" << setw(10) << "x2(k)" << setw(10) << "x3(k)" << setw(20) << "||x(k)-x(k-1)||oo" << endl;
    cout << string(60, '-') << endl;
    cout << setw(5) << i++ << setw(10) << 0 << setw(10) << 0 << setw(10) << 0 << setw(20) << "" << endl;

    do {
        for(int i = 0; i < X1.m; i++){
            double s = 0;
            for(int j = 0; j < X1.m; j++){
                if(i != j)s += X1.a[j][0] * A.a[i][j];
            }
            X1.a[i][0] = B.a[i][0] + s;
        }
        delta = chuan(X1 - X0);
        cout << setw(5) << i++ << setw(10) << X1.a[0][0] << setw(10) << X1.a[1][0] << setw(10) << X1.a[2][0] << setw(20) << delta << endl;
        X0 = X1;
    } while(delta > e);
}

int main() {
    /* BO TEST
    10 -2 -3
    -2 20 -5
    1 -3 10
    20 40 8
    */

    MATRIX A(3, 3), B(3, 1);
    double e = 0.01;

    cout << endl << "Ma tran A" << endl;
    cin >> A;
    cout << endl << "Ma tran he so B" << endl;
    cin >> B;

    //LAP_JACOBI(A, B, e);
    //LAP_DON(A, B, e);
    LAP_GAUSS_SEIDEL(A, B, e);
}
