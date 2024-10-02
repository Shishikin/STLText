// STLText.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <list>
#include <numeric>
#include <map>

#include <time.h>    // нужен для работы со временем

#ifdef _WIN32
#include <windows.h>
#endif

template <typename T>
void SplitTextIntoSentences(T& sentences, std::string& text)
{
    sentences.push_back("");  // заполнить первую строку

    for (auto it = text.begin(); it < text.end(); ++it)
    {
        if (*it != '\n')
        {
            if (*it == '.' || *it == '?' || *it == '!')
            {
                if (sentences.size() > 2)      // если число строк больше 2
                {
                    if (sentences.back().size() == 0)  // последняя строка вектора пустая
                    {
                        auto it2 = std::next(sentences.begin(), sentences.size() - 2); //достучаться до элемента контейнера с нужным номером
                        (*it2).push_back(*it); // добавить в предпоследний вектор точку
                    }
                    else
                    {
                        sentences.back().push_back(*it);   // копи паста шифр 1
                        sentences.push_back("");           // копи паста шифр 2
                    }
                }
                else
                {
                    sentences.back().push_back(*it);   // копи паста шифр 1
                    sentences.push_back("");           // копи паста шифр 2
                }
            }
            else
            {
                sentences.back().push_back(*it); // копи паста шифр 1
            }

        }
    }
}


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

    std::vector<std::string> sentencesVector; // вектор предложений

    clock_t t1Vector = clock();   // время в данный момент
    SplitTextIntoSentences(sentencesVector, text);
    clock_t t2Vector = clock();

    // CLOCKS_PER_SEC - количество единиц таймера clock() в секунду
    double timeSplitTextIntoSentencesVector = static_cast<double>(t2Vector - t1Vector) / CLOCKS_PER_SEC;


    std::list<std::string> sentencesList;     // список предложений

    clock_t t1List = clock();
    SplitTextIntoSentences(sentencesList, text);
    clock_t t2List = clock();
    
    double timeSplitTextIntoSentencesList = static_cast<double>(t2List - t1List) / CLOCKS_PER_SEC;

    std::ofstream out("testOutput.txt");
    for (auto& a : sentencesVector)
    {
        out << a << '\n';
    }
    out.close();

    std::cout << "Время заполнения вектора " << timeSplitTextIntoSentencesVector << '\n';
    std::cout <<"Время заполнения списка " << timeSplitTextIntoSentencesList << '\n';

    //создаём вектор числа слов
    std::vector<int> countWordsVector;
    for (auto& a : sentencesVector)
    {
        int countWords = 0;    // счётчик слов
        int countSpace = 0;    // счётчик пробелов
        for (auto& b : a)
        {
            if (b == ' ')
            {
                if (countSpace == 0)
                {
                    ++countWords;
                    ++countSpace;
                }
            }
            else
            {
                countSpace = 0;
            }
        }
        if (a[0] == ' ')
        {
            countWordsVector.push_back(countWords);
        }
        else
        {
            countWordsVector.push_back(countWords + 1);
        }
        
    }

    std::ofstream outCountWords("CountWords.txt");
    for (auto& a : countWordsVector)
    {
        outCountWords << a << '\n';
    }
    outCountWords.close();

    int indexMax = std::distance(countWordsVector.begin(), std::max_element(countWordsVector.begin(), countWordsVector.end()));
    std::cout << countWordsVector[indexMax] << '\n';
    std::cout << sentencesVector[indexMax] << '\n';

    std::map<int, int> lengthCount;
    for (auto& a : countWordsVector)
    {
        if (lengthCount.find(a) != lengthCount.end())
        {
            ++lengthCount[a];
        }
        else
        {
            lengthCount[a] = 1;
        }
    }

    std::ofstream outLengthCount("lengthCount.txt");
    for (auto& a : lengthCount)
    {
        outLengthCount << a.first << '\t' << a.second << '\n';
    }
    outLengthCount.close();

    std::cout << "Hello World!\n";
    return 0;
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
