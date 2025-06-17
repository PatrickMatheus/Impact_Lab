#include <iostream>
#include <fstream>

using namespace std;

int main(){
    ofstream imagem_entrada; 
    

    imagem_entrada.open("./images/imagem.ppm");
    if(imagem_entrada.is_open()){

        //Head
        imagem_entrada << "P3" << endl;
        imagem_entrada << "70 50" << endl;
        imagem_entrada << "255" << endl;
        
        //corpo
        for(int i = 0; i < 50; i++){
            for(int j = 0; j < 70; j++){
                if(i < 35){
                    imagem_entrada << "255 0 0 ";
                }else{
                    imagem_entrada << "0 0 255 ";
                }
            }
            imagem_entrada << endl;
        }

    }

    imagem_entrada.close();

    return 0;
}