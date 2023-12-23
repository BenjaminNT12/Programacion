// Try the following example in the editor below.

// Given the weekday number, print the weekday name corresponding to it.

// Note: Day 1 is Monday. First letter is always Capital.

// Sample Input

// 4
// Sample Output

// Thursday


#include <iostream>

int main(void){
    int day = 0;

    std::cin>>day;

    switch(day){
        case 1:{
            std::cout<<"Monday"<<std::endl;
        }break;
        case 2:{
            std::cout<<"Tuesday"<<std::endl;
        }break;
        case 3:{
            std::cout<<"Wensday"<<std::endl;
        }break;
        case 4:{
            std::cout<<"Thursday"<<std::endl;
        }break;
        case 5:{
            std::cout<<"Fraiday"<<std::endl;
        }break;
        case 6:{
            std::cout<<"Saturday"<<std::endl;
        }break;
        case 7:{
            std::cout<<"Sunday"<<std::endl;
        }break;
    } 

    return 0;
}