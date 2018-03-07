#include <iostream>
#include<ctime>
#include "Auto-SDT-Coder.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    vector<vector<float>> vec_points;
    vector<Auto_SDT> vec_auto_sdts;

    Auto_SDT_Coder auto_sdt_coder(0.4, 0, 10, 0.5, 0.1);
    auto_sdt_coder.start(0.5);
    srand((unsigned) time(NULL));
    for (int i = 0; i < 100; i++){
        float tmp = rand() / double(RAND_MAX);
        bool flag = auto_sdt_coder.update_door(tmp);
        if(flag){
            vec_points.push_back(auto_sdt_coder.get_points());
            vec_auto_sdts.push_back((auto_sdt_coder.get_Auto_SDT_result()));
            auto_sdt_coder.new_start(tmp);
        }
    }
    vec_points.push_back(auto_sdt_coder.get_points());
    vec_auto_sdts.push_back((auto_sdt_coder.get_Auto_SDT_result()));
    auto_sdt_coder.new_start(0.5);
    std::cout << "len " << vec_auto_sdts.size()<< std::endl;
    std::cout << "counts " << vec_auto_sdts[0].get_counts() << std::endl;
    return 0;
}