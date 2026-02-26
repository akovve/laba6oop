#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "MySet.h"
#include "MyDictionary.h"
#include "Point2D.h"
#include "Point3D.h"

struct Applicant {
    std::string surname;
    std::string name;
    int scores[3];

    bool operator<(const Applicant& other) const {
        if (surname != other.surname) return surname < other.surname;
        return name < other.name;
    }
};

/**
 * @brief Демонстрация задания 1: работа с множествами дискотек.
 */
void Task1() {
    std::cout << "Задание 1: Дискотеки\n";

    MySet<std::string> all_discos;
    all_discos.Add("Вышка 2");
    all_discos.Add("Улица 1905 года");
    all_discos.Add("Площадь Восстания");
    all_discos.Add("Гостиница Космос");
    all_discos.Add("Юность на Cherry Tiggo 7 Pro Max");

    MySet<std::string> student1;
    student1.Add("Вышка 2");
    student1.Add("Улица 1905 года");
    student1.Add("Гостиница Космос");

    MySet<std::string> student2;
    student2.Add("Вышка 2");
    student2.Add("Площадь Восстания");

    MySet<std::string> student3;
    student3.Add("Вышка 2");
    student3.Add("Улица 1905 года");

    std::vector<MySet<std::string>> students = {student1, student2, student3};

    MySet<std::string> all_visited = students[0];
    for (size_t i = 1; i < students.size(); ++i) {
        all_visited = all_visited.Intersect(students[i]);
    }
    std::cout << "Дискотеки, посещённые ВСЕМИ студентами:\n";
    for (const auto& d : all_visited) {
        std::cout << "  " << d << "\n";
    }

    MySet<std::string> some_visited = students[0];
    for (size_t i = 1; i < students.size(); ++i) {
        some_visited = some_visited.Union(students[i]);
    }
    std::cout << "Дискотеки, посещённые НЕКОТОРЫМИ студентами:\n";
    for (const auto& d : some_visited) {
        std::cout << "  " << d << "\n";
    }

    MySet<std::string> none_visited = all_discos.Except(some_visited);
    std::cout << "Дискотеки, НЕ посещённые НИ ОДНИМ студентом:\n";
    for (const auto& d : none_visited) {
        std::cout << "  " << d << "\n";
    }
    std::cout << "\n";
}

/**
 * @brief Демонстрация задания 2: чтение из файла и отбор абитуриентов.
 */
void Task2() {
    std::cout << "Задание 2: Абитуриенты\n";

    std::ifstream file("applicants.txt");
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла applicants.txt\n";
        return;
    }

    int n;
    file >> n;
    file.ignore(); // пропустить перевод строки

    std::vector<Applicant> admitted;

    for (int i = 0; i < n; ++i) {
        std::string line;
        std::getline(file, line);
        if (line.empty()) continue;

        Applicant app;
        size_t pos1 = line.find(' ');
        size_t pos2 = line.find(' ', pos1 + 1);
        size_t pos3 = line.find(' ', pos2 + 1);
        size_t pos4 = line.find(' ', pos3 + 1);

        app.surname = line.substr(0, pos1);
        app.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        app.scores[0] = std::stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
        app.scores[1] = std::stoi(line.substr(pos3 + 1, pos4 - pos3 - 1));
        app.scores[2] = std::stoi(line.substr(pos4 + 1));

        if (app.scores[0] >= 30 && app.scores[1] >= 30 && app.scores[2] >= 30 &&
            (app.scores[0] + app.scores[1] + app.scores[2]) >= 140) {
            admitted.push_back(app);
        }
    }

    file.close();

    std::sort(admitted.begin(), admitted.end());

    std::cout << "Абитуриенты, допущенные к экзаменам в первом потоке:\n";
    for (const auto& app : admitted) {
        std::cout << app.surname << " " << app.name << "\n";
    }
    std::cout << "\n";
}

/**
 * @brief Демонстрация задания 3: трёхмерные точки.
 */
void Task3() {
    std::cout << "Задание 3: Трёхмерная точка\n";

    Point3D p1(1.0, 2.0, 3.0);
    Point3D p2(4.0, 6.0, 8.0);

    double dist = p1.DistanceTo(p2);
    std::cout << "Расстояние между точками p1(1,2,3) и p2(4,6,8) = " << dist << "\n";

    Point3D p3(0,0,0);
    Point3D p4(3,4,12);
    std::cout << "Расстояние между (0,0,0) и (3,4,12) = " << p3.DistanceTo(p4) << "\n\n";
}

int main() {
    Task1();
    Task2();
    Task3();
    return 0;
}