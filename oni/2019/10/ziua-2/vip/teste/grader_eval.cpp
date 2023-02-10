#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void result(char msg[], int p)
{
    printf("%d %s", p , msg);
    exit(0);
}

int main (int argc, char **argv)
{

	int score = atoi( argv[2] );
    //int v1,v2,v3,v4,x1,x2,x3,x4;
    //FILE *fok = fopen("ape.ok","r");
    //FILE *fout = fopen("ape.out","r");

	int t, n, k, total = 1,fv[ 1000 ];
	string a, b, in1, in2;
	ifstream fin("vip.in");
	ifstream fok( "vip.ok" );
	ifstream fout( "vip.out" );
    if(!fout)
        result( "Fisier de iesire lipsa." , 0 );

	fin >> t;
	while( t-- )
	{
		fin >> n >> k >> in1 >> in2;
		fok >> a;
		for( int i = 'a' ; i <= 'z' ; i++ )
			fv[ i ] = 0;
		if( fout >> b )
		{
			if( a == b )
				continue;
			if( a.size() != b.size() )
				result( "Lungimea sirului nu este buna." , 0 );
			for( int i = 0 ; i < in1.size() ; i++ )
			{
				if( in1[ i ] != b[ i ] )
					k--;
				fv[ in2[ i ] ]++;
				fv[ b[ i ] ]--;
			}
			total = 0;
			for( int i = 'a' ; i <= 'z' ; i++ )
			{
				if( fv[ i ] != 0 )
				{
					result( "Nu este o anagrama." , 0 );
				}
			}

			if( k != 0 )
			{
				result( "Incorect." , 0 );
			}
		}
		else
		{
			result( "Fisierul de iesire nu contine t linii." , 0 );
		}
	}

	if( total == 1 )
		result( "OK" , score );
	else
	{
		score /= 4;

		result( "Nu e minim lexicografic." , score );
	}


    return 0;
}
