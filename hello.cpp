// #include <iostream>
// #include <time.h>
// using namespace std;
// int main() {
//     cout << "hello";
//     return 0;
// }
// #include <stdio.h>
// #include <conio.h>
// int main() {
//     printf("hello");
//     getch();
//     return 0;
// }
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

LARGE_INTEGER ft;
void usleep(__int64 usec)
{
    HANDLE timer;

    ft.QuadPart = -(10 * usec); // Convert to 100 nanosecond interval, negative value indicates relative time

    timer = CreateWaitableTimer(NULL, TRUE, NULL);
    SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
    WaitForSingleObject(timer, INFINITE);
    CloseHandle(timer);
}
#define R(mul,shift,x,y) \
  _=x; \
  x -= mul*y>>shift; \
  y += mul*_>>shift; \
  _ = 3145728-x*x-y*y>>11; \
  x = x*_>>10; \
  y = y*_>>10;

int8_t b[1760], z[1760];

int main() {
    int sA = 1024, cA = 0, sB = 1024, cB = 0, _;
    for (;;) {
        memset(b, 32, 1760);  // text buffer
        memset(z, 127, 1760);   // z buffer
        int sj = 0, cj = 1024;
        for (int j = 0; j < 90; j++) {
            int si = 0, ci = 1024;  // sine and cosine of angle i
            for (int i = 0; i < 324; i++) {
                int R1 = 1, R2 = 2048, K2 = 5120 * 1024;

                int x0 = R1 * cj + R2,
                    x1 = ci * x0 >> 10,
                    x2 = cA * sj >> 10,
                    x3 = si * x0 >> 10,
                    x4 = R1 * x2 - (sA * x3 >> 10),
                    x5 = sA * sj >> 10,
                    x6 = K2 + R1 * 1024 * x5 + cA * x3,
                    x7 = cj * si >> 10,
                    x = 40 + 30 * (cB * x1 - sB * x4) / x6,
                    y = 12 + 15 * (cB * x4 + sB * x1) / x6,
                    N = (-cA * x7 - cB * ((-sA * x7 >> 10) + x2) - ci * (cj * sB >> 10) >> 10) - x5 >> 7;

                int o = x + 80 * y;
                int8_t zz = (x6 - K2) >> 15;
                if (22 > y && y > 0 && x > 0 && 80 > x && zz < z[o]) {
                    z[o] = zz;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
                R(5, 8, ci, si)  // rotate i
            }
            R(9, 7, cj, sj)  // rotate j
        }
        for (int k = 0; 1761 > k; k++)
            putchar(k % 80 ? b[k] : 10);
        R(5, 7, cA, sA);
        R(5, 8, cB, sB);
        usleep(15000);
        printf("\x1b[23A");
    }
}

/*
Ki???u d??? li???u trong l???p tr??nh C
*** Ph??p chia:
- Chia h???t (/) v?? chia l???y ph???n d?? (%)
*** Chia h???t:
- result = a/b = s??? nguy??n (a&b khai b??o ki???u s??? nguy??n, result khai b??o ki???u d??? li???u s??? nguy??n ho???c s??? th???c)
- result = a/b = s??? th???c (a v?? b c?? m???t bi???n khai b??o ki???u s??? th???c)
- Ph??p bi???n ?????i ki???u s??? nguy??n th??nh ki???u s??? th???c: (a v?? b khai b??o ki???u s??? nguy??n)
float thuong = (float)a / b;
float thuong = a / (float)b;
float thuong = a * 1.0 / b;
float thuong = a / b * 1.0;

float quotient = (float)a / b;
float quotient = a / (float)b;
float quotient = a * 1.0 / b;
float quotient = a / b * 1.0;
float quotient = a / b * 1.0;

*** Chia l???y ph???n d?? (%): 
- S??? d???ng ?????i v???i bi???n khai b??o ki???u s??? nguy??n.
- Kh??ng s??? d???ng ?????i c??c bi???n khai b??o ki???u s??? th???c.
*/