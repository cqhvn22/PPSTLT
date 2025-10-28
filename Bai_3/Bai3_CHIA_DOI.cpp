/* cqhvn */

//Giai tong quat

#include<bits/stdc++.h>
using namespace std;

double f(double *c, int n, double x){
    if(n == 0) return c[0];
    else return c[n] * pow(x, n) + f(c, n - 1, x);
}

double df(double *c, int n, double x){
    if(n == 1) return c[1];
    else if(n > 1) return c[n] * n * pow(x, n - 1) + df(c, n - 1, x);
}

int main(){
    int n;
    double a, b, m, e, d, x;

    cout << "Bac cao nhat cua pt = ";
    cin >> n;

    double *c = new double[n + 1];

    for(int i = n; i >= 0; i--){
        cout << "He so cua x^" << i << " = ";
        cin >> c[i];
    }

    cout << "Nhap a b : ";
    cin >> a >> b;
    cout << "Sai so = ";
    cin >> e;

    m = (a + b) / 2;
    d = fabs(a - b) / 2;
    int i = 0;

    cout << endl;
    cout << "f(" << a << ") = " << f(c, n, a) << endl;
    cout << "f(" << b << ") = " << f(c, n, b) << endl;
    if(f(c, n, a) * f(c, n, b) < 0) cout << "=> f(a) * f(b) < 0" << endl << endl;
    else{
        cout << "(a, b) khong la khoang phan li nghiem";
        delete[] c;
        return 0;
    }

    cout << "f'("<< a << ") = " << df(c, n, a) << endl;
    cout << "f'(" << b << ") = " << df(c, n, b) << endl;
    if(df(c, n, a) * df(c, n, b) > 0) cout << "=> f'(a) * f'(b) > 0" << endl;
    else{
        cout << "(a, b) khong la khoang phan li nghiem";
        delete[] c;
        return 0;
    }

    cout << "=> (a, b) la khoang phan li nghiem" << endl;


    cout << endl << "n" << setw(12) << "an" << setw(12) << "bn" << setw(12) << "m" << setw(12) << "f(m)" << setw(12) << "|bn - an|/2" << endl << endl;

    while(d > e){
        cout << fixed << i++ << setw(12) << setprecision(6) << a << setw(12) << b << setw(12) << m << setw(12) << f(c, n, m) << setw(12) << d << endl;

        if(f(c, n, m) == 0) break;
        if(f(c, n, m) * f(c, n, a) < 0) b = m;
        else a = m;

        d = fabs(a - b) / 2;
        m = (a + b) / 2;
    }

    cout << fixed << i++ << setw(12) << setprecision(6) << a << setw(12) << b << setw(12) << m << setw(12) << " " << setw(12) << d << endl;

    cout << endl << "=> Nghiem gan dung la: " << m << " +- " << d;

    delete[] c;
}
