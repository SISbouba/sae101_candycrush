#include <iostream>
#include "score.h"

void updateScore (unsigned int & score, const unsigned & howMany){
    score += howMany * 10;     
}


// void displayScore (const unsigned int & score)
// {
//     std::cout << "Score : " << score << std::endl;
// }
