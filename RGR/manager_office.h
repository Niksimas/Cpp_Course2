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
        cout << "[0] | id ���짮��⥫� | �������� | ���ᠭ�� | \n";
        for (int i : data.GetRecordListId()) {
            Record * pp = data.GetRecord(i);
            cout << "["<< pp->id << "] | "<< pp->user_id << " | " << pp->name_project << "\n\t\t" << pp->description<< endl;
        }
    }
    void print_people() {
        cout << "[0] | ��� | ������� | ���� \n";
        for (int i : data.GetPeopleListId()) {
            People * pp = data.GetPeople(i);
            cout << "["<< pp->id << "] | " << pp->name << " | " << pp->surname << " | " << pp->email << endl;
        }
    }

    void add_new_people() {
        string name, surname, email, check;
        while (true) {
            cout << "������ ���, ������� � ����� ����� ��ப�� �१ �஡��: ";
            cin >> name >> surname >> email;
            cout << "�஢���� �ࠢ��쭮��� ����� ������ (y/n):\n"
                 << "���짮��⥫�: " << name << "\t" << surname << "\t" << email << endl;
            while (true) {
                cin >> check;
                if (check == "y" || check == "�") {
                    data.AddPeople(People(name, surname, email));
                    cout << "���짮��⥫� ��࠭��!\n";
                    return;
                }else if (check == "n" || check == "�") {
                    cout << "�⬥�� ���������!\n";
                    return;
                }else
                    {
                    cout << "�� ���४�� ����! ���஡�� ᭮�� (y/n):\n";
                }
            }

        }
    }
    void add_new_record() {
        int id_user;
        string name_project, description, check;
        while (true) {
            cout << "������ id ���짮��⥫�: ";
            cin >> id_user;
            cout << "������ �������� ��: ";
            getline(cin, name_project);
            cout << "������ ���ᠭ��: ";
            getline(cin, description);
            People * user = data.GetPeople(id_user);
            cout << "�஢���� �ࠢ��쭮��� ����� ������ (y/n):\n"
                << "���짮��⥫�: " << user->name + " " + user->surname << "\n�������� ��: "
            << name_project << "\n���ᠭ��: " << description << endl;
            while (true) {
                cin >> check;
                if (check == "y" || check == "�") {
                    data.AddRecord(Record(id_user, name_project, description));
                    cout << "������ ��࠭���!\n";
                    return;
                }else if (check == "n" || check == "�") {
                    cout << "�⬥�� ᮧ�����!\n";
                    return;
                }else
                    {
                    cout << "�� ���४�� ����! ���஡�� ᭮�� (y/n):\n";
                }
            }
        }
    }

    void deleted_record() {
        int k;
        string check;
        print_record();
        cout << "������ ����� �����: ";
        cin >> k;
        Record * delrec = data.GetRecord(k);
        People * pep = data.GetPeople(delrec->user_id);
        cout << "�� 㢥७� � 㤠����� ᫥���饩 �����? \n���짮��⥫�: " << pep->name + " " + pep->surname << "\n�������� ��: "
            << delrec->name_project << "\n���ᠭ��: " << delrec->description << "\n(y/n): ";
        while (true) {
            cin >> check;
            if (check == "y" || check == "�") {
                data.RemoveRecord(k);
                cout << "������ 㤠����!\n";
                return;
            }else if (check == "n" || check == "�") {
                cout << "�⬥�� 㤠�����!\n";
                return;
            }else{
                cout << "�� ���४�� ����! ���஡�� ᭮�� (y/n):\n";
            }
        }
    }
    void deleted_people() {
        int k;
        string check;
        print_people();
        cout << "������ ����� ���짮��⥫�: ";
        cin >> k;
        People * pep = data.GetPeople(k);
        cout << "�� 㢥७� � 㤠����� ᫥���饩 �����? \n���짮��⥫�: " << pep->name + " " + pep->surname + " " + pep->email + "\n";
        while (true) {
            cin >> check;
            if (check == "y" || check == "�") {
                data.RemoveRecord(k);
                cout << "������ 㤠����!\n";
                return;
            }else if (check == "n" || check == "�") {
                cout << "�⬥�� 㤠�����!\n";
                return;
            }else{
                cout << "�� ���४�� ����! ���஡�� ᭮�� (y/n):\n";
            }
        }
    }


    void edit_record() {
        int k;
        string name_project, description, check, new_user_id;
        Record * rec;
        People * pep;
        cout << "������ ����� ����� ��� ���������: ";
        cin >> k;
        rec = data.GetRecord(k);
        pep = data.GetPeople(rec->user_id);
        cout << "������ ��࠭��� ��� ।���஢����:\n���짮��⥫�: " << pep->name + " " + pep->surname + "\n"
             << "��������: " + rec->name_project + "\n" << "���ᠭ��: " + rec->description << "\n";
        while (true) {
            cout << "������ id ������ ���짮��⥫� (��� Enter ��� �ய�᪠): ";
            cin >> new_user_id;
            if (new_user_id == "") {
                new_user_id = to_string(pep->id);
            }
            cout << "������ �������� �஥�� (��� Enter ��� �ய�᪠): ";
            getline(cin, name_project);
            if (name_project == "") {
                name_project = rec->name_project;
            }
            cout << "������ ���ᠭ�� �஥�� (��� Enter ��� �ய�᪠): ";
            getline(cin, description);
            if (description == "") {
                description = rec->description;
            }
            pep = data.GetPeople(stoi(new_user_id));
            cout << "�஢���� �ࠢ��쭮��� ����� ������ (y/n):\n���짮��⥫�: " << pep->name + " " + pep->surname + "\n"
             << "��������: " + name_project + "\n" << "���ᠭ��: " + description << "\n";
            while (true) {
                cin >> check;
                if (check == "y" || check == "�") {
                    data.UpdateRecord(k, Record(rec->user_id,name_project, description));
                    cout << "������ ��࠭���!\n";
                    return;
                }else if (check == "n" || check == "�") {
                    cout << "�⬥�� ���������!\n";
                    return;
                }else{
                    cout << "�� ���४�� ����! ���஡�� ᭮�� (y/n):\n";
                }
            }

        }
    }

    void edit_people() {
        int k;
        string name, surname, email, check;
        People * pep;
        cout << "������ ����� ���짮��⥫� ��� ���������: ";
        cin >> k;
        pep = data.GetPeople(k);
        cout << "������ ��࠭��� ��� ।���஢����:\n���짮��⥫�: " << pep->name + " " + pep->surname + " " + pep->email;
        while (true) {
            cout << "������ ����� ��� ���짮��⥫� (��� Enter ��� �ய�᪠): ";
            cin >> name;
            if (name == "") {
                name = pep->name;
            }
            cout << "������ ����� 䠬���� ���짮��⥫� (��� Enter ��� �ய�᪠): ";
            cin >> surname;
            if (surname == "") {
                surname = pep->surname;
            }
            cout << "������ ���� email ���짮��⥫� (��� Enter ��� �ய�᪠): ";
            cin >> email;
            if (email == "") {
                email = pep->email;
            }
            cout << "�஢���� �ࠢ��쭮��� ����� ������ (y/n):\n���짮��⥫�: " << name + " " + surname + " " + email;
            while (true) {
                cin >> check;
                if (check == "y" || check == "�") {
                    data.UpdatePeople(k, People(name,surname, email));
                    cout << "������ ��࠭���!\n";
                    return;
                }else if (check == "n" || check == "�") {
                    cout << "�⬥�� ���������!\n";
                    return;
                }else{
                    cout << "�� ���४�� ����! ���஡�� ᭮�� (y/n):\n";
                }
            }

        }
    }
    };