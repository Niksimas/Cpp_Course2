//
// Created by nikita on 26.05.2024.
//

#ifndef NODE_H
#define NODE_H

#include <cstddef>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct BusStop {
    string name_stops; vector <int> num_buses;
    void setBus(int *numb) {
        num_buses.emplace_back(*numb);
    }
};
struct Route {string name_bus;vector <int> list_stop;};
struct IncorrectClosingTagExclusion{string open_tag;IncorrectClosingTagExclusion(string a){open_tag=a;}};

vector<string>separation(string *line_command, char sumb_sep = ' ') {
    vector<string> list_arg;
    string tmp;
    for (char sumb: *line_command) {
        if (sumb != sumb_sep) {
            tmp += sumb;
        }else {
            if (tmp == "") continue;
            list_arg.emplace_back(tmp);
            tmp = "";
        }
    }
    list_arg.emplace_back(tmp);
    return list_arg;
}
vector <int> separation_int(string *line_command, char sumb_sep = ' ') {
    vector <int> list_arg;
    string tmp;
    for (char sumb: *line_command) {
        if (sumb != sumb_sep) {
            tmp += sumb;
        }else {
            if (tmp == "") continue;
            list_arg.emplace_back(stoi(tmp));
            tmp = "";
        }
    }
    if (tmp != "") {
        list_arg.emplace_back(stoi(tmp));
    }
    return list_arg;
}

class Node{
    string name, value;
    vector <Node> subnode;
public:
    void setName(string *new_name){name = *new_name;}
    string getName(){ return name; }
    void setValue(const string *new_value){value = *new_value;}
    void setValue(const int *new_value){value = to_string(*new_value);}
    void setValue(const double *new_value){value = to_string(*new_value);}
    string getValue(){ return value; }
    int getConstSub(){ return subnode.size();}

    Node* getSub(const int *i){
        if (*i >= subnode.size() and *i < 0){
            return NULL;
        }else{
            return &subnode[*i];
        }
    }
    Node* getSub(const string *name_node){
        for (Node &actual_node: subnode){
            if (actual_node.name == *name_node){
                return &actual_node;
            }
        }
        return NULL;
    }
    Node* getSub(const string name_node){
        for (Node &actual_node: subnode){
            if (actual_node.name == name_node){
                return &actual_node;
            }
        }
        return NULL;
    }
    bool chekSub(const string *name_node){
        for (Node &actual_node: subnode){
            if (actual_node.name == *name_node){
                return true;
            }
        }
        return false;
    }
    void addSub(Node *new_sub_node){subnode.emplace_back(*new_sub_node);}
    void clear_subnode() {subnode.clear();}
};

class StructBusStops {
    string settings_line, name_files;
    ifstream in_file;
    Node root_node;
    Node * actual_node;
public:
    StructBusStops(){}

    virtual ~StructBusStops() {clear_subnode_r(&root_node);}
    void print() {print_rec(&root_node);}

    void clear_subnode_r(Node * in_node) {
        if (in_node->getConstSub() > 0) {
            for (int i =0; i < in_node->getConstSub()-1; i++) {
                clear_subnode_r(in_node->getSub(&i));
                in_node->clear_subnode();
            }
        }
    }

    void print_rec(Node * actual_node_loc, int level=0) {
        char tab =' ';
        cout << string(level, tab) << "<" << actual_node_loc->getName() << "> ";
        if (actual_node_loc->getConstSub() > 0) {
            cout << endl;
            for (int i=0; i<actual_node_loc->getConstSub(); i++) {
                Node *now_node = actual_node_loc->getSub(&i);
                print_rec(now_node, level + 2);
            }
        }
        if (actual_node_loc->getValue() != "") {
            cout << actual_node_loc->getValue()<< " ";
            cout << "</" << actual_node_loc->getName() << ">\n";
        }else {
            cout << string(level, tab) << "</" << actual_node_loc->getName() << ">\n";
        }
    }

    Node recursive_read() {
        Node actual_node_loc;
        char sumb;
        string op_tag, cl_tag, value;
        bool com_op_tag = false, com_cl_tag=false;
        while (in_file.get(sumb)){ // начинаем читать файл
            if ((int)sumb <= 32 || sumb == '\n'){continue;}
            if (sumb == '<') { // проверяем следующий символ
                // собираем отрывающий тег, если ещё не собран
                if (!com_op_tag){
                    in_file.get(sumb);
                    while (sumb != '>') {
                        op_tag += sumb;
                        in_file.get(sumb);
                    }
                    com_op_tag = true;
                    vector<string> params = separation(&op_tag);
                    actual_node_loc.setName(&op_tag);
                    continue;
                }
                // вызываем новую итерацию для нового тега
                if (in_file.peek() != '/') {
                    in_file.unget();
                    Node subnode = recursive_read();
                    actual_node_loc.addSub(&subnode);
                }
                if (in_file.peek() == '/' && !com_cl_tag) {
                    in_file.get(sumb);
                    in_file.get(sumb);
                    while (sumb != '>') {
                        cl_tag += sumb;
                        in_file.get(sumb);
                    }
                    if (op_tag == cl_tag) {
                        com_cl_tag = true;
                        actual_node_loc.setValue(&value);
                        return actual_node_loc;
                    }else {
                        throw IncorrectClosingTagExclusion(op_tag);
                    }
                }
            } else {
                if (sumb != '\n'){value += sumb;}
            }
        }
        actual_node_loc.setValue(&value);
        return actual_node_loc;
    }

    void load_file(string * name_file) {
        name_files = *name_file;
        in_file.open("../7--08-04-24/" + *name_file + ".xml");
        getline(in_file, settings_line);
        if (in_file.is_open()){
            root_node = recursive_read();
            actual_node = &root_node;
            cout << "Файл успещно загружен!\n";
            in_file.close();
        }else{
            cout << "Файл не найден!\n";
        }
    }

    Node * get_root_node() {return &root_node;}

};


#endif //NODE_H