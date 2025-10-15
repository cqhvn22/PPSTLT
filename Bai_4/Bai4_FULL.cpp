#include<bits/stdc++.h>
using namespace std;

class MATRIX{
public:
    int m, n;
    double a[100][100];

    MATRIX(int r, int c){
        m  = r;
        n = c;
        for(int i = 0; i < m; i++)
            for(int j  = 0; j < n; j++)
                a[i][j] = 0;
    }

    friend istream &operator >>(istream &in, MATRIX &M){
        for(int i = 0; i < M.m; i++){
            for(int j = 0; j < M.n; j++){
                cout << "a[" << i <<"][" << j << "] = ";
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

    MATRIX operator *(MATRIX &b){
        MATRIX rs(m, b.n);

        for(int i = 0; i < m; i++){
            for(int j = 0; j < b.n; j++){
                for(int k = 0; k < n; k++){
                    rs.a[i][j] += a[i][k] * b.a[k][j];
                }
            }
        }

        return rs;
    }

    MATRIX operator +(MATRIX &b){
        MATRIX rs(m, n);

        for(int i = 0; i < m; i++){
            for(int j = 0; j < b.n; j++){
                rs.a[i][j] = a[i][j] + b.a[i][j];
            }
        }

        return rs;
    }

    MATRIX operator -(MATRIX &b){
        MATRIX rs(m, n);

        for(int i = 0; i < m; i++){
            for(int j = 0; j < b.n; j++){
                rs.a[i][j] = a[i][j] - b.a[i][j];
            }
        }

        return rs;
    }


    friend double det_3_3(MATRIX M);
    friend double chuan(MATRIX M);
    friend void bienDoi(MATRIX &A, MATRIX &B);
};

double det_3_3(MATRIX M){
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

int main() {
    /* BO TEST
    10 -2 -3
    -2 20 -5
    1 -3 10
    20 40 8
    */

    MATRIX A(3, 3), B(3, 1), X1(3, 1);
    double delta, e = 0.01;
    int i = 1;
    cout << endl << "Ma tran A" << endl;
    cin >> A;
    cout << endl << "Ma tran he so B" << endl;
    cin >> B;

    bienDoi(A, B);
    MATRIX X0 = B;

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
