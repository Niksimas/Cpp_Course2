#ifndef DATABASE_H
#define DATABASE_H

#include <fstream>
#include "node.h"
using namespace std;

struct People {
    int id;
    string name, surname, email;
    People() {}
    People(string &n_name, string &n_surname, string &n_email) {
        name = n_name;
        surname = n_surname;
        email = n_email;
    }
};
struct Record {
    int id, user_id;
    string name_project, description;
    Record() {}
    Record(int &n_user_id, string &n_name_project, string &n_description) {
        user_id = n_user_id;
        name_project = n_name_project;
        description = n_description;
    }
};


class DataBase {
private:
    vector<Record> records;
    vector<People> peoples;

    void LoadFromFile() {
        TreeXML People, Record;
        if (People.load_file("peoples") && Record.load_file("recordes")) {cout << "Данные загружены!\n";}
        else {cout << "Файлы не найдены!\n";}
        // People.print();
        // cout << endl;
        // Record.print();
        read_tree_in_list(&People, &Record);
    }
    void SaveToFile() {
        ofstream file_p("files/peoples.xml");
        ofstream file_r("files/recordes.xml");
        file_p << "<?xml version=\"1.0\" encoding=\"IBM866\" ?><main>";
        for (People & pp: peoples) {
            file_p << "<user>";
            file_p << "<id>" << pp.id << "</id>";
            file_p << "<name>" << pp.name << "</name>";
            file_p << "<surname>" << pp.surname << "</surname>";
            file_p << "<email>" << pp.email << "</email></user>";
        }
        file_p << "</main>";

        file_r << "<?xml version=\"1.0\" encoding=\"IBM866\" ?><main>";
        for (Record & pp: records) {
            file_r << "<record>";
            file_r << "<id>" << pp.id << "</id>";
            file_r << "<user_id>" << pp.user_id << "</user_id>";
            file_r << "<name_project>" << pp.name_project << "</name_project>";
            file_r << "<description>" << pp.description << "</description></record>";
        }
        file_r << "</main>";
        file_p.close();
        file_r.close();
    }
    void read_tree_in_list(TreeXML * root_p, TreeXML * root_r) {
        Node * root_node = root_p->get_root_node();
        for (int i =0; i < root_node->subnode.size(); i++) {
            Node * node = &root_node->subnode[i];
            if (node->name != "user"){continue;}
            string name = node->getSub("name")->value;
            string surname = node->getSub("surname")->value;
            string email = node->getSub("email")->value;
            AddPeople(People(name, surname, email));
        }

        root_node = root_r->get_root_node();
        for (int i =0; i < root_node->subnode.size(); i++) {
            Node * node = &root_node->subnode[i];
            if (node->name != "record"){continue;}
            int user_id = stoi(node->getSub("user_id")->value);
            string name_project = node->getSub("name_project")->value;
            string description = node->getSub("description")->value;
            AddRecord(Record(user_id, name_project, description));
        }
    }
public:

    DataBase() {LoadFromFile();}
    ~DataBase(){SaveToFile();}

    Record * GetRecord(int record_id) {
        for (Record & rr: records) {
            if (rr.id == record_id) {
                return &rr;
            }
        }
        return nullptr;
    }
    People * GetPeople(int user_id) {
        for (People & pp: peoples) {
            if (pp.id == user_id) {
                return &pp;
            }
        }
        return nullptr;
    }

    vector<int> GetRecordListId() {
        vector<int> listId;
        for (Record & rr: records) {
            listId.emplace_back(rr.id);
        }
        return listId;
    }
    vector<int> GetPeopleListId() {
        vector<int> listId;
        for (People & pp: peoples) {
            listId.emplace_back(pp.id);
        }
        return listId;
    }

    int AddRecord(Record * new_rec) {
        if (peoples.size() > 0) {
            new_rec->id = records[records.size()-1].id + 1;
        }else {
            new_rec->id = 1;
        }
        records.emplace_back(*new_rec);
        return new_rec->id;
    }
    int AddRecord(Record new_rec) {
        if (records.size() > 0) {
            new_rec.id = records[records.size()-1].id + 1;
        }else {
            new_rec.id = 1;
        }
        records.emplace_back(new_rec);
        return new_rec.id;
    }
    int AddPeople(People new_pep) {
        if (peoples.size() > 0) {
            new_pep.id = peoples[peoples.size()-1].id + 1;
        }else {
            new_pep.id = 1;
        }
        peoples.emplace_back(new_pep);
        return new_pep.id;
    }
    int AddPeople(People * new_pep) {
        if (peoples.size() > 0) {
            new_pep->id = peoples[peoples.size()-1].id + 1;
        }else {
            new_pep->id = 1;
        }
        peoples.emplace_back(*new_pep);
        return new_pep->id;
    }

    void RemovePeople(int id) {
        for (int i=0; i < peoples.size(); i++) {
            if (peoples[i].id == id) {
                peoples.erase(peoples.begin() + (i - 1));
                return;
            }
        }
    }
    void RemoveRecord(int id) {
        for (int i=0; i < records.size(); i++) {
            if (records[i].id == id) {
                records.erase(records.begin() + (i - 1));
                return;
            }
        }
    }

    bool UpdateRecord(int record_id, Record * new_data_r) {
        Record * updt_p = GetRecord(record_id);
        if (updt_p != nullptr) {
            updt_p = new_data_r;
            return true;
        }
        return false;
    }
    bool UpdatePeople(int user_id, People * new_data_p) {
        People * updt_p = GetPeople(user_id);
        if (updt_p != nullptr) {
            updt_p = new_data_p;
            return true;
        }
        return false;
    }
    bool UpdateRecord(int record_id, Record new_data_r) {
        Record * updt_p = GetRecord(record_id);
        if (updt_p != nullptr) {
            updt_p = &new_data_r;
            return true;
        }
        return false;
    }
    bool UpdatePeople(int user_id, People new_data_p) {
        People * updt_p = GetPeople(user_id);
        if (updt_p != nullptr) {
            updt_p = &new_data_p;
            return true;
        }
        return false;
    }
};

#endif //DATABASE_H
