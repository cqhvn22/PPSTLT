/* cqhvn */

#include<bits/stdc++.h>
using namespace std;

double f(double x){
    return 2 * x * x + x - 3;
}

double df(double x){
    return 4 * x + 1;
}

int main(){
    double a, b, e, x0, x1, delta;
    int i = 1;
    a = 0.5;
    b = 1.2;
    e = 0.001;

    if(f(a) * f(b) < 0 && df(a) * df(b) > 0){
        cout << "(" << a << ", " << b << ") la khoang CLN!" << endl;
    }
    else{
        cout << "(" << a << ", " << b << ") khong la khoang CLN!" << endl;
        return 0;
    }

    double M = max(fabs(df(a)), fabs(df(b)));

    if(df(a) >= 0 && df(b) >= 0){
        M = - M;
    }

    double q = max(fabs(1 + df(a) / M), fabs(1 + df(b) / M));

    if(q < 1){
        cout << "q < 1 -> Thoa man dieu kien hoi tu" << endl;
    }
    else{
        cout << "q khong thoa man dk hoi tu" << endl;
        return 0;
    }

    x0 = (a + b) / 2;

    cout << left << setw(6) << "x0" << setw(10) << x0 << setw(30) << "(1/(1 - q)) x (xn - xn-1)" << setw(10) << e << endl;

    do{
        x1 = x0 + f(x0) / M;
        delta = (1/(1 - q)) * (x1 - x0);
        x0 = x1;
        cout << left << "x" << setw(5) << i++ << setw(10) << x1 << setw(30) << delta << setw(10) << (delta > e ? "FALSE" : "TRUE") << endl;
    } while(delta > e);

    cout << "Vay nghiem la x = " << x0 << " +- " << delta << endl;
}
