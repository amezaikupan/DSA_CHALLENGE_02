#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <chrono>
#include <fstream>

void BruceForceAlgorithm(char* input_path, char* output_path, int output_info){
    std::ifstream fin (input_path);
    
    if(!fin.is_open()){
        std::cout << "Khong mo duoc file" << std::endl;
        return;
    }
    
    std::string pat, txt;
    fin >> pat >> txt;

    long long cmp = 0;
    auto start = std::chrono::high_resolution_clock::now();   // Start measure time 
    
    int m = pat.length();
    int n = txt.length();
    std::vector<int> res;

    for (int i = 0; ++cmp && i <= n - m; i++) {
        int j = 0;
        for (j = 0; ++cmp && j < m; j++) {
            if (++cmp && txt[i + j] != pat[j]) {
                break;
            }
        }

        if (++cmp && j == m) {
            res.push_back(i);
        }
    }

    
    fin.close();

    std::ofstream fout (output_path);

    for(int i = 0; i < res.size(); i++){
        fout << res[i] << " " << res[i] + m - 1 << std::endl;
    }

    fout.close();
    
    auto end = std::chrono::high_resolution_clock::now();// Stop measuring time
	double time = double(std::chrono::duration_cast <std::chrono::nanoseconds> (end - start).count()) / 1e6;


    if(output_info == 0){
        std::cout << "Time: " << time << std::endl;
    }else if(output_info == 1){
        std::cout << "Comparisons: " << cmp << std::endl;
    }else{
        std::cout << "Time: " << time << std::endl;
        std::cout << "Comparisons: " << cmp << std::endl;
    }
}
