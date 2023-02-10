// Problema artifact O( 11! * simboluri distince )
// Razvan Turturica

#include <fstream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

long long int coef[ 1000 ], suma,ans;
int fv[ 1000 ], prima[ 1000 ];
int cifra[ 1000 ];
long long int valoare[ 1000 ];
const long long modulo = 1000000007;
int stiva[ 100 ];
string a;
int n,m;
string sir[ 5010 ];

void bk( int nivel )
{
	long long sum = 0, p;
	if( nivel == a.size() )
	{
		for( int i = 1 ; i <= n + m ; i++ )
		{
			p = 1;
			for( int j = sir[ i ].size() - 1 ; j >= 0 ; j-- )
			{
				if( i <= n )
					sum += p * valoare[ sir[ i ][ j ] ];
				else
					sum -= p * valoare[ sir[ i ][ j ] ];
				p *= 10;
			}
		}
		if( sum == 0 )
			ans++;
		return;
	}
	for( int i = 0 ; i <= 9 ; i++ )
	{
		if( fv[ i ] == 0 )
		{
			if( i == 0 && prima[ a[ nivel ] ] == 1 ) continue;
			fv[ i ] = 1;
			sum = suma;
			valoare[ a[ nivel ] ] = i;
			stiva[ nivel ] = i;
			suma = ( suma + i * coef[ a[ nivel ] ] );
			bk( nivel + 1 );
			suma = sum;
			fv[ i ] = 0;
		}
	}
}

int main()
{
	ifstream cin("artifact.in");
	ofstream cout("artifact.out");
	cin >> n >> m;
	for( int i = 1 ; i <= n + m ; i++ )
	{
		cin >> a;
		if( a.size() > 1 )
			prima[ a[ 0 ] ] = 1;
		long long p = 1;
		for( int j = a.size() - 1 ; j >= 0 ; j-- )
		{
			fv[ a[ j ] ] = 1;
			sir[ i ] = a;
			if( i <= n )
			{
				coef[ a[ j ] ] = ( coef[ a[ j ] ] + p );
			}
			else
			{
				coef[ a[ j ] ] = ( coef[ a[ j ] ] - p );
			}
			p = ( p * 10 );
		}
	}
	a = "";
	for( int i = 'A' ; i <= 'Z' ; i++ )
	{
		if( fv[ i ] == 1 )
		{
			a.push_back( i );
		}
	}
	bk( 0 );
	cout << ans;
	return 0;
}
