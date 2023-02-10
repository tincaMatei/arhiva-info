#include <bits/stdc++.h>
using namespace std;

ifstream fok("telefon.ok");
ifstream fout("telefon.out");

void Msg(int pct, string msg );
string Trim(string s);

int main(int argc, char* argv[])
{
    if ( !fout )
        Msg(0, "Nu exista fisierul telefon.out!");

    int testNumber, testPoints;
	testNumber = atoi(argv[1]);          // numarul testului
	testPoints = atoi(argv[2]);          // nr puncte/test
	int total = 0;

    long long xc, yc;
    long long xok, yok;

    bool ok1 = false, ok2 = false;

    fout >> xc >> yc;
    fok >> xok >> yok;

    if (xc == xok) ok1 = true, total += 2;
    if (yc == yok) ok2 = true, total += 3;

	if ( ok1 && ok2 ) Msg(total, "Corect !");
    else if (ok1) Msg(total, "Corect 1)!");
            else if (ok2) Msg(total, "Corect 2)!");
                     else Msg(total, "Incorect !");

    return 0;
}

void Msg(int pct, string msg )
{
    cout << pct << ' ' << msg;
    try
    {
        fok.close();
        fout.close();
    }
    catch (string ex) {}
    exit(0);
}

string Trim(string str)
{
	size_t pos2 = str.find_last_not_of(" \t");
	size_t pos1 = str.find_first_not_of(" \t");
	if ( pos1 != string::npos && pos2 != string::npos)
		str = str.substr(pos1, pos2 + 1);
	return str;
}

