#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "header_H.h"


using namespace std;

int pozycja_tasmy = 0;

/////////////////PRZEJSCIA/////////////////////////////

void q0(string &str, int pozycja_tasmy)
{
	wyswietl(str, pozycja_tasmy, "q0");
    if( str[pozycja_tasmy] == '0' )
    {
        str[pozycja_tasmy++] = 'B';
        q1(str , pozycja_tasmy);
    }
    else
    {
        str[pozycja_tasmy++] = 'B';
        q5(str , pozycja_tasmy);
    }
}
void q1(string &str, int pozycja_tasmy)
{
	wyswietl(str, pozycja_tasmy, "q1");
    if( str[pozycja_tasmy] == '0' )
    {
        str[pozycja_tasmy++] = '0';
        q1(str , pozycja_tasmy);
    }
    else
    {
        str[pozycja_tasmy++] = '1';
        q2(str , pozycja_tasmy);
    }
}
void q2(string &str, int pozycja_tasmy)
{
	wyswietl(str, pozycja_tasmy, "q2");
    if( str[pozycja_tasmy] == '0' )
    {
        str[pozycja_tasmy--] = '1';
        q3(str , pozycja_tasmy);
    }
    else if( str[pozycja_tasmy] == '1' )
    {
        str[pozycja_tasmy++] = '1';
        q2(str , pozycja_tasmy);
    }
    else
    {
        str[pozycja_tasmy--] = 'B';
        q4(str , pozycja_tasmy);
    }
}
void q3(string &str, int pozycja_tasmy)
{
	wyswietl(str, pozycja_tasmy, "q3");
    if( str[pozycja_tasmy] == '0' )
    {
        str[pozycja_tasmy--] = '0';
        q3(str , pozycja_tasmy);
    }
    else if( str[pozycja_tasmy] == '1' )
    {
        str[pozycja_tasmy--] = '1';
        q3(str , pozycja_tasmy);
    }
    else
    {
        str[pozycja_tasmy++] = 'B';
        q0(str , pozycja_tasmy);
    }
}
void q4(string &str, int pozycja_tasmy)
{
	wyswietl(str, pozycja_tasmy, "q4");
    if( str[pozycja_tasmy]=='0' )
    {
        str[pozycja_tasmy--] = '0';
        q4(str , pozycja_tasmy);
    }
    else if( str[pozycja_tasmy] == '1' )
    {
        str[pozycja_tasmy--] = 'B';
        q4(str , pozycja_tasmy);
    }
    else
    {
        str[pozycja_tasmy++] = '0';
        q6(str , pozycja_tasmy);
    }
}
void q5(string &str, int pozycja_tasmy)
{
	wyswietl(str, pozycja_tasmy, "q5");
    if( str[pozycja_tasmy] == '0' )
    {
        str[pozycja_tasmy++] = 'B';
        q5(str , pozycja_tasmy);
    }
    else if( str[pozycja_tasmy] == '1' )
    {
        str[pozycja_tasmy++] = 'B';
        q5(str , pozycja_tasmy);
    }
    else
    {
        str[pozycja_tasmy++] = 'B';
        q6(str , pozycja_tasmy);
    }
}
void q6(string &str, int pozycja_tasmy)
{
	wyswietl(str, pozycja_tasmy, "q6");
}

/////////////////////POZOSTALE//////////////////////////

string dec2un(int m, int n)
{
    string str;
    for ( int i = 0 ; i < m ; i++)
        str+='0';
    str+='1';
    for( int i = m+1 ; i < m+n+1 ; i++)
        str+='0';
    return str;
}

void roznica(int m, int n)
{
    if(m>=n)
    	cout<<"Roznica m-n wynosi: "<<m-n<<endl;
    else
    	cout<<"Roznica m-n wynosi: 0";
}

void wyswietl(string str , int pozycja_tasmy , string pozycja)
{
	cout<<"|-| ";
    for(int i = 0 ; i < pozycja_tasmy ; i++)
        cout << str[i];
    cout << "{" << pozycja << "}";
    for( int i = pozycja_tasmy ; i <= str.length() ; i++ )
        if( str[i] != 'B' )
			cout << str[i];
		else
			cout << " ";
    cout << " |-|" << endl;
}


int main (void)
{
    string str;
    int m, n;
    
    cout << "---------------------------------------" << endl;
    cout << "| D  |     0    |     0    |     B    | " << endl;
    cout << "---------------------------------------" << endl;
    cout << "| q0 | (q1,B,P) | (q5,B,P) |     -    | " << endl;
    cout << "---------------------------------------" << endl;
    cout << "| q1 | (q1,0,P) | (q2,1,P) |     -    | " << endl;
    cout << "---------------------------------------" << endl;
    cout << "| q2 | (q3,1,L) | (q2,1,P) | (q4,B,L) | " << endl;
    cout << "---------------------------------------" << endl;
    cout << "| q3 | (q3,0,L) | (q3,1,L) | (q0,B,P) | " << endl;
    cout << "---------------------------------------" << endl;
    cout << "| q4 | (q4,0,L) | (q4,B,L) | (q6,0,P) | " << endl;
    cout << "---------------------------------------" << endl;
    cout << "| q5 | (q5,B,P) | (q5,B,P) | (q6,B,P) | " << endl;
    cout << "---------------------------------------" << endl;
    cout << "| q6 |     -    |     -    |     -    | " << endl;
    cout << "---------------------------------------" << endl;
    cout << "\nM=({q0, q1, q2, q3, q4, q5, q6}, {0,1}, {0,1,B}, D, q0, B, 0)" << endl;
    
    cout << "Podaj pierwsza cyfre: ";
    cin >> m;
    cout << "Podaj druga cyfre: ";
    cin >> n;
    
    str = dec2un(m,n);
    cout<<"\nTasma wejsciowa: "<<str<<endl;
    cout<<endl;
    q0(str, pozycja_tasmy);
    roznica(m, n);
    return 0;
}
