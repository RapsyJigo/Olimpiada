#include <iostream>
#include <map>
#include <fstream>
#include <cstdlib>

using namespace std;

//Constanta primelor 47 de numere fibonaci
const unsigned int fibonaci[47] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887, 9227465, 
14930352, 24157817, 39088169, 63245986, 102334155, 165580141, 267914296, 433494437, 701408733, 1134903170, 1836311903, 2971215073};


//Functie folosita pentru a hardcoda toate numerele fibonaci mai mici decat 2^32
/*void generator ()
{
    unsigned long int x, y;
    int i = 0;
    x = y = 1;
    cout << "{";
    cout << x << ", "; i++;
    cout << y << ", "; i++;
    for (i; i < 47; i++)
    {
        x = x + y;
        cout << x << ", "; i++;
        y = x + y;
        cout << y << ", ";
    }
}*/


char indicefibo(unsigned long int x)
{
    int k;
    int inceput = 0, sfarsit = 46;

    while (inceput + 1 != sfarsit)
    {
        k = (inceput + sfarsit)/2;
        if (x == fibonaci[k])
            return k;
        if (x > fibonaci[k])
            inceput = k;
        else
            sfarsit = k;
    }
    if (x - fibonaci[inceput] == fibonaci[sfarsit] - x)
        return inceput * -1;
    return (x - fibonaci[inceput] > fibonaci[sfarsit] - x) ? (sfarsit * -1) : (inceput * -1);
}


int main ()
{
    ifstream in("fibosnek.in");
    ofstream out("fibosnek.out");

    int c, n, m;
    in >> c >> n >> m;
    
    //generator();
    
    if (c == 1)
    {
        unsigned long int x;
        int s = 0;
        for (int i = 0; i < n*m; i++)
        {
            in >> x;
            if (indicefibo(x) > 0)
                s = s + 1;
        }

        out << s;
    }
    else
    {
        long unsigned int x;
        char matrice[1500*1500] = {0};
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                in >> x;
                matrice[i + j*n] = indicefibo(x);
            }

        unsigned long int max = 0;
        unsigned long int l1 = 0;
        unsigned long int l2 = 0;
        unsigned long int l3 = 0;
        for (int i = 0; i < n*m; i++)
        {
            if (matrice[i] > 0)
            {
                if (l2 == 0)
                    l1+=fibonaci[matrice[i]];
                else
                    l3+=fibonaci[matrice[i]];
            }
            else
            {
                if (l3 == 0)
                    l2+=fibonaci[-1 * matrice[i]];
                else
                {
                    if (max < l1 + l2 + l3)
                        max = l1 + l2 + l3;
                    l1 = l3;
                    l2 = fibonaci[-1 * matrice[i]];
                    l3 = 0;
                }
            }
                
        }
        if (max < l1 + l2 + l3)
            max = l1 + l2 + l3;
        out << max;
    }
}