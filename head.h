#ifndef ConsoleApplication3
#define ConsoleApplication3

#include <iostream>

#include <algorithm>
#include <string>
#include <vector>

#include <Windows.h>

using namespace std;

/**
* Класс для решения задачи поиска уравнения A+B=C в числовом кольце
*/
class EquationRingSolver
{
public:
    /**
    * Конструктор класса
    * ring строка с цифрами кольца
    */
    explicit EquationRingSolver(const string& ring);

    /**
    * Основной метод поиска уравнения
    * return строка с уравнением или "No" если решение не найдено
    */
    string FindEquation();

private:
    /**
    * Извлекает число из кольца
    * start начальная позиция
    * length длина числа
    * return строка с числом
    */
    string ExtractNumber(int start, int length) const;

    /**
    * Проверяет наличие ведущего нуля
    * number строка с числом
    * return true если есть ведущий ноль
    */
    bool HasLeadingZero(const string& number) const;

    /**
    * Проверяет конкретную комбинацию чисел
    * aStart начальная позиция числа A
    * aLength длина числа A
    * bLength длина числа B
    * cLength длина числа C
    * result ссылка для сохранения результата
    * return true если комбинация верна A+B=C
    */
    bool CheckCombination(int aStart, int aLength,
        int bLength, int cLength, string& result) const;

    const string mRing;// Строка с цифрами кольца
};

/**
 * Класс для управления пользовательским интерфейсом приложения
 */
class RingSolverApp {
public:
    /**
    * Запускает основной цикл приложения
    */
    void Run();

private:
    /**
    * Выводит приветственное сообщение
    */
    void PrintWelcomeMessage() const;

    /**
    * Выводит результат работы
    * result строка с результатом
    */
    void PrintResult(const string& result) const;

    /**
    * Выводит милое изображение
    */
    void printCutePixelArt() const;

    /**
    * Проверяет корректность ввода
    * input строка для проверки
    * return true если ввод корректен
    */
    bool ValidateInput(const string& input) const;
};

/**
* Класс для работы с целыми числами произвольной длины
* Хранит цифры числа в виде вектора (в обратном порядке)
*/
class BigInt
{
public:
    /**
    * Конструктор из строки
    * s строка, содержащая только цифры
    */
    BigInt(const string& s);

    /**
    * Оператор сложения двух больших чисел
    * other второе слагаемое
    * return результат сложения
    */
    BigInt operator+(const BigInt& other) const;

    /**
    * Оператор сравнения на равенство
    * other число для сравнения
    * return true если числа равны
    */
    bool operator==(const BigInt& other) const;

    /**
    * Преобразование числа в строку
    * return строковое представление числа
    */
    string toString() const;

private:
    vector<int> digits;// Цифры числа (хранятся в обратном порядке)
};

#endif
