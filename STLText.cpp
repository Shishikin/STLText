// STLText.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif


int main()
{

#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    std::string pathInputFile;
    std::cout << "Введите путь к файлу из которого, будет извлекаться информаци (он должен быть без кавычек)\n";
    std::getline(std::cin, pathInputFile);   // нужно чтобы в пути использовать пробелы
    std::ifstream in(pathInputFile);    //конструктор сам в себе вызывает метод open in.open(pathInputFile)

    std::istreambuf_iterator<char> iterator_begin(in); // итератор указывающий на начало потока
    std::istreambuf_iterator<char> iterator_end;       // итератор указывает по умолчанию на eof
    
    std::string text(iterator_begin, iterator_end);    // заполняем строку файлом
    
    in.close();     // закрываем файла ввода

     

    std::vector<std::string> proposal; // вектор предложений
    proposal.push_back("");
    for (auto it = text.begin(); it < text.end(); ++it)
    {
        if (*it != '\n')
        {
            if (*it == '.' || *it == '?' || *it == '!')
            {
                if (proposal.size() > 2)      // если число строк больше 2
                {
                    if (proposal.back().size() == 0)  // последняя строка вектора пустая
                    {
                        proposal[proposal.size() - 2].push_back(*it); // добавить в предпоследний вектор точку
                    }
                    else
                    {
                        proposal.back().push_back(*it);   // копи паста шифр 1
                        proposal.push_back("");           // копи паста шифр 2
                    }
                }
                else
                {
                    proposal.back().push_back(*it);   // копи паста шифр 1
                    proposal.push_back("");           // копи паста шифр 2
                }
            }
            else
            {
                proposal.back().push_back(*it); // копи паста шифр 1
            }
            
        }
    }


    std::ofstream out("testOutput.txt");
    for (auto& a : proposal)
    {
        out << a << '\n';
    }


    out.close();

    std::cout << "коломна\n";
    std::cout << "Hello World!\n";
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
