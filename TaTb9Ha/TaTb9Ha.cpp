// Вариант 7
// Описать класс «студенческая группа».Предусмотреть возможность работы с переменным числом студентов, 
// поиска студента по какому - либо признаку(например, по фамилии, дате рождения или номеру телефона), 
// добавления и удаления записей, сортировки по разным полям.

#include <iostream>
#include<windows.h>
using namespace std;

class Student
{
public:
    string lastName;
    string birthDate;
    string phone;
    Student* previous;
    Student* next;
};

Student* Insert(Student* p, const string lastName, const string birthDate, const string phone)
{
    if (p == nullptr)
    {
        p = new Student;
        p->lastName = lastName;
        p->birthDate = birthDate;
        p->phone = phone;
        p->next = nullptr;
        p->previous = nullptr;
        return p;
    }
    else
    {
        Student* newStudent = new Student;
        newStudent->lastName = lastName;
        newStudent->birthDate = birthDate;
        newStudent->phone = phone;
        newStudent->next = nullptr;
        newStudent->previous = p;
        p->next = newStudent;
        return newStudent;
    }
}

void Delete(const string lastName, Student* p, Student*& lastPerson)
{
    if (p == nullptr) cout << "Студент не найден\n";
    else if (p->lastName == lastName)
    {
        if (p->previous != nullptr)
        {
            if (p->next != nullptr) //есть предыдущий и следующий элемент
            {
                (p->next)->previous = p->previous;
                (p->previous)->next = p->next;
                delete p;
            }
            else //есть только предыдущий
            {
                (p->previous)->next = nullptr;
                lastPerson = p->previous;
                delete p;
            }
        }
        else if (p->next != nullptr) //есть только следующий
        {
            (p->next)->previous = nullptr;
            delete p;
        }
        else //единственный элемент
        {
            lastPerson = p->previous;
            delete p;
        }
    }
    else Delete(lastName, p->previous, lastPerson);

}

void ShowAll(Student* p)
{
    if (p == nullptr) return;
    else
    {
        cout << p->lastName << ", " << p->birthDate << ", " << p->phone << endl;
        ShowAll(p->previous);
    }
}

void SearchLastName(Student* p, const string lastName)
{
    if (p == nullptr) cout << "Студент не найден \n";
    else if (p->lastName == lastName)
    {
        cout << "Найден: " << p->lastName << ", " << p->birthDate << ", " << p->phone << endl;
    }
    else SearchLastName(p->previous, lastName);
}
void SearchBirthDate(Student* p, const string birthDate)
{
    if (p == nullptr) cout << "Студент не найден \n";
    else if (p->birthDate == birthDate)
    {
        cout << "Найден: " << p->lastName << ", " << p->birthDate << ", " << p->phone << endl;
    }
    else SearchLastName(p->previous, birthDate);
}
void SearchPhone(Student* p, const string phone)
{
    if (p == nullptr) cout << "Студент не найден \n";
    else if (p->phone == phone)
    {
        cout << "Найден: " << p->lastName << ", " << p->birthDate << ", " << p->phone << endl;
    }
    else SearchLastName(p->previous, phone);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Student* lastPerson = nullptr;

    string lastName;
    string birthDate;
    string phone;
    int choice;

    do
    {
        cout << "\nМеню рабы с группой студентов:\n";
        cout << "1. Добавить запись о студенте\n";
        cout << "2. Удалить запись о студенте\n";
        cout << "3. Вывести весь список группы\n";
        cout << "4. Поиск студента по фамилии\n";
        cout << "5. Поиск студента по дате рождения\n";
        cout << "6. Поиск студента по номеру телефона\n";
        cout << "7. Выйти\n";
        cout << "Ваш выбор: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Введите фамилию: ";
            cin >> lastName;
            cout << "Введите дату рождения: ";
            cin >> birthDate;
            cout << "Введите номер телефона: ";
            cin >> phone;
            lastPerson = Insert(lastPerson, lastName, birthDate, phone);
            break;
        case 2:
            if (lastPerson == nullptr) cout << "Записи о студентах отсутствуют.\n";
            else
            {
                cout << "Введите фамилию: ";
                cin >> lastName;
                Delete(lastName, lastPerson, lastPerson);
            }
            break;
        case 3:
            if (lastPerson == nullptr) cout << "Записи о студентах отсутствуют.\n";
            else ShowAll(lastPerson);
            break;
        case 4:
            if (lastPerson == nullptr) cout << "Записи о студентах отсутствуют.\n";
            else
            {
                cout << "Введите фамилию: ";
                cin >> lastName;
                SearchLastName(lastPerson, lastName);
            }
            break;
        case 5:
            if (lastPerson == nullptr) cout << "Записи о студентах отсутствуют.\n";
            else
            {
                cout << "Введите дату рождения: ";
                cin >> birthDate;
                SearchBirthDate(lastPerson, birthDate);
            }
            break;
        case 6:
            if (lastPerson == nullptr) cout << "Записи о студентах отсутствуют.\n";
            else
            {
                cout << "Введите номер телефона: ";
                cin >> phone;
                SearchPhone(lastPerson, phone);
            }
            break;
        case 7:
            break;
        default:
            cout << "Неверный выбор. Повторите попытку.\n";
        }
    } while (choice != 7);
}