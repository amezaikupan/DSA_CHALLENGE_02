#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>

#define NUM_CHARS 256

using namespace std;

long long BoyerMooreAlgorithmCmp(char* input_path, char* output_path){
    long long cmp = 0;

    ifstream fin (input_path);

    string pattern, txt;
    fin >> pattern >> txt;

    int bad_char[NUM_CHARS];
    int pat_len = pattern.length();
    int txt_len = txt.length();

    for(int i = 0; i < NUM_CHARS && ++cmp; i++){
        bad_char[i] = -1;
    }

    for(int i = 0; i < pat_len && ++cmp; i++){
        bad_char[(int) pattern[i]] = i; 
    }

    int s = 0;
    vector<int> res;

    while(++cmp && s + pat_len < txt_len){
        int j = pat_len - 1;

        while(++cmp && j >= 0){
            if(txt[s + j] != pattern[j]) break;
            j--;
        }

        if(++cmp && j < 0){
            res.push_back(s);

            if(++cmp && s + pat_len < txt_len){
                s += pat_len - bad_char[txt[s + pat_len]];
            }else{
                s += 1;
            }
        }
        else{
            if(++cmp && j - bad_char[txt[s + j]] > 1){
                s += j - bad_char[txt[s + j]];
            }else{
                s += 1;
            }
        }
    }

    fin.close();

    ofstream fout (output_path);

    for(int i = 0; i < res.size(); i++){
        fout << res[i] << " " << res[i] + pat_len - 1 << endl;
    }

    fout.close();

    return cmp;
}

double BoyerMooreAlgorithmTime(char* input_path, char* output_path){
    auto start = chrono::high_resolution_clock::now();   // Start measure time 
    ifstream fin (input_path);

    string pattern, txt;
    fin >> pattern >> txt;

    int bad_char[NUM_CHARS];
    int pat_len = pattern.length();
    int txt_len = txt.length();


    for(int i = 0; i < NUM_CHARS; i++){
        bad_char[i] = -1;
    }

    for(int i = 0; i < pat_len; i++){
        bad_char[(int) pattern[i]] = i; 
    }

    int s = 0;
    vector<int> res;

    while(s + pat_len <= txt_len){
        int j = pat_len - 1;

        while(j >= 0){
            if(txt[s + j] != pattern[j]) break;
            j--;
        }

        if(j < 0){
            res.push_back(s);

            if(s + pat_len < txt_len){
                s += pat_len - bad_char[txt[s + pat_len]];
            }else{
                s += 1;
            }
        }
        else{
            if(j - bad_char[txt[s + j]] > 1){
                s += j - bad_char[txt[s + j]];
            }else{
                s += 1;
            }
        }
    }

    fin.close();

    ofstream fout (output_path);

    for(int i = 0; i < res.size(); i++){
        fout << res[i] << " " << res[i] + pat_len - 1 << endl;
    }

    fout.close();

    auto end = chrono::high_resolution_clock::now();
	double time = double(chrono::duration_cast <chrono::nanoseconds> (end - start).count()) / 1e6;

    return time;
}

void BoyerMooreAlgorithm(char* input_path, char* output_path, int output_info){
    if(output_info == 0){
        double time = BoyerMooreAlgorithmTime(input_path, output_path);
        cout << "Time: " << time << endl;
    }else if(output_info == 1){
        long long cmp = BoyerMooreAlgorithmCmp(input_path, output_path);
        cout << "Comparisons: " << cmp << endl;
    }else{
        double time = BoyerMooreAlgorithmTime(input_path, output_path);
        long long cmp = BoyerMooreAlgorithmCmp(input_path, output_path);
        cout << "Time: " << time << endl;
        cout << "Comparisons: " << cmp << endl;
    }
}