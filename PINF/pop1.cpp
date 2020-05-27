#include <bits/stdc++.h> 

char A[100][100]; 
char B[100][100];
char C[2][100]; 

using namespace std;

int main()
{
	int i=0; 
	int k=0; 
	int c1=0; 
	int c2=0; 
	int check=0;
	int j, index, clen1, clen2, c3, c4;
	int m=0; 
	int kroki[200];
	
	cout<<"Problem odpowiednosci Posta"<<endl;
	cout<<"A = w1,w2,...,wk"<<endl;
	cout<<"B = x1,x2,...,xk"<<endl;
	cout<<"Podaj lancuchy:\n"<<endl;
	
	while(1) { //dodawanie do listy
		cout<<"w"<<i+1<<"= ";
		fgets(A[i], 100, stdin);
		if(A[i][0]!='1' && A[i][0]!='0') 
			break;
		
		cout<<"x"<<i+1<<"= ";
		fgets(B[i], 100, stdin);
		if(B[i][0]!='1' && B[i][0]!='0') 
			break;
		i++;
		cout<<endl;
	}
	
	system("@cls||clear");
	
	cout<<"A = ";
	for( j=0 ; j<i ; j++ ) {//wypisanie listy i i sprawdzenie jej dlugosci
		k=0;
		while(1) {
			cout<< A[j][k];
			k++;
			if(A[j][k] != '1' && A[j][k] != '0') 
				break;
		}
		if(j != i-1) 
			cout<<", ";
	}
	cout<<endl;
	cout<<"B = ";
	for( j=0 ; j<i ; j++ ) {
		k=0;
		while(1) {
			cout<<B[j][k];
			k++;
			if(B[j][k] != '1' && B[j][k] != '0') 
				break;
		}
		if(j != i-1) 
			cout<<", ";
	}
	
	cout<<endl;
	
	while(1) {
		c3=0; 
		c4=0;
		cout<<"Podaj indeks lub 0 zeby zakonczyc: ";
		cin>>index;
		
		if(index == 0 && index <= i) {
			cout<<"Koniec"<<endl;
			return 0;
		}
		
		j=0;
		while(1) { //przypisane listy A do tab pomocniczej oraz dodawanie indeksow
			C[0][c1]=A[index-1][j];
			
			if(A[index-1][j] != '1' && A[index-1][j] != '0') 
				break;
			c1++; 
			j++; 
			c3++;
		}
	
		j=0;
		while(1) { //przypisane listy B do tab pomocniczej oraz dodawanie indeksow
			C[1][c2]=B[index-1][j];
			
			if(B[index-1][j] != '1' && B[index-1][j] != '0') 
				break;
			c2++; 
			j++; 
			c4++;
		}
			
		if(c1 > c2) { 
			clen1=c1;
			clen2=c2;
		} else {
			clen1=c2;
			clen2=c1;
		}
		
		check=0;
		for( k=0 ; k<clen1 ; k++ ) //Sprawdzenie poprawnosci utworzonyc ciagow, gdy sa identyczne to check=0
				if(C[0][k] != C[1][k]) 
					check=1;
		
		if(check == 0 && index <= i) { //Calkowita zgodnosc ciagow- wyswitlenie rozwiazania
			kroki[m]=index;
			m++;
			cout<<endl;
			cout<<"Rozwiazanie: ";
			
			for( j=0 ; j<m ; j++ )
				cout<<kroki[j]<<(j<m-1?", ":"");
				
			cout<<endl;
			
			for( j=0 ; j<c1 ; j++)
				cout<<C[0][j];
		
			cout<<" = ";
		
			for( j=0 ; j<c2 ; j++ )
				cout<<C[1][j];
			
			cout<<endl;
			cout<<"m= "<<m<<endl;
			
			return 0;
		}	
		
		check=0;
	
		for( k=0 ; k<clen2 ; k++ )
				if(C[0][k] != C[1][k]) 
					check=1;
		
		if(check == 0 && index <= i) { //Czesciowa zgodnosc ciagow- wyswitlenie czesciowego rozwiazania lub info o jego braku
			kroki[m]=index;
			m++;
			cout<<"Rozwiazanie czesciowe: ";
	
			for( j=0 ; j<c1 ; j++ ) 
				cout<<C[0][j];
		
			cout<<" ";
		
			for( j=0 ; j<c2 ; j++ )
				cout<<C[1][j];
				
			cout<<endl;
		} else if(index <= i) {
			cout<<"Brak rozwiazania przy dodaniu wskazanych lancuchow"<<endl;
			c1-=c3;
			c2-=c4;
		} else { 
			cout<<"Podaj poprawny indeks!"<<endl;
			c1-=c3;
			c2-=c4;
		}
	}
}
