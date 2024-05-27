//
// Created by Nikita on 04.03.2024.
// метод дейкстры

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

struct Conn{int start, end, length, time, amount;};
//struct Path{int root; string history_path; int length; int time; int cost;};
//struct Point{int n; bool used; int root; int length; int time; int cost;};
struct Point{int n; int root; int length; int time; int amount; int transfer;};


class Graph{
    int points_n=0;
    vector <Point> points;
    vector <Conn> connect;
    vector <int> used;
    vector <int> queue;
public:
    Graph(){
        //// направленный граф
        points_n = 7;
        for (int i=0; i<points_n;i++){
            points.emplace_back(Point{i, -1, -1, -1, -1, -1});
        }
        connect.emplace_back(Conn({0, 1, 12, 4, 200}));
        connect.emplace_back(Conn({0, 4, 6, 3, 800}));
        connect.emplace_back(Conn({0, 2, 1, 7, 500}));
        connect.emplace_back(Conn({1, 5, 7, 12, 1050}));
        connect.emplace_back(Conn({2, 3, 20, 8, 1000}));
        connect.emplace_back(Conn({2, 6, 7, 12, 100}));
        connect.emplace_back(Conn({3, 1, 8, 3, 350}));
        connect.emplace_back(Conn({3, 2, 20, 8, 1000}));
        connect.emplace_back(Conn({4, 0, 6, 3, 800}));
        connect.emplace_back(Conn({4, 3, 2, 2, 200}));
        connect.emplace_back(Conn({5, 6, 3, 1, 500}));
        connect.emplace_back(Conn({6, 4, 1, 2, 300}));


//// граф с двумя остравками
//        points_n = 5;
//        connect.emplace_back(Conn({0, 2}));
//        connect.emplace_back(Conn({2, 0}));
//        connect.emplace_back(Conn({2, 3}));
//        connect.emplace_back(Conn({3, 2}));
//        connect.emplace_back(Conn({3, 5}));
//        connect.emplace_back(Conn({5, 3}));
//        connect.emplace_back(Conn({1, 4}));
//        connect.emplace_back(Conn({4, 1}));
//        connect.emplace_back(Conn({2, 5}));
//        connect.emplace_back(Conn({5, 2}));

//// Это двудольный граф
//        points_n = 5;
//        connect.emplace_back(Conn({0, 1}));
//        connect.emplace_back(Conn({1, 0}));
//        connect.emplace_back(Conn({1, 3}));
//        connect.emplace_back(Conn({3, 1}));
//        connect.emplace_back(Conn({1, 4}));
//        connect.emplace_back(Conn({4, 1}));
//        connect.emplace_back(Conn({4, 2}));
//        connect.emplace_back(Conn({2, 4}));
//        connect.emplace_back(Conn({5, 4}));
//        connect.emplace_back(Conn({4, 5}));
    }
    virtual ~Graph(){}

    bool check_element_used(int &val){
        for(int i = 0; i< used.size(); i++){if (used[i] == val) return true;}
        return false;
    }

    void set_default(){
        points.clear();
        for (int i=0; i<points_n;i++){points.emplace_back(Point{i, -1, -1, -1, -1, -1});}
        if (not used.empty()){used.clear();}
    }

    void print_used(){
        if (not used.empty()){
            for (int i=0; i<used.size();i++){cout << used[i]<< " ";}
        }
        cout << endl;
    }

    void print_point(){
        cout << "n\troot\ttime\tlength\tamount\ttransfer\n";
        for (int i=0; i<points_n;i++){
            cout << points[i].n << "\t" << points[i].root << "\t" << points[i].time << "\t" << points[i].length << "\t" << points[i].amount <<"\t" << points[i].transfer << endl;}
        cout << endl;
    }


//####################################################################################################################//
//########################### поиск маршрута по минимальному времени перелета ########################################//
//####################################################################################################################//
    int point_min_time(){
        int tmp_time = 9999999, tmp_index = 0;
        for (int p_num=0; p_num < points_n; p_num++){
            if (points[p_num].time > 0 and points[p_num].time < tmp_time and not check_element_used(p_num)){
                tmp_index = p_num;
                tmp_time = points[p_num].time;
            }
        }
        return tmp_index;
    }


    void search_path_min_time(const int start_point, const int end_point){
        int point = start_point;
        points[start_point] = {start_point,-1,0,0,0};
        while (used.size() < points_n+1){
            // цикл перебора для обновления актуальности имеющихся данных(цикл с проверкой весов)
            for (int conn_num=0; conn_num < connect.size(); conn_num++){
                if (    connect[conn_num].end == point and points[connect[conn_num].start].time != -1 and // связь которая приходит в точку и точка которая была посчитана
                        points[connect[conn_num].start].time + connect[conn_num].time < points[point].time  // масса точки + масса связи < массы проверяемой точки
                        ){ // тогда происходит обновление весов для этой точки
                    points[point].time = points[connect[conn_num].start].time + connect[conn_num].time;
                    points[point].root = connect[conn_num].start;
                }
            }
            for (int conn_num = 0; conn_num < connect.size(); conn_num++) { // перебираем связи
                if (connect[conn_num].start == point and not check_element_used(connect[conn_num].end)) { // ищем не посещенные точки относящиеся к заданной
                    Conn actual_conn = connect[conn_num];
                    if (points[actual_conn.end].time == -1) {
                        points[actual_conn.end].time = points[actual_conn.start].time + actual_conn.time; // устанавливаем вес для точки (прошлая точка + вес связи)
                        points[actual_conn.end].root = connect[conn_num].start;
                    }
                }
            }
            used.emplace_back(point);
            point = point_min_time();
        }

        int tmp_index = end_point;
        string history_path = "";
        while (tmp_index != start_point){
            history_path = " - " + to_string(points[tmp_index].n) + history_path;
            tmp_index = points[tmp_index].root;
        }
        history_path = to_string(start_point) + history_path;
        cout << "The route with the minimum time: " << history_path << " time: " << points[end_point].time << endl;
    }

//####################################################################################################################//
//########### поиск маршрута по минимальной стоимости перелета ####################//
//####################################################################################################################//
    int point_min_amount(){
        int tmp_amount = 9999999, tmp_index = 0;
        for (int p_num=0; p_num < points_n; p_num++){
            if (points[p_num].amount > 0 and points[p_num].amount < tmp_amount and not check_element_used(p_num)){
                tmp_index = p_num;
                tmp_amount = points[p_num].amount;
            }
        }
        return tmp_index;
    }


    void search_path_min_amount(const int start_point, const int end_point){
        set_default();
        int point = start_point;
        points[start_point] = {start_point,-1,0,0,0};
        while (used.size() < points_n+1){
            // цикл перебора для обновления актуальности имеющихся данных(цикл с проверкой весов)
            for (int conn_num=0; conn_num < connect.size(); conn_num++){
                if (    connect[conn_num].end == point and points[connect[conn_num].start].amount != -1 and // связь которая приходит в точку и точка которая была посчитана
                        points[connect[conn_num].start].amount + connect[conn_num].amount < points[point].amount  // масса точки + масса связи < массы проверяемой точки
                        ){ // тогда происходит обновление весов для этой точки
                    points[point].amount = points[connect[conn_num].start].amount + connect[conn_num].amount;
                    points[point].root = connect[conn_num].start;
                }
            }
            for (int conn_num = 0; conn_num < connect.size(); conn_num++) { // перебираем связи
                if (connect[conn_num].start == point and not check_element_used(connect[conn_num].end)) { // ищем не посещенные точки относящиеся к заданной
                    Conn actual_conn = connect[conn_num];
                    if (points[actual_conn.end].amount == -1) {
                        points[actual_conn.end].amount = points[actual_conn.start].amount + actual_conn.amount; // устанавливаем вес для точки (прошлая точка + вес связи)
                        points[actual_conn.end].root = connect[conn_num].start;
                    }
                }
            }
            used.emplace_back(point);
            point = point_min_amount();
        }
        int tmp_index = end_point;
        string history_path = "";
        while (tmp_index != start_point){
            history_path = " - " + to_string(points[tmp_index].n) + history_path;
            tmp_index = points[tmp_index].root;
        }
        history_path = to_string(start_point) + history_path;
        cout << "The route with the minimum cost: " << history_path << " amount: " << points[end_point].amount << endl;
    }

//####################################################################################################################//
//######### поиск списка городов, в которые можно попасть из заданного, имея определенную сумму денег ################//
//####################################################################################################################//

    void search_list_cites_amount(const int start_point, const int max_amount){
        set_default();
        int point = start_point;
        points[start_point] = {start_point,-1,0,0,0};
        while (used.size() < points_n+1){
            // цикл перебора для обновления актуальности имеющихся данных(цикл с проверкой весов)
            for (int conn_num=0; conn_num < connect.size(); conn_num++){
                if (    connect[conn_num].end == point and points[connect[conn_num].start].amount != -1 and // связь которая приходит в точку и точка которая была посчитана
                        points[connect[conn_num].start].amount + connect[conn_num].amount < points[point].amount  // масса точки + масса связи < массы проверяемой точки
                        ){ // тогда происходит обновление весов для этой точки
                    points[point].amount = points[connect[conn_num].start].amount + connect[conn_num].amount;
                    points[point].root = connect[conn_num].start;
                }
            }
            for (int conn_num = 0; conn_num < connect.size(); conn_num++) { // перебираем связи
                if (connect[conn_num].start == point and not check_element_used(connect[conn_num].end)) { // ищем не посещенные точки относящиеся к заданной
                    Conn actual_conn = connect[conn_num];
                    if (points[actual_conn.end].amount == -1) {
                        points[actual_conn.end].amount = points[actual_conn.start].amount + actual_conn.amount; // устанавливаем вес для точки (прошлая точка + вес связи)
                        points[actual_conn.end].root = connect[conn_num].start;
                    }
                }
            }
            used.emplace_back(point);
            point = point_min_amount();
        }
        cout << "List cites: (max amount " << max_amount << ")" << endl;
        for(int i=0; i<points_n; i++){
            if (points[i].amount <= max_amount and points[i].n != start_point){
                int tmp_index = points[i].n;
                string history_path = "";
                while (tmp_index != start_point){
                    history_path = " - " + to_string(points[tmp_index].n) + history_path;
                    tmp_index = points[tmp_index].root;
                }
                history_path = to_string(start_point) + history_path;
                cout << history_path << " amount: " << points[points[i].n].amount << endl;
            }
        }
    }


//####################################################################################################################//
//####################### поиск списка городов, в которые можно попасть за определенное время ########################//
//####################################################################################################################//

    void search_list_cites_time(const int start_point, const int max_time){
        set_default();
        int point = start_point;
        points[start_point] = {start_point,-1,0,0,0};
        while (used.size() < points_n+1){
            // цикл перебора для обновления актуальности имеющихся данных(цикл с проверкой весов)
            for (int conn_num=0; conn_num < connect.size(); conn_num++){
                if (    connect[conn_num].end == point and points[connect[conn_num].start].time != -1 and // связь которая приходит в точку и точка которая была посчитана
                        points[connect[conn_num].start].time + connect[conn_num].time < points[point].time  // масса точки + масса связи < массы проверяемой точки
                        ){ // тогда происходит обновление весов для этой точки
                    points[point].time = points[connect[conn_num].start].time + connect[conn_num].time;
                    points[point].root = connect[conn_num].start;
                }

            }
            for (int conn_num = 0; conn_num < connect.size(); conn_num++) { // перебираем связи
                if (connect[conn_num].start == point and not check_element_used(connect[conn_num].end)) { // ищем не посещенные точки относящиеся к заданной
                    Conn actual_conn = connect[conn_num];
                    if (points[actual_conn.end].time == -1) {
                        points[actual_conn.end].time = points[actual_conn.start].time + actual_conn.time; // устанавливаем вес для точки (прошлая точка + вес связи)
                        points[actual_conn.end].root = connect[conn_num].start;
                    }
                }
            }
            used.emplace_back(point);
            point = point_min_time();
        }
        cout << "List cites: (max time " << max_time << ")" << endl;
        for(int i=0; i<points_n; i++){
            if (points[i].time <= max_time and points[i].n != start_point){
                int tmp_index = points[i].n;
                string history_path = "";
                while (tmp_index != start_point){
                    history_path = " - " + to_string(points[tmp_index].n) + history_path;
                    tmp_index = points[tmp_index].root;
                }
                history_path = to_string(start_point) + history_path;
                cout << history_path << " time: " << points[points[i].n].time << endl;
            }
        }
    }

//####################################################################################################################//
//######## Определить, можно ли попасть из одного города в другой не более чем с двумя или тремя пересадками #########//
//####################################################################################################################//
    int point_min_transfer(){
        int tmp_transfer = 9999999, tmp_index = 0;
        for (int p_num=0; p_num < points_n; p_num++){
            if (points[p_num].transfer > 0 and points[p_num].transfer < tmp_transfer and not check_element_used(p_num)){
                tmp_index = p_num;
                tmp_transfer = points[p_num].transfer;
            }
        }
        return tmp_index;
    }

    void define_path_cites_min_transfer(const int start_point, const int end_point) {
        set_default();
        int point = start_point;
        points[start_point] = {start_point, -1, 0, 0, 0, 0};
        while (used.size() < points_n + 1) {
            // цикл перебора для обновления актуальности имеющихся данных(цикл с проверкой весов)
            for (int conn_num = 0; conn_num < connect.size(); conn_num++) {
                if (
                        connect[conn_num].end == point and points[connect[conn_num].start].transfer != -1 and  // связь которая приходит в точку и точка которая была посчитана
                        points[connect[conn_num].start].transfer + 1 < points[point].transfer  // масса точки + масса связи < массы проверяемой точки
                        ) { // тогда происходит обновление весов для этой точки
                    points[point].transfer = points[connect[conn_num].start].transfer + 1;
                    points[point].root = connect[conn_num].start;
                }
            }
            for (int conn_num = 0; conn_num < connect.size(); conn_num++) { // перебираем связи
                if (connect[conn_num].start == point and not check_element_used(connect[conn_num].end)) { // ищем не посещенные точки относящиеся к заданной
                    Conn actual_conn = connect[conn_num];
                    if (points[actual_conn.end].transfer == -1) {
                        points[actual_conn.end].transfer = points[actual_conn.start].transfer + 1; // устанавливаем вес для точки (прошлая точка + вес связи)
                        points[actual_conn.end].root = connect[conn_num].start;
                    }
                }
            }
            used.emplace_back(point);
            point = point_min_transfer();
        }
        if (points[end_point].transfer <= 3 and points[end_point].transfer >= 1){
                cout << "There is a route from city " << start_point << " to city " << end_point << " with " << points[end_point].transfer << " transfers.\n";
        } else {
            cout << "There is no route from city " << start_point << " to city " << end_point << " with 2-3 transfers.\n";
        }
    }


//####################################################################################################################//
//###### Определить максимальное расстояние, на которое можно улететь с пересадками, имея определенную сумму #########//
//####################################################################################################################//
    int point_max_transfer(){
        int tmp_transfer = 0, tmp_index = 0;
        for (int p_num=0; p_num < points_n; p_num++){
            if ( points[p_num].transfer > tmp_transfer and not check_element_used(p_num)){
                tmp_index = p_num;
                tmp_transfer = points[p_num].transfer;
            }
        }
        return tmp_index;
    }

    tuple<string, int, int> define_path_cites_max_transfer(const int start_point, const int max_amount) {
        set_default();
        int point = start_point;
        points[start_point] = {start_point, -1, 0, 0, 0, 0};
        while (used.size() < points_n + 1) {

            // цикл перебора для обновления актуальности имеющихся данных(цикл с проверкой весов)
            for (int conn_num = 0; conn_num < connect.size(); conn_num++) {
                if (
                        connect[conn_num].end == point and points[connect[conn_num].start].transfer != -1 and  // связь которая приходит в точку и точка которая была посчитана
                        points[connect[conn_num].start].transfer + 1 > points[point].transfer and  // масса точки + масса связи > массы проверяемой точки
                        points[connect[conn_num].start].amount + connect[conn_num].amount < max_amount and
                        connect[conn_num].end != point
                        ) { // тогда происходит обновление весов для этой точки
                    points[point].transfer = points[connect[conn_num].start].transfer + 1;
                    points[point].amount = points[connect[conn_num].start].amount + connect[conn_num].amount;
                    points[point].root = connect[conn_num].start;
                }
            }
            for (int conn_num = 0; conn_num < connect.size(); conn_num++) { // перебираем связи
                if (connect[conn_num].start == point and not check_element_used(connect[conn_num].end)) { // ищем не посещенные точки относящиеся к заданной
                    Conn actual_conn = connect[conn_num];
                    if (points[actual_conn.end].transfer == -1) {
                        points[actual_conn.end].transfer = points[actual_conn.start].transfer + 1; // устанавливаем вес для точки (прошлая точка + вес связи)
                        points[actual_conn.end].amount = points[actual_conn.start].amount + actual_conn.amount;
                        points[actual_conn.end].root = connect[conn_num].start;
                    }
                }
            }
            used.emplace_back(point);
            point = point_max_transfer();
        }

        int end_point = 0, tmp_amount=0;
        for (int i=0; i<points_n; i++ ){
            if (points[i].amount > tmp_amount and points[i].amount < max_amount){
                end_point = i;
                tmp_amount = points[i].amount;
            }
        }

        int tmp_index = end_point;
        string history_path = "";
        while (tmp_index != start_point){
            history_path = " - " + to_string(points[tmp_index].n) + history_path;
            tmp_index = points[tmp_index].root;
        }
        history_path = to_string(start_point) + history_path;
        return {history_path, points[end_point].transfer, points[end_point].amount};
    }

    void output_max_path(const int max_amount){
        string history_path;
        int max_transfer =0;
        int amount =0;
        for (int i=0; i<points_n; i++){
            auto [tmp_history_path, tmp_max_transfer, tmp_amount] = define_path_cites_max_transfer(i, max_amount);
            if (tmp_max_transfer > max_transfer){
                amount = tmp_amount;
                max_transfer =tmp_max_transfer;
                history_path= tmp_history_path;
            }
        }
        cout << "The longest way: " << history_path << " amount: " << amount << endl;
    }


//####################################################################################################################//
//####################################################################################################################//
//####################################################################################################################//
};

int main() {
    Graph graph;
//    graph.search_path_min_time(1, 6);
//    cout << endl;
//    graph.search_path_min_amount(0, 6);
//    cout << endl;
//    graph.search_list_cites_amount(1, 2000);
//    cout << endl;
//    graph.search_list_cites_time(6, 200);
//    cout << endl;
//    graph.define_path_cites_min_transfer(6, 1);
    cout << endl;
    graph.output_max_path(3000);
//    graph.print_point();
    return 0;
}