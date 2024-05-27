//
// Created by Nikita on 15.04.2024.
//
// Множественное дерево
// Реализовать класс multiplTree, реализующий множественное дерево хранения данных. Каждый узел имеет текстовое название
// и может хранить тестовые данные и указатели на неограниченное число потомков.
// Для узла дерева реализовать следующие методы:
// setName - установка имени узла.
// getName - получение имени узла.
// setValue (перегрузить данный метод для установки текстового значения, значения double, int, данные сохраняются в виде текстового значения),
// getValue - получение текстового значения узла.
// isInt - проверяет можно ли представить данные в виде целого числа.
// isDouble - проверяет можно ли представить данные узла в виде действительного числа.
// getInt - получение данных узла в виде целого числа. При невозможности выдает 0.
// getDouble - получение данных узла  действительного числа. При невозможности выдает 0.
// getCountSub - выдает количество потомков.
// getSub(i) - выдает потомка по порядковому номеру. При невозможности выдает Null.
// getSub(name) - выдает потомка по порядковому имени. При невозможности выдает Null.
// addSub - добавляет узел потомок.
// Для всего класса реализовать поиск узла (первое вхождение) по заданному  имени,
//
// Created by Nikita on 22.04.2024.
//
// добавить чтение параметров, выпадение ошибок при неправильной структуре
//
// Created by Nikita on 29.04.2024.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

vector <string> separation(string *line_command, char sumb_sep = ' ') {
    vector <string> list_arg;
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
    if (tmp != "") {
        list_arg.emplace_back(tmp);
    }

    // for (string a: list_arg) {
    //     cout << a << "||";
    // }
    // cout << endl;
    return list_arg;
}

set <pair<int, int>> ererer;


struct IncorrectClosingTagExclusion{
    string open_tag;
    IncorrectClosingTagExclusion(string a){open_tag=a;}
};

struct Parametrs {string name, value;};

class Node{
    string name, value;
    vector <Parametrs> params;
    vector <Node> subnode;
    Node * parent = nullptr;
public:
    void setName(string *new_name){name = *new_name;}
    string getName(){ return name; }

    void setParent(Node *new_name){parent = new_name;}
    Node * getParent(){ return parent; }
    string getNameParent(){ return parent->getName(); }

    void setValue(const string *new_value){value = *new_value;}
    void setValue(const int *new_value){value = to_string(*new_value);}
    void setValue(const double *new_value){value = to_string(*new_value);}
    string getValue(){ return value; }

    bool isInt(){
        for (int i = 0; i < value.size(); i++) {
            if (!(value[i] >= '0' && value[i] <= '9')) {return false;}
        }
        return true;
    }

    bool isDouble(){
        int p=0;
        for (int i = 0; i < value.size(); i++) {
            if (!(value[i] >= '0' && value[i] <= '9')) {
                return false;
            }else if(value[i] != '.'){
                if (p == 0){
                    p++;
                    continue;
                }
                return false;
            }
        }
        return true;
    }

    int getInt(){if(isInt()){return stoi(value);}else return 0;}
    double getDouble(){if(isDouble()){return stoi(value);}else return 0;}
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

    bool chekSub(const string *name_node){
        // if (subnode.size() == 0){return false;}
        for (Node &actual_node: subnode){
            if (actual_node.name == *name_node){
                return true;
            }
        }
        return false;
    }

    Parametrs* getParam(const string *name_param){
        for (Parametrs &actual_node: params){
            if (actual_node.name == *name_param){
                return &actual_node;
            }
        }
        return NULL;
    }

    Parametrs* getParam(const int num_param){
        if (params.size() > num_param){
            return &params[num_param];
        }
        return NULL;
    }

    void addSub(Node *new_sub_node){
        subnode.emplace_back(*new_sub_node);
    }

    void addParam(string *name_param, string *value_param){
        Parametrs new_param {*name_param, *value_param};
        params.emplace_back(new_param);
    }

    int getConstParam() {return params.size();}

    void clear_subnode() {
        subnode.clear();
    }
    void clear_param() {
        params.clear();
    }

};

class MultiplTree{
    string settings_line, name_files;
    ifstream in_file;
    ofstream out_file;
    Node root_node;
    Node * actual_node;
public:
    MultiplTree(){}

    virtual ~MultiplTree() {clear_subnode_r(&root_node);}

    void clear_subnode_r(Node * in_node) {
        if (in_node->getConstSub() > 0) {
            for (int i =0; i < in_node->getConstSub()-1; i++) {
                clear_subnode_r(in_node->getSub(&i));
                in_node->clear_subnode();
                in_node->clear_param();
            }
        }
    }

    void print_rec(Node * actual_node_loc, int level=0) {
        char tab =' ';
        cout << string(level, tab) << "<" << actual_node_loc->getName();
        for (int i=0; i < actual_node_loc->getConstParam(); i++) {
            cout << " " << actual_node_loc->getParam(i)->name << "=" << actual_node_loc->getParam(i)->value;
        }
        // cout << " link: " << &actual_node_loc;
        // cout << " parent: " << actual_node_loc->getParent();
        cout << ">\n";
        if (actual_node_loc->getConstSub() > 0) {
            for (int i=0; i<actual_node_loc->getConstSub(); i++) {
                Node *now_node = actual_node_loc->getSub(&i);
                print_rec(now_node, level + 2);
            }
        }
        if (actual_node_loc->getValue() != "") {
            cout << string(level+2, tab) << actual_node_loc->getValue() << endl;
        }
        cout << string(level, tab) << "</" << actual_node_loc->getName() << ">\n";
    }

    void save_rec(Node * actual_node_loc, int level=0) {
        char tab =' ';
        out_file << string(level, tab) << "<" << actual_node_loc->getName() << ">\n";
        if (actual_node_loc->getConstSub() > 0) {
            for (int i=0; i<actual_node_loc->getConstSub(); i++) {
                Node *now_node = actual_node_loc->getSub(&i);
                save_rec(now_node, level+2);
            }
        }
        if (actual_node_loc->getValue() != "") {
            out_file << string(level, tab) << actual_node_loc->getValue() << endl;
        }
        out_file << string(level, tab) << "</" << actual_node_loc->getName() << ">\n";
    }

    Node recursive_read() {
        Node actual_node_loc;
        char sumb;
        string op_tag, cl_tag, value;
        bool com_op_tag = false, com_cl_tag=false;
        while (in_file.get(sumb)){ // начинаем читать файл
            if (sumb == '\n'){continue;}
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
                    if (params.size() > 1) {
                        op_tag = params[0];
                        for (int i = 1; i < params.size(); i++) {
                            vector<string> atrib = separation(&params[i], '=');
                            actual_node_loc.addParam(&atrib[0], &atrib[1]);
                        }
                    }
                    actual_node_loc.setName(&op_tag);
                    continue;
                }
                // вызываем новую итерацию для нового тега
                if (in_file.peek() != '/') {
                    in_file.unget();
                    Node subnode = recursive_read();
                    subnode.setParent(&actual_node_loc);
                    // cout << actual_node_loc.getName() << " -> " << subnode.getName() << "\n"
                    // << &actual_node_loc << " -> " << subnode.getParent() << endl;
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
                value += sumb;
            }
        }
        actual_node_loc.setValue(&value);
        return actual_node_loc;
    }

    void setParentRec(Node * node_edit, Node * link_node_root =nullptr) {
        for (int i =0; i < node_edit->getConstSub(); i ++) {
            setParentRec(node_edit->getSub(&i), node_edit);
        }
        if (node_edit->getName() == root_node.getName()) {return;}
        node_edit->setParent(link_node_root);
    }

    void load_file(string *name_file) {
        name_files = *name_file;
        in_file.open("../8.9.10--15-04-24/" + *name_file + ".xml");
        getline(in_file, settings_line);
        if (in_file.is_open()){
            root_node = recursive_read();
            setParentRec(&root_node);
            actual_node = &root_node;
            cout << "Файл успещно загружен!\n";
            in_file.close();
        }else{
            cout << "Файл не найден!\n";
        }
    }

    void save_file(string *name_file=nullptr) {
        if (!name_file){name_file=&name_files;}
        out_file.open("../8.9.10--15-04-24/n_" + *name_file + ".xml");
        if (!out_file.is_open()) {
            cout << "Файл не найден!\n";
            return;
        }
        out_file << settings_line << endl;
        save_rec(&root_node);
        out_file.close();
    }

    void cd_tree(string *path=nullptr) {
        if (!path) {
            if (actual_node->getParent() == nullptr) {
                cout << "Вы в корневом узле\n";
            }else {
                actual_node = &root_node;
            }
            return;
        }else {
            vector<string> path_node = separation(path, '/');
            Node * tmp_ac_node = actual_node;
            for (string &element_path: path_node) {
                if (element_path == "..") {
                    if (!(actual_node->getParent() == nullptr)) {
                        tmp_ac_node = actual_node->getParent();
                        actual_node=tmp_ac_node;
                    }
                }else if(tmp_ac_node->chekSub(&element_path)) {
                    tmp_ac_node = tmp_ac_node->getSub(&element_path);
                }else {
                    cout << "Такого узла не существует!\n";
                    return;
                }
            }
            actual_node = tmp_ac_node;
        }
    }

    void edit_node(vector<string> & atrib) {
        if (atrib.size() < 3){cout << "Недостаточно параметров\n";}
        if (atrib[1] == "name"){
           actual_node->setName(&atrib[2]);
        }else
        if (atrib[1] == "val"){
            if (actual_node->getConstSub() > 1) {
                cout << "Узел содержит дочерние узлы, редактирование значения невозможно";
            }else {
                actual_node->setValue(&atrib[2]);
            }
        }else
        if (atrib[1] == "atr"){

        }
    }

    void del_node(){}

    void add_subnode(){}

    void ls() {
        for (int i=0; i < actual_node->getConstSub();i++) {
            if (i%4 == 0 && i !=0) {cout << endl;}
            cout << actual_node->getSub(&i)->getName() << "\t";
            if (i == actual_node->getConstSub() -1) { cout << endl;}
        }
    }

    void execute() {
        string command;
        vector<string> comm_args;
        while (true) {
            try{
                if (actual_node->getParent())
                cout << ">>> ";
                getline(cin, command);
                comm_args = separation(&command);
                if (comm_args[0] == "exit") {break;} else
                if (comm_args[0] == "ls") {ls();} else
                if (comm_args[0] == "edit") {
                    if (comm_args.size() > 1) {
                        edit_node(comm_args);
                    }else {
                        cout << "Вы не указали параметры!\n";
                    }
                } else
                if (comm_args[0] == "load") {
                    if (comm_args.size() > 1) {
                        load_file(&comm_args[1]);
                    }else {
                        cout << "Вы не указали название файла!\n";
                    }
                } else
                if (comm_args[0] == "save") {
                    if (comm_args.size() > 1) {
                        save_file(&comm_args[1]);
                    }else {
                        save_file();
                    }
                }else
                if (comm_args[0] == "cd") {
                    if (comm_args.size() > 1) {
                        cd_tree(&comm_args[1]);
                    }else {
                        cd_tree();
                    }
                }else
                if (comm_args[0] == "info") {
                    cout << "Name: " << actual_node->getName() << "\n";
                    if (actual_node->getConstParam() != 0) {
                        cout << "Parametrs: \n";
                        // for (Parametrs &tmp: actual_node->getSub())
                    }
                }else
                if (command == "print") {
                    print_rec(&root_node);
                }else{
                    cout << "Такой команды не существует!\n>>> ";
                }
            }catch (IncorrectClosingTagExclusion &ex) {
                cerr << "Для открывающего тега: " << ex.open_tag << " не указан закрывающий тег";

            }
        }
    }
};


int main(){
    try {
        MultiplTree MT;
        MT.execute();
    }catch (IncorrectClosingTagExclusion &ex) {
        cerr << "Для открывающего тэга: " << ex.open_tag << " не указан закрывающий тег\n";
    }
    //
    // string * a = nullptr;
    // if (!a){cout << "Ok";}
};