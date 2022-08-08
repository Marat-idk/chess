#include <iostream>
#include "Chess.h"

using namespace Chess;

#include <vector>
#include <algorithm>

int main(){
    ChessBoard temp;
    //temp.StartGame();

    std::vector<int> v = {1, 2, 3, 4, 1, 1, 2, 2, 3, 3};
    v.erase(std::remove(v.begin(), v.end(), 2), v.end());
    for(const int &value: v){
        std::cout << value << " ";
    }
    std::cout << std::endl;
}