// reverseString
#include <iostream>
#include <string.h>

char* solve(char* A){
    int cont = 0;
    int len = strlen(A);
    char* B = (char*)malloc(sizeof(char)*len +1);

    for(int i = 0; i < len; i ++){
        B[len-i-1] = A[i];
    }

    for(int i = 0; i < len; i ++){
        if(B[i] == ' '){
            continue;
        }
        else{
            cont = 0;
            while(B[i+cont] != ' ')cont++;
            char* temp = (char*)malloc(sizeof(char)*cont +1);
            for(int j = 0; j<cont ; j ++){
                temp[cont-j-1] = B[i+j];
            }
            for(int j = 0; j <cont; j ++){
                B[i+j] = temp[j];
            }
            i += cont;
            free(temp);
        }
    }
    std::cout << "A: " << A << std::endl;
    std::cout << "B: " << B << std::endl;

    return A;
}

int main(){
    char A[] = " Yo lo estoy haciendo con Linux, pero si tienes Windows o Mac te recomiendo estos videos (ya que el compilador cambia):";
    solve(A);
    return 0;
}
