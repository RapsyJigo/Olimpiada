#include <iostream>
#include <fstream>

/*
Pentru rezolvarea acestei probleme se va folosi un vector de numere prime pentru a determina instant daca un numar este sau nu prim.

Pentru cerinta 1 se va folosi un vector de frecventa, se creaza si afiseaza.
Pentru cerinta 2 se aplica countsort cu specificatile de afisare necesare.
*/

using namespace std;
//Functia de genrare a numerelor prime intre 10 si 99
/*
void generator ()
{
    for (int i = 2; i < 100; i++)
    {
        bool prim = true;
        for (int j = 2; j < i; j++)
        {
            if (i % j == 0)
                {prim = false; break;}
        }
        if (prim)
            cout << "prim[" << i << "]=true;\n"; 
        
    }
}
*/
int main ()
{
    ifstream in ("cufere.in");
    ofstream out ("cufere.out");

    int c, n;
    in >> c >> n;

    //generator();
    bool prim[100] = {0}; //Toate numerele prime de  la 10 la 99 hardcodade pentru viteza
    prim[11]=true;
    prim[13]=true;
    prim[17]=true;
    prim[19]=true;
    prim[23]=true;
    prim[29]=true;
    prim[31]=true;
    prim[37]=true;
    prim[41]=true;
    prim[43]=true;
    prim[47]=true;
    prim[53]=true;
    prim[59]=true;
    prim[61]=true;
    prim[67]=true;
    prim[71]=true;
    prim[73]=true;
    prim[79]=true;
    prim[83]=true;
    prim[89]=true;
    prim[97]=true;

    int cantitate[100] = {0}; //Vector de frecventa pentru cantitatea de fiecare item
    int x;

    //Citim toate valorile din fisier si le adaugam direct in vectorul de frecventa
    for (int i = 0; i < n*27; i++)
    {
        in >> x;
        cantitate[x%100] += x/100; //Decodificate si adaugate vectorului de frecventa
    }


    if (c == 1)
    {
        //Afisaera vectorului de frecventa
        for (int i = 10; i < 100; i++)
        {
            if (cantitate[i]) //Verificam sa nu fie nul
                out << i << ' ' << cantitate[i] << '\n';
        }
    }
    else
    {
        int plasate = 0; //Contor pentru a urmari finalul de rand
        int stack; //Variabila ajutatoare pentru a determina daca este stack de 16 sau 64
        
        //Se parcurge vectorul de frecventa si se afiseaza toate numerele in ordinea aparitiei lor
        //Daca se depaseste stackul se va afisa stackul si se scade din cantitate
        for (int i = 10; i < 100; i++)
        {
            if (cantitate[i]) //Sa nu fie nul
            {
                stack = prim[i] ? (16) : (64); //Daca este prim stackul este 16 altfel 64

                //Cattim depasim stackul
                while (cantitate[i] > stack)
                {
                    out << stack << i << ' '; plasate++; //Se afiseaza recodificat un stack si incrementm plasate
                    if (!(plasate % 9)) out << '\n'; //Daca am plasat un multiplu de 9 randul este plin

                    cantitate[i] -= stack; //Se scade stackul din cantitate
                }

                //Aceasi regula de afisare ca mai sus
                out << cantitate[i] << i << ' '; plasate++;
                if (!(plasate % 9)) out << '\n';
            }
        }

        //In finl se plaseaz 0-uri pana cnd au ramaas locuri in cufere
        for (++plasate; plasate <= n*27; plasate++)
        {
            out << 0 << ' ';
            if (!(plasate % 9)) out << '\n';
        }
    }
}