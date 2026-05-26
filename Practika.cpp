/******************************************************************
 * File Name: Practika
 * Project Type: Win32 Console Application
 * Project Name: MAI.practice
 * Language: C++, Microsoft Visual Studio 2022
 *
 * Programmer (1): Гривцова Арина Александровна
 *
 * Created: 01.05.2026
 * Last Revision: 26.05.2026
 * Modified by:
 *
 * Comment:
 * Код для дисциплины "ознакомительная практика", "структуры"
 * Вариант 10
 *
 *
 ******************************************************************/


#define _CRT_SECURE_NO_WARNINGS
#include <iostream> //ввод и вывод
#include <fstream>//работа с файлами
#include <cstring>//работа со строками
using namespace std;

//глобальные константы
char FILE_NAME[50] = "Board.txt";

const int TEXT_SIZE = 30;
const int ERROR_SIZE = 200;


//структура самолета
struct Plane
{
    int flight; //номер рейса
    char model[TEXT_SIZE]; //модель самолета
    char board[TEXT_SIZE]; //бортовой номер
    int point; //пункт прибытия

    bool correct; //корректность записи
    char error[ERROR_SIZE]; //текст ошибки
};

//чтение количества записей
bool readN(const char fileName[], int& n);
//выделение памяти под структуры
Plane* create(int n);
//выделение памяти под индексный массив
int* createIndex(int n);
//освобождение памяти
void clear(Plane* planes, int* index);
//ввод данных из файла
void input(const char fileName[], Plane planes[], int n);
//создание индексного массива
void makeIndex(int index[], int n);
//индексная сортировка
void sort(Plane planes[], int index[], int n);
//вывод таблицы до сортировки
void printBefore(Plane planes[], int n);
//вывод таблицы после сортировки
void printAfter(Plane planes[], int index[], int n);
//вывод ошибок
void printErrors(Plane planes[], int n);
//проверка строки на число
bool isNumber(char s[]);
//перевод строки в число
int toInt(char s[]);
//проверка бортового номера
bool checkBoard(char board[]);
//добавление ошибки
void addError(Plane& plane, const char text[]);
//проверка смысловых ошибок
void checkErrors(Plane planes[], int n);

int main()
{
    setlocale(LC_ALL, "Russian");
    int n;
    //тесты для проверки программы
    strcpy(FILE_NAME, "Board.txt");

    //strcpy(FILE_NAME, "test_positive_01.txt");
    //strcpy(FILE_NAME, "test_positive_02.txt");
    //strcpy(FILE_NAME, "test_positive_03.txt");
    //strcpy(FILE_NAME, "test_positive_04.txt");
    //strcpy(FILE_NAME, "test_positive_05.txt");

    //strcpy(FILE_NAME, "test_negative_01.txt");
    //strcpy(FILE_NAME, "test_negative_02.txt");
    //strcpy(FILE_NAME, "test_negative_03.txt");
    //strcpy(FILE_NAME, "test_negative_04.txt");
    //strcpy(FILE_NAME, "test_negative_05.txt");
    //strcpy(FILE_NAME, "test_negative_06.txt");
    //strcpy(FILE_NAME, "test_negative_07.txt");
    //strcpy(FILE_NAME, "test_negative_08.txt");
    //strcpy(FILE_NAME, "test_negative_09.txt");
    //strcpy(FILE_NAME, "test_negative_10.txt");

    //проверка количества записей
    if (!readN(FILE_NAME, n))
    {
        return 0;
    }

    //динамическое выделение памяти
    Plane* planes = create(n);
    int* index = createIndex(n);
    //ввод данных
    input(FILE_NAME, planes, n);
    //проверка смысловых ошибок
    checkErrors(planes, n);
    //вывод ошибок
    printErrors(planes, n);
    //эхо-печать
    printBefore(planes, n);
    //создание индексов
    makeIndex(index, n);
    //индексная сортировка
    sort(planes, index, n);
    //вывод после сортировки
    printAfter(planes, index, n);
    //очистка памяти
    clear(planes, index);

    return 0;
}

//чтение количества записей
bool readN(const char fileName[], int& n)
{
    ifstream fin(fileName);
    //проверка открытия файла
    if (!fin)
    {
        cout << "ошибка: файл не найден" << endl;
        return false;
    }

    char nStr[TEXT_SIZE];
    fin >> nStr;

    //проверка пустого файла
    if (fin.fail())
    {
        cout << "ошибка: файл пустой" << endl;
        fin.close();
        return false;
    }

    //проверка количества записей
    if (!isNumber(nStr))
    {
        cout << "ошибка: количество записей должно быть числом" << endl;
        fin.close();
        return false;
    }
    n = toInt(nStr);
    //проверка диапазона
    if (n <= 0)
    {
        cout << "ошибка: количество записей должно быть больше нуля" << endl;
        fin.close();
        return false;
    }
    fin.close();
    return true;
}

//выделение памяти под структуры
Plane* create(int n)
{
    Plane* planes = new Plane[n];
    return planes;
}

//выделение памяти под индексный массив
int* createIndex(int n)
{
    int* index = new int[n];
    return index;
}

//освобождение памяти
void clear(Plane* planes, int* index)
{
    delete[] planes;
    delete[] index;
}

//ввод данных из файла
void input(const char fileName[], Plane planes[], int n)
{
    ifstream fin(fileName);

    char temp[TEXT_SIZE];
    //пропуск первой строки
    fin >> temp;
    //чтение записей
    for (int i = 0; i < n; i++)
    {
        char flightStr[TEXT_SIZE];
        char pointStr[TEXT_SIZE];

        //начальные значения
        planes[i].flight = 0;
        planes[i].point = 0;
        planes[i].model[0] = '\0';
        planes[i].board[0] = '\0';
        planes[i].correct = true;
        planes[i].error[0] = '\0';

        fin >> flightStr;
        fin >> planes[i].model;
        fin >> planes[i].board;
        fin >> pointStr;

        //проверка чтения строки
        if (fin.fail())
        {
            addError(planes[i], "недостаточно данных");
            fin.clear();
            break;
        }

        //проверка номера рейса
        if (!isNumber(flightStr))
        {
            addError(planes[i], "номер рейса не число");
        }
        else
        {
            planes[i].flight = toInt(flightStr);
            if (planes[i].flight <= 0)
            {
                addError(planes[i], "номер рейса <= 0");
            }
        }

        //проверка модели
        if (strlen(planes[i].model) == 0)
        {
            addError(planes[i], "пустая модель");
        }

        //проверка бортового номера
        if (!checkBoard(planes[i].board))
        {
            addError(planes[i], "неверный бортовой номер");
        }

        //проверка пункта прибытия
        if (!isNumber(pointStr))
        {
            addError(planes[i], "пункт прибытия не число");
        }
        else
        {
            planes[i].point = toInt(pointStr);
            if (planes[i].point <= 0)
            {
                addError(planes[i], "пункт прибытия <= 0");
            }
        }
    }
    fin.close();
}

//создание индексного массива
void makeIndex(int index[], int n)
{
    for (int i = 0; i < n; i++)
    {
        index[i] = i;
    }
}

//индексная сортировка
void sort(Plane planes[], int index[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            int left = index[j];
            int right = index[j + 1];
            //некорректные записи остаются в начале
            if (!planes[left].correct && planes[right].correct)
            {
                continue;
            }

            if (planes[left].correct && !planes[right].correct)
            {
                int temp = index[j];
                index[j] = index[j + 1];
                index[j + 1] = temp;
            }
            else
            {
                if (planes[left].flight > planes[right].flight)
                {
                    int temp = index[j];
                    index[j] = index[j + 1];
                    index[j + 1] = temp;
                }
            }
        }
    }
}

//вывод таблицы до сортировки
void printBefore(Plane planes[], int n)
{
    cout << "таблица до сортировки:" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << planes[i].flight << " ";
        cout << planes[i].model << " ";
        cout << planes[i].board << " ";
        cout << planes[i].point << endl;
    }

    cout << endl;
}

//вывод таблицы после сортировки
void printAfter(Plane planes[], int index[], int n)
{
    cout << "таблица после сортировки:" << endl;

    for (int i = 0; i < n; i++)
    {
        int k = index[i];
        cout << planes[k].flight << " ";
        cout << planes[k].model << " ";
        cout << planes[k].board << " ";
        cout << planes[k].point;
        //пометка некорректной записи
        if (!planes[k].correct)
        {
            cout << " [ошибка]";
        }
        cout << endl;
    }
}

//вывод ошибок
void printErrors(Plane planes[], int n)
{
    bool hasErrors = false;
    cout << "ошибки:" << endl;
    for (int i = 0; i < n; i++)
    {
        if (!planes[i].correct)
        {
            hasErrors = true;
            cout << "запись ";
            cout << i + 1;
            cout << ": ";
            cout << planes[i].error;
            cout << endl;
        }
    }

    //если ошибок нет
    if (!hasErrors)
    {
        cout << "ошибок нет" << endl;
    }

    cout << endl;
}

//проверка строки на число
bool isNumber(char s[])
{
    //пустая строка
    if (strlen(s) == 0)
    {
        return false;
    }
    //проверка всех символов
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] < '0' || s[i] > '9')
        {
            return false;
        }
    }
    return true;
}

//перевод строки в число
int toInt(char s[])
{
    int number = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        number = number * 10 + (s[i] - '0');
    }
    return number;
}

//проверка бортового номера
bool checkBoard(char board[])
{
    //длина должна быть 6:
    //B-1234
    if (strlen(board) != 6)
    {
        return false;
    }
    //проверка буквы
    if (board[0] != 'B')
    {
        return false;
    }
    //проверка дефиса
    if (board[1] != '-')
    {
        return false;
    }
    //проверка цифр
    for (int i = 2; i < 6; i++)
    {
        if (board[i] < '0' || board[i] > '9')
        {
            return false;
        }
    }
    return true;
}

//добавление ошибки
void addError(Plane& plane, const char text[])
{
    plane.correct = false;
    int i = strlen(plane.error);
    if (i != 0)
    {
        plane.error[i] = ';';
        plane.error[i + 1] = ' ';
        i = i + 2;
    }
    int j = 0;
    while (text[j] != '\0' && i < ERROR_SIZE - 1)
    {
        plane.error[i] = text[j];
        i++;
        j++;
    }
    plane.error[i] = '\0';
}

//проверка смысловых ошибок
void checkErrors(Plane planes[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            //одинаковые рейсы
            if (planes[i].flight == planes[j].flight
                && planes[i].flight != 0)
            {
                addError(planes[i], "повтор рейса");
                addError(planes[j], "повтор рейса");
            }
            //один борт - разные модели
            if (strcmp(planes[i].board,
                planes[j].board) == 0)
            {
                if (strcmp(planes[i].model,
                    planes[j].model) != 0)
                {
                    addError(planes[i],
                        "один борт у разных моделей");
                    addError(planes[j],
                        "один борт у разных моделей");
                }
            }
        }
    }
}
