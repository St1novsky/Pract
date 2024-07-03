 // G_zad1.cpp: главный файл проекта.

#include "stdafx.h" // подключение библиотек си++
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
#include <clocale>

using namespace std; // Использование пространств имен
using namespace System; //Использование пространства имен библиотеки Windows Forms в С++/CLI
using namespace System::IO; //Использование пространства имен для ввода-вывода в библиотеке Windows Forms в С++/CLI

// Определение констант для клавиш
#define ENTER 13 
#define ESC 27
#define UP 72
#define DOWN 80
#define HOME 71
#define END 79 

int NC; // Количество позиций в меню

// Структура для хранения информации о позиции меню
struct z {
	char name[30]; // Название позиции
	char rarity[10]; // Частота заказов 
	long summa; // Цена позиции
	char type[11]; // Тип позиции
	int time; // Время приготовления
};
// Структура для двусвязного списка
struct sp {
	char pos[30]; // Название позиции
	long summa; // Цена позиции	
	struct sp* sled; //указатель на следующий элемент
	struct sp* pred; // указатель на предыдущий элемент
} *spisok;

int menu(int);
void minim(struct z*, int NC); // Функция для нахождения самой дешевой позиции
void fast(struct z*, int NC); // Функция для нахождения кратчайшего времени приготовления позиции
void ovosch(struct z*, int NC); // Функция для нахождения овощных позиций дешевле 300 рублей
void alfalist(struct z*, int NC, struct sp **spisok); // Функция для вывода алфавитного списка
void vstavka(struct z*, char*, int NC, struct sp **spisok); // Функция для вставки элемента в двусвязный список
void diagram(struct z*, int NC, struct sp **spisok); // Функция для вывода диаграммы
void sravn(struct z*, int NC); // Функция для сравнения

// Основная функция программы
int main(array<System::String ^> ^args)
{
	int i,n; // Объявление переменных i и n
	FILE *in; // Объявление указателя на файл
	struct z *position;
	struct sp *spisok = 0;

	// Определение массива строк меню
	char dan[7][55]={
		"Какая самая дешевая позиция в меню?                   ",
		"Какой вареник мне принесут быстрее?		         ",
		"Какие овощные вареники дешевле 300 рублей?            ",
		"Альфалист                                             ",
		"Диаграмма                                             ",
		"Первое совпадение                                     ",
		"Выход                                                 "
	};
	char BlankLine[ ]="                                                        "; // Пустая строка
	setlocale(LC_CTYPE,"Russian"); // Установка локали для работы с русским языком
	Console::CursorVisible::set(false); // Скрытие курсора
	Console::BufferHeight=Console::WindowHeight; // Установка высоты буфера консоли
	Console::BufferWidth=Console::WindowWidth; // Установка ширины буфера консол

	// Открытие файла с меню
	if((in=fopen("Menu.dat","r"))==NULL)
	{
		printf("\nФайл Menu.dat не открыт !"); // Вывод сообщения об ошибке, если файл не удалось открыть
		getch(); exit(1); // Завершение программы с ошибкой
	}
	fscanf(in,"%d",&NC); // Чтение количества позиций в меню из файла
	position=(struct z*)malloc(NC*sizeof(struct z)); // Выделение памяти под массив позиций

	// Вывод заголовка таблицы
	printf("\n|---------------------------|---------|-------|---------|----------|");
	printf("\n|   Наименование позиции    | Частота | Цена  |   Тип   |  Время   |");
	printf("\n|---------------------------|---------|-------|---------|----------|");

	
	for(i=0;i<NC;i++)
		fscanf(in,"%s%s%d%s%d",position[i].name,
		position[i].rarity, &position[i].summa, position[i].type, &position[i].time); // Чтение данных из файла
	for(i=0;i<NC;i++)
		printf("\n| %-25s | %-7s |  %-4d | %-7s | %2d-Минут |",
		position[i].name, position[i].rarity, position[i].summa, position[i].type, position[i].time); // Вывод данных из файла
	printf("\n|---------------------------|---------|-------|---------|----------|");
		getch(); // Ожидание нажатия клавиши

	// Бесконечный цикл для работы с меню
	while(1)
	{
		// Установка цвета и очистка консоли
		Console::ForegroundColor=ConsoleColor::White;  // Установка цвета текста в консоли
		Console::BackgroundColor=ConsoleColor::DarkBlue; // Установка цвета фона в консоли
		Console::Clear(); // Очистка консоли

		// Установка цвета консоли (после очистки)
		Console::ForegroundColor=ConsoleColor::White; 
		Console::BackgroundColor=ConsoleColor::Blue;
		Console::CursorLeft=10; // Установка позиции курсора в консоли
		Console::CursorTop=4; // Установка позиции курсора в консоли
		printf(BlankLine); // Вывод пустой строки

		// Вывод пунктов меню
		for(i=0;i<7;i++)
		{
			Console::CursorLeft=10; // Перемещение позиции курсора в консоли
			Console::CursorTop=i+5; // Перемещение позиции курсора в консоли
			printf(" %s ",dan[i]); // Вывод пункта меню
}
		Console::CursorLeft=10; // Установка позиции курсора в консоли
		Console::CursorTop=12; // Установка позиции курсора в консоли
		printf(BlankLine); // Вывод пустой строки

		// Обработка выбора в меню
		n=menu(7); 
		switch(n) 
		{
		case 1: minim(position, NC); break; // Вызов функции минимальной цены
		case 2: fast(position, NC); break; // Вызов функции кратчайшего времени приготовления позиции
		case 3: ovosch(position, NC); break; // Вызов функции овощных позиций дешевле 300 рублей
		case 4: alfalist(position, NC, &spisok); break; // Вызов функции алфавитного списка
		case 5: diagram(position, NC, &spisok); break; // Вызов функции диаграммы
		case 6: sravn(position, NC);break; // Вызов функции сравнения
		case 7: exit(0); // Выход из программы
		}
	} // конец while(1)...
return 0;
} // конец main()

// Функция для обработки меню
int menu(int n)
{
	int y1=0,y2=n-1;
	char c=1;

	// Определение массива строк меню
	char dan[7][55]={
		"Какая самая дешевая позиция в меню?                   ",
		"Какой вареник мне принесут быстрее?		         ",
		"Какие овощные вареники дешевле 300 рублей?            ",
		"Альфалист                                             ",
		"Диаграмма                                             ",
		"Первое совпадение                                     ",
		"Выход                                                 "
	};
	while (c!=ESC)
	{
		switch(c) {
		case DOWN: y2=y1; y1++; break; // Переход к нижнему пункту меню при нажатии клавиши вниз
		case UP: y2=y1; y1--; break; // Переход к верхнему пункту меню при нажатии клавиши вверх
		case ENTER: return y1+1; // Выбор пункта меню при нажатии клавиши Enter
		case HOME: y2 = y1; y1 = 0; break; // Переход к первому пункту меню при нажатии Home
        case END: y2 = y1; y1 = n - 1; break; // Переход к последнему пункту меню при нажатии End

	}
	// Обработка выхода за границы меню
	if(y1>n-1){y2=n-1;y1=0;} // Если вышли за пределы меню снизу, переход к первому пункту
	if(y1<0) {y2=0;y1=n-1;} // Если вышли за пределы меню сверху, переход к последнему пункту

	Console::ForegroundColor=ConsoleColor::Cyan; // Установка цвета текста для выделенного пункта меню
	Console::BackgroundColor=ConsoleColor::DarkBlue; // Установка цвета фона для выделенного пункта меню
	Console::CursorLeft=11; // Перемещение позиции курсора в консоли
	Console::CursorTop=y1+5; // Перемещение позиции курсора в консоли
	printf("%s",dan[y1]);
	Console::ForegroundColor=ConsoleColor::White; // Возвращаем цвет текста для пункта меню
	Console::BackgroundColor=ConsoleColor::Blue; // Возвращаем цвет фона для пункта меню
	Console::CursorLeft=11; // Перемещение позиции курсора в консоли
	Console::CursorTop=y2+5; // Перемещение позиции курсора в консоли
	printf("%s",dan[y2]);
	c=getch(); // Ожидание нажатия клавиши
	} // конец while(c!=ESC)...
exit(0);
}
// Функция для нахождения самой дешевой позиции
void minim(struct z* position, int NC)
{
	int i;
	struct z worse; // Структура для хранения информации о самой дешевой позиции
	strcpy(worse.name,position[0].name);
	worse.summa=position[0].summa;

	// Поиск самой дешевой позиции
	for(i=1;i<NC;i++)
		if (position[i].summa<worse.summa)
		{
			strcpy(worse.name,position[i].name);
			worse.summa=position[i].summa;
		}

	// Вывод информации о самой дешевой позиции
	Console::ForegroundColor=ConsoleColor::White;
	Console::BackgroundColor=ConsoleColor::DarkBlue;
	Console::CursorLeft=10;
	Console::CursorTop=15;
	printf("Самый дешевый вареник: %s",worse.name);
	Console::CursorLeft=10;
	Console::CursorTop=16;
	printf("Стоит: %i рублей",worse.summa);
	getch();
}

// Функция для нахождения кратчайшего времени приготовления позиции
void fast(struct z* position, int NC)
{
	int i;
	struct z best; // Структура для хранения информации о самом быстром времени пригтовления позиции
	strcpy(best.name, position[0].name);
	best.time=position[0].time;

	//Поиск кратчайшего времени приготовления позиции
	for(i=1;i<NC;i++)
		if(position[i].time<best.time)
		{
			strcpy(best.name,position[i].name);
			best.time=position[i].time;
		}

	// Вывод информации о самой быстрой позиции
	Console::ForegroundColor=ConsoleColor::White;
	Console::BackgroundColor=ConsoleColor::DarkBlue;
	Console::CursorLeft=10;
	Console::CursorTop=15;
	printf("Быстрее всего принесут вареник %s",best.name);
	Console::CursorLeft=10;
	Console::CursorTop=16;
	printf("За %i Минут ",best.time);
	getch();
}

// Функция для нахождения овощных позиций дешевле 300 рублей
void ovosch(struct z* position, int NC)
{
	int i;
	struct z* nt; // Указатель на структуру

	Console::ForegroundColor=ConsoleColor::White;
	Console::BackgroundColor=ConsoleColor::DarkBlue;
	Console::Clear();
	printf("\n                Список овощных позиций дешевле 300 рублей");
	printf("\n                  |----------------------|------------|");
	printf("\n                  |       Позиция        |   Цена     |");
	printf("\n                  |----------------------|------------|");

	// Поиск овощных позиций дешевле 300 рублей
	for(i=0,nt=position;i<NC;nt++,i++)
		if(nt->summa<300 && strcmp(nt->type,"Овощной")==0)
			printf("\n                  |%-22s| %ld Рублей |",nt->name,nt->summa);
	printf("\n                  |----------------------|------------|");
	getch();
}

// Функция для вставки элемента в двусвязный список
void vstavka(struct z* position, char* pos, int NC, struct sp **spisok)
{
	int i;
	struct sp *nov, *nt, *z=0; // Указатели на структуры
	Console::ForegroundColor=ConsoleColor::White;
	Console::BackgroundColor=ConsoleColor::DarkBlue;
	for(nt=*spisok; nt!=0 && strcmp(nt->pos,pos)<0; z=nt, nt=nt->sled); // Поиск позиции для вставки
		if(nt && strcmp(nt->pos,pos)==0) return; // Если элемент уже существует, выходим из функции
	nov =(struct sp *) malloc(sizeof(struct sp)); // Создание нового элемента списка
	strcpy(nov->pos,pos);
	nov->sled=nt;
	nov->summa=0;
	nov->pred=z;

	// Вставка элемента в список
	for(i=0;i<NC;i++)
		if(strcmp(position[i].name,pos)==0)
			nov->summa+=position[i].summa;
	if(!z) *spisok=nov;
	else z->sled=nov;
	if(nt) nt->pred=nov;
	return;
}

// Функция для вывода алфавитного списка
void alfalist(struct z* position, int NC, struct sp **spisok)
{
	int i;
	struct sp *nt, *z;
	Console::ForegroundColor=ConsoleColor::White;
	Console::BackgroundColor=ConsoleColor::DarkBlue;
	Console::Clear();
	printf("\n           Алфавитный список позиций          ||          Обратный алфавитный список");
	printf("\n|--------------------------------|------------||--------------------------------|------------|");
	printf("\n|       Наименование позиции     |    Цена    ||       Наименование позиции     |    Цена    |");
	printf("\n|--------------------------------|------------||--------------------------------|------------|");
	if(!*spisok)
		for(i=0;i<NC;i++)
			vstavka(position,position[i].name, NC, spisok);
	for(nt=*spisok;nt!=0;nt=nt->sled)
		printf("\n| %-30s | %d Рублей ||", nt->pos,nt->summa);
	for(nt=*spisok, z=0; nt!=0; z=nt, nt=nt->sled)
		Console::CursorTop=5;
	for(nt=z, i=0; nt!=0; i++, nt=nt->pred)
	{
		Console::CursorLeft=48;
		printf(" %-30s | %d Рублей |", nt->pos, nt->summa);
		Console::CursorTop+=1;
	}
	Console::CursorTop=20;
	printf("\n|--------------------------------|------------||--------------------------------|------------|");
	getch();
}

// Функция для вывода диаграммы
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
	printf("\n|   Наименование позиции    |  %%%%  |                Диаграмма                   |");
	printf("\n|---------------------------|------|--------------------------------------------|");

	// Поиск максимальной цены
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

// Функция для сравнения
void sravn(struct z* postion, int NC) 
{ 
	int i, j; 
	int srvn=0; 
	Console::ForegroundColor=ConsoleColor::White; 
	Console::BackgroundColor=ConsoleColor::DarkBlue;
	Console::Clear(); 
	printf("\n|--------------------|-----------|------|");
	printf("\n|Наименование позиции|    Тип    | Цена |");
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