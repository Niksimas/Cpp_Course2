//
// Created by Nikita on 26.02.2024.

//
//  -- Поиск цикла в ориентированном графе
//  -- Проверка графа на двудольность
//


#include <iostream>
#include <vector>

using namespace std;

struct conn{int start, end;};


class Graph{

    int points_n = 0;
    bool  IsBipartite = true;
    bool  IsCycle = false;
    vector <conn> connect;
    vector <int> Color;
    int num_color[3] {1, 2, 1};
    vector <int> queue;


public:

    Graph(){
//// напрваленый граф
        points_n = 7;
        connect.emplace_back(conn({0, 1}));
        connect.emplace_back(conn({0, 4}));
        connect.emplace_back(conn({0, 2}));
        connect.emplace_back(conn({1, 5}));
        connect.emplace_back(conn({2, 3}));
        connect.emplace_back(conn({2, 6}));
        connect.emplace_back(conn({3, 1}));
        connect.emplace_back(conn({3, 2}));
        connect.emplace_back(conn({4, 0}));
        connect.emplace_back(conn({4, 3}));
        connect.emplace_back(conn({5, 6}));
        connect.emplace_back(conn({6, 4}));

//// граф с двумя остравками
//        points_n = 5;
//        connect.emplace_back(conn({0, 2}));
//        connect.emplace_back(conn({2, 0}));
//        connect.emplace_back(conn({2, 3}));
//        connect.emplace_back(conn({3, 2}));
//        connect.emplace_back(conn({3, 5}));
//        connect.emplace_back(conn({5, 3}));
//        connect.emplace_back(conn({1, 4}));
//        connect.emplace_back(conn({4, 1}));
//        connect.emplace_back(conn({2, 5}));
//        connect.emplace_back(conn({5, 2}));

//// Это двудольный граф
//        points_n = 5;
//        connect.emplace_back(conn({0, 1}));
//        connect.emplace_back(conn({1, 0}));
//        connect.emplace_back(conn({1, 3}));
//        connect.emplace_back(conn({3, 1}));
//        connect.emplace_back(conn({1, 4}));
//        connect.emplace_back(conn({4, 1}));
//        connect.emplace_back(conn({4, 2}));
//        connect.emplace_back(conn({2, 4}));
//        connect.emplace_back(conn({5, 4}));
//        connect.emplace_back(conn({4, 5}));

        for (int i=0; i<points_n;i++){Color.emplace_back(0);}
    }

    void print_Color(){
        for (int i=0; i<points_n;i++){cout << Color[i]<< " ";}
        cout << endl;
    }

    void print_used(){
        if (not queue.empty()){
            for (int i=0; i<points_n;i++){cout << queue[i]<< " ";}
        }
        cout << endl;
    }

    void clear_parametr(){
        IsBipartite = true;
        IsCycle = false;
        for (int i=0; i<points_n;i++){Color[i]=0;}
        queue.emplace_back(0);
        queue.clear();
    }


//####################################################################################################################//
//################################### Рекурсивная проверка на двудольность ###########################################//
//####################################################################################################################//
    void recursion_bipartite(const int *num_point){
        for (int conn_num=0; conn_num < connect.size(); conn_num++){ //// перебираем все связи для имеющейся точки
            if (connect[conn_num].start == *num_point and IsBipartite){ //// проверяем что связь относится к точке
                conn actual_conn = connect[conn_num];
//                cout << "Conn: " << actual_conn.start << " - " << actual_conn.end << "->";
                //// если цвет конечной точки 0 запуск рекурсии для этой точки (и окрашивание в противоположный цвет)
                if (Color[actual_conn.end] == 0){
                    Color[actual_conn.end] = num_color[Color[actual_conn.start]];
//                    cout << "new point " << Color[actual_conn.start] << " - " << Color[actual_conn.end] << endl;
                    recursion_bipartite(&actual_conn.end);
                    //// Если цвета совпадают, изменение параметра IsBipartite
                } else if (Color[actual_conn.start] == Color[actual_conn.end]){
//                    cout << "return s=n\n";
                    IsBipartite = false;
                    return;
                }
//                cout << "skip\n";
            }
        }
    }

    void check_bipartite_recursion(){
        clear_parametr();
        Color[0] = 1;
        int start = 0;
        recursion_bipartite(&start);
        if (IsBipartite){ // проверяем параметр двудольности и выводим ответ
            cout << "The graph is bipartite. (recursion_bipartite)" << endl;
            return;
        }
        cout << "The graph is not bipartite. (recursion_bipartite)" << endl;
    }


//####################################################################################################################//
//################################### Рекурсивная проверка на наличие цикла ##########################################//
//####################################################################################################################//
    void recursion_cycle(const int* num_point){
        for (int conn_num=0; conn_num < connect.size(); conn_num++){ // перебираем все связи для имеющейся точки
            if (connect[conn_num].start == *num_point and not IsCycle){ // проверяем что связь относится к точке и ранее цикл не найден
                conn actual_conn = connect[conn_num];
//                cout << "Conn: " << actual_conn.start << " - " << actual_conn.end << "->";
                // если состояние 0, запуск рекурсии с присвоением статуса 1
                if (Color[actual_conn.end] == 0){
                    Color[actual_conn.end] = 1;
//                    cout << "new point " << Color[actual_conn.start] << " - " << Color[actual_conn.end] << endl;
                    recursion_cycle(&actual_conn.end);
                    // Если статус 1 возврат и изменение параметра IsCycle
                } else if (Color[actual_conn.start] == 1){
//                    cout << "return s=n\n";
                    IsCycle = true;
                    return;
                }
//                cout << "skip\n";
                Color[*num_point] = 2;
            }
        }
    }

    void check_cycle_recursion(){
        clear_parametr();
        Color[0] = 1;
        int start = 0;
        recursion_cycle(&start);
        if (IsCycle){ // проверяем параметр двудольности и выводим ответ
            cout << "The graph contains a cycle. (recursion_cycle)" << endl;
            return;
        }
        cout << "The graph does not contain a cycle. (recursion_cycle)" << endl;
    }


//####################################################################################################################//
//################################### Проверка на двудольность очередью ##############################################//
//####################################################################################################################//
    void check_bipartite_queue(){
        clear_parametr();
        queue.emplace_back(0); // добавляем точку для запуска процесса
        Color[0] = 1;

        while (not queue.empty()){ // проверяем что в очереди ещё есть точки
//            print_Color();
//            print_queue();

            for (int i=0; i < connect.size(); i++){ // перебираем все связи для имеющейся точки
                if (connect[i].start == queue[queue.size()-1] and IsBipartite){ // проверяем что связь относится к точке и проблем не найдено раньше
                    conn actual_conn = connect[i];
//                    cout << "Conn_"<<i<<": " << connect[i].start << " - " << connect[i].end << "->";
                    if (Color[actual_conn.end] == 0 ){ // если вершина не посещена
//                        cout << "new point ";
                        queue.emplace_back(actual_conn.end); // добавляем в очередь
                        Color[actual_conn.end] = num_color[Color[actual_conn.start]]; // назначение точкам противоположного цвета
//                        cout << Color[connect[i].start] << " - " << Color[connect[i].end] << endl;
                        break; // запускаем обход сначала для новой точки
                    } else if (Color[actual_conn.end] == Color[queue[actual_conn.start]]){ // если цвета совпадают меняем параметр, чистим очередь, выходим
//                        cout << "return s=n\n";
                        IsBipartite = false;
                        queue.clear();
                        break;
                    }
//                    cout << "skip\n";
                }
            }
            if (not queue.empty()) {
                queue.erase(queue.begin()); // удаляем первый элемент из очереди
            }
        }
        if (IsBipartite){ // проверяем параметр двудольности и выводим ответ
            cout << "The graph is bipartite. (queue_bipartite)" << endl;
            return;
        }
        cout << "The graph is not bipartite. (queue_bipartite)" << endl;
    }


//####################################################################################################################//
//################################### Проверка на наличие цикла очередью #############################################//
//####################################################################################################################//
    void check_cycle_queue(){
        clear_parametr();
        queue.emplace_back(0); // добавляем точку для запуска процесса
        Color[0] = 1;

        while (not queue.empty()){ // проверяем что в очереди ещё есть точки
//            print_Color();
//            print_queue();

            for (int i=0; i < connect.size(); i++){ // перебираем все связи для имеющейся точки
                if (connect[i].start == queue[queue.size()-1] and not IsCycle){ // проверяем что связь относится к точке и цикла не найдено раньше
                    conn actual_conn = connect[i];
//                    cout << "Conn_"<<i<<": " << connect[i].start << " - " << connect[i].end << "->";
                    if (Color[actual_conn.end] == 0 ){ // если вершина не посещена
                        queue.emplace_back(actual_conn.end); // добавляем в очередь
                        Color[actual_conn.end] = 1; // назначение точке статуса 1
//                        cout << "new point " << Color[connect[i].start] << " - " << Color[connect[i].end] << endl;
                        break; // запускаем обход сначала для новой точки
                    } else if (Color[actual_conn.end] == 1){ // если цвет статуса 1, чистим очередь, выходим
//                        cout << "return s=n\n";
                        IsCycle = true;
                        queue.clear();
                        break;
                    }
//                    cout << "skip\n";
                }
            }
            Color[queue[0]] = 2;

            if (not queue.empty()) {
                queue.pop_back(); // удаляем первый элемент из очереди
            }
        }
        if (IsCycle){ // проверяем параметр двудольности и выводим ответ
            cout << "The graph contains a cycle. (queue_cycle)" << endl;
            return;
        }
        cout << "The graph does not contain a cycle. (queue_cycle)" << endl;
    }
};


int main(){
    Graph my_graph;
    my_graph.check_bipartite_queue();
    my_graph.check_bipartite_recursion();
    cout << endl;
    my_graph.check_cycle_queue();
    my_graph.check_cycle_recursion();
    return 0;
}