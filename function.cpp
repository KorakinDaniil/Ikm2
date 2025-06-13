#include "head.h"

// Безопасный ввод числа
int getIntegerInput()
{
    string input;
    int num;
    bool valid = false;

    while (!valid)
    {
        cout << "Введите целое число: ";
        cin >> input;

        try
        {
            size_t pos;
            num = stoi(input, &pos);

            // Проверяем, что вся строка была преобразована
            if (pos == input.length())
            {
                valid = true;
            }
            else
            {
                cout << "Ошибка! Введите целое число без дополнительных символов." << endl;
            }
        }
        catch (const invalid_argument&)
        {
            cout << "Ошибка! Введите целое число." << endl;
        }
        catch (const out_of_range&)
        {
            cout << "Ошибка! Число слишком большое." << endl;
        }

        if (!valid)
        {
            cin.clear();
            cin.ignore();
        }
    }

    return num;
}

//1
// Преобразует символ операции в числовой код
int TreeOperands::operationToCode(char op)
{
    switch (op)
    {
    case '+': return -1;
    case '-': return -2;
    case '*': return -3;
    case '/': return -4;
    case '%': return -5;
    case '^': return -6;
    default: return 0;
    }
}

// Проверяет, является ли токен оператором
bool TreeOperands::isOperator(const string& token)
{
    return token.size() == 1 && tValidOps.find(token[0]) != string::npos;
}

// Рекурсивно строит дерево из префиксного выражения
TreeOperands::TreeNode* TreeOperands::buildTreeFromPrefix(const vector<string>& tokens, int& index)
{
    if (index >= tokens.size())
    {
        return nullptr;
    }

    string token = tokens[index++];
    TreeNode* node;

    if (isOperator(token))
    {
        node = new TreeNode(operationToCode(token[0]));
        node->tLeft = buildTreeFromPrefix(tokens, index);
        node->tRight = buildTreeFromPrefix(tokens, index);
    }
    else
    {
        node = new TreeNode(stoi(token));
    }

    return node;
}

// Вычисляет значение поддерева
int TreeOperands::evaluate(TreeNode* node)
{
    if (!node)
    {
        return 0;
    }

    if (node->tValue >= 0)
    {
        return node->tValue;
    }

    int leftVal = evaluate(node->tLeft);
    int rightVal = evaluate(node->tRight);

    switch (node->tValue)
    {
    case -1: return leftVal + rightVal;
    case -2: return leftVal - rightVal;
    case -3: return leftVal * rightVal;
    case -4:
    {
        if (rightVal == 0)
        {
            throw runtime_error("Деление на ноль");
        }
        return leftVal / rightVal;
    }
    case -5:
    {
        if (rightVal == 0)
        {
            throw runtime_error("Деление по модулю на ноль");
        }
        return leftVal % rightVal;
    }
    case -6:
    {
        if (leftVal == 0 && rightVal <= 0)
        {
            throw runtime_error("Недопустимая операция возведения в степень");
        }
        int result = 1;
        for (int i = 0; i < rightVal; ++i)
        {
            result *= leftVal;
        }
        return result;
    }
    default: return 0;
    }
}

// Преобразует дерево, заменяя поддеревья с нулевыми результатами
void TreeOperands::transformTree(TreeNode* node)
{
    if (!node)
    {
        return;
    }

    if (node->tValue < 0)// Это оператор
    {
        transformTree(node->tLeft);
        transformTree(node->tRight);

        int leftVal = 0, rightVal = 0;
        bool leftIsNum = false, rightIsNum = false;

        if (node->tLeft && node->tLeft->tValue >= 0)
        {
            leftVal = node->tLeft->tValue;
            leftIsNum = true;
        }
        if (node->tRight && node->tRight->tValue >= 0)
        {
            rightVal = node->tRight->tValue;
            rightIsNum = true;
        }

        if (leftIsNum && leftVal == 0)
        {
            delete node->tLeft;
            node->tLeft = nullptr;
            TreeNode* newRight = new TreeNode(evaluate(node->tRight));
            delete node->tRight;
            node->tRight = nullptr;
            node->tValue = newRight->tValue;
            delete newRight;
        }
        else if (rightIsNum && rightVal == 0)
        {
            delete node->tRight;
            node->tRight = nullptr;
            TreeNode* newLeft = new TreeNode(evaluate(node->tLeft));
            delete node->tLeft;
            node->tLeft = nullptr;
            node->tValue = newLeft->tValue;
            delete newLeft;
        }
    }
}

// Рекурсивно выводит дерево в понятном виде
void TreeOperands::printTree(TreeNode* node, int depth)
{
    if (!node)
    {
        return;
    }

    printTree(node->tRight, depth + 1);
    cout << string(depth * 4, ' ') << node->tValue << endl;
    printTree(node->tLeft, depth + 1);
}

// Рекурсивно освобождает память, занятую деревом
void TreeOperands::clearTree(TreeNode* node)
{
    if (!node)
    {
        return;
    }

    clearTree(node->tLeft);
    clearTree(node->tRight);
    delete node;
}

// Строит дерево из файла
void TreeOperands::buildFromFile(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        throw runtime_error("Невозможно открыть файл: " + filename);
    }

    vector<string> tokens;
    string token;
    while (file >> token)
    {
        tokens.push_back(token);
    }

    int index = 0;
    tRoot = buildTreeFromPrefix(tokens, index);
}

// Строит дерево из ввода пользователя
void TreeOperands::buildFromConsole()
{
    /*cout << "Введите префиксное выражение (операции: + - * / % ^, "
        << "операнды: 0-9):" << endl;
    string line;
    getline(cin, line);

    vector<string> tokens;
    stringstream ss(line);
    string token;
    while (ss >> token)
    {
        tokens.push_back(token);
    }

    int index = 0;
    tRoot = buildTreeFromPrefix(tokens, index);*/
    bool input_valid = false;

    while (!input_valid)
    {
        cout << "Введите префиксное выражение (операции: + - * / % ^, "
            << "операнды: 0-9):" << endl;
        string line;
        getline(cin, line);

        vector<string> tokens;
        stringstream ss(line);
        string token;
        bool tokens_valid = true;

        // Проверка каждого токена
        while (ss >> token && tokens_valid)
        {
            if (token.size() != 1)
            {
                tokens_valid = false;
                break;
            }

            // Проверка на оператор
            if (isOperator(token))
            {
                tokens.push_back(token);
                continue;
            }

            // Проверка на число
            if (isdigit(token[0]))
            {
                try
                {
                    size_t pos;
                    int num = stoi(token, &pos);
                    if (pos != token.length() || num < 0 || num > 9)
                    {
                        tokens_valid = false;
                    }
                    else
                    {
                        tokens.push_back(token);
                    }
                }
                catch (...)
                {
                    tokens_valid = false;
                }
                continue;
            }

            // Если ни оператор, ни число
            tokens_valid = false;
        }

        if (!tokens_valid)
        {
            cout << "Ошибка! Недопустимые символы в выражении. Используйте только "
                << tValidOps << " и цифры 0-9." << endl;
            continue;
        }

        // Проверка корректности префиксной записи
        try
        {
            int index = 0;
            tRoot = buildTreeFromPrefix(tokens, index);
            if (index != tokens.size())
            {
                throw runtime_error("Неверное количество элементов в выражении");
            }
            input_valid = true;
        }
        catch (const exception& e)
        {
            cout << "Ошибка в выражении: " << e.what()
                << ". Попробуйте снова." << endl;
            if (tRoot)
            {
                clearTree(tRoot);
                tRoot = nullptr;
            }
        }
    }
}

// Генерирует случайное дерево
void TreeOperands::buildRandom()
{
    srand(time(nullptr));
    int numNodes = rand() % 10 + 5; // От 5 до 14 узлов
    vector<string> tokens;

    for (int i = 0; i < numNodes; ++i)
    {
        if (rand() % 3 == 0)// 33% вероятность оператора
        {
            tokens.push_back(string(1, tValidOps[rand() % tValidOps.size()]));
        }
        else// 67% вероятность операнда (0-9)
        {
            tokens.push_back(to_string(rand() % 10));
        }
    }

    int index = 0;
    tRoot = buildTreeFromPrefix(tokens, index);
}

// Применяет преобразование дерева
void TreeOperands::transform()
{
    transformTree(tRoot);
}

// Выводит дерева
void TreeOperands::print()
{
    if (!tRoot)
    {
        cout << "Дерево пустое." << endl;
        return;
    }
    printTree(tRoot);
}

// Вычисление выражения
int TreeOperands::evaluateNode()
{
    if (!tRoot)
    {
        throw runtime_error("Дерево пустое");
    }
    return evaluate(tRoot);
}

// Возвращает указатель на корень дерева
TreeOperands::TreeNode* TreeOperands::getRoot()
{
    return tRoot;
}

//------------

//1
// Сортировка списка
void BubbleSortList(Nodee* nHead)
{
    if (!nHead) return;

    bool bSwapped;
    Nodee* nEnd = nullptr;
    do
    {
        bSwapped = false;
        Nodee* nCurrent = nHead;

        while (nCurrent->nNext != nEnd)
        {
            if (nCurrent->nData > nCurrent->nNext->nData)
            {
                swap(nCurrent->nData, nCurrent->nNext->nData);
                bSwapped = true;
            }
            nCurrent = nCurrent->nNext;
        }
        nEnd = nCurrent;
    } while (bSwapped);
}

// Создаёт двусвязный список на основе ввода пользователя
Nodee* CreateListFromInput()
{
    Nodee* nHead = nullptr;
    Nodee* nTail = nullptr;
    int nValue;
    int n;

    cout << "Введите кол-во элементы для списка:" << endl;
    n = getIntegerInput();

    cout << "Введите элементы для списка:" << endl;

    for (int i = 0; i < n; i++)
    {
        nValue = getIntegerInput();
        Nodee* nNewNode = new Nodee(nValue);

        if (!nHead)
        {
            nHead = nNewNode;
            nTail = nNewNode;
        }
        else
        {
            nTail->nNext = nNewNode;
            nNewNode->nPrev = nTail;
            nTail = nNewNode;
        }
    }

    //BubbleSortList(nHead);
    return nHead;
}

// Печатает элементы списка
void PrintList(Nodee* nHead)
{
    Nodee* nCurrent = nHead;
    while (nCurrent)
    {
        cout << nCurrent->nData << " ";
        nCurrent = nCurrent->nNext;
    }
    cout << endl;
}

//Подсчитывает количество узлов в списке
int CountNodes(Nodee* nHead)
{
    int nCount = 0;
    Nodee* nTemp = nHead;
    while (nTemp)
    {
        nCount++;
        nTemp = nTemp->nNext;
    }
    return nCount;
}

//Рекурсивно преобразует часть списка в сбалансированное BST
Nodee* ListToBST(Nodee*& nHead, int n)
{
    if (n <= 0)
    {
        return nullptr;
    }

    // Рекурсивно строим левое поддерево
    Nodee* nLeft = ListToBST(nHead, n / 2);

    // Текущий узел становится корнем
    Nodee* nRoot = nHead;

    // Связываем левое поддерево
    nRoot->nPrev = nLeft;

    // Перемещаем голову на следующий узел
    nHead = nHead->nNext;

    // Рекурсивно строим правое поддерево
    nRoot->nNext = ListToBST(nHead, n - n / 2 - 1);

    return nRoot;
}

//Преобразует отсортированный список в сбалансированное BST
Nodee* SortedListToBST(Nodee* nHead)
{
    int nCount = CountNodes(nHead);
    return ListToBST(nHead, nCount);
}

//Печатает дерево в заданном формате с отступами
void PrintTreeFormatted(Nodee* nRoot, int nLevel, char cPrefix)
{
    if (!nRoot)
    {
        return;
    }

    // Сначала правые поддеревья (они выводятся выше)
    PrintTreeFormatted(nRoot->nNext, nLevel + 1, '/');

    // Отступы для текущего уровня
    for (int i = 0; i < nLevel * 4; i++)
    {
        cout << " ";
    }

    // Вывод узла с префиксом
    cout << cPrefix << "-- " << nRoot->nData << endl;

    // Затем левые поддеревья (они выводятся ниже)
    PrintTreeFormatted(nRoot->nPrev, nLevel + 1, '\\');
}

//2
// Функция для вывода дерева в горизонтальном формате
template <typename T>
void PrintTree(shared_ptr<TreeNode<T>> node, int space, int gap)
{
    if (node == nullptr) return;

    // Увеличиваем отступ для правого поддерева
    space += gap;

    // Сначала выводим правое поддерево
    PrintTree(node->tRight, space);

    // Выводим текущий узел
    cout << endl;
    for (int i = gap; i < space; i++)
    {
        cout << " ";
    }
    cout << node->tValue << endl;

    // Затем выводим левое поддерево
    PrintTree(node->tLeft, space);
}

//---------------
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
    cout << "\nРезультат:\n";
    cout << "----------------------------------------\n";

    if (result != "No")
    {
        cout << "Найдено уравнение: " << result << "\n";
    }
    else
    {
        //cout << "Решение не найдено\n";
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