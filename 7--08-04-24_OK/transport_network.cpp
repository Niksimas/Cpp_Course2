//
// Created by nikita on 08.04.2024.
//
// В населённом пункте присутствует N остановок.
// Дана информация о транспортных маршрутах в виде последовательного списка остановок
// через которые проходит маршрут.
//
// Задание 0. Разработать наиболее удобный формат входных данных для этой задачи.
// Задание 1. a) По заданной входной информации проверить возможность попасть из одной остановки на другую на
//               одном транспорте.
//            b) Проверить возможность попасть из одной остановки на другую с заданным
//               количеством пересадок.
// Задание 2. Проверить Возможно ли с каждой остановки добраться до любой другой остановки.
//          ->find_unreachable_stop()
// Задание 3. Проверить выполнение предыдущего условия при удалении любого из маршрутов
//          ->find_critical_connection()
// Задание 4. Найти минимальное количество маршрутов удаление которых приведёт
//            к прекращению выполнения условия задания 2.
//          ->find_min_routes_to_isolate_stop()
// Задание 5. Разработать не менее 6 различных тестов для проверки корректности работы всех алгоритмов.


#include <iostream>
#include <fstream>
#include <vector>
#include "graph.h"
using namespace std;


class City {
private:
    vector<BusStop> bus_stops;
    vector<Route> routes;

public:
    City() {
        StructBusStops SBS;
        Graph city_stops;
        string name_file;
        cout << "Введите название файла: ";
        cin >> name_file;
        SBS.load_file(&name_file);
        // SBS.print();
        read_tree_in_list(&SBS);
        // print_lists();
        city_stops.creat_graph(routes, bus_stops);
        // city_stops.print();
        city_stops.checking_availability_of_direct_flights();
        city_stops.find_path_with_transfers();
        city_stops.find_unreachable_stop();
        city_stops.find_critical_connection();
        city_stops.find_min_routes_to_isolate_stop();
    }

    void print_lists() {
        cout << "bus_stop:\n";
        for (BusStop stop: bus_stops) {
            cout << stop.name_stops << "|";
            for (int i =0;i < stop.num_buses.size(); i++) {
                cout << " " << stop.num_buses[i] << ", ";
            }
            cout<< endl;
        }
        cout << endl;
        cout << endl;
        cout << "Route:\n";
        for (Route stop: routes) {
            cout << stop.name_bus << "|";
            for (int i =0;i < stop.list_stop.size(); i++) {
                cout << stop.list_stop[i] << "-";
            }
            cout<< endl;
        }
        cout << endl;
    }

    void read_tree_in_list(StructBusStops * root_SBS) {
        Node * root_node = root_SBS->get_root_node();
        for (int i =0; i < root_node->getConstSub(); i++) {
            Node * node = root_node->getSub(&i);
            if (node->getName() != "bus"){continue;}
            string name_bus = node->getSub("name")->getValue();
            string route_bus = node->getSub("route")->getValue();
            vector<int> route_bus_list = separation_int(&route_bus, '-');
            Route tmp{name_bus, route_bus_list};
            routes.emplace_back(tmp);
        }
        for (int i = 0;i < routes.size(); i ++) { // перебираем маршруты
            Route as = routes[i];
            int num_bus = stoi(as.name_bus);//номер автобуса
            for (int num_stop: as.list_stop) {// перебираем его маршрут
                bool addBusInStop = false;
                for (int j =0;j < bus_stops.size(); j++) {// перебираем имеющиеся остановки, если есть остановка, добавляем в неё номер автобуса
                    bool CheckBus = false;
                    if (bus_stops[j].name_stops == to_string(num_stop)) {
                        addBusInStop = true;
                        for (int k: bus_stops[j].num_buses) {if (k == num_bus) {CheckBus=true;break;}}
                        if (CheckBus) {continue;}
                        bus_stops[j].setBus(&num_bus);
                        break;
                    }
                }
                if (!addBusInStop) {//иначе создаем остановку
                    BusStop new_stop;
                    new_stop.name_stops = to_string(num_stop);
                    new_stop.setBus(&num_bus);
                    bus_stops.emplace_back(new_stop);
                }
            }
        }
    }

    int GetConstStops(){return bus_stops.size();}
};

int main(){
    City city;
    // cout << "На данный момент остановок: "<< city.GetConstStops() << endl;

}
