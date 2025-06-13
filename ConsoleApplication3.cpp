#include "head.h"

int main()
{
    setlocale(LC_ALL, "russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //1
    /*TreeOperands tree;
    int choice;

    do
    {
        cout << "\nМеню:\n"
            << "1. Построить дерево из файла\n"
            << "2. Построить дерево через консоль\n"
            << "3. Сгенерировать случайное дерево\n"
            << "4. Преобразовать дерево\n"
            << "5. Вывести дерево\n"
            << "6. Вычислить выражение\n"
            << "0. Выход\n"
            << "Ваш выбор:" << endl;
        choice = getIntegerInput();
        cin.ignore();

        try
        {
            switch (choice)
            {
            case 1:
            {
                tree.buildFromFile("filename.txt");
                cout << "Дерево заполнено." << endl;
                break;
            }
            case 2:
                tree.buildFromConsole();
                cout << "Дерево заполнено." << endl;
                break;
            case 3:
                tree.buildRandom();
                cout << "Дерево заполнено." << endl;
                break;
            case 4:
                tree.transform();
                cout << "Дерево преобразовано." << endl;
                break;
            case 5:
                cout << "Текущее дерево:" << endl;
                tree.print();
                break;
            case 6:
            {
                int result = tree.evaluateNode();
                cout << "Результат вычисления: " << result << endl;
                break;
            }
            case 0:
                cout << "Выход..." << endl;
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl;
            }
        }
        catch (const exception& e)
        {
            cout << "Ошибка: " << e.what() << endl;
        }
    } while (choice != 0);*/

    //2
    //ExpressionTree tree;
    //int choice;
    //int x;
    //
    //cout << "Меню:\n";
    //cout << "1. Построить дерево из файла\n";
    //cout << "2. Построить дерево через консоль\n";
    //cout << "3. Сгенерировать случайное дерево\n";
    //cout << "Ваш выбор:" << endl;
    //choice = getIntegerInput();
    //cin.ignore();
    //
    //switch(choice)
    //{
    //    case 1:
    //        if (!tree.loadFromFile("FN1.txt"))
    //        {
    //            return 1;
    //        }
    //        break;
    //    case 2:
    //        tree.inputFromConsole();
    //        break;
    //    case 3:
    //        tree.generateRandom();
    //        break;
    //    default:
    //        cout << "Неверный выбор!" << endl;
    //        return 1;
    //}

    //// Сохранение результатов в файл
    //ofstream outFile("FN2.txt");
    //if (!outFile)
    //{
    //    cout << "Невозможно создать файл FN2" << endl;
    //    return 1;
    //}
    //outFile << "Исходное выражение: ";
    //tree.printExpression(outFile);
    //
    //outFile << "\nДерево выражения:\n";
    //tree.printTree(outFile);



    //cout << "\nИсходное выражение: ";
    //tree.printExpression(cout);
    //
    //cout << "\nДерево выражения:\n";
    //tree.printTree(cout);
    //
    //if (tree.containsX())
    //{
    //    cout << "\nВведите значение x:" << endl;
    //    x = getIntegerInput();
    //    
    //    int result = tree.evaluate(x);
    //    cout << "Значение выражения: " << result << endl;

    //    outFile << "\nЗначение выражения при x=" << x << ": " << result << endl;
    //    
    //    tree.simplify(x);
    //    cout << "\nУпрощенное дерево:\n";
    //    tree.printTree(cout);

    //    outFile << "\nУпрощенное дерево:\n";
    //    tree.printTree(outFile);
    //    
    //    cout << "\nУпрощенное выражение: ";
    //    tree.printExpression(cout);

    //    outFile << "\nУпрощенное выражение: ";
    //    tree.printExpression(outFile);
    //} 
    //else
    //{
    //    int result = tree.evaluate(0); // x не используется
    //    cout << "Значение выражения (константа): " << result << endl;

    //    outFile << "\nЗначение выражения (константа): " << result << endl;
    //}
    //
    //cout << "\nРезультаты сохранены в FN2" << endl;

    //ExpressionTree tree;
    //int x;

    //// Загрузка выражения из файла
    //tree.loadFromFile("FN1.txt");
    //
    //// Вывод оригинального дерева
    //cout << "Исходное дерево:" << endl;
    //tree.printExpression();

    //// Ввод значения x
    //cout << "\nВведите значение x: ";
    //cin >> x;

    //// Вычисление и вывод результата
    //cout << "\nРезультат выражения: " << tree.evaluate(x) << endl;

    //// Упрощение дерева и вывод результата
    //tree.replaceX(x);
    //cout << "\nУпрощённое дерево:" << endl;
    //tree.printExpression();

    //// Сохранение результатов в файл
    //tree.printToFile("FN2.txt");
    //cout << "\nРезультаты сохранены в FN2" << endl;

    //---------------
    
    //1
    //Nodee* nListHead = CreateListFromInput();
    //
    //if (!nListHead)
    //{
    //    cout << "Список пуст!" << endl;
    //    return 0;
    //}
    //
    //cout << "\nИсходный список: ";
    //PrintList(nListHead);
    //
    //BubbleSortList(nListHead);
    //cout << "\nОтсортированный список: ";
    //PrintList(nListHead);

    //// Преобразование в дерево
    //Nodee* nTreeRoot = SortedListToBST(nListHead);
    //
    //cout << "\nБинарное дерево поиска:\n";
    //PrintTreeFormatted(nTreeRoot);

    //2
    //BinaryTree<int> tree;
    //
    //cout << "Введите целые числа для построения бинарного дерева (через пробел): ";
    //string input;
    //getline(cin, input);
    //
    //istringstream iss(input);
    //int number;
    //while (iss >> number) 
    //{
    //    tree.Insert(number);
    //}
    //
    //// Выводим дерево в горизонтальном формате
    //tree.Print();

    //cout << "Обход дерева с использованием итератора (право-корень-лево): ";
    //for (auto it = tree.Begin(); it != tree.End(); ++it) 
    //{
    //    cout << *it << " ";
    //}
    //cout << endl;

    /*BinaryTree<int> tree;
    
    cout << "Enter numbers separated by spaces: ";
    string line;
    getline(cin, line);
    
    istringstream iss(line);
    int num;
    while (iss >> num) {
        tree.Insert(num);
    }
    
    cout << "Reverse in-order traversal: ";
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;*/

    //3
    /*TreeNodeе* root = buildTreeFromConsoleInput();
    
    cout << "Original tree: ";
    printTreeLevelOrder(root);
    cout << endl;
    
    DuplicateSubtreesRemover remover;
    remover.removeDuplicateSubtrees(root);
    
    cout << "After removal: ";
    printTreeLevelOrder(root);
    cout << endl;
    
    deleteTree(root);*/

    //---------------
    
    RingSolverApp app;
    app.Run();
    return 0;
}