/* cqhvn */

#include<bits/stdc++.h>
using namespace std;


//Pt bac n: [2,1,1], n = 2 <=> 2x^2 + x + 1
class PT{
public:
    int n;
    double *a;

    PT(){
        n = 0;
        a = nullptr;
    }
    PT(int x){
        n = x;
        a = new double[n + 1];

        for(int i = n; i >= 0; i--) a[i] = 0;
    }

    PT(int x, double *y){
        n = x;
        a = new double[n + 1];
        for (int i = 0; i <= n; i++) a[i] = y[i];
    }

    friend istream& operator >> (istream &in, PT &p){
        in >> p.n;
        p.a = new double[p.n + 1];

        for(int i = p.n; i >= 0; i--){
            cout << "[" << i << "]: ";
            in >> p.a[i];
        }

        return in;
    }

    friend ostream& operator << (ostream &out, const PT &p){
        if(p.a == nullptr) return out;
        for(int i = p.n; i >= 0; i--){
            if(fabs(p.a[i]) > 1|| p.a[i] != 0) cout << p.a[i] << (i > 0 ? "x" : "");
            if(i > 1) cout << "^" << i;
            if(i > 0){
                if(p.a[i - 1] > 0) cout << "+";
            }
        }

        return out;
    }

    void operator = (const PT &b){
        this -> n = b.n;
        this -> a = new double[n + 1];

        for(int i = 0; i <= n; i++) this -> a[i] = b.a[i];

    }

    PT operator *(PT &b){
        PT r(n + b.n);
        for(int i = n; i >= 0; i--){
            for(int j = b.n; j >= 0; j--){
                r.a[i + j] += a[i] * b.a[j];
            }
        }

        return r;
    }

    PT operator + (const PT &b) {
        PT r(max(n, b.n));
        for (int i = 0; i <= r.n; i++) {
            double ai = (i <= n ? a[i] : 0);
            double bi = (i <= b.n ? b.a[i] : 0);
            r.a[i] = ai + bi;
        }
        return r;
    }

    PT operator + (double b) {
        this -> a[0] += b;
        return *this;
    }

    PT operator *(double c){
        PT r(n);

        for(int i = n; i >= 0; i--){
            r.a[i] = a[i] * c;
        }

        return r;
    }

    ~PT(){
        delete[] a;
    }
};



void Lagrange(double *X, double *Y, int n){
    PT L(n);

    for(int i = 0; i <= n; i++){
        PT p(0);
        p.a[0] = 1;
        cout << "P" << i << "(x) = ";
        for(int j = 0; j <= n; j++){
            if(i != j){
                double arr[2]; // (x - X[i]) -> he so x la 1
                arr[1] = 1; // set he so x la 1
                arr[0] = -X[j];
                PT q(1, arr);
                q = q * (1.0 / (X[i] - X[j]));
                p = p * q;
            }
        }

        cout << p << endl;
        L = L + p * Y[i];
        //Lx = P0(x) + P1(x) + ...
    }

    cout << endl << "L" << n << "(x) = " << L << endl;
}



void NEWTON(double *X, double *Y, int n){
    PT Nt(n);
    PT Nl(n);

    double **a = new double *[n + 1];

    a[0] = new double[n + 1];
    for (int i = 0; i <= n; i++)
        a[0][i] = Y[i];

    for(int i = 1; i <= n; i++){
        a[i] = new double[n - i + 1];
        for(int j = 0; j <= n - i; j++){
            a[i][j] = (a[i - 1][j + 1] - a[i - 1][j]) / (X[j + i] - X[j]);

            if(j == 0){ // TH tien (1)
                PT p(0);
                p.a[0] = 1;
                for(int k = 0; k < i; k++){
                    PT t(1);
                    t.a[1] = 1;
                    t.a[0] = - X[k];
                    p = p * t;
                }
                Nt = Nt + p * a[i][j];
            }

            if(j == n - i){ // TH lui (2)
                PT p(0);
                p.a[0] = 1;
                for(int k = n; k > n - i; k--){
                    PT t(1);
                    t.a[1] = 1;
                    t.a[0] = - X[k];
                    p = p * t;
                }
                Nl = Nl + p * a[i][j];
            }
        }

    }

    //Dung (1) hoac (2) ung voi tien hoc lui

    Nt = Nt + Y[0];
    Nl = Nl + Y[n];

    cout << endl << "Nt(x) = " << Nt << endl;
    cout << endl << "Nl(x) = " << Nl << endl;

    for (int i = 0; i <= n; i++) delete[] a[i];
    delete[] a;
}


int GiaiThua(int n){
    if(n == 0 || n == 1) return 1;
    else return n * GiaiThua(n - 1);
}

void NEWTON_CD(double *X, double *Y, int n){
    PT Nt(n);
    PT Nl(n);
    double h = X[1] - X[0];

    double **a = new double *[n + 1];

    a[0] = new double[n + 1];
    for (int i = 0; i <= n; i++)
        a[0][i] = Y[i];

    for(int i = 1; i <= n; i++){
        a[i] = new double[n - i];
        for(int j = 0; j <= n - i; j++){
            a[i][j] = (a[i - 1][j + 1] - a[i - 1][j]);
            if(j == 0){ // TH lui (1)
                PT p(0);
                p.a[0] = 1;
                for(int k = 0; k < i; k++){
                    PT t(1);
                    t.a[1] = 1;
                    t.a[0] = - X[k];
                    p = p * t * (1 / h);
                }
                Nt = Nt + p * (a[i][j] / GiaiThua(i));
            }

            if(j == n - i){ // TH lui (2)
                PT p(0);
                p.a[0] = 1;
                for(int k = n; k > n - i; k--){
                    PT t(1);
                    t.a[1] = 1;
                    t.a[0] = - X[k];
                    p = p * t * (1 / h);
                }
                Nl = Nl + p * (a[i][j] / GiaiThua(i));
            }
        }

    }

    //Dung (1) hoac (2) ung voi tien hoc lui

    Nt = Nt + Y[0];
    Nl = Nl + Y[n];

    cout << endl << "Nt(x) = " << Nt << endl;
    cout << endl << "Nl(x) = " << Nl << endl;

    for (int i = 0; i <= n; i++) delete[] a[i];
    delete[] a;
}

int main(){
    double X[] = {-1,0,1,2}; // Mang gia tri x
    double Y[] = {3,0,2,1}; // Mang gia tri y = f(x)

    Lagrange(X, Y, 3); // n = 2

    NEWTON(X, Y, 3); // Newton ko cach deu

    NEWTON_CD(X, Y, 3); // Newton cach deu
}
