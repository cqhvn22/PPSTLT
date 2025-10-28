/* cqhvn */


#include<bits/stdc++.h>

using namespace std;

int main(){
    int n;
    double c;

    cin >> n;

    double a[n + 1];

    for(int i = n; i >= 0; i--){
        cin >> a[i];
    }
//6 1 0 -5 2 0 -1 -1 -2
    cin >> c;
    for(int i = n; i >= 0; i--){
        cout << setw(7) << a[i];
    }
    cout << endl << "-----------------------------------------------------------" << endl;

    for(int k = 0; k < n; k++){

        cout << setw(7) << " ";
        for(int i = n; i >= k; i--){
            a[i] += a[i + 1] * c;
            cout << fixed << setprecision(2) << setw(7) << a[i + 1] * c;
        }


        cout << endl << "-----------------------------------------------------------" << endl;

        cout << setw(7) << "";
        for(int i = n; i >= k; i--){
            cout << fixed << setprecision(2) << setw(7) <<  a[i];
        }
        cout << endl;
    }

    for(int i = n; i > 0; i--){
        if(a[i]) cout << a[i] << "y^" << i << " ";
        if(a[i - 1] > 0) cout << "+ ";
    }
    cout << a[0];

}
