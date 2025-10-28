/* cqhvn */

#include<bits/stdc++.h>
using namespace std;


//Pt bac n: [2,1,1], n = 2 <=> 2x^2 + x + 1
class PT{
public:
    int n;
    double *a;
    bool active = false;

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
        active = true;
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
        cout << "P" << i << "(x) = ";
        for(int j = 0; j <= n; j++){
            if(i != j){
                double arr[2]; // (x - X[i]) -> he so x la 1
                arr[1] = 1; // set he so x la 1
                arr[0] = -X[j];
                PT q(1, arr);
                q = q * (1.0 / (X[i] - X[j]));
                if(!p.active) {
                    p = q;
                    p.active = true;
                }
                else {
                    p = p * q;
                }
            }
        }

        cout << p << endl;
        L = L + p * Y[i];
        //Lx = P0(x) + P1(x) + ...
    }

    cout << endl << "L" << n << "(x) = " << L << endl;
}

int main(){
    double X[] = {-1,0,1}; // Mang gia tri x
    double Y[] = {0.5,1,2}; // Mang gia tri y = f(x)

    Lagrange(X, Y, 2); // n = 2

}
