#include <iostream>
#include "manager_office.h"
using namespace std;



class controller {
private:
    string name;
    manager_office_development office_development;
public:
    controller() {name="default";}
    void execute() {
        menu();
        while (true) {
            string command;
            vector<string> com_args;
            cout << ">>> ";
            getline(cin, command);
            if(command == ""){continue;}
            com_args = separation(&command);
            if (com_args[0] == "help") {menu();continue;}
            else if (com_args[0] == "exit") { break;}
            else if (com_args.size() < 2){cout << "��  �� 㪠���� ��㬥��� ��� �������!";continue;}
            else if (com_args[0] == "print") {
                if (com_args[1] == "record") {
                    office_development.print_record();
                }else if (com_args[1] == "people") {
                    office_development.print_people();
                }else {
                    cout << "����� ��⥣�ਨ ���!\n";
                }
                continue;
            }
            else if (com_args[0] == "creat") {
                if (com_args[1] == "record") {
                    office_development.add_new_record();
                } else if (com_args[1] == "people") {
                    office_development.add_new_people();
                }
                continue;
            }
            else if (com_args[0] == "del") {
                if (com_args[1] == "record") {
                    office_development.add_new_record();
                } else if (com_args[1] == "people") {
                    office_development.deleted_people();
                }
                continue;
            }
            else if (com_args[0] == "edit") {
                if (com_args[1] == "record") {
                    office_development.edit_record();
                } else if (com_args[1] == "people") {
                    office_development.edit_people();
                }
                continue;
            }

            else cout << "�������⭠� �������!";
        }
    }

    static void menu() {
        cout << "�������: \n"
        << "-- help (�뢮��� ᯨ᮪ ����㯭�� ������)\n"
        << "-- print record/people (�뢮��� ᯨ᮪ ����ᥩ/��)\n"
        << "-- creat record/people (ᮧ���� ������/祫�����)\n"
        << "-- del record/people (㤠��� ������/祫�����)\n"
        << "-- edit record/people\n"
        << "-- exit\n";
    }
};