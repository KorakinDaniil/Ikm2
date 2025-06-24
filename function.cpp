#include "head.h"

// Конструктор создает циклический список из строки цифр
CircularList::CircularList(const string& digits) : head(nullptr), size(0)
{
    if (digits.empty())
    {
        return;
    }

    // Создаем первый узел
    head = new Node(digits[0]);
    Node* current = head;
    size = 1;

    // Добавляем остальные цифры
    for (size_t i = 1; i < digits.size(); ++i)
    {
        current->next = new Node(digits[i]);
        current = current->next;
        size++;
    }

    // Замыкаем список в кольцо
    current->next = head;
}

// Деструктор освобождает память
CircularList::~CircularList()
{
    if (!head)
    {
        return;
    }

    Node* current = head;
    do
    {
        Node* temp = current;
        current = current->next;
        delete temp;
    } while (current != head);
}

// Возвращает указатель на начальный узел
Node* CircularList::getHead() const
{
    return head;
}

// Возвращает количество цифр в кольце
int CircularList::getSize() const
{
    return size;
}

// Извлекает число заданной длины, начиная с указанного узла
string CircularList::extractNumber(Node* start, int length) const
{
    string num;
    Node* current = start;

    // Собираем цифры в строку
    for (int i = 0; i < length; ++i)
    {
        num += current->digit;
        current = current->next;
    }
    return num;
}

// Перемещает указатель на заданное количество узлов вперед
Node* CircularList::advance(Node* node, int steps) const
{
    while (steps-- > 0)
    {
        node = node->next;
    }
    return node;
}

// Основной метод решения
string RingSolver::Solve(const string& digits)
{
    // Создание циклического списка цифр
    CircularList ring(digits);

    // Перебор всех возможных комбинаций длин A, B и C
    for (int aLen = 1; aLen <= ring.getSize() - 2; ++aLen)
    {
        for (int bLen = 1; bLen <= ring.getSize() - aLen - 1; ++bLen)
        {
            int cLen = ring.getSize() - aLen - bLen;
            if (cLen < 1)
            {
                continue; // Пропускаем невозможные варианты
            }

            // Проверка всех стартовых позиций в кольце
            for (int pos = 0; pos < ring.getSize(); ++pos)
            {
                // Извлечение чисел A, B, C из кольца
                auto* current = ring.advance(ring.getHead(), pos);
                string a = ring.extractNumber(current, aLen);

                current = ring.advance(current, aLen);
                string b = ring.extractNumber(current, bLen);

                current = ring.advance(current, bLen);
                string c = ring.extractNumber(current, cLen);

                // Проверка чисел и суммы
                if (!a.empty() && !b.empty() && !c.empty() && // Не пустые строки
                    !(a.size() > 1 && a[0] == '0') && // Нет ведущих нулей в A
                    !(b.size() > 1 && b[0] == '0') && // Нет ведущих нулей в B
                    !(c.size() > 1 && c[0] == '0')) // Нет ведущих нулей в C
                {
                    // Быстрое преобразование строк в числа
                    int numA = 0, numB = 0, numC = 0;
                    for (char ch : a)
                        {
                            numA = numA * 10 + (ch - '0');
                        }
                    for (char ch : b)
                        {
                            numB = numB * 10 + (ch - '0');
                        }
                    for (char ch : c)
                        {
                            numC = numC * 10 + (ch - '0');
                        }

                    // Основная проверка уравнения
                    if (numA + numB == numC)
                    {
                        return a + "+" + b + "=" + c;
                    }
                }
            }
        }
    }
    return "No";
}

// Главный метод, запускающий приложение
void RingSolverUI::Run()
{
    PrintWelcomeMessage();

    string input = GetValidInput();

    cout << "\nВыполнение. . .\n";

    string result = RingSolver::Solve(input);

    PrintResult(result);

    PrintCutePixelArt();
}

// Вывод приветствия и инструкции
void RingSolverUI::PrintWelcomeMessage() const
{
    cout << "========================================\n";
    cout << "    Числовое кольцо: решатель A+B=C     \n";
    cout << "========================================\n\n";
    cout << "Введите последовательность цифр кольца (без пробелов):\n";
    cout << "Правила ввода:\n";
    cout << "1. Только цифры без пробелов\n";
    cout << "2. Минимум 3 символа, максимум 1000\n";
    cout << "Пример: 102030\n";
    cout << "(При больших входных данных решение может занять некоторое время)\n\n";
}

// Ввод пользователя
string RingSolverUI::GetValidInput() const
{
    string input;
    while (true)
    {
        cout << "> ";
        getline(cin, input);

        // Удаление всех пробелов
        input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());

        if (ValidateInput(input))
        {
            break;
        }
    }
    return input;
}

// Проверка корректность ввода
bool RingSolverUI::ValidateInput(const string& input) const
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

    if (input.length() > 1000)
    {
        cout << "Ошибка: максимальная длина ввода не более 1000 цифр\n";
        return false;
    }

    return true;
}

// Выводит результат решения
void RingSolverUI::PrintResult(const string& result) const
{
    cout << "\nРезультат:\n";
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

// Выводит милое изображение
void RingSolverUI::PrintCutePixelArt() const
{
    cout << "  /\\_/\\  \n";
    cout << " ( o.o ) \n";
    cout << "  > ^ <   \n";
    cout << "  /   \\  \n";
    cout << " (     ) \n";
    cout << "  `~~~`  \n";
}
