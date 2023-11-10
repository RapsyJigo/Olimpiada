#include <iostream>
#include <map>
#include <fstream>
#include <algorithm>

/*
Problema este rezolvata numarand o familie de drepte care dupa rotatie vor fi verticale sau orizontale.

Se face observatia ca toate dreptele care au acelasi unghi sau care sunt perpendiculare vor face parte din aceasta familie,
Deci se va calcula panta unei drepte si panta dreptei perpendiculare
*/

using namespace std;

int main ()
{
    ifstream in("arhitect.in");
    ofstream out("arhitect.out");

    int n;
    in >> n;
    double x1, x2, y1, y2; //Trebuie folosit double pentru a evita erori de calcul
    double x;

    map<double, int> counter; //Un dictionar cu cheie numar real (panta) si valoare intreg (cate sunt)

    for (int i = 0; i < n; i++)
    {
        in >> x1 >> y1 >> x2 >> y2;
        x = (y2 - y1)/(x2 - x1); //Calculam panta dreptei din coordonate

        //Se aduna si panta si perpendicularele pe panta pentru a evita conditi la final
        counter[x]++; 
        counter[-1/x]++;
    }

    int maxim = 0;

    //Parcurgerea iterativa a dictionarului map<double, int> pentru a gasi maximul
    //Se declara un iterator pe map<double, int> denumit i, initializat cu counter.begin() pentru inceputul dictionarului
    //Se parcurge pana cand este diferit de counter.end(), finalul dictionarului
    //i++ in contextul actual itereaza la urmatorul element din dictionar
    //i->first va oferi cheia din dictionar
    //i->second va oferi valoarea din dictionar
    for (map<double, int>::iterator i = counter.begin(); i != counter.end(); i++)
    {
        if (i->second > maxim)
        {
            maxim = i->second;
        }
    }

    out << maxim;
}