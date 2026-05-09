#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int SIZE = 100;

struct Plane
{
    int flight;
    char model[20];
    char board[20];
    int point;
};

void outputBeforeSort(Plane planes[], int n);
bool input(Plane planes[], int& n);
void makeIndex(int index[], int n);
void sortIndex(Plane planes[], int index[], int n);
void output(Plane planes[], int index[], int n);
bool isNumber(char s[]);
bool isText(char s[]);

int main()
{
    setlocale(LC_ALL, "Russian");

    Plane planes[SIZE];
    int index[SIZE];
    int n;

    if (input(planes, n))
    {
        outputBeforeSort(planes, n);

        makeIndex(index, n);

        sortIndex(planes, index, n);

        output(planes, index, n);
    }

    return 0;
}

bool isNumber(char s[])
{
    if (strlen(s) == 0)
    {
        return false;
    }

    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] < '0' || s[i] > '9')
        {
            return false;
        }
    }

    return true;
}

bool isText(char s[])
{
    if (strlen(s) == 0)
    {
        return false;
    }

    return true;
}

bool input(Plane planes[], int& n)
{
    ifstream fin("Board.txt");

    if (!fin)
    {
        cout << "Ошибка: файл не найден" << endl;
        return false;
    }

    char nStr[20];

    fin >> nStr;

    if (fin.fail())
    {
        cout << "Ошибка: файл пустой" << endl;
        fin.close();
        return false;
    }

    if (!isNumber(nStr))
    {
        cout << "Ошибка: количество записей должно быть числом" << endl;
        fin.close();
        return false;
    }

    n = atoi(nStr);

    if (n <= 0 || n > SIZE)
    {
        cout << "Ошибка: некорректное количество записей" << endl;
        fin.close();
        return false;
    }

    char flightStr[20];
    char pointStr[20];

    for (int i = 0; i < n; i++)
    {
        fin >> flightStr;
        fin >> planes[i].model;
        fin >> planes[i].board;
        fin >> pointStr;

        if (fin.fail())
        {
            cout << "Ошибка: недостаточно данных в записи № " << i + 1 << endl;
            fin.close();
            return false;
        }

        if (!isNumber(flightStr))
        {
            cout << "Ошибка: номер рейса в записи № " << i + 1 << " должен быть числом" << endl;
            fin.close();
            return false;
        }

        if (!isText(planes[i].model))
        {
            cout << "Ошибка: пустая марка самолета в записи № " << i + 1 << endl;
            fin.close();
            return false;
        }

        if (!isText(planes[i].board))
        {
            cout << "Ошибка: пустой бортовой номер в записи № " << i + 1 << endl;
            fin.close();
            return false;
        }

        if (!isNumber(pointStr))
        {
            cout << "Ошибка: пункт прибытия в записи № " << i + 1 << " должен быть числом" << endl;
            fin.close();
            return false;
        }

        planes[i].flight = atoi(flightStr);
        planes[i].point = atoi(pointStr);

        if (planes[i].flight <= 0)
        {
            cout << "Ошибка: номер рейса должен быть положительным" << endl;
            fin.close();
            return false;
        }

        if (planes[i].point <= 0)
        {
            cout << "Ошибка: пункт прибытия должен быть положительным" << endl;
            fin.close();
            return false;
        }
    }

    fin.close();

    return true;
}

void makeIndex(int index[], int n)
{
    for (int i = 0; i < n; i++)
    {
        index[i] = i;
    }
}

void sortIndex(Plane planes[], int index[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (planes[index[j]].flight >
                planes[index[j + 1]].flight)
            {
                int temp = index[j];

                index[j] = index[j + 1];

                index[j + 1] = temp;
            }
        }
    }
}

void output(Plane planes[], int index[], int n)
{
    cout << "Рейсы после сортировки:\n\n";

    for (int i = 0; i < n; i++)
    {
        int k = index[i];

        cout << planes[k].flight << " ";
        cout << planes[k].model << " ";
        cout << planes[k].board << " ";
        cout << planes[k].point << endl;
    }
}

void outputBeforeSort(Plane planes[], int n)
{
    cout << "Рейсы до сортировки:\n\n";

    for (int i = 0; i < n; i++)
    {
        cout << planes[i].flight << " ";
        cout << planes[i].model << " ";
        cout << planes[i].board << " ";
        cout << planes[i].point << endl;
    }

    cout << endl;
}