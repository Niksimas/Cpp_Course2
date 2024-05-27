//
// Created by Nikita on 26.02.2024.

//
//  -- ����� ����� � ��������������� �����
//  -- �������� ����� �� ������������
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
//// ����������� ����
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

//// ���� � ����� ����������
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

//// ��� ���������� ����
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
//################################### ����������� �������� �� ������������ ###########################################//
//####################################################################################################################//
    void recursion_bipartite(const int *num_point){
        for (int conn_num=0; conn_num < connect.size(); conn_num++){ //// ���������� ��� ����� ��� ��������� �����
            if (connect[conn_num].start == *num_point and IsBipartite){ //// ��������� ��� ����� ��������� � �����
                conn actual_conn = connect[conn_num];
//                cout << "Conn: " << actual_conn.start << " - " << actual_conn.end << "->";
                //// ���� ���� �������� ����� 0 ������ �������� ��� ���� ����� (� ����������� � ��������������� ����)
                if (Color[actual_conn.end] == 0){
                    Color[actual_conn.end] = num_color[Color[actual_conn.start]];
//                    cout << "new point " << Color[actual_conn.start] << " - " << Color[actual_conn.end] << endl;
                    recursion_bipartite(&actual_conn.end);
                    //// ���� ����� ���������, ��������� ��������� IsBipartite
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
        if (IsBipartite){ // ��������� �������� ������������ � ������� �����
            cout << "The graph is bipartite. (recursion_bipartite)" << endl;
            return;
        }
        cout << "The graph is not bipartite. (recursion_bipartite)" << endl;
    }


//####################################################################################################################//
//################################### ����������� �������� �� ������� ����� ##########################################//
//####################################################################################################################//
    void recursion_cycle(const int* num_point){
        for (int conn_num=0; conn_num < connect.size(); conn_num++){ // ���������� ��� ����� ��� ��������� �����
            if (connect[conn_num].start == *num_point and not IsCycle){ // ��������� ��� ����� ��������� � ����� � ����� ���� �� ������
                conn actual_conn = connect[conn_num];
//                cout << "Conn: " << actual_conn.start << " - " << actual_conn.end << "->";
                // ���� ��������� 0, ������ �������� � ����������� ������� 1
                if (Color[actual_conn.end] == 0){
                    Color[actual_conn.end] = 1;
//                    cout << "new point " << Color[actual_conn.start] << " - " << Color[actual_conn.end] << endl;
                    recursion_cycle(&actual_conn.end);
                    // ���� ������ 1 ������� � ��������� ��������� IsCycle
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
        if (IsCycle){ // ��������� �������� ������������ � ������� �����
            cout << "The graph contains a cycle. (recursion_cycle)" << endl;
            return;
        }
        cout << "The graph does not contain a cycle. (recursion_cycle)" << endl;
    }


//####################################################################################################################//
//################################### �������� �� ������������ �������� ##############################################//
//####################################################################################################################//
    void check_bipartite_queue(){
        clear_parametr();
        queue.emplace_back(0); // ��������� ����� ��� ������� ��������
        Color[0] = 1;

        while (not queue.empty()){ // ��������� ��� � ������� ��� ���� �����
//            print_Color();
//            print_queue();

            for (int i=0; i < connect.size(); i++){ // ���������� ��� ����� ��� ��������� �����
                if (connect[i].start == queue[queue.size()-1] and IsBipartite){ // ��������� ��� ����� ��������� � ����� � ������� �� ������� ������
                    conn actual_conn = connect[i];
//                    cout << "Conn_"<<i<<": " << connect[i].start << " - " << connect[i].end << "->";
                    if (Color[actual_conn.end] == 0 ){ // ���� ������� �� ��������
//                        cout << "new point ";
                        queue.emplace_back(actual_conn.end); // ��������� � �������
                        Color[actual_conn.end] = num_color[Color[actual_conn.start]]; // ���������� ������ ���������������� �����
//                        cout << Color[connect[i].start] << " - " << Color[connect[i].end] << endl;
                        break; // ��������� ����� ������� ��� ����� �����
                    } else if (Color[actual_conn.end] == Color[queue[actual_conn.start]]){ // ���� ����� ��������� ������ ��������, ������ �������, �������
//                        cout << "return s=n\n";
                        IsBipartite = false;
                        queue.clear();
                        break;
                    }
//                    cout << "skip\n";
                }
            }
            if (not queue.empty()) {
                queue.erase(queue.begin()); // ������� ������ ������� �� �������
            }
        }
        if (IsBipartite){ // ��������� �������� ������������ � ������� �����
            cout << "The graph is bipartite. (queue_bipartite)" << endl;
            return;
        }
        cout << "The graph is not bipartite. (queue_bipartite)" << endl;
    }


//####################################################################################################################//
//################################### �������� �� ������� ����� �������� #############################################//
//####################################################################################################################//
    void check_cycle_queue(){
        clear_parametr();
        queue.emplace_back(0); // ��������� ����� ��� ������� ��������
        Color[0] = 1;

        while (not queue.empty()){ // ��������� ��� � ������� ��� ���� �����
//            print_Color();
//            print_queue();

            for (int i=0; i < connect.size(); i++){ // ���������� ��� ����� ��� ��������� �����
                if (connect[i].start == queue[queue.size()-1] and not IsCycle){ // ��������� ��� ����� ��������� � ����� � ����� �� ������� ������
                    conn actual_conn = connect[i];
//                    cout << "Conn_"<<i<<": " << connect[i].start << " - " << connect[i].end << "->";
                    if (Color[actual_conn.end] == 0 ){ // ���� ������� �� ��������
                        queue.emplace_back(actual_conn.end); // ��������� � �������
                        Color[actual_conn.end] = 1; // ���������� ����� ������� 1
//                        cout << "new point " << Color[connect[i].start] << " - " << Color[connect[i].end] << endl;
                        break; // ��������� ����� ������� ��� ����� �����
                    } else if (Color[actual_conn.end] == 1){ // ���� ���� ������� 1, ������ �������, �������
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
                queue.pop_back(); // ������� ������ ������� �� �������
            }
        }
        if (IsCycle){ // ��������� �������� ������������ � ������� �����
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