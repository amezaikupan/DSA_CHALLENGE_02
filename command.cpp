#include <iostream>
#include <string.h>
#include "algorithms.h"

using namespace std;

int OutputInfo(char* output_info){
    if(strcmp(output_info, "-t") == 0) return 0;
    if(strcmp(output_info, "-n") == 0) return 1;
    if(strcmp(output_info, "-ind") == 0) return 2;
    else{
        cout << "INVALID OUTPUT INFO" << endl;
        return -1;
    }
}

void Command(char* algorithm, char* input_path, char* output_path, char* output_info){
    int output_info_code = OutputInfo(output_info);

    if(output_info_code == -1) return;    

    if(strcmp(algorithm, "-bf") == 0){
        cout << "Algorithm: Bruce Force" << endl;
        cout << "Input path: " << input_path << endl;
        cout << "Output Path: " << output_path << endl;
        BruceForceAlgorithm(input_path, output_path, output_info_code);
    }
    else if(strcmp(algorithm, "-rk") == 0){
        cout << "Algorithm: Rabin Karp" << endl;
        cout << "Input path: " << input_path << endl;
        cout << "Output Path: " << output_path << endl;
        RabinKarpAlgorithm(input_path, output_path, output_info_code);
    }
    else if(strcmp(algorithm, "-kmp") == 0){
        cout << "Algorithm: Knuth Morris Pratt" << endl;
        cout << "Input path: " << input_path << endl;
        cout << "Output Path: " << output_path << endl;
        KMPAlgorithm(input_path, output_path, output_info_code);
    }
    else if(strcmp(algorithm, "-bm") == 0){
        cout << "Algorithm: Boyer Moore Algorithm" << endl;
        cout << "Input path: " << input_path << endl;
        cout << "Output Path: " << output_path << endl;
        BoyerMooreAlgorithm(input_path, output_path, output_info_code);
    }
    else if(strcmp(algorithm, "-tw") == 0){
        cout << "Algorithm: Two Way Algorithm" << endl;
        cout << "Input path: " << input_path << endl;
        cout << "Output Path: " << output_path << endl;
        TwoWayAlgorithm(input_path, output_path, output_info_code);
    }else{
        cout << "INVALID ALGORITHM" << endl;
    }
}