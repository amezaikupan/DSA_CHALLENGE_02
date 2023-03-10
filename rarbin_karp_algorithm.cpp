#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>

void RabinKarpAlgorithm(char* input_path, char* output_path, int output_info){
    std::ifstream fin (input_path);

    std::string pat, txt;
    fin >> pat >> txt;
    
    long long cmp = 0;
    auto start = std::chrono::high_resolution_clock::now();   // Start measuring time 

    int m = pat.length(); 
    int n = txt.length();
    int i, j;

    int p = 0; // Hash value for pattern 
    int t = 0; // hash value for txt 
    int q = 11; // For modulo, avoid collision
    int d = 26; //Number of characters used in test

    int h = 1;

    
    std::vector<int> res;// Record found position of pat in txt

    // Calculate the hash value of pattern and first window of text
    // Here, the initial formula for the hash function of first window of text (for example) is: 
    // t = d^(m - 1) * txt[0] + d^(m - 2) * txt[1] + ... + d^1 * txt[m - 2] + txt[m - 1] 
    for (i = 0; ++cmp && i < m; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    // We want our hash function to be O(1), so we have to update the hash value 
    // of the current window of text by the hash value of the previous window of text
    // The formula would be: 
    // t_cur = (t_pre - d^(m - 1) * txt[i - 1]) * d + txt[i + m - 1]
    // So the h value would be d^(m - 1)

    for (i = 0; ++cmp && i < m - 1; i++) {
        h = (h * d) % q; // Not using pow because it can be out of range 
    }

    // Slide the pattern over text one by one
    for (i = 0; ++cmp && i <= n - m; i++) {
        // Check if the hash value of pattern and the current text window are the same. 
        // If match, start to compare chars one by one
        if (++cmp && p == t) {
            for (j = 0; ++cmp && j < m; j++) {
                if (++cmp && txt[i + j] != pat[j]) {
                    break;
                }
            }

            if (++cmp && j == m) {
                res.push_back(i);
                // std::cout << "\n Pattern found at index " << i << ". ";
            }
        }

        // Calculate the hash value for the next window of text 
        if (++cmp && i < n - m) {
            t = (d * (t - h * txt[i]) + txt[i + m]) % q;

            // We might get negative t, so just adjust it
            if (++cmp && t < 0) {
                    t += q;
            }
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