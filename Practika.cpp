/******************************************************************
 * File Name: Practika
 * Project Type: Win32 Console Application
 * Project Name: MAI.practice
 * Language: C++, Microsoft Visual Studio 2022
 *
 * Programmer (1): Гривцова Арина Александровна
 *
 * Created: 01.05.2025
 * Last Revision: 09.05.2025
 * Modified by:
 *
 * Comment:
 * Код для дисциплины "ознакомительная практика", "структуры"
 * Вариант 10
 *
 *
 ******************************************************************/
#include <iostream> 
#include <fstream>  
#include <cstring>  

using namespace std;
const int SIZE = 100; // Максимальное количество записей о самолетах

// Структура хранит данные об одном самолете
struct Plane
{
    int flight;      // Номер рейса
    char model[20];  // Марка летательного аппарата
    char board[20];  // Бортовой номер самолета
    int point;       // Пункт прибытия
};

// Функция выводит исходные данные до сортировки. Нужна для эхо-печати, чтобы показать, какие данные были считаны из файла.
void outputBeforeSort(Plane planes[], int n);
// Функция считывает данные из файла Board.txt. Также выполняет основные проверки входных данных.
bool input(Plane planes[], int& n);
// Функция создает индексный массив. В index записываются номера элементов массива planes: 0, 1 и т.д.
void makeIndex(int index[], int n);
// Функция сортирует индексный массив методом пузырька.
void sortIndex(Plane planes[], int index[], int n);
// Функция выводит данные после сортировки. Вывод идет не напрямую из planes, а через индексный массив index.
void output(Plane planes[], int index[], int n);
// Функция проверяет, состоит ли строка только из цифр. Используется для проверки номера рейса, пункта прибытия и количества записей.
bool isNumber(char s[]);
// Функция проверяет, что строка не пустая. Используется для проверки марки самолета и бортового номера.
bool isText(char s[]);

int main()
{
    setlocale(LC_ALL, "Russian"); 

    Plane planes[SIZE]; // Основной массив структур, где хранятся самолеты
    int index[SIZE];    // Индексный массив для сортировки
    int n;              // Количество записей в файле

    // Если данные из файла считались без ошибок, то выполняется эхо-печать, создание индексов, сортировка и вывод.
    if (input(planes, n))
    {
        outputBeforeSort(planes, n); // Показываем данные до сортировки
        makeIndex(index, n); // Создаем индексный массив
        sortIndex(planes, index, n); // Сортируем только индексный массив
        output(planes, index, n); // Выводим данные в отсортированном порядке
    }

    return 0;
}

// Функция проверяет, является ли строка числом
bool isNumber(char s[])
{
    // Если строка пустая, значит это не число
    if (strlen(s) == 0)
    {
        return false;
    }
    // Проверяем каждый символ строки
    for (int i = 0; s[i] != '\0'; i++)
    {
        // Если символ не находится в диапазоне от '0' до '9', значит строка содержит не только цифры
        if (s[i] < '0' || s[i] > '9')
        {
            return false;
        }
    }

    // Если все символы являются цифрами, строка считается числом
    return true;
}

// Функция проверяет, что строка не пустая
bool isText(char s[])
{
    // strlen возвращает длину строки. Если длина равна 0, значит строка пустая.
    if (strlen(s) == 0)
    {
        return false;
    }

    return true;
}

// Функция считывает данные из файла и проверяет их корректность
bool input(Plane planes[], int& n)
{
    ifstream fin("Board.txt"); // Открываем файл для чтения

    // Если файл не открылся, значит он отсутствует или находится не в той папке, откуда запускается программа.
    if (!fin)
    {
        cout << "Ошибка: файл не найден" << endl;
        return false;
    }

    char nStr[20]; // Количество записей сначала читаем как строку
        fin >> nStr; // Читаем первую строку файла

    // Если чтение не удалось, значит файл пустой
    if (fin.fail())
    {
        cout << "Ошибка: файл пустой" << endl;
        fin.close();
        return false;
    }

    // Проверяем, что количество записей записано числом
    if (!isNumber(nStr))
    {
        cout << "Ошибка: количество записей должно быть числом" << endl;
        fin.close();
        return false;
    }

    // Переводим строку в число
    n = atoi(nStr);

    // Проверяем, что количество записей входит в допустимый диапазон
    if (n <= 0 || n > SIZE)
    {
        cout << "Ошибка: некорректное количество записей" << endl;
        fin.close();
        return false;
    }

    char flightStr[20]; // Номер рейса временно читаем как строку
    char pointStr[20];  // Пункт прибытия временно читаем как строку

    // Считываем n записей из файла
    for (int i = 0; i < n; i++)
    {
        fin >> flightStr;
        fin >> planes[i].model;
        fin >> planes[i].board;
        fin >> pointStr;

        // Если не удалось считать все 4 поля, значит в записи не хватает данных.
        if (fin.fail())
        {
            cout << "Ошибка: недостаточно данных в записи № " << i + 1 << endl;
            fin.close();
            return false;
        }

        // Проверяем номер рейса. Он должен состоять только из цифр.
        if (!isNumber(flightStr))
        {
            cout << "Ошибка: номер рейса в записи № "
                << i + 1 << " должен быть числом" << endl;

            fin.close();
            return false;
        }

        // Проверяем марку самолета. Она не должна быть пустой.
        if (!isText(planes[i].model))
        {
            cout << "Ошибка: пустая марка самолета в записи № "
                << i + 1 << endl;

            fin.close();
            return false;
        }

        // Проверяем бортовой номер. Он не должен быть пустым.
        if (!isText(planes[i].board))
        {
            cout << "Ошибка: пустой бортовой номер в записи № "
                << i + 1 << endl;

            fin.close();
            return false;
        }

        // Проверяем пункт прибытия. Он тоже должен быть числом.
        if (!isNumber(pointStr))
        {
            cout << "Ошибка: пункт прибытия в записи № "
                << i + 1 << " должен быть числом" << endl;

            fin.close();
            return false;
        }

        // После проверок переводим строки в числа
        planes[i].flight = atoi(flightStr);
        planes[i].point = atoi(pointStr);

        // Номер рейса не может быть отрицательным или равным нулю
        if (planes[i].flight <= 0)
        {
            cout << "Ошибка: номер рейса должен быть положительным" << endl;

            fin.close();
            return false;
        }

        // Пункт прибытия тоже должен быть положительным числом
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

// Функция создает индексный массив
void makeIndex(int index[], int n)
{
    // Каждый элемент index хранит номер соответствующей записи в planes
    for (int i = 0; i < n; i++)
    {
        index[i] = i;
    }
}

// Функция выполняет индексную сортировку методом пузырька
void sortIndex(Plane planes[], int index[], int n)
{
    // Внешний цикл отвечает за количество проходов
    for (int i = 0; i < n - 1; i++)
    {
        // Внутренний цикл сравнивает соседние элементы
        for (int j = 0; j < n - i - 1; j++)
        {
            // Сравниваются номера рейсов через индексный массив. То есть мы смотрим не planes[j], а planes[index[j]].
            if (planes[index[j]].flight >
                planes[index[j + 1]].flight)
            {
                // Если порядок неправильный, то меняем местами только индексы.
                int temp = index[j];
                index[j] = index[j + 1];
                index[j + 1] = temp;
            }
        }
    }
}

// Функция выводит данные после сортировки
void output(Plane planes[], int index[], int n)
{
    cout << "Рейсы после сортировки:\n\n";

    // Вывод идет в порядке, который хранится в index
    for (int i = 0; i < n; i++)
    {
        // k — это номер элемента в массиве planes
        int k = index[i];

        cout << planes[k].flight << " ";
        cout << planes[k].model << " ";
        cout << planes[k].board << " ";
        cout << planes[k].point << endl;
    }
}

// Функция выводит данные в исходном порядке
void outputBeforeSort(Plane planes[], int n)
{
    cout << "Рейсы до сортировки:\n\n";

    // Здесь вывод идет напрямую из массива planes, поэтому порядок такой же, как в файле.
    for (int i = 0; i < n; i++)
    {
        cout << planes[i].flight << " ";
        cout << planes[i].model << " ";
        cout << planes[i].board << " ";
        cout << planes[i].point << endl;
    }

    cout << endl;
}
