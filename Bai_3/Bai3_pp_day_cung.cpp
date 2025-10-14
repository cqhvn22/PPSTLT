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
    double a, b, e, x0, x1, delta;
    int i = 1;
    a = 0;
    b = 1;
    e = 0.01;

    if(f(a) * f(b) < 0 && df(a) * df(b) > 0){
        cout << "(" << a << ", " << b << ") la khoang CLN!" << endl;
    }
    else{
        cout << "(" << a << ", " << b << ") khong la khoang CLN!" << endl;
        return 0;
    }

    if(f(a) * d2f(a) >= 0 && f(a) * d2f(b) >= 0){
        x0 = a;
    }
    else x0 = b;

    cout << setw(5) << "n" << setw(15) << x0 << setw(15) << e << endl << endl;

    do{
        x1 = x0 - f(x0) / df(x0);
        delta = fabs(f(x0) / df(x0));
        x0 = x1;
        cout << setw(5) << i++ << setw(15) << x0 << setw(15) << delta << endl;
    } while(e < delta);

}
