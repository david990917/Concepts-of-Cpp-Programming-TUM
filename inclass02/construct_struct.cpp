#include <iostream>
#include <string>

struct Student
{
    unsigned int id;
    std::string name;
    std::string study_program;
};

int main()
{
    Student Hanwen = {0, "Hanwen", "Info"};
    std::cout << Hanwen.name << '\n';
    std::cout << Hanwen.study_program << '\n';
}
