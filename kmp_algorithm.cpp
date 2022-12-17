#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>
#include <chrono>

void ComputeLPSArray(std::string pat, std::vector<int> lps, long long &cmp){
	int m = pat.size();
	int len = 0;
	lps[0] = 0;

	int i = 1;
	while (++cmp && i < m) {
		if (++cmp && pat[i] == pat[len]) {
			len++;
			lps[i] = len; 
			i++;
		} else {
			if (++cmp && len != 0) {
				len = lps[len - 1];
			} else {
				lps[i] = 0;
				i++;
			} 
		}
	}
}

void KMPAlgorithm(char* input_path, char* output_path, int output_info){

	std::ifstream fin (input_path);
		
	std::string pat, txt;
	fin >> pat >> txt;

	long long cmp = 0;
	auto start = std::chrono::high_resolution_clock::now();   // Start measure time 

	int n = txt.size();
	int m = pat.size();

	std::vector<int> lps(m, 0);

	ComputeLPSArray(pat, lps, cmp);

	std::vector<int> res;

	int i = 0; 
	int j = 0; 
	while (++cmp && (n - i) >= (m - j)) {
		if (++cmp && pat[j] == txt[i]) {
			i++;
			j++;
		}

		if (++cmp && j == m) {
			res.push_back(i - j);
			j = lps[j - 1];
		} else if (++cmp && i < n && ++cmp && pat[j] != txt[i]) {
			if (++cmp && j != 0) {
				j = lps[j - 1];
			} else {
				i++;
			}
		}
	}
	
	auto end = std::chrono::high_resolution_clock::now();// Stop measuring time
	double time = double(std::chrono::duration_cast <std::chrono::nanoseconds> (end - start).count()) /1e6;


	fin.close();

    std::ofstream fout (output_path);

    for(int i = 0; i < res.size(); i++){
        fout << res[i] << " " << res[i] + m - 1 << std::endl;
    }

    fout.close();

    if(output_info == 0){
        std::cout << "Time: " << time << std::endl;
    }else if(output_info == 1){
        std::cout << "Comparisons: " << cmp << std::endl;
    }else{
        std::cout << "Time: " << time << std::endl;
        std::cout << "Comparisons: " << cmp << std::endl;
    }
}