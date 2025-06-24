#include "head.h"

int main()
{
    setlocale(LC_ALL, "russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    RingSolverUI app;
    app.Run();
    return 0;
}
