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
bool errors(ifstream& fin, int n);

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

bool input(Plane planes[], int& n)
{
    ifstream fin("Board.txt");

    fin >> n;

    if (errors(fin, n))
    {
        return false;
    }

    for (int i = 0; i < n; i++)
    {
        fin >> planes[i].flight;
        fin >> planes[i].model;
        fin >> planes[i].board;
        fin >> planes[i].point;

        if (fin.fail())
        {
            cout << "Ошибка чтения данных" << endl;
            fin.close();
            return false;
        }
    }

    fin.close();

    return true;
}

bool errors(ifstream& fin, int n)
{
    if (!fin)
    {
        cout << "Файл не найден" << endl;
        return true;
    }

    if (fin.fail())
    {
        cout << "Ошибка чтения количества записей" << endl;
        return true;
    }

    if (n <= 0 || n > SIZE)
    {
        cout << "Некорректное количество записей" << endl;
        return true;
    }

    return false;
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