#include <iostream>
#include <string.h>
#include "algorithms.h"

using namespace std;

int OutputInfo(char* output_info){
    if(strcmp(output_info, "-t")) return 0;
    if(strcmp(output_info, "-n")) return 1;
    if(strcmp(output_info, "-ind")) return 2;
    else{
        cout << "INVALID OUTPUT INFO" << endl;
        return -1;
    }
}

void Command(char* algorithm, char* input_path, char* output_path, char* output_info){
    int output_info_code = OutputInfo(output_info);

    if(output_info_code == 1) return;

    if(strcmp(algorithm, "-bf")){
        BruceForeAlgorithm(input_path, output_path, output_info_code);
    }
    else if(strcmp(algorithm, "-rk")){
        RabinKarpAlgorithm(input_path, output_path, output_info_code);
    }
    else if(strcmp(algorithm, "-kmp")){
        KnuthMorrisPrattAlgorithm(input_path, output_path, output_info_code);
    }
    else if(strcmp(algorithm, "-bm")){
        BoyerMooreAlgorithm(input_path, output_path, output_info_code);
    }
    else if(strcmp(algorithm, "-tw")){
        TwoWayAlgorithm(input_path, output_path, output_info_code);
    }
}