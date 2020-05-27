#include <bits/stdc++.h> 

using namespace std;

string c = "";
string tab[50];
const int MAX_ELE = 50;

void display(int n, string str[])
{
	for( int i = 0 ; i< n ; i ++ )
		cout << str[i] << endl;
	cout<< endl;
}

void sortAlpha(int n, string str[])
{
	for(int j=1; j<n ; j++)
		for(int i=0 ; i<n-j ; i++)
			if(str[i].compare(str[i+1])>0)
				swap(str[i], str[i+1]);
}

void sortLength(int n, string str[])
{
	for(int i=0;i<n;i++)
		for(int j=1;j<n-i;j++){
		if(tab[j-1].length() == tab[j].length())
			continue;
		if(tab[j-1].length()>tab[j].length())
			swap(tab[j-1], tab[j]);
		}
}

void fS()
{
	int los = ( rand() % 5 ) + 1;
	if(c.length() >= MAX_ELE)
		return void();
	switch(los)
	{
		case 1: 
			c += "a";
			fS();
			c +="b";
		break;
		
		case 2:
			c +="a";
			fS();
			c +="b";
		break;
		
		case 3:
			c +="a";
			fS();
		break;
		
		case 4:
			c +="b";
			fS();
		break;
		
		case 5:
			
		break;
	}
	
}

bool check(int x)
{
	for(int i = 0 ; i < MAX_ELE ; i++){
	if(x==i)
		continue;
	if(tab[i] == c)
		return true;
	}
	return false;
	
}

int main(void)
{
	int n = 0;
	srand( time( NULL ));
	
	cout<<setw(3)<<"|"<<setw(23)<<"Gramatyka"<<setw(17)<<"|"<<endl;
	cout<<setw(3)<<"|"<<"---------------------------------------|"<<endl;
	cout<<setw(4)<<"|	"<<"G = (V,T,P,S)"<<setw(20)<<"	  |"<<endl;
	cout<<setw(4)<<"|	"<<"V='S'"<<setw(30)<<"	  |"<<endl;
	cout<<setw(4)<<"|	"<<"T='a','b'"<<setw(25)<<"	  |"<<endl;
	cout<<setw(4)<<"|	"<<"P={S -> aSb | aSb | a | b | e}"<<"	  |"<<endl;
	cout<<setw(4)<<"|	"<<"S='S'"<<setw(30)<<"	  |"<<endl;
	cout<<setw(3)<<"|"<<"---------------------------------------|"<<endl<<endl;
	
	cout<<"Podaj ilosc lancuchow: ";
	cin>>n;
	cout<<endl;
	int tmp  = n;
	int i = 0;
	while(tmp != 0)
	{
		c="";
		fS();
		tab[i] = c;
		if(check(i))
		{
			tab[i] = "";
			continue;	
		} else {
			tmp--;
			i++;
		}
	}
	
	//display(n,tab);
	
	sortAlpha(n, tab);
	sortLength(n, tab);
		
	display(n, tab);
	return 0;
	
	
	
}

