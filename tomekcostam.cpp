/************************************************************
*program liczy przybli?enie sqrt(2)
*i pokazuje stosowanie funkcji
* *********************************************************/
#include<stdio.h>
#define LIMIT 100
int nl = 3, nm = 2;
int srednia (int a, int b, int c, int d)
/*zwraca 1 jesli srednia liczb a/b i c/d jest wieksza od sqrt(2)*/
{
    if ((d * a + b * c) * (d * a + b * c) > 8 * b * d * b * d)
        return 1;
    return 0;
}
void sprawdz (int a, int b, int c, int d)
{
    if ((a * a > 2 * b * b) && (c * c > 2 * d * d))
        if (d * a > b * c) {
            nl = c;
            nm = d;
        }
    return;
    if ((a * a < 2 * b * b) && (c * c < 2 * d * d))
        if (d * a < b * c) {
            nl = c;
            nm = d;
        }
    return;
    if (a * a > 2 * b * b)
        if (srednia (a, b, c, d) == 1) {
            nl = c;
            nm = d;
        }
    return;
    if (srednia (a, b, c, d) != 1) {
        nl = c;
        nm = d;
    }
}
int main (void)
{
    int l, m;
    for (m = 3; m < LIMIT; m++)
        for (l = m; l < 2 * m; l++)
            sprawdz (nl, nm, l, m);
    printf("najlepszym przybli?eniem pierwiastka jest liczba %d/%d\n",nl,nm);
    return 0;
}

