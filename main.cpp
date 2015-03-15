#include "MyFunc.h"


void main () {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	string L[4]={"худождественная","спортивная","учебная","развлекательная"};
	string buttonsNames[] = {"Случайный","Консоль","Bin Файл","Txt файл","Выход","Сортировка","Назад","Задание А","Задание Б"};
	int n = 0, g;
	char *q = new char[10];
	int K;
	Magazin A;
	Menu My = Menu(9,buttonsNames);
do{
	int buttonsIDs[] = {0,1,2,3,4};
	cout<<"Выберите способ ввода данных\n";
	g = My.showMenu(5,buttonsIDs);
	K = g;
	if (g!=51 && g!=52 && g!=53){
		do{
		cout<<"Введите количество магазинов: ";
		cin>>q;
		n = atoi(q);
		}while(!atoi(q) || n < 0);
		system("cls");
		A = Magazin(n, L);
	}
	switch(g) {
	case 49: A.inputRnd ();break;
	case 50: A.InputCon();break;
	case 51: {
		FILE *fb;
		string fname;
		cout<<"Введите имя файла: ";
		cin>>fname;
		fname += ".bin";
		while (!A.FileExists(fname.c_str())){
			cout<<"Файла не существует. Введите имя заного: ";
			cin>>fname;
			fname += ".bin";
		}
		fb = fopen(fname.c_str(), "rb");
		n = filelength(fileno(fb))/sizeof(Mag);
		A = Magazin(n,L);
		system("cls");
		A.InputFl(fb);
			}break;
	case 52: {
		FILE *f;
		string fname;
		cout<<"Введите имя файла: ";
		cin>>fname;
		fname += ".txt";
		while (!A.FileExists(fname.c_str())){
			cout<<"Файла не существует. Введите имя заного: ";
			cin>>fname;
			fname += ".txt";
		}
		f = fopen(fname.c_str(),"rt");
		char *st = new char[255];
		while(fgets(st,255,f)){
			n++;
		}
		fclose(f);
		f = fopen(fname.c_str(),"rt");
		n = (n - 4)/2;
		A = Magazin(n,L);
		system("cls");
		A.inputTxt(f);
			} break;
	case 53: g = 0;break;
	}
	if (g) {
		K = A.output (My);
		cout<<"Хотите сохранить новые данные в файл? (0 или 1) ";
		g=getch();
		if (g!=48) A.textZap();
		system("cls");
	}
}while(K==49 || K==50 || K==51);
}