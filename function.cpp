#include "head.h"

// ���������� ���� �����
int getIntegerInput()
{
    string input;
    int num;
    bool valid = false;

    while (!valid)
    {
        cout << "������� ����� �����: ";
        cin >> input;

        try
        {
            size_t pos;
            num = stoi(input, &pos);

            // ���������, ��� ��� ������ ���� �������������
            if (pos == input.length())
            {
                valid = true;
            }
            else
            {
                cout << "������! ������� ����� ����� ��� �������������� ��������." << endl;
            }
        }
        catch (const invalid_argument&)
        {
            cout << "������! ������� ����� �����." << endl;
        }
        catch (const out_of_range&)
        {
            cout << "������! ����� ������� �������." << endl;
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
// ����������� ������ �������� � �������� ���
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

// ���������, �������� �� ����� ����������
bool TreeOperands::isOperator(const string& token)
{
    return token.size() == 1 && tValidOps.find(token[0]) != string::npos;
}

// ���������� ������ ������ �� ����������� ���������
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

// ��������� �������� ���������
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
            throw runtime_error("������� �� ����");
        }
        return leftVal / rightVal;
    }
    case -5:
    {
        if (rightVal == 0)
        {
            throw runtime_error("������� �� ������ �� ����");
        }
        return leftVal % rightVal;
    }
    case -6:
    {
        if (leftVal == 0 && rightVal <= 0)
        {
            throw runtime_error("������������ �������� ���������� � �������");
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

// ����������� ������, ������� ���������� � �������� ������������
void TreeOperands::transformTree(TreeNode* node)
{
    if (!node)
    {
        return;
    }

    if (node->tValue < 0)// ��� ��������
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

// ���������� ������� ������ � �������� ����
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

// ���������� ����������� ������, ������� �������
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

// ������ ������ �� �����
void TreeOperands::buildFromFile(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        throw runtime_error("���������� ������� ����: " + filename);
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

// ������ ������ �� ����� ������������
void TreeOperands::buildFromConsole()
{
    /*cout << "������� ���������� ��������� (��������: + - * / % ^, "
        << "��������: 0-9):" << endl;
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
        cout << "������� ���������� ��������� (��������: + - * / % ^, "
            << "��������: 0-9):" << endl;
        string line;
        getline(cin, line);

        vector<string> tokens;
        stringstream ss(line);
        string token;
        bool tokens_valid = true;

        // �������� ������� ������
        while (ss >> token && tokens_valid)
        {
            if (token.size() != 1)
            {
                tokens_valid = false;
                break;
            }

            // �������� �� ��������
            if (isOperator(token))
            {
                tokens.push_back(token);
                continue;
            }

            // �������� �� �����
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

            // ���� �� ��������, �� �����
            tokens_valid = false;
        }

        if (!tokens_valid)
        {
            cout << "������! ������������ ������� � ���������. ����������� ������ "
                << tValidOps << " � ����� 0-9." << endl;
            continue;
        }

        // �������� ������������ ���������� ������
        try
        {
            int index = 0;
            tRoot = buildTreeFromPrefix(tokens, index);
            if (index != tokens.size())
            {
                throw runtime_error("�������� ���������� ��������� � ���������");
            }
            input_valid = true;
        }
        catch (const exception& e)
        {
            cout << "������ � ���������: " << e.what()
                << ". ���������� �����." << endl;
            if (tRoot)
            {
                clearTree(tRoot);
                tRoot = nullptr;
            }
        }
    }
}

// ���������� ��������� ������
void TreeOperands::buildRandom()
{
    srand(time(nullptr));
    int numNodes = rand() % 10 + 5; // �� 5 �� 14 �����
    vector<string> tokens;

    for (int i = 0; i < numNodes; ++i)
    {
        if (rand() % 3 == 0)// 33% ����������� ���������
        {
            tokens.push_back(string(1, tValidOps[rand() % tValidOps.size()]));
        }
        else// 67% ����������� �������� (0-9)
        {
            tokens.push_back(to_string(rand() % 10));
        }
    }

    int index = 0;
    tRoot = buildTreeFromPrefix(tokens, index);
}

// ��������� �������������� ������
void TreeOperands::transform()
{
    transformTree(tRoot);
}

// ������� ������
void TreeOperands::print()
{
    if (!tRoot)
    {
        cout << "������ ������." << endl;
        return;
    }
    printTree(tRoot);
}

// ���������� ���������
int TreeOperands::evaluateNode()
{
    if (!tRoot)
    {
        throw runtime_error("������ ������");
    }
    return evaluate(tRoot);
}

// ���������� ��������� �� ������ ������
TreeOperands::TreeNode* TreeOperands::getRoot()
{
    return tRoot;
}

//------------

//1
// ���������� ������
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

// ������ ���������� ������ �� ������ ����� ������������
Nodee* CreateListFromInput()
{
    Nodee* nHead = nullptr;
    Nodee* nTail = nullptr;
    int nValue;
    int n;

    cout << "������� ���-�� �������� ��� ������:" << endl;
    n = getIntegerInput();

    cout << "������� �������� ��� ������:" << endl;

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

// �������� �������� ������
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

//������������ ���������� ����� � ������
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

//���������� ����������� ����� ������ � ���������������� BST
Nodee* ListToBST(Nodee*& nHead, int n)
{
    if (n <= 0)
    {
        return nullptr;
    }

    // ���������� ������ ����� ���������
    Nodee* nLeft = ListToBST(nHead, n / 2);

    // ������� ���� ���������� ������
    Nodee* nRoot = nHead;

    // ��������� ����� ���������
    nRoot->nPrev = nLeft;

    // ���������� ������ �� ��������� ����
    nHead = nHead->nNext;

    // ���������� ������ ������ ���������
    nRoot->nNext = ListToBST(nHead, n - n / 2 - 1);

    return nRoot;
}

//����������� ��������������� ������ � ���������������� BST
Nodee* SortedListToBST(Nodee* nHead)
{
    int nCount = CountNodes(nHead);
    return ListToBST(nHead, nCount);
}

//�������� ������ � �������� ������� � ���������
void PrintTreeFormatted(Nodee* nRoot, int nLevel, char cPrefix)
{
    if (!nRoot)
    {
        return;
    }

    // ������� ������ ���������� (��� ��������� ����)
    PrintTreeFormatted(nRoot->nNext, nLevel + 1, '/');

    // ������� ��� �������� ������
    for (int i = 0; i < nLevel * 4; i++)
    {
        cout << " ";
    }

    // ����� ���� � ���������
    cout << cPrefix << "-- " << nRoot->nData << endl;

    // ����� ����� ���������� (��� ��������� ����)
    PrintTreeFormatted(nRoot->nPrev, nLevel + 1, '\\');
}

//2
// ������� ��� ������ ������ � �������������� �������
template <typename T>
void PrintTree(shared_ptr<TreeNode<T>> node, int space, int gap)
{
    if (node == nullptr) return;

    // ����������� ������ ��� ������� ���������
    space += gap;

    // ������� ������� ������ ���������
    PrintTree(node->tRight, space);

    // ������� ������� ����
    cout << endl;
    for (int i = gap; i < space; i++)
    {
        cout << " ";
    }
    cout << node->tValue << endl;

    // ����� ������� ����� ���������
    PrintTree(node->tLeft, space);
}

//---------------
// ����� EquationRingSolver
/**
* ����������� �������������� ������ ������
*/
EquationRingSolver::EquationRingSolver(const string& ring)
    : mRing(ring) {}

/**
* ����� ���������
*/
string EquationRingSolver::FindEquation()
{
    const int ringSize = mRing.size();
    string result;

    // ������� ���� ��������� ���� ��� A, B � C
    for (int aLength = 1; aLength <= ringSize - 2; ++aLength)
    {
        for (int bLength = 1; bLength <= ringSize - aLength - 1; ++bLength)
        {
            const int cLength = ringSize - aLength - bLength;
            if (cLength < 1)
            {
                continue;
            }

            // �������� ���� ��������� �������
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
* ��������� ��������� �� ������
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
* �������� �� ������� ����
*/
bool EquationRingSolver::HasLeadingZero(const string& number) const
{
    return number.size() > 1 && number[0] == '0';
}

/**
* ��������� ����������� �� ��� ������ ���������� A+B=C
*/
bool EquationRingSolver::CheckCombination(int aStart, int aLength,
    int bLength, int cLength, string& result) const
{
    const string aPart = ExtractNumber(aStart, aLength);
    const string bPart = ExtractNumber((aStart + aLength) % mRing.size(), bLength);
    const string cPart = ExtractNumber((aStart + aLength + bLength) % mRing.size(), cLength);

    // �������� �� ������� ����
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

// ����� RingSolverApp
/**
* �������� ���� ����������
*/
void RingSolverApp::Run()
{
    PrintWelcomeMessage();

    string ring;
    while (true)
    {
        cout << "> ";
        getline(cin, ring);

        // ������� ��������� ������� � ������/�����
        ring.erase(0, ring.find_first_not_of(" \t"));
        ring.erase(ring.find_last_not_of(" \t") + 1);
        if (ValidateInput(ring))
        {
            break;
        }
    }

    cout << "\n���������� ������. . .\n" ;
    EquationRingSolver solver(ring);
    string result = solver.FindEquation();

    PrintResult(result);
    printCutePixelArt();
}

/**
* �������������� ���������
*/
void RingSolverApp::PrintWelcomeMessage() const
{
    cout << "========================================\n";
    cout << "    �������� ������: �������� A+B=C     \n";
    cout << "========================================\n\n";
    cout << "������� ������������������ ���� ������ (��� ��������):\n";
    cout << "������� �����:\n";
    cout << "1. ������ ����� ��� ��������\n";
    cout << "2. ������� 3 �������\n";
    cout << "������: 102030\n";
    cout << "(��� ������� ������� ������ ����� ������ ��������� ����� ��� ������� ������)\n\n";
}

/**
* ������� ��������� ������
*/
void RingSolverApp::PrintResult(const string& result) const
{
    cout << "\n���������:\n";
    cout << "----------------------------------------\n";

    if (result != "No")
    {
        cout << "������� ���������: " << result << "\n";
    }
    else
    {
        //cout << "������� �� �������\n";
        cout << "No\n";
    }

    cout << "----------------------------------------\n";
}

/**
* ������� ����� �����������
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
* �������� ������������ �����
*/
bool RingSolverApp::ValidateInput(const string& input) const
{
    if (input.empty())
    {
        cout << "������: ������ ����\n";
        return false;
    }

    if (input.find(' ') != string::npos)
    {
        cout << "������: ���� �� ������ ��������� ��������\n";
        return false;
    }

    for (char c : input)
    {
        if (!isdigit(c))
        {
            cout << "������: ���� ������ ��������� ������ �����\n";
            return false;
        }
    }

    if (input.length() < 3)
    {
        cout << "������: ����������� ����� ����� - 3 �����\n";
        return false;
    }

    return true;
}

// ����� BigInt
/**
* ����������� ����������� ������ � ������ ����
*/
BigInt::BigInt(const string& s)
{
    for (char c : s)
    {
        digits.push_back(c - '0'); // ������������ ������ � �����
    }
    reverse(digits.begin(), digits.end()); // �������������� ��� �������� ����������
}

/**
* �������� ���� ������� �����
*/
BigInt BigInt::operator+(const BigInt& other) const
{
    BigInt result("");
    int carry = 0; // ������� � ��������� ������
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
* ��������� �����
*/
bool BigInt::operator==(const BigInt& other) const
{
    return digits == other.digits;
}

/**
* �������������� ����� � ������
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