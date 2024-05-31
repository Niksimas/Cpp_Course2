//
// Created by nikita on 29.05.2024.
//

#ifndef GRAPH_H
#define GRAPH_H
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "node.h"

using namespace std;

struct Conn{int start, end, num_bus;};
struct Point{int n, root=-1, transfer, used_route; vector<int> buses; vector<int>used_bus;};
struct PathNode {int stop;int transfers;vector<int> route;};


class Graph {
private:
    vector <Conn> connects;
    vector <Point> stops;
    vector <int> used;
    vector <int> queue;
    vector <int> isoledstops;
public:
    Graph() {}

    void creat_graph(vector<Route> & routes, vector<BusStop> & stops) {
        for (BusStop BS: stops) {
            Point new_point;
            new_point.n = stoi(BS.name_stops);
            new_point.buses = BS.num_buses;
            this->stops.emplace_back(new_point);
        }
        for (Route R: routes) {
            for (int i=1; i < R.list_stop.size(); i++) {
                Conn new_connect={R.list_stop[i-1], R.list_stop[i], stoi(R.name_bus)};
                connects.emplace_back(new_connect);
            }
        }
    }

    void print() {
        cout << "Connects:\n";
        for (Conn i: connects) {
            cout << "Num bus: " <<i.num_bus << " start: " << i.start << " end: " << i.end<<"\n";
        }
        cout << "\nStops:\n";
        for (Point i: stops) {
            cout << "Num stops: " <<i.n << " Buses: ";
            for (int j: i.buses) {
                cout << j<< ", ";
            }
            cout << endl;
        }
    }

    virtual ~Graph() {}

    bool check_element_used(int &val){
        for(int i = 0; i< used.size(); i++){if (used[i] == val) return true;}
        return false;
    }

    bool check_element_queue(int &val){
        for(int i = 0; i< queue.size(); i++){if (queue[i] == val) return true;}
        return false;
    }

    void clear_root_point(){for (int i=0; i<stops.size();i++){stops[i].root=-1;}}

    void clear_used_point(){used.clear();}

    bool is_reachable(int start, int end, Conn* ignore_conn = nullptr) {
        int ignore_num_bus=-1;
        if(ignore_conn != nullptr) {ignore_num_bus = ignore_conn->num_bus;}
        if (start == end) return true;
        clear_used_point();
        if(!queue.empty()){queue.clear();}
        queue.push_back(start);
        used.push_back(start);

        while (!queue.empty()) {
            int current = queue[0];
            queue.erase(queue.begin());

            for (Conn c : connects) {
                if (c.num_bus == ignore_num_bus) continue;  // Игнорируем указанное соединение

                if ((c.start == current && !check_element_used(c.end)) || (c.end == current && !check_element_used(c.start))) {
                    int next_stop = (c.start == current) ? c.end : c.start;
                    if (next_stop == end) return true;
                    queue.push_back(next_stop);
                    used.push_back(next_stop);
                }
            }
        }

        return false;
    }

    void find_unreachable_stop() {
        cout << "\nTask2\n";
        bool isIsolated = false;
        for (Point stop : stops) {
            bool reachable = false;
            for (Point other_stop : stops) {
                if (stop.n != other_stop.n && is_reachable(other_stop.n, stop.n)) {
                    reachable = true;
                    break;
                }
            }
            if (!reachable) {
                isIsolated = true;
                isoledstops.emplace_back(stop.n);
                cout << "До остановки №" << stop.n << " нельзя добраться ни с какой другой остановки." << endl;
            }
        }
        if (!isIsolated){cout << "Нет изолированных остановок!\n";}
    }

    void find_critical_connection() {
        cout << "\nTask3\n";
        bool isIsoleted=false;
        for (Conn& conn : connects) {
            for (Point stop : stops) {
                bool reachable = false;
                for (Point other_stop : stops) {
                    if (stop.n != other_stop.n && is_reachable(other_stop.n, stop.n, &conn)) {
                        reachable = true;
                        break;
                    }
                }
                bool isBreak=false;
                for (int i: isoledstops) {if (stop.n == i){isBreak=true;}}
                if(isBreak){break;}
                if (!reachable) {
                    isIsoleted =true;
                    isoledstops.emplace_back(stop.n);
                    cout << "Игнорирование маршрута №" << conn.num_bus << " изолирует остановку №" << stop.n << endl;
                }
            }
        }
        if (!isIsoleted){cout << "При игнорировании одного маршрута, ни одна остановка не становится изолированной\n";}
    }

    void find_min_routes_to_isolate_stop() {
        cout << "\nTask4\n";
        unordered_map<int, unordered_set<int>> stop_to_routes;
        for (const Conn& conn : connects) {
            stop_to_routes[conn.start].insert(conn.num_bus);
            stop_to_routes[conn.end].insert(conn.num_bus);
        }
        int min_routes = connects.size() + 1;
        int critical_stop = -1;
        for (const auto& entry : stop_to_routes) {
            int stop = entry.first;
            int route_count = entry.second.size();
            if (route_count < min_routes) {
                min_routes = route_count;
                critical_stop = stop;
            }
        }
        if (critical_stop != -1) {
            cout << "Остановка №" << critical_stop << " является наиболее уязвимой. Необходимо скрыть минимум " << min_routes << " маршрутов." << endl;
        } else {
            cout << "Ни одна остановка не может быть изолирована путем сокрытия какого-либо отдельного маршрута." << endl;
        }
    }

    void checking_availability_of_direct_flights() {
        cout << "\nTask-1a\n";
        int start, end;
        cout << "Введите начальную остановку (от 1 до "<< stops.size()<<"): ";
        cin >> start;
        cout << "Введите конечную остановку (от 1 до "<< stops.size()<<"): ";
        cin >> end;
        for (int snum: stops[start-1].buses) {
            for (int endnum: stops[end-1].buses) {
                if (snum == endnum) {
                    cout << "От остановки №" << start << "до №" << end <<" можно добраться без пересадок";
                    return;
                }
            }
        }
        cout << "От остановки №" << start << "до №" << end <<" нельзя добраться без пересадок";
    }


    void find_path_with_transfers() {
        cout << "\nTask-1b\n";
        int start, end, max_transfers;
        cout << "Введите начальную остановку (от 1 до "<< stops.size()<<"): ";
        cin >> start;
        cout << "Введите конечную остановку (от 1 до "<< stops.size()<<"): ";
        cin >> end;
        cout << "Введите необходимое кол-во пересадок: ";
        cin >> max_transfers;
        cout << "\nПоиск пути с " << max_transfers << " пересадками:\n";
        if (start == end) {cout << "Начальная и конечная остановки совпадают.\n";return;}
        vector<PathNode> q;
        unordered_set<int> visited;
        q.emplace_back(PathNode{start, 0, {start}});
        visited.insert(start);
        while (!q.empty()) {
            PathNode current = q.front();
            q.erase(q.begin());
            if (current.transfers > max_transfers) {continue;}
            for (Conn &c : connects) {
                if (c.start == current.stop || c.end == current.stop) {
                    int next_stop = (c.start == current.stop) ? c.end : c.start;
                    if (visited.find(next_stop) == visited.end()) {
                        vector<int> new_route = current.route;
                        new_route.push_back(next_stop);
                        if (next_stop == end && current.transfers <= max_transfers) {
                            cout << "Найденный путь: ";
                            for (int stop : new_route) {
                                cout << stop << " ";
                            }
                            cout << "\n";
                            return;
                        }
                        q.emplace_back(PathNode{next_stop, current.transfers + 1, new_route});
                        visited.insert(next_stop);
                    }
                }
            }
        }
        cout <<"Не найден маршрут с " << max_transfers << " пересадками.\n";
    }

};

#endif //GRAPH_H
