#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

/*
Problema se rezolva prin crearea unei matrici de solutii, in aceasta matrice se va stoca distanta dinrte 2 litere.

Pentru cerinta 1 problema este triviala, se face doar suma distantelor a 2 litere consecutive in lista.
Pentru cerinta 2 se va aplica metoda brute force (aplicabila din cauza optimizari matricii de distante) pentru a determina distanta dintre 2 litere consecutive
cu toate literele rosii introduse intre cele 2 albastre. Se va aduna doar distanta minima
ALBASTRU_1 + ROSU_N + ALBASTRU_2
Unde N va parcurge toate posibilele litere rosii
*/

using namespace std;
//Generarea matricei de distanta intre 2 litere
void distanta (int mat[26][26])
{
    
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
            if (abs(j - i) < 13)
                mat[i][j] = abs(j - i); //Daca diferenta dintra o litera (j) si cealalta (i) este sub 13 se merge clockwise
            else
                mat[i][j] = 13 - abs(i - j)%13; //Daca diferenta dintre o litera (j) si cealalta (i) este peste 13 se merge counterclockwise
    
}

int main ()
{
    int dist[26][26];
    distanta(dist);

    ifstream in ("circular.in");
    ofstream out ("circular.out");
    string albastre;
    string rosii;
    int c;
    int timp = 0;
    in >> c >> albastre >> rosii;
    if (c == 1)
    {
        //Se aduna toaaate distantele intre litere 2 cate doua
        timp += dist[albastre[0] - 'A'][0]; //Totimpul se incepe cu acul pe 'A'
        for (int i = 0; i < albastre.size() - 1; i++)
        {
            timp += dist[albastre[i] - 'A'][albastre[i+1] - 'A']; //Scadem codul ascii 'A' pentru a pune literele intra 0 si 25
        }
        out << timp;
    }
    else
    {
        //Consideram toate distantele posibile de la o litera albastra la toate literele rosii si dupaia la urmatoarea litera albastra
        //Se va lua minimul acestei distnte, daca exista multiple se v-or inmulti posibilitatile

        timp += dist[albastre[0] - 'A'][0]; //Totimpul se incepe cu acul pe 'A'
        string minim;
        minim.push_back(albastre[0]); //Introducereaa primei litere
        long long int posibilitati = 1;

        for (int i = 0; i < albastre.size() - 1; i++)
        {
            int crt_timp = 100; //Presupunem un timp maxim pentru cele 2 litere albastre curente pentru a afla minimul
            long long int crt_posibilitati = 1; //Posibilittile curente egale
            char crt_litera; //Prima litera gasita cu distanta minima

            //Parcurgerea tuturor literelor rosii
            for (int j = 0; j < rosii.size(); j++) 
            {
                //Daca dist dintre o litera albstra la o litera rosie + aceasi liter arosii si urmatoare litera albastra este mai mica decat minimul curent
                if (dist[albastre[i] - 'A'][rosii[j] - 'A'] + dist[albastre[i+1] - 'A'][rosii[j] - 'A'] < crt_timp)
                {
                    //Setam noul minim, resetam posibilitatile si memoram litera
                    crt_timp = dist[albastre[i] - 'A'][rosii[j] - 'A'] + dist[albastre[i+1] - 'A'][rosii[j] - 'A'];
                    crt_posibilitati = 1;
                    crt_litera = rosii[j];
                }
                //Daca distanta de mai sus este egala
                else if (dist[albastre[i] - 'A'][rosii[j] - 'A'] + dist[albastre[i+1] - 'A'][rosii[j] - 'A'] == crt_timp)
                {
                    crt_posibilitati++; //Incrementam posibilitatile
                }
            }
            timp += crt_timp; //Timpul total creste
            minim.push_back(crt_litera); //Adaugam litera rosie
            minim.push_back(albastre[i + 1]); //Adaugam litera albastra
            posibilitati = (posibilitati * crt_posibilitati) % 666013; //Inmultim posibilitatila %66013 comform cerintei
        }
        out << timp << '\n' << posibilitati << '\n' << minim;
    }
}