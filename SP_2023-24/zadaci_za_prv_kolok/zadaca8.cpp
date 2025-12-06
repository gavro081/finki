#include <iostream>
using namespace std;
int main() {
    int n, x, broj,i2,x2,cifra;
    broj = 0;
    cin >> n >> x;
    for (int i = n-1; i > 0; i--) {
        bool p = true;
        i2 = i;
        while (i2 > 0) {
            cifra = i2 % 10;
            i2 /= 10;
            x2 = x;
            while (x2 > 0) {
                if (cifra == x2 % 10) {
                    p = false;
                    break;
                }
                x2 /= 10;
            }
        }
        if (p)
        {
            broj = i;
            break;
        }
    }
    cout << broj;
    return 0;
}
