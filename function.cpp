#include "head.h"

// Класс EquationRingSolver
/**
* Конструктор инициализирует строку кольца
*/
EquationRingSolver::EquationRingSolver(const string& ring)
    : mRing(ring) {}

/**
* Поиск уравнения
*/
string EquationRingSolver::FindEquation()
{
    const int ringSize = mRing.size();
    string result;

    // Перебор всех возможных длин для A, B и C
    for (int aLength = 1; aLength <= ringSize - 2; ++aLength)
    {
        for (int bLength = 1; bLength <= ringSize - aLength - 1; ++bLength)
        {
            const int cLength = ringSize - aLength - bLength;
            if (cLength < 1)
            {
                continue;
            }

            // Проверка всех стартовых позиций
            for (int start = 0; start < ringSize; ++start)
            {
                if (CheckCombination(start, aLength, bLength, cLength, result))
                {
                    return result;
                }
            }
        }
    }

    return "No";
}

/**
* Извлекает подстроку из кольца
*/
string EquationRingSolver::ExtractNumber(int start, int length) const
{
    string number;
    const int ringSize = mRing.size();

    for (int i = 0; i < length; ++i)
    {
        const int position = (start + i) % ringSize;
        number += mRing[position];
    }

    return number;
}

/**
* Проверка на ведущий ноль
*/
bool EquationRingSolver::HasLeadingZero(const string& number) const
{
    return number.size() > 1 && number[0] == '0';
}

/**
* Проверяет выполняется ли для данной комбинации A+B=C
*/
bool EquationRingSolver::CheckCombination(int aStart, int aLength,
    int bLength, int cLength, string& result) const
{
    const string aPart = ExtractNumber(aStart, aLength);
    const string bPart = ExtractNumber((aStart + aLength) % mRing.size(), bLength);
    const string cPart = ExtractNumber((aStart + aLength + bLength) % mRing.size(), cLength);

    // Проверка на ведущие нули
    if (HasLeadingZero(aPart) || HasLeadingZero(bPart) || HasLeadingZero(cPart))
    {
        return false;
    }

    try
    {
        BigInt a(aPart);
        BigInt b(bPart);
        BigInt c(cPart);
        BigInt sum = a + b;

        if (sum == c)
        {
            result = aPart + "+" + bPart + "=" + cPart;
            return true;
        }
    }
    catch (const invalid_argument&)
    {
        return false;
    }
    catch (const out_of_range&)
    {
        return false;
    }

    return false;
}

// Класс RingSolverApp
/**
* Основной цикл приложения
*/
void RingSolverApp::Run()
{
    PrintWelcomeMessage();

    string ring;
    while (true)
    {
        cout << "> ";
        getline(cin, ring);

        // Удаляем случайные пробелы в начале/конце
        ring.erase(0, ring.find_first_not_of(" \t"));
        ring.erase(ring.find_last_not_of(" \t") + 1);
        if (ValidateInput(ring))
        {
            break;
        }
    }

    cout << "\nВыполнение работы. . .\n" ;
    EquationRingSolver solver(ring);
    string result = solver.FindEquation();

    PrintResult(result);
    printCutePixelArt();
}

/**
* Приветственное сообщение
*/
void RingSolverApp::PrintWelcomeMessage() const
{
    cout << "========================================\n";
    cout << "    Числовое кольцо: решатель A+B=C     \n";
    cout << "========================================\n\n";
    cout << "Введите последовательность цифр кольца (без пробелов):\n";
    cout << "Правила ввода:\n";
    cout << "1. Только цифры без пробелов\n";
    cout << "2. Минимум 3 символа\n";
    cout << "Пример: 102030\n";
    cout << "(При больших входных данных может занять некоторое время для решения задачи)\n\n";
}

/**
* Выводит результат работы
*/
void RingSolverApp::PrintResult(const string& result) const
{
    cout << "\Результат:\n";
    cout << "----------------------------------------\n";

    if (result != "No")
    {
        cout << "Найдено уравнение: " << result << "\n";
    }
    else
    {
        cout << "No\n";
    }

    cout << "----------------------------------------\n";
}

/**
* Выводит милое изображение
*/
void RingSolverApp::printCutePixelArt() const
{
    cout << "  /\\_/\\  \n";
    cout << " ( o.o ) \n";
    cout << "  > ^ <   \n";
    cout << "  /   \\  \n";
    cout << " (     ) \n";
    cout << "  `~~~`  \n";
}

/**
* Проверка корректности ввода
*/
bool RingSolverApp::ValidateInput(const string& input) const
{
    if (input.empty())
    {
        cout << "Ошибка: пустой ввод\n";
        return false;
    }

    if (input.find(' ') != string::npos)
    {
        cout << "Ошибка: ввод не должен содержать пробелов\n";
        return false;
    }

    for (char c : input)
    {
        if (!isdigit(c))
        {
            cout << "Ошибка: ввод должен содержать только цифры\n";
            return false;
        }
    }

    if (input.length() < 3)
    {
        cout << "Ошибка: минимальная длина ввода - 3 цифры\n";
        return false;
    }

    return true;
}

// Класс BigInt
/**
* Конструктор преобразует строку в массив цифр
*/
BigInt::BigInt(const string& s)
{
    for (char c : s)
    {
        digits.push_back(c - '0'); // Конвертируем символ в цифру
    }
    reverse(digits.begin(), digits.end()); // Переворачиваем для удобства вычислений
}

/**
* Сложение двух больших чисел
*/
BigInt BigInt::operator+(const BigInt& other) const
{
    BigInt result("");
    int carry = 0; // Перенос в следующий разряд
    size_t max_len = max(digits.size(), other.digits.size());

    for (size_t i = 0; i < max_len || carry; ++i)
    {
        int sum = carry;
        if (i < digits.size()) sum += digits[i];
        if (i < other.digits.size()) sum += other.digits[i];

        result.digits.push_back(sum % 10);
        carry = sum / 10;
    }

    return result;
}

/**
* Сравнение чисел
*/
bool BigInt::operator==(const BigInt& other) const
{
    return digits == other.digits;
}

/**
* Преобразование числа в строку
*/
string BigInt::toString() const
{
    string s;
    for (auto it = digits.rbegin(); it != digits.rend(); ++it)
    {
        s += to_string(*it);
    }
    return s;
}
