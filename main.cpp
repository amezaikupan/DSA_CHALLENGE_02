#include <iostream>
#include <vector>
#include <fstream>
#include "command.h"
#include "algorithms.h"
#include <time.h>

using namespace std;

int main(int argc, char** argv){

    // vector<char> generator = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' ,'k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    // srand(time(0));
    // string res = "";

    // for(int i = 0; i < 50; i++){
    //     int r = rand() % 26;
    //     res += generator[r];
    // } 
    // cout << res << endl;
    
    if(argc != 5){
        cout << "INVALID INPUT" << endl;
    }else{
        Command(argv[1], argv[2], argv[3], argv[4]);
    }
}