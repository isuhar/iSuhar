#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <windows.h>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <io.h>
#include "Class Menu.h"
using namespace std;

struct Mag{
	int M[5],T,k,MaxT;
	string Name;
	float Sr;
};

struct Lit{
	int Sum, nomMax;
	float Sr;
	string L;
};

class Magazin{
private:
	Mag *A;
	int n;
	Lit *Liter;
public:
	Magazin(){
	}
	Magazin(int NN, string *L){
		n = NN;
		A = new Mag[n];
		Liter = new Lit[4];
		for (int i=0; i<4; i++)
		{
			Liter[i].L = L[i];
		}
	}
	void outShortMenu();
	void inputTxt( FILE *f);
	void inputRnd();
	int output( Menu My);
	void mySort (int n, int N, int S, int a);
	void count (int i);
	float countM ();
	int whereY();
	void curs (int x);
	void colorBlack();
	void colorRed();
	void outMenu(int N);
	string inputName(int *y, int i);
	float sum (int N);
	void outSum (int N);
	int intData (int *N, int *S, int *a, int *b, Menu My, int K);
	void InputFl( FILE *f);
	void InputCon();
	void curs2 (int x);
	void textZap();
	bool FileExists(const char *fname);
	string reName(string name, int b);
	bool Save();
	void countB (int i);
	int outA(Menu My);
	int outB(Menu My);
};

void Magazin::textZap(){
	int g;
	do{
		if (Save()) cout<<"Файл успешно сохранен.\n";
		else cout<<"Сохранение не удалось.\n";
		cout<<"Хотите сделать ещё копию? (1 или 0)";
		g=getch();
	}while(g!=48);
}

bool Magazin::Save(){
	FILE *f;
	string nameStr;
	int b;
	cout<<"\n0 - txt файл, иначе - двоичный файл: ";
	cin>>b;
	cout<<"Введите имя файла: "; 
	cin>>nameStr;
	if (b) nameStr += ".bin";
	else nameStr += ".txt";
	nameStr = reName(nameStr.c_str(), b);
	if (b) {
		f = fopen(nameStr.c_str(),"wb");
		for(int i=0; i<n; i++){
			fwrite(A+i,sizeof(Mag),1,f);
		}
	}
	else {
		f = fopen(nameStr.c_str(),"wt");
		fprintf(f,"%30s","_____________________________________________");
		fprintf(f,"\n%2s | %10s | %4s | %4s | %4s | %4s |", "1", "2","3", "4", "5","6"); 
		fprintf(f,"\n%2s | %10s | %4s | %4s | %4s | %4s |", "№", "Название","Худо", "Спор", "Учеб","Разв");
		fprintf(f,"\n%30s","_____________________________________________");
		for(int i=0; i<n; i++){
			fprintf(f,"\n%2d | ", i+1);
			fprintf(f,"%10s",A[i].Name.c_str());
			fprintf(f," |");
			for(int j=0; j<4; j++){
				fprintf(f," %4d |",A[i].M[j]);
			}
			fprintf(f,"\n%30s","_____________________________________________");
		}
	}
	return FileExists(nameStr.c_str());
}

string Magazin::reName(string name, int b){
	int a = 0;
	while (FileExists(name.c_str()) && a==0){
		cout<<"ТАКОЙ ФАЙЛ УЖЕ СУЩЕСТВУЕТ. Вы хотите его перезаписать? (1 или 0): ";
		cin>>a;
		if (a==0) {
			cout<<"Введите имя файла заного: "; 
			cin>>name;
			if (b) name += ".bin";
			else name += ".txt";
		}
	}
	return name;
}
void Magazin::inputTxt( FILE *f){
	int koef = 0, i = 0, j = 0;
	char *st = new char[255];
	char simbl[] = " |";
	char *s;
	outShortMenu();
	while(fgets(st,255,f)){
		koef++;
		if ( koef > 4 && koef%2 != 0) {
			s = new char[255];
			strcpy ( s , st );
			while (s = strtok(s,simbl)){
				i++;
				if ( i > 2 ) {
					A[j].M[i - 3] = atoi(s);
				}
				else if (i == 2){
					A[j].Name = s;
				}
				s = 0;
			}
			count(j);
			printf("%2d | %10s | %4d | %4d | %4d | %4d |\n", j+1, A[j].Name.c_str(), A[j].M[0], A[j].M[1], A[j].M[2], A[j].M[3]);
			printf("%30s\n","_____________________________________________");
			j++;
			i = 0;
		}
	}
	fclose(f);
}

void Magazin::InputFl( FILE *f){
	outShortMenu();
	for (int i=0; i<n; i++){
		fread(A+i,sizeof(Mag), 1, f);
		count(i);
		printf("%2d | %10s | %4d | %4d | %4d | %4d |\n", i+1, A[i].Name.c_str(), A[i].M[0], A[i].M[1], A[i].M[2], A[i].M[3]);
		printf("%30s\n","_____________________________________________");
	}
	fclose(f);
}
void Magazin::InputCon(){
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	char *test = new char[10];
	int x;
	outShortMenu();
	for(int i=0; i<n; i++){
		x=15;
		printf("%2d | ", i+1);
		cin>>A[i].Name;
		curs(x);
		for(int j=0; j<4; j++)
		{
			printf(" | ");
				cin>>test;
				while (!atoi(test)) {
					curs(x+3);
					COORD coord = {x+3, whereY()};
					FillConsoleOutputCharacter(hStdOut, ' ', 80, coord, NULL);
					cin>>test;
				}
			A[i].M[j] = atoi(test);
			x+=7;
			curs(x);
		}
		printf(" |");
		count(i);
		printf("\n%30s\n","_____________________________________________");
	}
}
void Magazin::inputRnd (){
	int *y  = new int[n];
	srand((unsigned)time(0));
	outShortMenu();
	for(int i=0; i<n; i++){
		printf("%2d | ", i+1);
		A[i].Name = inputName(y,i);
		printf("%10s",A[i].Name.c_str());
		for(int j=0; j<4; j++){
			printf(" | ");
			A[i].M[j] = rand()/(RAND_MAX/100);
			printf("%4d",A[i].M[j]);
		}
		printf(" |");
		count(i);
		printf("\n%30s\n","_____________________________________________");
	}
}
string Magazin::inputName(int *y, int i){
	int k,p=0;
		do{
			k=1;
			y[i] = 1 + rand()%(15);
			if (i!=0){
				if (i>14){
					for (int j=i-1; j>(i-14)&&k; j--){
						if (y[i]==y[j]) k=0;
					}
				}
				else {
					for (int j=0; j<i&&k; j++){
						if (y[i]==y[j]) k=0;
					}
				}
			}
		} while (k!=1);
		ifstream iFile;
		iFile.open("text.txt");
		string str;
		k=0;
		while (!iFile.eof()&&(k!=y[i] || k==0)){
			getline(iFile,str);
			k++;
		}
	return str;
}
int Magazin::output (Menu My){
	int K;
	int butIDs[] = {7,8,6,4};
	K = My.showMenu(4,butIDs);
	if (K==49){
		K = outA(My);
	}
	else if (K == 50)
	{
		K = outB(My);
	}
	return K;
}

int Magazin::outA(Menu My)
{
	system("cls");
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int N,a=0,b;
	int S,K=0;
		outMenu(0);
		for (int i=0; i<n; i++){
			printf("%2d | %10s | %4d | %4d | %4d | %4d | %6.1f | %4d | %15s |\n", i+1, A[i].Name.c_str(), A[i].M[0], A[i].M[1], A[i].M[2], A[i].M[3], A[i].Sr, A[i].T, Liter[A[i].k].L.c_str());
			printf("%61s\n","_______________________________________________________________________________");
		}
		K = intData(&N,&S,&a,&b, My,K);
		if(N!=1 && K==49){
			do{
				system ("cls");
				mySort (b, N, S, a);
				outMenu(N);
				for (int i=0; i<n; i++){
					if (i==a-1 || i==b-1) SetConsoleTextAttribute(h, FOREGROUND_GREEN );
					if (countM ()==A[i].Sr) {SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_RED   | FOREGROUND_INTENSITY );}
					printf("%2d | %10s | %4d | %4d | %4d | %4d | %6.1f | %4d | %15s |\n", i+1, A[i].Name.c_str(), A[i].M[0], A[i].M[1], A[i].M[2], A[i].M[3], A[i].Sr, A[i].T, Liter[A[i].k].L.c_str());
					colorBlack();
					printf("%61s\n","_______________________________________________________________________________");
				}
				outSum(N);
				K = intData(&N,&S,&a,&b,My,K);
				if (K==52 || K==51) return K;
				if (K == 50) outB(My);
			}while (N!=1);
		}
		else if (K == 50) outB(My);
}

int Magazin::outB(Menu My)
{
	int K;
	system("cls");
		printf("%50s","__________________________________________________________________");
		printf("\n%2s | %15s | %13s | %7s | %15s |", "1", "2","3", "4", "5"); 
		printf("\n%2s | %15s | %13s | %7s | %15s |", "№", "Содержание","Всего продано", "Среднее","Больше всего");
		printf("\n%50s\n","__________________________________________________________________");
		for (int i=0; i<4; i++)
		{
			countB(i);
			printf("%2d | %15s | %13d | %7.2f | %15s |\n", i+1, Liter[i].L.c_str(), Liter[i].Sum, Liter[i].Sr, A[Liter[i].nomMax].Name.c_str());
			printf("%50s\n","__________________________________________________________________");
		}
		int IDs[] = {5,7,6,4};
		K = My.showMenu(4,IDs);
		if (K == 50) outA(My);
		return K;
}

void Magazin::countB (int i){
	Liter[i].Sum = 0;
	int max = 0;
	for (int j=0; j<n; j++)
	{
		Liter[i].Sum += A[j].M[i];
		if (max < A[j].M[i]) {max = A[j].M[i]; Liter[i].nomMax = j;}
	}
	Liter[i].Sr = (float)Liter[i].Sum/n;
}

int Magazin::intData (int *N, int *S, int *a, int *b, Menu My, int K){
		int IDs[] = {5,8,6,4};
		K = My.showMenu(4,IDs);
		if (K==49){
			do{
				cout<<"Номер столбца: ";
				cin>>*N;
				if ( *N<10 && *N>1 ) {
					cout<<"По возрастанию 1, по убыванию 0: ";
					cin>>*S;
					do {
						cout<<"Сортировать между (0 - всё): ";
						cin>>*a;
						if (*a) cin>>*b;
						else { *a = 1; *b = n;}
					} while(*a<=0 || *a>=n || *b<=*a || *b>n);
				}
			} while (*N>9 || *N<1 || *a<=0 || *a>=n || *b<=*a || *b>n );
		}
	return K;
}
void Magazin::colorBlack (){
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );
}
void Magazin::colorRed (){
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, BACKGROUND_RED);
}
void Magazin::mySort (int n, int N, int S, int a){
	Mag B;
	int b;
	for (int i=a-1; i<n; i++){
		for (int j=i; j<n; j++){
			switch (N){
			case 2: b=strcmp(A[i].Name.c_str(), A[j].Name.c_str()) > 0; break;
			case 3:case 4: case 5: case 6: {b=A[j].M[N-3]<A[i].M[N-3];}break;
			case 7: {b=A[j].Sr<A[i].Sr;} break;
			case 8: {b=A[j].T<A[i].T;}break;
			case 9: b=strcmp(Liter[A[i].k].L.c_str(), Liter[A[i].k].L.c_str()) > 0; break;
			}
			if (S==0) b=!b;
			if (b){
				B=A[i];
				A[i]=A[j];
				A[j]=B;
			}
		}
	}
}
void Magazin::count (int i){
	A[i].MaxT=0;
	A[i].T=0;
	for (int j=0; j<4; j++){
		A[i].T+=A[i].M[j];
		if (A[i].MaxT<A[i].M[j])
		{
			A[i].MaxT=A[i].M[j];
			A[i].k=j;
		}
	}
	A[i].Sr=(float)A[i].T/4;
}
float Magazin::countM (){
	float MAX=0;
	Mag C;
	for (int i=0; i<n; i++){
		if (A[i].Sr>MAX)
		{
			MAX=A[i].Sr;
			C=A[i];
		}
	}
	return MAX;
}
int Magazin::whereY(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.Y;
}
void Magazin::curs (int x){
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cPos;
	cPos.Y = whereY()-1;
	cPos.X = x;
	SetConsoleCursorPosition(h, cPos);
}
void Magazin::curs2 (int x){
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cPos;
	cPos.Y = whereY();
	cPos.X = x;
	SetConsoleCursorPosition(h, cPos);
}
void Magazin::outMenu(int N){
	printf("%61s\n","_______________________________________________________________________________");
		printf("%2s |", "1");
		if (N==2) colorRed();printf(" %10s |", "2");colorBlack();
		if (N==3) colorRed();printf(" %4s |", "3");colorBlack();
		if (N==4) colorRed();printf(" %4s |", "4");colorBlack();
		if (N==5) colorRed();printf(" %4s |", "5");colorBlack();
		if (N==6) colorRed();printf(" %4s |", "6");colorBlack();
		if (N==7) colorRed();printf(" %6s |", "7");colorBlack();
		if (N==8) colorRed();printf(" %4s |", "8");colorBlack();
		if (N==9) colorRed();printf(" %15s |\n", "9");colorBlack();
		printf("%2s |", "№");
		if (N==2) colorRed();printf(" %10s |", "Название");colorBlack();
		if (N==3) colorRed();printf(" %4s |", "Худо");colorBlack();
		if (N==4) colorRed();printf(" %4s |", "Спор");colorBlack();
		if (N==5) colorRed();printf(" %4s |", "Учеб");colorBlack();
		if (N==6) colorRed();printf(" %4s |", "Разв");colorBlack();
		if (N==7) colorRed();printf(" %6s |", "Сред");colorBlack();
		if (N==8) colorRed();printf(" %4s |", "Сумм");colorBlack();
		if (N==9) colorRed();printf(" %15s |\n", "Больше всего");colorBlack();
		printf("%61s\n","_______________________________________________________________________________");
}
bool Magazin::FileExists(const char *fname){
	return (_access(fname, 0) == 0);
}

void Magazin::outShortMenu(){
	printf("%30s","_____________________________________________");
	printf("\n%2s | %10s | %4s | %4s | %4s | %4s |", "1", "2","3", "4", "5","6"); 
	printf("\n%2s | %10s | %4s | %4s | %4s | %4s |", "№", "Название","Худо", "Спор", "Учеб","Разв");
	printf("\n%30s\n","_____________________________________________");
}
float Magazin::sum (int N){
	float sum=0;
	for (int i=0; i<n; i++){
		switch (N){
		case 3:case 4: case 5: case 6: sum+=A[i].M[N-3]; break;
		case 7: {sum+=A[i].Sr; } break;
		case 8: {sum+=A[i].T;}break;
		}
	}
	return sum;
}
void Magazin::outSum (int N){
	printf("%2d | %10s |", n+1, "Общ. cумма");
	switch (N){
	case 3:case 4: case 5: case 6: {curs2(16+(N-3)*7); colorRed(); printf("|%6.1f|", sum(N));}break;
	case 7: {curs2(44); colorRed(); printf("|%8.1f|", sum(N));} break;
	case 8: {curs2(53); colorRed(); printf("|%6.1f|", sum(N));}break;
	}
	colorBlack();
	curs2(78);
	cout<<"|"<<endl;
	printf("%61s\n","_______________________________________________________________________________");
}