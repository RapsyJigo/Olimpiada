#include <iostream>
#include <fstream>
#include <map>
using namespace std;

ifstream in ("changemin.in");
ofstream out ("changemin.out");
map<unsigned long long int, int> t;

void tester ()
{
    in.close();
    in.open("changemin.in");
    int c, n;
    unsigned long long int A[1000];
    in >> c >> n;
    for (int i = 1; i <= n; i++)
    {
        in >> A[i];
    }

    unsigned long long int cnt = 0;
    unsigned long long int score = 0;
    for (int i = 1; i <= n; i++)
    {
        long long int min = 0xffffffffffffffff;
        for (int j = i; j <=  n; j++)
        {
            if (A[j] < min)
            {
                t[A[j]]++;
                min = A[j];
                cnt = cnt + 1;
                score = score + cnt * A[j];
            }
        }
    }
}

int main ()
{
    tester();
    for (map<unsigned long long int, int>::const_iterator it = t.begin(); it != t.end(); it++)
    {
        out << it->first << ' ' << it->second << '\n';
    }
    in.close();
    in.open("changemin.in");
    int c, n;
    unsigned long long int a;
    in >> c >> n;

    unsigned long long int cnt = 0;
    unsigned long long int score = 0;

    unsigned long long int minime_gasite = 1;
    bool scazut = false;

    unsigned long long int mi;
    in >> mi;
    cnt += n;
    for (int i = 1; i < n; i++)
    {
        in >> a;
        if (a < mi)
        {
            mi = a;
            cnt += minime_gasite;
            minime_gasite++;
            scazut = true;
        }
        else
        {
            if (scazut)
            {
                if (a == mi)
                    minime_gasite++;
                else
                {
                    minime_gasite = 1;
                    scazut = false;
                    mi = a;
                }
            }
            else
            {
                minime_gasite++;
            }
        }
        out << a << ' ' << cnt << '\n';
    }

    if (c == 1)
    {
        out << cnt;
    }
    else
    {
        out << score;
    }
}