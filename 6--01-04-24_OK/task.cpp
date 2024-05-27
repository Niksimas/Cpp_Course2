//
// Created by Nikita on 01.04.2024.
//

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class TASK{
    int line = 0, stolb = 0, plots=0;
    vector <string> massive;
public:

    TASK(){
        ifstream in_data("INPUT.txt", ios::in);
        if (!in_data.is_open())cout << "Errors open file!\n";
        else {
            string tmp = "def";
            in_data >> line >> stolb;
            for (int i=0; i < line; i++) {
                in_data >> tmp;
                massive.emplace_back(tmp);
            }
        }
    }

    void print_pole(){
        cout << line << " " << stolb << endl;
        for (int i=0; i < line; i++){
            cout << massive[i];
            cout << endl;
        }
    }

    void print_plots(){
        cout << plots<< endl;
    }

    void write_file(int &out_result){
        std::ofstream out;          // поток для записи
        out.open("OUTPUT.txt");      // открываем файл для записи
        if (out.is_open())
        {
            out << out_result << std::endl;
        }
        out.close();
        std::cout << "File has been written" << std::endl;
    }

    void deleted_plots(int i, int j){
        while (true){
//            cout << "del";
//            print_pole();
            if (massive[i][j] == *"#"){
                massive[i][j] = *".";
            }
            if (i != line-1 and massive[i+1][j] == *"#"){
                massive[i][j] = *".";
                i += 1;
                continue;
            }
            if (j != stolb-1 and massive[i][j+1] == *"#"){
                massive[i][j] = *".";
                j += 1;
                continue;
            }
            if (j != 0 and massive[i][j-1] == *"#"){
                massive[i][j] = *".";
                j -= 1;
                continue;
            }
            if (i != 0 and massive[i-1][j] == *"#"){
                massive[i][j] = *".";
                i -= 1;
                continue;
            }
            break;
        }
    }

    void search_plots(){
        for (int line_num=0; line_num < line; line_num++){
            for (int stolb_num=0; stolb_num < stolb; stolb_num++){
//                cout << massive[line_num][stolb_num] << line_num << " " << stolb_num << endl;
                    if (massive[line_num][stolb_num] == *"#"){
                        plots++;
                        deleted_plots(line_num,stolb_num);
                }
            }
        }
        write_file(plots);
    }
};



int main(){
    TASK task;
    task.print_pole();
    task.search_plots();
    task.print_plots();
}