//
// Created by Nikita on 19.02.2024.
// обход в ширину
//Реализовать оберточный класс Graph, содержащий вершины графа и ребра между ними в виде элементов матрицы смежности. Реализовать алгоритм обхода в ширину.
//
//При помощи этого алгоритма реализовать решение следующих задач:
//      - Поиск кратчайшего пути между двумя заданными точками
//      - Нахождение кратчайшего цикла в ориентированном невзвешенном графе:
//    производим поиск в ширину из каждой вершины; как только в процессе обхода мы пытаемся пойти из текущей вершины по какому-то ребру
//    в уже посещённую вершину, то это означает, что мы нашли кратчайший цикл, и останавливаем обход в ширину; среди всех таких найденных циклов
//    (по одному от каждого запуска обхода) выбираем кратчайший.
//      - Поиск компонент связности в графе. Запускаем обход в ширину от каждой вершины, за исключением вершин, оставшихся посещёнными
//    после предыдущих запусков. Таким образом, мы выполняем обычный запуск в ширину от каждой вершины, но не обнуляем каждый раз массив,
//    за счёт чего мы каждый раз будем обходить новую компоненту связности (такие несколько запусков обхода на графе без обнуления массива
//    называются серией обходов в ширину).
//      - Найти вершину (или несколько) удаление которой разбивает граф несколько компонент связности


#include <iostream>
#include <vector>

using namespace std;

struct conn{int start, end;};
struct path{int n_points = 0; string path_point;};



class Graph{

    int points_n = 0;
    vector <int> root_point;
    vector <conn> connect;
    vector <int> used;
    vector <int> queue;
    vector <path> history_path;

public:

    Graph(){
//        points_n = 7;
//        for (int i=0; i<points_n;i++){root_point.emplace_back(-1);}
//        connect.emplace_back(conn({0, 1}));
//        connect.emplace_back(conn({0, 4}));
//        connect.emplace_back(conn({0, 2}));
//        connect.emplace_back(conn({1, 5}));
//        connect.emplace_back(conn({2, 3}));
//        connect.emplace_back(conn({2, 6}));
//        connect.emplace_back(conn({3, 1}));
//        connect.emplace_back(conn({3, 2}));
//        connect.emplace_back(conn({4, 0}));
//        connect.emplace_back(conn({4, 3}));
//        connect.emplace_back(conn({5, 6}));
//        connect.emplace_back(conn({6, 4}));

//        points_n = 5;
//        for (int i=0; i<points_n;i++){root_point.emplace_back(-1);}
//        connect.emplace_back(conn({0, 1}));
//        connect.emplace_back(conn({1, 2}));
//        connect.emplace_back(conn({2, 3}));
//        connect.emplace_back(conn({3, 4}));
//        connect.emplace_back(conn({4, 0}));

        points_n = 5;
        for (int i=0; i<points_n;i++){root_point.emplace_back(-1);}
        connect.emplace_back(conn({0, 2}));
        connect.emplace_back(conn({2, 0}));
        connect.emplace_back(conn({2, 3}));
        connect.emplace_back(conn({3, 2}));
        connect.emplace_back(conn({3, 5}));
        connect.emplace_back(conn({5, 3}));
        connect.emplace_back(conn({1, 4}));
        connect.emplace_back(conn({4, 1}));
        connect.emplace_back(conn({2, 5}));
        connect.emplace_back(conn({5, 2}));


    }

    bool check_element_used(int &val){
        for(int i = 0; i< used.size(); i++){if (used[i] == val) return true;}
        return false;
    }

    bool check_element_queue(int &val){
        for(int i = 0; i< queue.size(); i++){if (queue[i] == val) return true;}
        return false;
    }

    void clear_root_point(){for (int i=0; i<points_n;i++){root_point[i]=-1;}}

    void clear_used_point(){used.clear();}

    void short_path(int S, int E){
        clear_root_point(); // обнуляем родителей
        root_point[S] = -2;
        queue.emplace_back(S);
        while (not queue.empty()){
            used.emplace_back(queue[0]);
            for (int i=0; i < connect.size(); i++){
                // ищем связи по данному узлу  и  проверяем отсутствие элемента в посещенных вершинах
                if (connect[i].start == queue[0] and not check_element_used(connect[i].end)){
                    queue.emplace_back(connect[i].end);
                    used.emplace_back(connect[i].end);
                    if (root_point[connect[i].end] == -1) root_point[connect[i].end] = queue[0];
                }
            }
            queue.erase(queue.begin());
        }
        int tpm1 = E, tpm;
        string out = to_string(E);
        int check = 0;
        while (-1 != tpm1 and root_point[tpm1] >= 0){
            check++;
            tpm = root_point[tpm1];
            out = to_string(tpm) + " - " + out;
            tpm1 = tpm;
        }
        if (check == 0){out = "No paths!";}
        cout << "Path from " << S << " to " << E << ": " << out;
    }

    void short_cycle() {
        clear_used_point();
        int E;
        for (int S=0; S < points_n; S++) {
            clear_root_point(); // обнуляем родителей
            queue.emplace_back(S);
            root_point[S] = -2;
            while (not queue.empty()) {
                used.emplace_back(queue[0]);
                for (int i = 0; i < connect.size(); i++) { //перебираем все связи
                    if (connect[i].start == queue[0]) {//обрабатываем те что относятся к нашей точке
                        if (root_point[connect[i].end] == -1) root_point[connect[i].end] = queue[0]; // устанавливаем родительскую точку
                        if (check_element_used(connect[i].end)) { // Если конец точки попадает в посещенную -> закрываемся
                            E = connect[i].start;
                            queue.clear();
                            break;
                        }
                        else{
                            queue.emplace_back(connect[i].end);
                        }
                        used.emplace_back(connect[i].end);
                    }
                }
                if (queue.size()>0)queue.erase(queue.begin());
            }
            int tpm1 = E, tpm;
            string path_p;
            int path_num;
            path_p = to_string(E);
            while (root_point[tpm1] > 0) {
                tpm = root_point[tpm1];
                path_num++;
                path_p = to_string(tpm) + " - " + path_p;
                tpm1 = tpm;
            }
            path_p = to_string(S) + " - " + path_p;
            path path_now{path_num, path_p};
            history_path.emplace_back(path_now);
        }
        path short_path_result{1000, "123"};
        for (int i=0; i < history_path.size(); i++){
            if (short_path_result.n_points > history_path[i].n_points){
                short_path_result.n_points = history_path[i].n_points;
                short_path_result.path_point = history_path[i].path_point;
            }
        }
        cout << "Path short cycle: " << short_path_result.path_point;
    }

    int connectivity_component(){
        clear_root_point(); // обнуляем родителей
        clear_used_point(); // чистим историю посещений
        int quantity_component = 0;
        for (int S=0; S<points_n; S++){
            if (check_element_used(S)){continue;}
            quantity_component++;
            queue.emplace_back(S);
            while (not queue.empty()){
                used.emplace_back(queue[0]);
                for (int i=0; i < connect.size(); i++){
                    // ищем связи по данному узлу   и  проверяем отсутствие элемента в посещенных вершинах
                    if (connect[i].start == queue[0] and not check_element_used(connect[i].end)){
                        queue.emplace_back(connect[i].end);
                        used.emplace_back(connect[i].end);
                    }
                }
                queue.erase(queue.begin());
            }
        }
        return quantity_component;
    }

    void searching_for_connecting_vertex(){
        string point_drop = "";
        clear_root_point(); // обнуляем родителей
        int current_number_components = connectivity_component();
        for (int ignor=0; ignor<points_n; ignor++){
            clear_used_point(); // чистим историю посещений
            int quantity_component = 0;
            for (int S=0; S<points_n; S++){
                if (check_element_used(S) or S == ignor){continue;}
                quantity_component++;
                queue.emplace_back(S);
                while (not queue.empty()){
                    used.emplace_back(queue[0]);
                    for (int i=0; i < connect.size(); i++){
                        // ищем связи по данному узлу   и  проверяем отсутствие элемента в посещенных вершинах
                        if (connect[i].start == queue[0] and not check_element_used(connect[i].end) and connect[i].start != ignor){
                            queue.emplace_back(connect[i].end);
                            used.emplace_back(connect[i].end);
                        }
                    }
                    queue.erase(queue.begin());
                }
            }
            if (current_number_components < quantity_component){point_drop += " " + to_string(ignor);}
        }
        if (point_drop == ""){cout << "The graph is not split by removing 1 vertex!\n";}
        else cout << "When ~" << point_drop << " ~ vertices are removed, the graph is split into new connectivity components\n";
    }

};


int main(){
    Graph my_graph;
    my_graph.short_path(5, 1);
    cout << endl;
    my_graph.short_cycle();
    cout << endl;
    cout << "There are ~ " <<  my_graph.connectivity_component() << " ~ connectivity components in a given graph";
    cout << endl;
    my_graph.searching_for_connecting_vertex();
    return 0;
}