#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <chrono>
#include <fstream>

/* Naive Pattern searching */
long long BruceForceAlgorithmCmp(char* input_path, char* output_path){
    long long cmp = 0;

    std::ifstream fin (input_path);
    
    std::string pat, txt;
    fin >> pat >> txt;
    
    int m = pat.length();
    int n = txt.length();
    std::vector<int> res;

    for (int i = 0; ++cmp && i < n - m; i++) {
        int j = 0;
        for (j = 0; ++cmp && j < m; j++) {
            if (txt[i + j] != pat[j]) {
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

    return cmp;
}

double BruceForceAlgorithmTime(char* input_path, char* output_path){
    
    std::ifstream fin (input_path);
    
    std::string pat, txt;
    fin >> pat >> txt;
    
    auto start = std::chrono::high_resolution_clock::now();   // Start measure time 
    
    int m = pat.length();
    int n = txt.length();
    std::vector<int> res;

    for (int i = 0; i < n - m; i++) {
        int j = 0;
        for (j = 0; j < m; j++) {
            if (txt[i + j] != pat[j]) {
                break;
            }
        }

        if (j == m) {
            res.push_back(i);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();// Stop measuring time
	double time = double(std::chrono::duration_cast <std::chrono::nanoseconds> (end - start).count()) / 1e6;

    fin.close();

    std::ofstream fout (output_path);

    for(int i = 0; i < res.size(); i++){
        fout << res[i] << " " << res[i] + m - 1 << std::endl;
    }

    fout.close();

    
    return time;
}

void BruceForceAlgorithm(char* input_path, char* output_path, int output_info){
    if(output_info == 0){
        double time = BruceForceAlgorithmTime(input_path, output_path);
        std::cout << "Time: " << time << std::endl;
    }else if(output_info == 1){
        long long cmp = BruceForceAlgorithmCmp(input_path, output_path);
        std::cout << "Comparisons: " << cmp << std::endl;
    }else{
        double time = BruceForceAlgorithmTime(input_path, output_path);
        long long cmp = BruceForceAlgorithmCmp(input_path, output_path);
        std::cout << "Time: " << time << std::endl;
        std::cout << "Comparisons: " << cmp << std::endl;
    }
}
