#ifndef NODE_H
#define NODE_H

#include <cstddef>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <strings.h>

using namespace std;

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

struct  Node{
    string name, value;
    vector <Node> subnode;

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
    void clear_subnode() {subnode.clear();}
};

class TreeXML {
    string settings_line, name_files;
    ifstream in_file;
    Node root_node;
    Node * actual_node;
public:
    TreeXML(){}

    virtual ~TreeXML() {clear_subnode_r(&root_node);}
    void print() {print_rec(&root_node);}

    void clear_subnode_r(Node * in_node) {
        if (in_node->subnode.size() > 0) {
            for (Node & subnode: in_node->subnode) {
                clear_subnode_r(&subnode);
            }
            in_node->clear_subnode();
        }
    }

    void print_rec(Node * actual_node_loc, int level=0) {
        char tab =' ';
        cout << string(level, tab) << "<" << actual_node_loc->name << "> ";
        if (actual_node_loc->subnode.size() > 0) {
            cout << endl;
            for (int i=0; i<actual_node_loc->subnode.size(); i++) {
                Node *now_node = &actual_node_loc->subnode[i];
                print_rec(now_node, level + 2);
            }
        }
        if (actual_node_loc->value != "") {
            cout << actual_node_loc->value<< " ";
            cout << "</" << actual_node_loc->name << ">\n";
        }else {
            cout << string(level, tab) << "</" << actual_node_loc->name << ">\n";
        }
    }

    Node recursive_read() {
        Node actual_node_loc;
        char sumb, sumb1;
        string op_tag, cl_tag, value;
        bool com_op_tag = false, com_cl_tag=false;
        if (settings_line == "") {
            in_file.get(sumb);
            if(sumb == '<') {
                in_file.get(sumb);
                if (sumb == '?') {
                    settings_line += '<' + sumb;
                    while (true) {
                        in_file.get(sumb);
                        if(sumb == '?') {
                            settings_line += sumb + '>';
                            in_file.get(sumb);
                            break;
                        }
                        settings_line += sumb + sumb1;
                    }
                }
            }
        }

        while (in_file.get(sumb)){ // начинаем читать файл
            if (((int)sumb <= 31 && (int)sumb > -1) || sumb == '\n'){continue;}
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
                    actual_node_loc.name = op_tag;
                    continue;
                }
                // вызываем новую итерацию для нового тега
                if (in_file.peek() != '/') {
                    in_file.unget();
                    Node subnode = recursive_read();
                    actual_node_loc.subnode.emplace_back(subnode);
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
                        actual_node_loc.value = value;
                        return actual_node_loc;
                    }else {
                        throw IncorrectClosingTagExclusion(op_tag);
                    }
                }
            } else {
                if (sumb != '\n'){value += sumb;}
            }
        }
        actual_node_loc.value = value;
        return actual_node_loc;
    }

    void clear_trash(Node * node) {
        if (node->subnode.size() > 0) {
            for (Node & sndoe: node->subnode) {
                clear_trash(&sndoe);
            }
            node->value = "";
        }
    }

    bool load_file(string * name_file) {
        name_files = *name_file;
        in_file.open("files/" + name_files + ".xml");
        // getline(in_file, settings_line);
        if (in_file.is_open()){
            root_node = recursive_read();
            clear_trash(&root_node);
            actual_node = &root_node;
            in_file.close();
            return true;
        }else{
            cout << "Файл не найден!\n";
            return false;
        }
    }
    bool load_file(string name_file) {
            name_files = name_file;
            in_file.open("files/" + name_files + ".xml");
            // getline(in_file, settings_line);
            if (in_file.is_open()){
                root_node = recursive_read();
                clear_trash(&root_node);
                actual_node = &root_node;
                in_file.close();
                return true;
            }else{
                return false;
            }
        }
    Node * get_root_node() {return &root_node;}

};


#endif //NODE_H