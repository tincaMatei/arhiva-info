//Autor: Patcas Csaba
#include <vector> 
#include <cstdio> 
#include <iostream>  

using namespace std;

#define LL long long 
#define VI vector <int> 
#define FOR(i, a, b) for(int i = (a); i <= (b); ++i) 

#define IN_FILE "nisip.in" 
#define OUT_FILE "nisip.out" 

int n, m, headRock;
VI rocks, prevRock, nextRock, sand, rockInd, firstRock, removeTime;

//Citire
void read()
{
    cin >> n >> m;
    rockInd.resize(n + 1);
    int s = 0;
    FOR(i, 1, n)
    {
        char ch;
        cin >> ch;
        s += ch == '1';
        if (ch == '2')
        {
            rocks.push_back(i);
            sand.push_back(s);
            rockInd[i] = rocks.size() - 1;
            firstRock.push_back(rocks.size() - 1);
            s = 0;
        }
        else rockInd[i] = rocks.size();
    }
}

//Initializari
void initPointers()
{
    nextRock.resize(rocks.size()); //indicele pietrei urmatoare
    prevRock.resize(rocks.size()); //indecele pietrei precedente
    removeTime.resize(rocks.size()); //cand s-a spart piatra
    nextRock[0] = 1;
    prevRock[0] = -1;
    nextRock.back() = -1;
    prevRock.back() = rocks.size() - 2;
    FOR(i, 1, rocks.size() - 2)
    {
        nextRock[i] = i + 1;
        prevRock[i] = i - 1;
    }
    headRock = 0; //indicele primei pietre
}

//Spargem piatra cu indicele ri la seconda t
void removeRock(int ri, int t)
{
    if (nextRock[ri] != -1) prevRock[nextRock[ri]] = prevRock[ri];
    if (prevRock[ri] != -1) nextRock[prevRock[ri]] = nextRock[ri];
    else headRock = nextRock[ri];
    //Prima piatra nesparta sub ri
    firstRock[ri] = firstRock[firstRock[nextRock[ri]]];
    removeTime[ri] = t;
}

//Mutam tot nisipul deasupra pietrei cu indicele ri
void moveSand(int ri)
{
    sand[nextRock[ri]] += sand[ri];
    sand[ri] = 0;
}

//Cautam prima piatra existenta sub pozitia ind
int findFirstRock(int ind)
{
    int ri = rockInd[ind];
    while (removeTime[ri])
    {
        ri = firstRock[ri];
    }
    //Redirectionam ce gasim pe drum, 
    //astfel data viitoare va merge mai rapid
    int i = rockInd[ind];
    while (i != ri)
    {
        int next = firstRock[i];
        firstRock[i] = ri;
        i = next;
    }
    return ri;
}

//Solutia in cazul in care mina este stabila
int getStable(int ind, int firstRockIndex)
{
    if (ind == rocks[firstRockIndex]) return 2;
    else
        if (rocks[firstRockIndex] - ind <= sand[firstRockIndex]) return 1;
        else return 0;
}

//Solutia in secunda in care se sparge o piatra
int getStart(int ind, int firstRockIndex, int removedIndex)
{
    if (ind == rocks[firstRockIndex] || ind == rocks[firstRockIndex]) return 2;
    else
        if (ind > rocks[removedIndex] && rocks[firstRockIndex] - ind <= sand[firstRockIndex] ||
            ind < rocks[removedIndex] && rocks[removedIndex] - ind <= sand[removedIndex]) return 1;
        else return 0;
}

//Solutia cand se misca nisipul
int getMovingBlock(int ind, int firstRockIndex, int removedIndex, int dt)
{
    if (dt == 0) return getStart(ind, firstRockIndex, removedIndex);
    if (dt == 1)
        if (ind == rocks[removedIndex]) return 0;
        else return getStart(ind, firstRockIndex, removedIndex);
   
    //Piatra
    if (ind == rocks[firstRockIndex]) return 2;
    //Nisipul care nu se misca
    if (rocks[firstRockIndex] - ind <= sand[firstRockIndex]) return 1;
    //Aerul deasupra nisipului care se misca
    if (ind < rocks[removedIndex] - sand[removedIndex]) return 0;

    int col = ind - (rocks[removedIndex] - sand[removedIndex]) + 1;
    int sandToMove = sand[removedIndex];
    int distanceToMove = rocks[firstRockIndex] - sand[firstRockIndex] -
        rocks[removedIndex];

    int openTime = sandToMove; //Cat timp se "deschide" nisipul
    int travelTime = distanceToMove - (sandToMove - 1); //Cat timp se misca deschis
    int closeTime = sandToMove - 1; //Cat timp se inchide
    if (travelTime > 0)
    {
        //Daca are timp sa se miste total deschis
        if (dt <= openTime)
        {
            //Faza de deschidere
            if (col <= sandToMove - dt + 1) return 1;
            if (col > sandToMove + dt - 1) return 0;
            return (col + dt - sandToMove) & 1;
        }
        if (dt <= openTime + travelTime)
        {
            //Faza de miscare
            if (col < dt - openTime) return 0;
            if (col > dt - openTime + sandToMove * 2 - 1) return 0;
            return (col + dt - sandToMove) & 1;
        }
        //Faza de inchidere
        if (col <= min(dt - openTime, distanceToMove)) return 0;
        if (dt - openTime - travelTime >=
            sandToMove + distanceToMove - col) return 1;
        return (col + dt - sandToMove) & 1;
    }
    else
    {
        //Daca in timp ce se deschide incepe sa se si inchida
        if (dt <= openTime)
        {
            if (col <= sandToMove - dt + 1) return 1;
            if (col > sandToMove + dt - 1) return 0;
        }
        if (dt >= sandToMove + distanceToMove - closeTime)
        {
            if (col <= min(dt - openTime, distanceToMove)) return 0;
            if (dt - (sandToMove + distanceToMove - closeTime) >=
                sandToMove + distanceToMove - col) return 1;
        }
        return (col + dt - sandToMove) & 1;
    }
}

void solve()
{
    int lastRemoved = -1;
    int z = 0;
    FOR(q, 1, m)
    {
        int c, t, ind;
        cin >> c >> t >> ind;

        if (c == 1)
        {
            if (lastRemoved != -1) moveSand(lastRemoved);
            lastRemoved = rockInd[ind];
            removeRock(lastRemoved, t);
        }
        else
        {
            ++z;
            int ri = findFirstRock(ind);
            if (lastRemoved < prevRock[ri] || lastRemoved > ri)
            {
                //Nu s-a schimbat nimica in aceasta sectiune
                cout << getStable(ind, ri) << "\n";
                continue;
            }
            //Cat timp a trecut de la spargerea pietrei
            int dt = t - removeTime[lastRemoved];
            cout << getMovingBlock(ind, ri, lastRemoved, dt) << "\n";
        }
    }
}

int main()
{
    //Lucram cu fisiere mari, nu avem nevoie de sincronizare
    //Astfel citirea si scrierea va merge mai rapid
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    freopen(IN_FILE, "r", stdin);
    freopen(OUT_FILE, "w", stdout);

    read();
    initPointers();
    solve();

    return 0;
}
