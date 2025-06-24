#ifndef ConsoleApplication3
#define ConsoleApplication3

#include <iostream>

#include <string>
#include <algorithm>

#include <Windows.h>

using namespace std;

// Представляет элемент списка
struct Node
{
    char digit; // Хранит одну цифру (0-9)
    Node* next; // Указатель на следующий узел

    // Конструктор узла
    Node(char d) : digit(d), next(nullptr) {}
};

// Класс для работы с кольцевым списком
class CircularList
{
private:
    Node* head; // Указатель на начальный узел
    int size; // Количество элементов в списке

public:
    // Конструктор создает циклический список из строки цифр
    CircularList(const string& digits); 

    // Деструктор освобождает память
    ~CircularList();
    
    // Доступ к начальному узлу
    Node* getHead() const;
    
    // Получение размера списка
    int getSize() const; 
    
    // Извлечение числа заданной длины, начиная с указанного узла
    string extractNumber(Node* start, int length) const; 
    
    // Перемещение на указанное количество узлов вперед
    Node* advance(Node* node, int steps) const; 
};

// Класс для нахождения A+B=C
class RingSolver
{
public:
    // Основной метод решения
    static string Solve(const string& digits); 
};

// Класс для пользовательского интерфейса
class RingSolverUI
{
public:
    // Главный метод, запускающий приложение
    void Run(); 

private:
    // Выводит приветствие и инструкции
    void PrintWelcomeMessage() const; 

    // Получает и валидирует ввод пользователя
    string GetValidInput() const;

    // Проверяет корректность ввода
    bool ValidateInput(const string& input) const;

    // Выводит результат решения
    void PrintResult(const string& result) const;
    
    // Выводит милое изображение
    void PrintCutePixelArt() const; 
};

#endif
