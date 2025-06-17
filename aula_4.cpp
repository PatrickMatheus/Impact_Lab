#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

int main(){
    ifstream image("./images/imagem_leitura.ppm");
    ofstream newImage("./images/saida/imagem.ppm");

    if (!image.is_open() || !newImage.is_open()) {
        cerr << "Erro ao abrir os arquivos!" << endl;
        return 1;
    }

    string tipo = "", colunas = "", linhas = "", RGB = "";

    image >> tipo;
    image >> colunas;
    image >> linhas;
    image >> RGB;


    newImage << tipo << endl;
    newImage << colunas << " " << linhas << endl;
    newImage << RGB << endl;

    string red = "", green = "", blue = "";
    int r = 0, v = 0, b = 0;

    auto start = high_resolution_clock :: now();

    while(!image.eof()){
        image >> red;
        image >> green;
        image >> blue;

        r = stoi(red);
        v = stoi(green);
        b = stoi(blue);

        v = min(v*2, 255);

        red = to_string(r);
        green = to_string(v);
        blue = to_string(b);

        newImage << red << " " << green << " " << blue << " " ;

    }
    auto end = high_resolution_clock:: now();
    auto duration = duration_cast<milliseconds> (end - start);

    cout << "read and write images time: " << duration.count() << "ms" << endl;
     

    image.close(); 
    newImage.close();


    return 0;
}
