 // G_zad1.cpp: ������� ���� �������.

#include "stdafx.h" // ����������� ��������� ��++
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
#include <clocale>

using namespace std; // ������������� ����������� ����
using namespace System; //������������� ������������ ���� ���������� Windows Forms � �++/CLI
using namespace System::IO; //������������� ������������ ���� ��� �����-������ � ���������� Windows Forms � �++/CLI

// ����������� �������� ��� ������
#define ENTER 13 
#define ESC 27
#define UP 72
#define DOWN 80
#define HOME 71
#define END 79 

int NC; // ���������� ������� � ����

// ��������� ��� �������� ���������� � ������� ����
struct z {
	char name[30]; // �������� �������
	char rarity[10]; // ������� ������� 
	long summa; // ���� �������
	char type[11]; // ��� �������
	int time; // ����� �������������
};
// ��������� ��� ����������� ������
struct sp {
	char pos[30]; // �������� �������
	long summa; // ���� �������	
	struct sp* sled; //��������� �� ��������� �������
	struct sp* pred; // ��������� �� ���������� �������
} *spisok;

int menu(int);
void minim(struct z*, int NC); // ������� ��� ���������� ����� ������� �������
void fast(struct z*, int NC); // ������� ��� ���������� ����������� ������� ������������� �������
void ovosch(struct z*, int NC); // ������� ��� ���������� ������� ������� ������� 300 ������
void alfalist(struct z*, int NC, struct sp **spisok); // ������� ��� ������ ����������� ������
void vstavka(struct z*, char*, int NC, struct sp **spisok); // ������� ��� ������� �������� � ���������� ������
void diagram(struct z*, int NC, struct sp **spisok); // ������� ��� ������ ���������
void sravn(struct z*, int NC); // ������� ��� ���������

// �������� ������� ���������
int main(array<System::String ^> ^args)
{
	int i,n; // ���������� ���������� i � n
	FILE *in; // ���������� ��������� �� ����
	struct z *position;
	struct sp *spisok = 0;

	// ����������� ������� ����� ����
	char dan[7][55]={
		"����� ����� ������� ������� � ����?                   ",
		"����� ������� ��� �������� �������?		         ",
		"����� ������� �������� ������� 300 ������?            ",
		"���������                                             ",
		"���������                                             ",
		"������ ����������                                     ",
		"�����                                                 "
	};
	char BlankLine[ ]="                                                        "; // ������ ������
	setlocale(LC_CTYPE,"Russian"); // ��������� ������ ��� ������ � ������� ������
	Console::CursorVisible::set(false); // ������� �������
	Console::BufferHeight=Console::WindowHeight; // ��������� ������ ������ �������
	Console::BufferWidth=Console::WindowWidth; // ��������� ������ ������ ������

	// �������� ����� � ����
	if((in=fopen("Menu.dat","r"))==NULL)
	{
		printf("\n���� Menu.dat �� ������ !"); // ����� ��������� �� ������, ���� ���� �� ������� �������
		getch(); exit(1); // ���������� ��������� � �������
	}
	fscanf(in,"%d",&NC); // ������ ���������� ������� � ���� �� �����
	position=(struct z*)malloc(NC*sizeof(struct z)); // ��������� ������ ��� ������ �������

	// ����� ��������� �������
	printf("\n|---------------------------|---------|-------|---------|----------|");
	printf("\n|   ������������ �������    | ������� | ����  |   ���   |  �����   |");
	printf("\n|---------------------------|---------|-------|---------|----------|");

	
	for(i=0;i<NC;i++)
		fscanf(in,"%s%s%d%s%d",position[i].name,
		position[i].rarity, &position[i].summa, position[i].type, &position[i].time); // ������ ������ �� �����
	for(i=0;i<NC;i++)
		printf("\n| %-25s | %-7s |  %-4d | %-7s | %2d-����� |",
		position[i].name, position[i].rarity, position[i].summa, position[i].type, position[i].time); // ����� ������ �� �����
	printf("\n|---------------------------|---------|-------|---------|----------|");
		getch(); // �������� ������� �������

	// ����������� ���� ��� ������ � ����
	while(1)
	{
		// ��������� ����� � ������� �������
		Console::ForegroundColor=ConsoleColor::White;  // ��������� ����� ������ � �������
		Console::BackgroundColor=ConsoleColor::DarkBlue; // ��������� ����� ���� � �������
		Console::Clear(); // ������� �������

		// ��������� ����� ������� (����� �������)
		Console::ForegroundColor=ConsoleColor::White; 
		Console::BackgroundColor=ConsoleColor::Blue;
		Console::CursorLeft=10; // ��������� ������� ������� � �������
		Console::CursorTop=4; // ��������� ������� ������� � �������
		printf(BlankLine); // ����� ������ ������

		// ����� ������� ����
		for(i=0;i<7;i++)
		{
			Console::CursorLeft=10; // ����������� ������� ������� � �������
			Console::CursorTop=i+5; // ����������� ������� ������� � �������
			printf(" %s ",dan[i]); // ����� ������ ����
}
		Console::CursorLeft=10; // ��������� ������� ������� � �������
		Console::CursorTop=12; // ��������� ������� ������� � �������
		printf(BlankLine); // ����� ������ ������

		// ��������� ������ � ����
		n=menu(7); 
		switch(n) 
		{
		case 1: minim(position, NC); break; // ����� ������� ����������� ����
		case 2: fast(position, NC); break; // ����� ������� ����������� ������� ������������� �������
		case 3: ovosch(position, NC); break; // ����� ������� ������� ������� ������� 300 ������
		case 4: alfalist(position, NC, &spisok); break; // ����� ������� ����������� ������
		case 5: diagram(position, NC, &spisok); break; // ����� ������� ���������
		case 6: sravn(position, NC);break; // ����� ������� ���������
		case 7: exit(0); // ����� �� ���������
		}
	} // ����� while(1)...
return 0;
} // ����� main()

// ������� ��� ��������� ����
int menu(int n)
{
	int y1=0,y2=n-1;
	char c=1;

	// ����������� ������� ����� ����
	char dan[7][55]={
		"����� ����� ������� ������� � ����?                   ",
		"����� ������� ��� �������� �������?		         ",
		"����� ������� �������� ������� 300 ������?            ",
		"���������                                             ",
		"���������                                             ",
		"������ ����������                                     ",
		"�����                                                 "
	};
	while (c!=ESC)
	{
		switch(c) {
		case DOWN: y2=y1; y1++; break; // ������� � ������� ������ ���� ��� ������� ������� ����
		case UP: y2=y1; y1--; break; // ������� � �������� ������ ���� ��� ������� ������� �����
		case ENTER: return y1+1; // ����� ������ ���� ��� ������� ������� Enter
		case HOME: y2 = y1; y1 = 0; break; // ������� � ������� ������ ���� ��� ������� Home
        case END: y2 = y1; y1 = n - 1; break; // ������� � ���������� ������ ���� ��� ������� End

	}
	// ��������� ������ �� ������� ����
	if(y1>n-1){y2=n-1;y1=0;} // ���� ����� �� ������� ���� �����, ������� � ������� ������
	if(y1<0) {y2=0;y1=n-1;} // ���� ����� �� ������� ���� ������, ������� � ���������� ������

	Console::ForegroundColor=ConsoleColor::Cyan; // ��������� ����� ������ ��� ����������� ������ ����
	Console::BackgroundColor=ConsoleColor::DarkBlue; // ��������� ����� ���� ��� ����������� ������ ����
	Console::CursorLeft=11; // ����������� ������� ������� � �������
	Console::CursorTop=y1+5; // ����������� ������� ������� � �������
	printf("%s",dan[y1]);
	Console::ForegroundColor=ConsoleColor::White; // ���������� ���� ������ ��� ������ ����
	Console::BackgroundColor=ConsoleColor::Blue; // ���������� ���� ���� ��� ������ ����
	Console::CursorLeft=11; // ����������� ������� ������� � �������
	Console::CursorTop=y2+5; // ����������� ������� ������� � �������
	printf("%s",dan[y2]);
	c=getch(); // �������� ������� �������
	} // ����� while(c!=ESC)...
exit(0);
}
// ������� ��� ���������� ����� ������� �������
void minim(struct z* position, int NC)
{
	int i;
	struct z worse; // ��������� ��� �������� ���������� � ����� ������� �������
	strcpy(worse.name,position[0].name);
	worse.summa=position[0].summa;

	// ����� ����� ������� �������
	for(i=1;i<NC;i++)
		if (position[i].summa<worse.summa)
		{
			strcpy(worse.name,position[i].name);
			worse.summa=position[i].summa;
		}

	// ����� ���������� � ����� ������� �������
	Console::ForegroundColor=ConsoleColor::White;
	Console::BackgroundColor=ConsoleColor::DarkBlue;
	Console::CursorLeft=10;
	Console::CursorTop=15;
	printf("����� ������� �������: %s",worse.name);
	Console::CursorLeft=10;
	Console::CursorTop=16;
	printf("�����: %i ������",worse.summa);
	getch();
}

// ������� ��� ���������� ����������� ������� ������������� �������
void fast(struct z* position, int NC)
{
	int i;
	struct z best; // ��������� ��� �������� ���������� � ����� ������� ������� ������������ �������
	strcpy(best.name, position[0].name);
	best.time=position[0].time;

	//����� ����������� ������� ������������� �������
	for(i=1;i<NC;i++)
		if(position[i].time<best.time)
		{
			strcpy(best.name,position[i].name);
			best.time=position[i].time;
		}

	// ����� ���������� � ����� ������� �������
	Console::ForegroundColor=ConsoleColor::White;
	Console::BackgroundColor=ConsoleColor::DarkBlue;
	Console::CursorLeft=10;
	Console::CursorTop=15;
	printf("������� ����� �������� ������� %s",best.name);
	Console::CursorLeft=10;
	Console::CursorTop=16;
	printf("�� %i ����� ",best.time);
	getch();
}

// ������� ��� ���������� ������� ������� ������� 300 ������
void ovosch(struct z* position, int NC)
{
	int i;
	struct z* nt; // ��������� �� ���������

	Console::ForegroundColor=ConsoleColor::White;
	Console::BackgroundColor=ConsoleColor::DarkBlue;
	Console::Clear();
	printf("\n                ������ ������� ������� ������� 300 ������");
	printf("\n                  |----------------------|------------|");
	printf("\n                  |       �������        |   ����     |");
	printf("\n                  |----------------------|------------|");

	// ����� ������� ������� ������� 300 ������
	for(i=0,nt=position;i<NC;nt++,i++)
		if(nt->summa<300 && strcmp(nt->type,"�������")==0)
			printf("\n                  |%-22s| %ld ������ |",nt->name,nt->summa);
	printf("\n                  |----------------------|------------|");
	getch();
}

// ������� ��� ������� �������� � ���������� ������
void vstavka(struct z* position, char* pos, int NC, struct sp **spisok)
{
	int i;
	struct sp *nov, *nt, *z=0; // ��������� �� ���������
	Console::ForegroundColor=ConsoleColor::White;
	Console::BackgroundColor=ConsoleColor::DarkBlue;
	for(nt=*spisok; nt!=0 && strcmp(nt->pos,pos)<0; z=nt, nt=nt->sled); // ����� ������� ��� �������
		if(nt && strcmp(nt->pos,pos)==0) return; // ���� ������� ��� ����������, ������� �� �������
	nov =(struct sp *) malloc(sizeof(struct sp)); // �������� ������ �������� ������
	strcpy(nov->pos,pos);
	nov->sled=nt;
	nov->summa=0;
	nov->pred=z;

	// ������� �������� � ������
	for(i=0;i<NC;i++)
		if(strcmp(position[i].name,pos)==0)
			nov->summa+=position[i].summa;
	if(!z) *spisok=nov;
	else z->sled=nov;
	if(nt) nt->pred=nov;
	return;
}

// ������� ��� ������ ����������� ������
void alfalist(struct z* position, int NC, struct sp **spisok)
{
	int i;
	struct sp *nt, *z;
	Console::ForegroundColor=ConsoleColor::White;
	Console::BackgroundColor=ConsoleColor::DarkBlue;
	Console::Clear();
	printf("\n           ���������� ������ �������          ||          �������� ���������� ������");
	printf("\n|--------------------------------|------------||--------------------------------|------------|");
	printf("\n|       ������������ �������     |    ����    ||       ������������ �������     |    ����    |");
	printf("\n|--------------------------------|------------||--------------------------------|------------|");
	if(!*spisok)
		for(i=0;i<NC;i++)
			vstavka(position,position[i].name, NC, spisok);
	for(nt=*spisok;nt!=0;nt=nt->sled)
		printf("\n| %-30s | %d ������ ||", nt->pos,nt->summa);
	for(nt=*spisok, z=0; nt!=0; z=nt, nt=nt->sled)
		Console::CursorTop=5;
	for(nt=z, i=0; nt!=0; i++, nt=nt->pred)
	{
		Console::CursorLeft=48;
		printf(" %-30s | %d ������ |", nt->pos, nt->summa);
		Console::CursorTop+=1;
	}
	Console::CursorTop=20;
	printf("\n|--------------------------------|------------||--------------------------------|------------|");
	getch();
}

// ������� ��� ������ ���������
void diagram(struct z* position, int NC, struct sp **spisok) 
{ 
	struct sp *nt; 
	int len, i, NColor; 
	long sum = 0; 
	char str1[35]; 
	char str2[35]; 
	System::ConsoleColor Color; 
	Console::ForegroundColor=ConsoleColor::White; 
	Console::BackgroundColor=ConsoleColor::DarkBlue; 
	Console::Clear(); 
	printf("\n|---------------------------|------|--------------------------------------------|");
	printf("\n|   ������������ �������    |  %%%%  |                ���������                   |");
	printf("\n|---------------------------|------|--------------------------------------------|");

	// ����� ������������ ����
	for (i=0; i<NC; i++) 
		sum = sum+position[i].summa; 
	if(!*spisok) 
		for(i=0; i<NC; i++) 
			vstavka(position,position[i].name, NC, spisok); 
	Color=ConsoleColor::DarkRed; 
	NColor=0;
	for(nt=*spisok, i=3; nt!=0; nt = nt->sled, i++) 
	{ 
		 sprintf(str1, "| %-27s", nt->pos); 
		 sprintf(str2, "%3.lf%%", (nt->summa*100./sum)); 
		 Console::ForegroundColor=ConsoleColor::White; 
		 Console::BackgroundColor=ConsoleColor::DarkBlue; 
		 Console::CursorLeft=0; 
		 Console::CursorTop=i+1; 
		 printf(str1); 
		 Console::CursorLeft=28;
		 printf("|%s  |", str2); 
		 Console::CursorLeft=80;
		 printf("|");
		 Console::BackgroundColor=++Color; 
		 NColor++; 
		 Console::CursorLeft=36;
		 for(len=0; len<nt->summa*100./sum; len++) printf(" "); 
			if (NColor==6)
			{ 
				Color=ConsoleColor::DarkRed; 
				NColor=0;
			} 
	}
	Console::ForegroundColor=ConsoleColor::White; 
	Console::BackgroundColor=ConsoleColor::DarkBlue; 
	printf("\n|---------------------------|------|--------------------------------------------|");
	_getch(); 
	return; 
}

// ������� ��� ���������
void sravn(struct z* postion, int NC) 
{ 
	int i, j; 
	int srvn=0; 
	Console::ForegroundColor=ConsoleColor::White; 
	Console::BackgroundColor=ConsoleColor::DarkBlue;
	Console::Clear(); 
	printf("\n|--------------------|-----------|------|");
	printf("\n|������������ �������|    ���    | ���� |");
	printf("\n|--------------------|-----------|------|");
	for (i=0; i<NC; i++)
	{ 
		for (j=i+1; j<NC; j++)
		{ 
			if ((postion[i].summa == postion[j].summa) && (strcmp(postion[i].type, postion[j].type)==0))
			{ 
				printf("\n|%-19s |  %-9s| %3ld  | \n|%-19s |  %-9s| %3ld  |", postion[i].name, postion[i].type, postion[i].summa, postion[j].name, postion[j].type, postion[j].summa); 
				srvn++;
				break; 
			} 
		} 
		if (srvn == 1) break;
	}
	printf("\n|--------------------|-----------|------|");
	_getch(); 
}