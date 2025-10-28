/* cqhvn */

#include<bits/stdc++.h>
using namespace std;

double f(double x){
    return 5 * x * x * x - 20 * x + 3;
}

double df(double x){
    return 15 * x * x - 20;
}

double d2f(double x){
    return 30 * x;
}

int main(){
    double a, b, e, x0, x1, delta, d;
    int i = 1;
    a = 0;
    b = 1;
    e = 0.0001;

    if(d2f(a) * f(a) >= 0 && d2f(b) * f(b) >= 0){
        d = a;
        x0 = b;
    }
    else{
        d = b;
        x0 = a;
    }

    cout << left << setw(5) << "n" << setw(12) << "xn" << setw(20) << "dxn = |f(xn) / f'(xn)|" << endl;
    cout << left << setw(5) << "0" << setw(12) << x0 << setw(20) << "" << endl;

    do{
        x1 = x0 - (f(x0) * (x0 - d)) / (f(x0) - f(d));
        delta = fabs(f(x1) / df(x1));
        x0 = x1;
        cout << left << setw(5) << i++ << setw(12) << x0 << setw(20) << delta << endl;

    } while(delta > e);

}
