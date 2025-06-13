#ifndef ConsoleApplication3
#define ConsoleApplication3

#include <iostream>

#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <stack>
#include <algorithm>
#include <map>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <list>
#include <iterator>
#include <numeric>
#include <set>
#include <limits>
#include <queue>
#include <cmath>
#include <iomanip>
#include <memory>
#include <unordered_map>
#include <functional>

#include <Windows.h>

using namespace std;

// Безопасный ввод числа
int getIntegerInput();

//1
class TreeOperands
{
private:
    // Внутренний класс узла дерева
    struct TreeNode
    {
        int tValue;     // Значение узла (число или код операции)
        TreeNode* tLeft; // Левый потомок
        TreeNode* tRight; // Правый потомок

        TreeNode(int val) : tValue(val), tLeft(nullptr), tRight(nullptr) {}
    };

    TreeNode* tRoot; // Корень дерева
    const string tValidOps = "+-*/%^";

    // Преобразует символ операции в числовой код
    int operationToCode(char op);

    // Проверяет, является ли токен оператором
    bool isOperator(const string& token);

    // Рекурсивно строит дерево из префиксного выражения
    TreeNode* buildTreeFromPrefix(const vector<string>& tokens, int& index);

    // Вычисляет значение поддерева
    int evaluate(TreeNode* node);

    // Преобразует дерево, заменяя поддеревья с нулевыми результатами
    void transformTree(TreeNode* node);

    // Рекурсивно выводит дерево в понятном виде
    void printTree(TreeNode* node, int depth = 0);

    // Рекурсивно освобождает память, занятую деревом
    void clearTree(TreeNode* node);

public:
    TreeOperands() : tRoot(nullptr) {}

    ~TreeOperands()
    {
        clearTree(tRoot);
    }

    // Строит дерево из файла
    void buildFromFile(const string& filename);

    // Строит дерево из ввода пользователя
    void buildFromConsole();

    // Генерирует случайное дерево
    void buildRandom();

    // Применяет преобразование дерева
    void transform();

    // Выводит дерева
    void print();

    // Вычисление выражения
    int evaluateNode();

    // Возвращает указатель на корень дерева
    TreeNode* getRoot();
};

//2
//class ExpressionTree
//{
//private:
//    // Внутренний класс для узлов дерева
//    class TreeNode
//    {
//    public:
//        virtual ~TreeNode() = default;
//        virtual int tevaluate(int tx) const = 0;
//        virtual bool tcontainsX() const = 0;
//        virtual shared_ptr<TreeNode> tsimplify(int tx) const = 0;
//        virtual void tprint(ostream& tout, int tlevel = 0) const = 0;
//        virtual string ttoString() const = 0;
//    };
//
//    // Класс для числовых узлов
//    class NumberNode : public TreeNode
//    {
//        int nvalue;
//    public:
//        NumberNode(int nval) : nvalue(nval) {}
//
//        int tevaluate(int) const override
//        {
//            return nvalue;
//        }
//
//        bool tcontainsX() const override
//        {
//            return false;
//        }
//
//        shared_ptr<TreeNode> tsimplify(int) const override
//        {
//            return make_shared<NumberNode>(nvalue);
//        }
//
//        void tprint(ostream& tout, int tlevel) const override
//        {
//            tout << setw(tlevel * 8) << right << nvalue << endl;
//        }
//
//        string ttoString() const override
//        {
//            return to_string(nvalue);
//        }
//    };
//
//    // Класс для переменной x
//    class VariableNode : public TreeNode
//    {
//    public:
//        int tevaluate(int tx) const override
//        {
//            return tx;
//        }
//
//        bool tcontainsX() const override
//        {
//            return true;
//        }
//
//        shared_ptr<TreeNode> tsimplify(int tx) const override
//        {
//            return make_shared<NumberNode>(tx);
//        }
//
//        void tprint(ostream& tout, int tlevel) const override
//        {
//            tout << setw(tlevel * 8) << right << "x" << endl;
//        }
//
//        string ttoString() const override
//        {
//            return "x";
//        }
//    };
//
//    // Класс для операторов
//    class OperatorNode : public TreeNode
//    {
//        char oop;
//        shared_ptr<TreeNode> oleft;
//        shared_ptr<TreeNode> oright;
//    public:
//        OperatorNode(char oop, shared_ptr<TreeNode> ol, shared_ptr<TreeNode> ori )
//            : oop(oop), oleft(ol), oright(ori )
//        {}
//
//        int tevaluate(int tx) const override
//        {
//            int lval = oleft->tevaluate(tx);
//            int rval = oright->tevaluate(tx);
//
//            switch (oop)
//            {
//            case '+': return lval + rval;
//            case '-': return lval - rval;
//            case '*': return lval * rval;
//            case '/': return lval / rval;
//            case '%': return lval % rval;
//            case '^': return static_cast<int>(pow(lval, rval));
//            default: return 0;
//            }
//        }
//
//        bool tcontainsX() const override
//        {
//            return oleft->tcontainsX() || oright->tcontainsX();
//        }
//
//        shared_ptr<TreeNode> tsimplify(int tx) const override
//        {
//            auto simplifiedLeft = oleft->tsimplify(tx);
//            auto simplifiedRight = oright->tsimplify(tx);
//
//            /*if (!simplifiedLeft->tcontainsX() && !simplifiedRight->tcontainsX())
//            {
//                return make_shared<NumberNode>(this->tevaluate(tx));
//            }*/
//
//            bool hadX = oleft->tcontainsX() || oright->tcontainsX();
//            bool nowNoX = !simplifiedLeft->tcontainsX() && !simplifiedRight->tcontainsX();
//
//            if (hadX && nowNoX)
//            {
//                return make_shared<NumberNode>(this->tevaluate(tx));
//            }
//
//
//            return make_shared<OperatorNode>(oop, simplifiedLeft, simplifiedRight);
//        }
//
//        void tprint(ostream& tout, int tlevel = 0) const override
//        {
//            /*oright->tprint(tout, tlevel + 1);
//            tout << setw(tlevel * 8) << right << oop << endl;
//            oleft->tprint(tout, tlevel + 1);*/
//            // Вывод правого поддерева
//            if (oright) oright->tprint(tout, tlevel + 1);
//
//            // Вывод текущего оператора
//            tout << setw(tlevel * 8) << right << oop;
//
//            // Если узел был упрощён (например, (x+1) → 2), добавляем метку
//            if (!this->tcontainsX() && (oleft->tcontainsX() || oright->tcontainsX())) {
//                tout << " [simplified]";
//            }
//            tout << endl;
//
//            // Вывод левого поддерева
//            if (oleft) oleft->tprint(tout, tlevel + 1);
//        }
//
//        string ttoString() const override
//        {
//            string leftStr = oleft->ttoString();
//            string rightStr = oright->ttoString();
//
//            // Если поддерево было упрощено (был x, но теперь его нет), берём его значение
//            if (!oleft->tcontainsX() && oleft->tcontainsX()) {
//                leftStr = to_string(oleft->tevaluate(0)); // 0 — заглушка, tx не используется
//            }
//            if (!oright->tcontainsX() && oright->tcontainsX()) {
//                rightStr = to_string(oright->tevaluate(0));
//            }
//
//            return "(" + leftStr + " " + oop + " " + rightStr + ")";
//            /*return "(" + oleft->ttoString() + " " + oop + " " + oright->ttoString() + ")";*/
//        }
//    };
//
//    shared_ptr<TreeNode> eroot;
//    string eoriginalExpression;
//
//    // Вспомогательные методы
//    int egetPriority(char eop) const
//    {
//        switch (eop)
//        {
//        case '^': return 4;
//        case '*': case '/': case '%': return 3;
//        case '+': case '-': return 2;
//        default: return 0;
//        }
//    }
//
//    //Преобразует инфиксное выражение в постфиксную форму (ОПН)
//    vector<string> einfixedToPostfix(const string& expr) const
//    {
//        vector<string> output;
//        stack<char> ops;
//        string num;
//
//        for (size_t i = 0; i < expr.size(); ++i)
//        {
//            char c = expr[i];
//
//            if (isdigit(c))
//            {
//                num += c;
//                continue;
//            }
//
//            if (!num.empty())
//            {
//                output.push_back(num);
//                num.clear();
//            }
//
//            if (c == 'x')
//            {
//                output.push_back("x");
//            }
//            else if (c == '(')
//            {
//                ops.push(c);
//            }
//            else if (c == ')')
//            {
//                while (!ops.empty() && ops.top() != '(')
//                {
//                    output.push_back(string(1, ops.top()));
//                    ops.pop();
//                }
//                ops.pop(); // Удаляем '('
//            }
//            else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^')
//            {
//                while (!ops.empty() && egetPriority(ops.top()) >= egetPriority(c))
//                {
//                    output.push_back(string(1, ops.top()));
//                    ops.pop();
//                }
//                ops.push(c);
//            }
//        }
//
//        if (!num.empty())
//        {
//            output.push_back(num);
//        }
//
//        while (!ops.empty())
//        {
//            output.push_back(string(1, ops.top()));
//            ops.pop();
//        }
//
//        return output;
//    }
//
//    //Строит дерево выражения из постфиксной записи
//    shared_ptr<TreeNode> ebuildTreeFromPostfix(const vector<string>& postfix) const
//    {
//        stack<shared_ptr<TreeNode>> nodes;
//
//        for (const auto& token : postfix)
//        {
//            if (token == "x")
//            {
//                nodes.push(make_shared<VariableNode>());
//            }
//            else if (isdigit(token[0]))
//            {
//                nodes.push(make_shared<NumberNode>(stoi(token)));
//            }
//            else
//            {
//                char op = token[0];
//                auto right = nodes.top();
//                nodes.pop();
//                auto left = nodes.top();
//                nodes.pop();
//                nodes.push(make_shared<OperatorNode>(op, left, right));
//            }
//        }
//
//        return nodes.empty() ? nullptr : nodes.top();
//    }
//
//    //Генерирует случайное арифметическое выражение
//    string egenerateRandomExpression(int maxDepth) const
//    {
//        if (maxDepth <= 0)
//        {
//            // Листья - либо числа 1-30, либо x
//            static random_device rd;
//            static mt19937 gen(rd());
//            static uniform_int_distribution<int> dist(0, 1);
//
//            if (dist(gen) == 0)
//            {
//                uniform_int_distribution<int> numDist(1, 30);
//                return to_string(numDist(gen));
//            }
//            else
//            {
//                return "x";
//            }
//        }
//
//        static random_device rd;
//        static mt19937 gen(rd());
//        static uniform_int_distribution<int> opDist(0, 5);
//        static uniform_int_distribution<int> branchDist(0, 2);
//
//        string ops = "+-*/%^";
//        char op = ops[opDist(gen)];
//
//        string left = egenerateRandomExpression(maxDepth - 1);
//        string right = egenerateRandomExpression(maxDepth - 1);
//
//        // 30% chance to add parentheses
//        if (branchDist(gen) == 0)
//        {
//            return "(" + left + ")" + op + "(" + right + ")";
//        }
//        return left + op + right;
//    }
//
//public:
//    ExpressionTree() : eroot(nullptr) {}
//
//    // Загружает выражение из файла
//    bool loadFromFile(const string& filename)
//    {
//        ifstream file(filename);
//        if (!file)
//        {
//            cerr << "Невозможно открыть файл: " << filename << endl;
//            return false;
//        }
//        getline(file, eoriginalExpression);
//        file.close();
//
//        auto postfix = einfixedToPostfix(eoriginalExpression);
//        eroot = ebuildTreeFromPostfix(postfix);
//        return eroot != nullptr;
//    }
//
//    //Вводит выражение с консоли
//    void inputFromConsole()
//    {
//        cout << "Введите арифметическое выражение: ";
//        getline(cin, eoriginalExpression);
//
//        auto postfix = einfixedToPostfix(eoriginalExpression);
//        eroot = ebuildTreeFromPostfix(postfix);
//    }
//
//    //Генерирует случайное выражение
//    void generateRandom(int maxDepth = 3)
//    {
//        eoriginalExpression = egenerateRandomExpression(maxDepth);
//        cout << "Сгенерированное выражение: " << eoriginalExpression << endl;
//
//        auto postfix = einfixedToPostfix(eoriginalExpression);
//        eroot = ebuildTreeFromPostfix(postfix);
//    }
//
//    //Вычисляет значение выражения для заданного x
//    int evaluate(int x) const
//    {
//        if (!eroot)
//        {
//            cerr << "Дерево пустое!" << endl;
//            return 0;
//        }
//        return eroot->tevaluate(x);
//    }
//
//    //Упрощает дерево, заменяя поддеревья с x на их значения
//    void simplify(int x)
//    {
//        if (!eroot)
//        {
//            return;
//        }
//        eroot = eroot->tsimplify(x);
//    }
//
//    //Выводит выражение в инфиксной форме
//    void printExpression(ostream& out) const
//    {
//        if (!eroot)
//        {
//            out << "Дерево пустое" << endl;
//            return;
//        }
//        out << eroot->ttoString() << endl;
//    }
//
//    //Выводит дерево боком
//    void printTree(ostream& out) const
//    {
//        if (!eroot)
//        {
//            out << "Дерево пустое" << endl;
//            return;
//        }
//        eroot->tprint(out);
//    }
//
//    //Проверяет содержит ли выражение переменную x
//    bool containsX() const
//    {
//        if (!eroot)
//        {
//            return false;
//        }
//        return eroot->tcontainsX();
//    }
//
//    //Возвращает исходное выражение
//    string getOriginalExpression() const
//    {
//        return eoriginalExpression;
//    }
//};

class ExpressionTree
{
private:
    // Внутренний класс для представления узла дерева выражения
    class Node
    {
    public:
        virtual ~Node() = default;
        virtual int nEvaluate(int x) const = 0;
        virtual string nToString() const = 0;
        virtual bool nContainsX() const = 0;
        virtual shared_ptr<Node> nReplaceX(int x) = 0;
        virtual void nPrint(ostream& out, int level) const = 0;
    };

    // Класс для числовых констант
    class NumberNode : public Node
    {
        int nValue;
    public:
        NumberNode(int val) : nValue(val) {}

        int nEvaluate(int) const override
        {
            return nValue;
        }

        string nToString() const override
        {
            return to_string(nValue);
        }

        bool nContainsX() const override
        {
            return false;
        }

        shared_ptr<Node> nReplaceX(int) override
        {
            return make_shared<NumberNode>(nValue);
        }

        void nPrint(ostream& out, int level) const override
        {
            out << string(level * 8, ' ') << nValue << endl;
        }
    };

    // Класс для переменной x
    class VariableNode : public Node
    {
    public:
        int nEvaluate(int x) const override
        {
            return x;
        }

        string nToString() const override
        {
            return "x";
        }

        bool nContainsX() const override
        {
            return true;
        }

        shared_ptr<Node> nReplaceX(int x) override
        {
            return make_shared<NumberNode>(x);
        }

        void nPrint(ostream& out, int level) const override
        {
            out << string(level * 8, ' ') << "x" << endl;
        }
    };

    // Класс для бинарных операций
    class BinaryOpNode : public Node
    {
        char nOp;
        shared_ptr<Node> nLeft;
        shared_ptr<Node> nRight;
    public:
        BinaryOpNode(char op, shared_ptr<Node> l, shared_ptr<Node> r)
            : nOp(op), nLeft(l), nRight(r)
        {}

        int nEvaluate(int x) const override
        {
            int l = nLeft->nEvaluate(x);
            int r = nRight->nEvaluate(x);

            switch (nOp)
            {
            case '+': return l + r;
            case '-': return l - r;
            case '*': return l * r;
            case '/': return l / r;
            case '%': return l % r;
            case '^': return static_cast<int>(pow(l, r));
            default: return 0;
            }
        }

        string nToString() const override
        {
            return "(" + nLeft->nToString() + " " + nOp + " " + nRight->nToString() + ")";
        }

        bool nContainsX() const override
        {
            return nLeft->nContainsX() || nRight->nContainsX();
        }

        shared_ptr<Node> nReplaceX(int x) override
        {
            /*auto simplifiedLeft = nLeft->nReplaceX(x);
            auto simplifiedRight = nRight->nReplaceX(x);

            if (!simplifiedLeft->nContainsX() && !simplifiedRight->nContainsX())
            {
                int result = BinaryOpNode(nOp, simplifiedLeft, simplifiedRight).nEvaluate(x);
                return make_shared<NumberNode>(result);
            }

            return make_shared<BinaryOpNode>(nOp, simplifiedLeft, simplifiedRight);*/

            auto newLeft = nLeft->nReplaceX(x);
            auto newRight = nRight->nReplaceX(x);
            return make_shared<BinaryOpNode>(nOp, newLeft, newRight);
        }

        void nPrint(ostream& out, int level) const override
        {
            nRight->nPrint(out, level + 1);
            out << string(level * 8, ' ') << nOp << endl;
            nLeft->nPrint(out, level + 1);
        }
    };

    shared_ptr<Node> nRoot;
    string nOriginalExpression;

    //Определение приоритета операций
    static int nPrecedence(char op)
    {
         if (op == '^')
         {
             return 4;
         }
         if (op == '*' || op == '/' || op == '%')
         {
             return 3;
         }
         if (op == '+' || op == '-')
         {
             return 2;
         }
         return 0;
    }

     /* Преобразование инфиксной записи в постфиксную (ОПН)
      * Использует алгоритм сортировочной станции (алгоритм Дейкстры)
      * expr - входное выражение в инфиксной форме
      * Возвращает вектор токенов в постфиксной форме
      */
     vector<string> nInfixToPostfix(const string& expr)
     {
         vector<string> output;
         stack<char> ops;
         string num;

         for (size_t i = 0; i < expr.size(); ++i)
         {
             char c = expr[i];

             if (isdigit(c))
             {
                 num += c;
                 if (i == expr.size() - 1 || !isdigit(expr[i + 1]))
                 {
                     output.push_back(num);
                     num.clear();
                 }
             }
             else if (c == 'x')
             {
                 output.push_back("x");
             }
             else if (c == '(')
             {
                 ops.push(c);
             }
             else if (c == ')')
             {
                 while (!ops.empty() && ops.top() != '(')
                 {
                     output.push_back(string(1, ops.top()));
                     ops.pop();
                 }
                 ops.pop();
             }
             else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^')
             {
                 if (c == '-' && (i == 0 || expr[i - 1] == '('))
                 {
                     output.push_back("0");
                 }

                 while (!ops.empty() && nPrecedence(ops.top()) >= nPrecedence(c))
                 {
                     output.push_back(string(1, ops.top()));
                     ops.pop();
                 }
                 ops.push(c);
             }
         }

         while (!ops.empty())
         {
             output.push_back(string(1, ops.top()));
             ops.pop();
         }

         return output;
     }

     /* Построение дерева выражения из постфиксной записи
      * postfix - вектор токенов в постфиксной форме
      * Возвращает указатель на корень построенного дерева
      */
     shared_ptr<Node> nBuildExpressionTree(const vector<string>& postfix)
     {
         stack<shared_ptr<Node>> st;

         for (const auto& token : postfix)
         {
             if (isdigit(token[0]))
             {
                 st.push(make_shared<NumberNode>(stoi(token)));
             }
             else if (token == "x")
             {
                 st.push(make_shared<VariableNode>());
             }
             else
             {
                 auto right = st.top();
                 st.pop();
                 auto left = st.top();
                 st.pop();
                 st.push(make_shared<BinaryOpNode>(token[0], left, right));
             }
         }

         return st.top();
     }

public:
    ExpressionTree() : nRoot(nullptr) {}

    /* Загрузка выражения из файла
     * filename - имя файла для чтения
     */
    void loadFromFile(const string& filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cerr << "Невозможно открыть файл: " << filename << endl;
            return;
        }
        getline(file, nOriginalExpression);
        file.close();

        auto postfix = nInfixToPostfix(nOriginalExpression);
        nRoot = nBuildExpressionTree(postfix);
    }

    /* Вычисление значения выражения
     * x - значение переменной x
     * Возвращает результат вычисления
     */
    int evaluate(int x) const
    {
        if (!nRoot)
        {
            cerr << "Дерево пустое!" << endl;
            return 0;
        }
        return nRoot->nEvaluate(x);
    }

    /* Упрощение дерева (замена поддеревьев с x)
     * x - значение для замены переменной x
     */
    void replaceX(int x)
    {
        if (!nRoot)
        {
            cerr << "Дерево пустое!" << endl;
            return;
        }
        nRoot = nRoot->nReplaceX(x);
    }

    /* Вывод дерева в понятном виде
     * out - поток для вывода (по умолчанию cout)
     */
    void printExpression(ostream& out = cout) const
    {
        if (!nRoot)
        {
            out << "Дерево пустое!" << endl;
            return;
        }
        out << "Выражение: " << nOriginalExpression << endl;
        out << "Дерево выражения:" << endl;
        nRoot->nPrint(out, 0);
    }

    /* Вывод результатов в файл
     * filename - имя файла для записи
     */
    void printToFile(const string& filename) const
    {
        ofstream outFile(filename);
        if (!outFile.is_open())
        {
            cerr << "Невозможно открыть файл: " << filename << endl;
            return;
        }
        printExpression(outFile);
        outFile.close();
    }

    // Получение оригинального выражения
    string getOriginalExpression() const
    {
        return nOriginalExpression;
    }
};

//--------

//1
// Узел для двусвязного списка и бинарного дерева поиска
struct Nodee
{
    int nData;      // Данные узла
    Nodee* nPrev;    // Указатель на предыдущий/левый узел
    Nodee* nNext;    // Указатель на следующий/правый узел

    Nodee(int val) : nData(val), nPrev(nullptr), nNext(nullptr) {}
};

// Сортировка списка
void BubbleSortList(Nodee* nHead);

// Создаёт двусвязный список на основе ввода пользователя
Nodee* CreateListFromInput();

// Печатает элементы списка
void PrintList(Nodee* nHead);

//Подсчитывает количество узлов в списке
int CountNodes(Nodee* nHead);

//Рекурсивно преобразует часть списка в сбалансированное BST
Nodee* ListToBST(Nodee*& nHead, int n);

//Преобразует отсортированный список в сбалансированное BST
Nodee* SortedListToBST(Nodee* nHead);

//Печатает дерево в заданном формате с отступами
void PrintTreeFormatted(Nodee* nRoot, int nLevel = 0, char cPrefix = ' ');

//2
// Узел бинарного дерева
//template <typename T>
//struct TreeNode
//{
//    T tValue;
//    shared_ptr<TreeNode<T>> tLeft;
//    shared_ptr<TreeNode<T>> tRight;
//
//    TreeNode(T val) : tValue(val), tLeft(nullptr), tRight(nullptr) {}
//};
//
//// Функция для вывода дерева в горизонтальном формате
//template <typename T>
//void PrintTree(shared_ptr<TreeNode<T>> node, int space = 0, int gap = 4);
//
//// Класс итератора для обратного in-order обхода (право-корень-лево)
//template <typename T>
//class ReverseInOrderIterator
//{
//public:
//    // Конструктор инициализирует итератор, начиная с самого правого узла
//    ReverseInOrderIterator(shared_ptr<TreeNode<T>> root) : rCurrent(root)
//    {
//        // Инициализация стека - доходим до самого правого узла
//        while (rCurrent != nullptr)
//        {
//            rStack.push(rCurrent);
//            rCurrent = rCurrent->tRight;
//        }
//
//        // Если стек не пуст, устанавливаем текущий элемент
//        if (!rStack.empty())
//        {
//            rCurrent = rStack.top();
//            rStack.pop();
//        }
//    }
//
//    // Оператор разыменования - возвращает значение текущего узла
//    T operator*() const
//    {
//        return rCurrent->tValue;
//    }
//
//    // Оператор перехода к следующему элементу
//    ReverseInOrderIterator& operator++()
//    {
//        // Переходим к левому поддереву
//        if (rCurrent->tLeft != nullptr)
//        {
//            rCurrent = rCurrent->tLeft;
//
//            // Идем до самого правого узла в этом поддереве
//            while (rCurrent != nullptr)
//            {
//                rStack.push(rCurrent);
//                rCurrent = rCurrent->tRight;
//            }
//        }
//
//        // Если стек не пуст, берем следующий элемент
//        if (!rStack.empty())
//        {
//            rCurrent = rStack.top();
//            rStack.pop();
//        }
//        else
//        {
//            rCurrent = nullptr; // Конец обхода
//        }
//
//        return *this;
//    }
//
//    // Оператор сравнения для использования в циклах
//    bool operator!=(const ReverseInOrderIterator& other) const
//    {
//        return rCurrent != other.rCurrent;
//    }
//
//private:
//    shared_ptr<TreeNode<T>> rCurrent;
//    stack<shared_ptr<TreeNode<T>>> rStack;
//};
//
//// Класс бинарного дерева поиска
//template <typename T>
//class BinaryTree
//{
//public:
//    BinaryTree() : bRoot(nullptr) {}
//
//    // Вставляет новое значение в дерево согласно правилам BST
//    void Insert(T value)
//    {
//        if (bRoot == nullptr)
//        {
//            bRoot = make_shared<TreeNode<T>>(value);
//            return;
//        }
//
//        auto current = bRoot;
//        while (true)
//        {
//            if (value < current->tValue)
//            {
//                if (current->tLeft == nullptr)
//                {
//                    current->tLeft = make_shared<TreeNode<T>>(value);
//                    break;
//                }
//                else
//                {
//                    current = current->tLeft;
//                }
//            }
//            else
//            {
//                if (current->tRight == nullptr)
//                {
//                    current->tRight = make_shared<TreeNode<T>>(value);
//                    break;
//                }
//                else
//                {
//                    current = current->tRight;
//                }
//            }
//        }
//    }
//
//    // Метод для вывода дерева
//    void Print()
//    {
//        cout << "Горизонтальное представление дерева:" << endl;
//        PrintTree(bRoot);
//        cout << endl;
//    }
//
//    // Возвращает итератор на начало (первый элемент в порядке право-корень-лево)
//    ReverseInOrderIterator<T> Begin()
//    {
//        return ReverseInOrderIterator<T>(bRoot);
//    }
//
//    // Возвращает итератор на конец последовательности
//    ReverseInOrderIterator<T> End()
//    {
//        return ReverseInOrderIterator<T>(nullptr);
//    }
//
//private:
//    shared_ptr<TreeNode<T>> bRoot;
//};

template <typename T>
struct TreeNode {
    T tValue;
    shared_ptr<TreeNode<T>> tLeft;
    shared_ptr<TreeNode<T>> tRight;

    TreeNode(T val) : tValue(val), tLeft(nullptr), tRight(nullptr) {}
};

template <typename T>
class ReverseInOrderIterator {
public:
    ReverseInOrderIterator(shared_ptr<TreeNode<T>> root) : rCurrent(root) {}

    T operator*() const {
        if (!rCurrent) throw logic_error("Dereferencing end iterator");
        return rCurrent->tValue;
    }

    ReverseInOrderIterator& operator++() {
        if (!rCurrent) return *this;

        // Алгоритм Морриса для обратного in-order обхода
        shared_ptr<TreeNode<T>> prev = nullptr;
        while (rCurrent) {
            if (rCurrent->tRight) {
                // Находим крайний левый узел в правом поддереве
                prev = rCurrent->tRight;
                while (prev->tLeft && prev->tLeft != rCurrent) {
                    prev = prev->tLeft;
                }

                if (!prev->tLeft) {
                    // Создаем временную связь
                    prev->tLeft = rCurrent;
                    rCurrent = rCurrent->tRight;
                }
                else {
                    // Удаляем временную связь
                    prev->tLeft = nullptr;
                    // Текущий узел готов к обработке
                    break;
                }
            }
            else {
                // Нет правого поддерева - обрабатываем текущий узел
                break;
            }
        }

        if (!rCurrent) return *this;

        // Переходим к следующему узлу (левому поддереву)
        rCurrent = rCurrent->tLeft;
        return *this;
    }

    bool operator!=(const ReverseInOrderIterator& other) const {
        return rCurrent != other.rCurrent;
    }

private:
    shared_ptr<TreeNode<T>> rCurrent;
};

template <typename T>
class BinaryTree {
public:
    BinaryTree() : bRoot(nullptr) {}

    void Insert(T value) {
        auto newNode = make_shared<TreeNode<T>>(value);
        if (!bRoot) {
            bRoot = newNode;
            return;
        }

        auto current = bRoot;
        while (true) {
            if (value < current->tValue) {
                if (!current->tLeft) {
                    current->tLeft = newNode;
                    break;
                }
                current = current->tLeft;
            }
            else {
                if (!current->tRight) {
                    current->tRight = newNode;
                    break;
                }
                current = current->tRight;
            }
        }
    }

    ReverseInOrderIterator<T> begin() {
        // Инициализация итератора - находим первый узел (самый правый)
        auto current = bRoot;
        while (current && current->tRight) {
            current = current->tRight;
        }
        return ReverseInOrderIterator<T>(current);
    }

    ReverseInOrderIterator<T> end() {
        return ReverseInOrderIterator<T>(nullptr);
    }

private:
    shared_ptr<TreeNode<T>> bRoot;
};

//3
// Структура узла бинарного дерева
//struct TreeNodeе
//{
//    int tValue;       // Значение узла
//    TreeNodeе* tLeft;  // Левый потомок
//    TreeNodeе* tRight; // Правый потомок
//
//    TreeNodeе(int x) : tValue(x), tLeft(nullptr), tRight(nullptr) {}
//};
//
//class DuplicateSubtreesRemover
//{
//public:
//    // Находит и удаляет все дублирующиеся поддеревья в бинарном дереве, начиная с самых крупных
//    void removeDuplicateSubtrees(TreeNodeе* root)
//    {
//        vector<TreeNodeе*> duplicates = findDuplicateSubtrees(root);
//
//        for (TreeNodeе* dup : duplicates)
//        {
//            findAndDelete(root, dup);
//        }
//    }
//
//private:
//    // Находит все дублирующиеся поддеревья в бинарном дереве
//    vector<TreeNodeе*> findDuplicateSubtrees(TreeNodeе* root)
//    {
//        unordered_map<string, vector<TreeNodeе*>> subtreeMap;
//        vector<TreeNodeе*> duplicates;
//        serializeSubtree(root, subtreeMap);
//
//        // Объявляем функцию для вычисления размера
//        function<int(TreeNodeе*)> calculateSize;
//
//        // Определяем лямбда-функцию с рекурсией
//        calculateSize = [&calculateSize](TreeNodeе* node) -> int
//            {
//                if (!node) return 0;
//                return 1 + calculateSize(node->tLeft) + calculateSize(node->tRight);
//            };
//
//        // Находим дубликаты
//        for (auto& entry : subtreeMap)
//        {
//            if (entry.second.size() > 1)
//            {
//                duplicates.insert(duplicates.end(),
//                    entry.second.begin() + 1,
//                    entry.second.end());
//            }
//        }
//
//        // Сортируем по размеру (убывание)
//        sort(duplicates.begin(), duplicates.end(),
//            [&calculateSize](TreeNodeе* a, TreeNodeе* b)
//            {
//                return calculateSize(a) > calculateSize(b);
//            });
//
//        return duplicates;
//    }
//
//    // Сериализует поддерево в строку для сравнения и сохраняет в карту
//    string serializeSubtree(TreeNodeе* node,
//        unordered_map<string, vector<TreeNodeе*>>& subtreeMap)
//    {
//        if (!node)
//        {
//            return "#";
//        }
//
//        string serialized = "(" + serializeSubtree(node->tLeft, subtreeMap) +
//            to_string(node->tValue) +
//            serializeSubtree(node->tRight, subtreeMap) + ")";
//        subtreeMap[serialized].push_back(node);
//
//        return serialized;
//    }
//
//    // Вычисляет размер поддерева (количество узлов)
//    int calculateSubtreeSize(TreeNodeе* node)
//    {
//        if (!node)
//        {
//            return 0;
//        }
//        return 1 + calculateSubtreeSize(node->tLeft) +
//            calculateSubtreeSize(node->tRight);
//    }
//
//    // Находит и удаляет целевой узел в дереве, обнуляя соответствующую ссылку
//    bool findAndDelete(TreeNodeе* root, TreeNodeе* target)
//    {
//        if (!root)
//        {
//            return false;
//        }
//
//        if (root->tLeft == target)
//        {
//            root->tLeft = nullptr;
//            return true;
//        }
//
//        if (root->tRight == target)
//        {
//            root->tRight = nullptr;
//            return true;
//        }
//
//        return findAndDelete(root->tLeft, target) ||
//            findAndDelete(root->tRight, target);
//    }
//
//    void deleteSubtree(TreeNodeе* node)
//    {
//        if (!node) return;
//        deleteSubtree(node->tLeft);
//        deleteSubtree(node->tRight);
//        delete node;
//    }
//};
//
//// Строит бинарное дерево из ввода пользователя
//TreeNodeе* buildTreeFromConsoleInput()
//{
//    string inputLine;
//    cout << "Enter tree nodes in level-order (space separated, 'null' for missing nodes):\n";
//    getline(cin, inputLine);
//
//    if (inputLine.empty())
//    {
//        return nullptr;
//    }
//
//    vector<string> nodeValues;
//    istringstream iss(inputLine);
//    string token;
//
//    while (iss >> token)
//    {
//        nodeValues.push_back(token);
//    }
//
//    if (nodeValues.empty() || nodeValues[0] == "null")
//    {
//        return nullptr;
//    }
//
//    TreeNodeе* root = new TreeNodeе(stoi(nodeValues[0]));
//    queue<TreeNodeе*> nodeQueue;
//    nodeQueue.push(root);
//
//    size_t index = 1;
//    while (!nodeQueue.empty() && index < nodeValues.size())
//    {
//        TreeNodeе* currentNode = nodeQueue.front();
//        nodeQueue.pop();
//
//        if (index < nodeValues.size() && nodeValues[index] != "null")
//        {
//            currentNode->tLeft = new TreeNodeе(stoi(nodeValues[index]));
//            nodeQueue.push(currentNode->tLeft);
//        }
//        index++;
//
//        if (index < nodeValues.size() && nodeValues[index] != "null")
//        {
//            currentNode->tRight = new TreeNodeе(stoi(nodeValues[index]));
//            nodeQueue.push(currentNode->tRight);
//        }
//        index++;
//    }
//
//    return root;
//}
//
//// Печатает бинарное дерево по уровням
//void printTreeLevelOrder(TreeNodeе* root)
//{
//    if (!root)
//    {
//        cout << "null";
//        return;
//    }
//
//    queue<TreeNodeе*> printQueue;
//    printQueue.push(root);
//
//    while (!printQueue.empty())
//    {
//        TreeNodeе* current = printQueue.front();
//        printQueue.pop();
//
//        if (current)
//        {
//            cout << current->tValue << " ";
//            printQueue.push(current->tLeft);
//            printQueue.push(current->tRight);
//        }
//        else
//        {
//            cout << "null ";
//        }
//    }
//}
//
//// Рекурсивно удаляет дерево, освобождая память
//void deleteTree(TreeNodeе* root)
//{
//    if (!root)
//    {
//        return;
//    }
//
//    deleteTree(root->tLeft);
//    deleteTree(root->tRight);
//    delete root;
//}

//-------------
//1
//class Graph
//{
//private:
//    int numVertices;
//    vector<vector<int>> adjMatrix;
//    vector<vector<int>> incidenceMatrix;
//    vector<pair<int, int>> edges;
//public:
//
//    // Конструктор
//    Graph() : numVertices(0) {}
//
//    // Функция для чтения матрицы смежности из файла
//    void readAdjacencyMatrix(const string& filename);
//
//    // Функция для получения списка ребер в нужном порядке
//    void buildEdges();
//
//    // Функция для построения матрицы инцидентности
//    void buildIncidenceMatrix();
//
//    // Функция для записи матрицы инцидентности в файл
//    void writeIncidenceMatrix(const string& filename);
//
//    // Функция для вывода матрицы
//    void printMatrix(const vector<vector<int>>& matrix, const string& title);
//
//    // Геттеры для матриц
//    const vector<vector<int>>& getAdjMatrix() const { return adjMatrix; }
//    const vector<vector<int>>& getIncidenceMatrix() const { return incidenceMatrix; }
//    const vector<pair<int, int>>& getEdges() const { return edges; }
//    int getNumVertices() const { return numVertices; }
//
//    //2
//    // Функция находит города, достижимые из start за ≤L шагов
//    vector<int> getReachableCities(const vector<vector<int>>& adj, int start, int L);
//
//    //3
//    void findPaths(const vector<vector<int>>& graph, int current, int end, int steps, vector<int>& path, vector<vector<int>>& allPaths);
//};

//----------------
/**
* Класс для решения задачи поиска уравнения A+B=C в числовом кольце
*/
class EquationRingSolver
{
public:
    /**
    * Конструктор класса
    * @param ring строка с цифрами кольца
    */
    explicit EquationRingSolver(const string& ring);

    /**
    * Основной метод поиска уравнения
    * @return строка с уравнением или "No" если решение не найдено
    */
    string FindEquation();

private:
    /**
    * Извлекает число из кольца
    * @param start начальная позиция
    * @param length длина числа
    * @return строка с числом
    */
    string ExtractNumber(int start, int length) const;

    /**
    * Проверяет наличие ведущего нуля
    * @param number строка с числом
    * @return true если есть ведущий ноль
    */
    bool HasLeadingZero(const string& number) const;

    /**
    * Проверяет конкретную комбинацию чисел
    * @param aStart начальная позиция числа A
    * @param aLength длина числа A
    * @param bLength длина числа B
    * @param cLength длина числа C
    * @param result ссылка для сохранения результата
    * @return true если комбинация верна A+B=C
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
    * @param result строка с результатом
    */
    void PrintResult(const string& result) const;

    /**
    * Выводит милое изображение
    */
    void printCutePixelArt() const;

    /**
    * Проверяет корректность ввода
    * @param input строка для проверки
    * @return true если ввод корректен
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
    * @param s строка, содержащая только цифры
    */
    BigInt(const string& s);

    /**
    * Оператор сложения двух больших чисел
    * @param other второе слагаемое
    * @return результат сложения
    */
    BigInt operator+(const BigInt& other) const;

    /**
    * Оператор сравнения на равенство
    * @param other число для сравнения
    * @return true если числа равны
    */
    bool operator==(const BigInt& other) const;

    /**
    * Преобразование числа в строку
    * @return строковое представление числа
    */
    string toString() const;

private:
    vector<int> digits;// Цифры числа (хранятся в обратном порядке)
};

#endif