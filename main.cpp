#include <iostream>
#include <command.h>

using namespace std;

int main(int argc, char** argv){
    if(argc != 5){
        cout << "INVALID INPUT" << endl;
    }else{
        Command(argv[1], argv[2], argv[3], argv[4]);
    }
}