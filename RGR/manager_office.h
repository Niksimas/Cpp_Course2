#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "database.h"
using namespace std;


class manager_office_development {
private:
    DataBase data;
public:
    manager_office_development() {}

    void print_record() {
        cout << "[0] | id пользователя | Название | Описание | \n";
        for (int i : data.GetRecordListId()) {
            Record * pp = data.GetRecord(i);
            cout << "["<< pp->id << "] | "<< pp->user_id << " | " << pp->name_project << "\n\t\t" << pp->description<< endl;
        }
    }
    void print_people() {
        cout << "[0] | Имя | Фамилия | Почта \n";
        for (int i : data.GetPeopleListId()) {
            People * pp = data.GetPeople(i);
            cout << "["<< pp->id << "] | " << pp->name << " | " << pp->surname << " | " << pp->email << endl;
        }
    }

    void add_new_people() {
        string name, surname, email, check;
        while (true) {
            cout << "Введите Имя, Фамилию и Почту одной строкой через пробел: ";
            cin >> name >> surname >> email;
            cout << "Проверьте правильность ввода данных (y/n):\n"
                 << "Пользователь: " << name << "\t" << surname << "\t" << email << endl;
            while (true) {
                cin >> check;
                if (check == "y" || check == "д") {
                    data.AddPeople(People(name, surname, email));
                    cout << "Пользователь сохранен!\n";
                    return;
                }else if (check == "n" || check == "н") {
                    cout << "Отмена изменений!\n";
                    return;
                }else
                    {
                    cout << "Не корректный ввод! Попробуйте снова (y/n):\n";
                }
            }

        }
    }
    void add_new_record() {
        int id_user;
        string name_project, description, check;
        while (true) {
            cout << "Введите id пользователя: ";
            cin >> id_user;
            cout << "Введите название ПО: ";
            getline(cin, name_project);
            cout << "Введите описание: ";
            getline(cin, description);
            People * user = data.GetPeople(id_user);
            cout << "Проверьте правильность ввода данных (y/n):\n"
                << "Пользователь: " << user->name + " " + user->surname << "\nНазвание ПО: "
            << name_project << "\nОписание: " << description << endl;
            while (true) {
                cin >> check;
                if (check == "y" || check == "д") {
                    data.AddRecord(Record(id_user, name_project, description));
                    cout << "Запись сохранена!\n";
                    return;
                }else if (check == "n" || check == "н") {
                    cout << "Отмена создания!\n";
                    return;
                }else
                    {
                    cout << "Не корректный ввод! Попробуйте снова (y/n):\n";
                }
            }
        }
    }

    void deleted_record() {
        int k;
        string check;
        print_record();
        cout << "Введите номер записи: ";
        cin >> k;
        Record * delrec = data.GetRecord(k);
        People * pep = data.GetPeople(delrec->user_id);
        cout << "Вы уверены в удалении следующей записи? \nПользователь: " << pep->name + " " + pep->surname << "\nНазвание ПО: "
            << delrec->name_project << "\nОписание: " << delrec->description << "\n(y/n): ";
        while (true) {
            cin >> check;
            if (check == "y" || check == "д") {
                data.RemoveRecord(k);
                cout << "Запись удалена!\n";
                return;
            }else if (check == "n" || check == "н") {
                cout << "Отмена удаления!\n";
                return;
            }else{
                cout << "Не корректный ввод! Попробуйте снова (y/n):\n";
            }
        }
    }
    void deleted_people() {
        int k;
        string check;
        print_people();
        cout << "Введите номер пользователя: ";
        cin >> k;
        People * pep = data.GetPeople(k);
        cout << "Вы уверены в удалении следующей записи? \nПользователь: " << pep->name + " " + pep->surname + " " + pep->email + "\n";
        while (true) {
            cin >> check;
            if (check == "y" || check == "д") {
                data.RemoveRecord(k);
                cout << "Запись удалена!\n";
                return;
            }else if (check == "n" || check == "н") {
                cout << "Отмена удаления!\n";
                return;
            }else{
                cout << "Не корректный ввод! Попробуйте снова (y/n):\n";
            }
        }
    }


    void edit_record() {
        int k;
        string name_project, description, check, new_user_id;
        Record * rec;
        People * pep;
        cout << "Введите номер записи для изменения: ";
        cin >> k;
        rec = data.GetRecord(k);
        pep = data.GetPeople(rec->user_id);
        cout << "Запись выбранная для редактирования:\nПользователь: " << pep->name + " " + pep->surname + "\n"
             << "Название: " + rec->name_project + "\n" << "Описание: " + rec->description << "\n";
        while (true) {
            cout << "Введите id нового пользователя (или Enter для пропуска): ";
            cin >> new_user_id;
            if (new_user_id == "") {
                new_user_id = to_string(pep->id);
            }
            cout << "Введите название проекта (или Enter для пропуска): ";
            getline(cin, name_project);
            if (name_project == "") {
                name_project = rec->name_project;
            }
            cout << "Введите описание проекта (или Enter для пропуска): ";
            getline(cin, description);
            if (description == "") {
                description = rec->description;
            }
            pep = data.GetPeople(stoi(new_user_id));
            cout << "Проверьте правильность ввода данных (y/n):\nПользователь: " << pep->name + " " + pep->surname + "\n"
             << "Название: " + name_project + "\n" << "Описание: " + description << "\n";
            while (true) {
                cin >> check;
                if (check == "y" || check == "д") {
                    data.UpdateRecord(k, Record(rec->user_id,name_project, description));
                    cout << "Запись сохранена!\n";
                    return;
                }else if (check == "n" || check == "н") {
                    cout << "Отмена изменений!\n";
                    return;
                }else{
                    cout << "Не корректный ввод! Попробуйте снова (y/n):\n";
                }
            }

        }
    }

    void edit_people() {
        int k;
        string name, surname, email, check;
        People * pep;
        cout << "Введите номер пользователя для изменения: ";
        cin >> k;
        pep = data.GetPeople(k);
        cout << "Запись выбранная для редактирования:\nПользователь: " << pep->name + " " + pep->surname + " " + pep->email;
        while (true) {
            cout << "Введите новое имя пользователя (или Enter для пропуска): ";
            cin >> name;
            if (name == "") {
                name = pep->name;
            }
            cout << "Введите новую фамилию пользователя (или Enter для пропуска): ";
            cin >> surname;
            if (surname == "") {
                surname = pep->surname;
            }
            cout << "Введите новый email пользователя (или Enter для пропуска): ";
            cin >> email;
            if (email == "") {
                email = pep->email;
            }
            cout << "Проверьте правильность ввода данных (y/n):\nПользователь: " << name + " " + surname + " " + email;
            while (true) {
                cin >> check;
                if (check == "y" || check == "д") {
                    data.UpdatePeople(k, People(name,surname, email));
                    cout << "Запись сохранена!\n";
                    return;
                }else if (check == "n" || check == "н") {
                    cout << "Отмена изменений!\n";
                    return;
                }else{
                    cout << "Не корректный ввод! Попробуйте снова (y/n):\n";
                }
            }

        }
    }
    };