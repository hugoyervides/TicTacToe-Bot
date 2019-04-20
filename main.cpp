#include <iostream>
#include "Tablero.h"
#include <vector>
#include <climits>
#include <time.h>
using namespace std;
//Declaracion de la estructura movimiento
struct Movimiento{
    int row;
    int col;
    int score;
};
//Funcion mianMax
int miniMax(Tablero currentTablero, char jugador){
    //Conseguir numero de espacios disponbles
    int numeroEspacios=currentTablero.numberOfEmptySpaces();
    int mayor=INT_MIN;
    int menor=INT_MAX;
    std::vector< std::vector<int> > emptySpaces= currentTablero.emptySpaces();
    std::vector<Movimiento> moves;
    //cout << currentTablero <<endl;
    //Ver si tenemos un ganador
    if(currentTablero.getWiner()=='X'){
            return -10;
    }
    else if(currentTablero.getWiner()=='O'){
            return 10;
    }
    else if(numeroEspacios==0){
            return 0;
    }
    //Ciclo for para recorrer los espacios vacios
    for(int i=0; i<numeroEspacios; i++){
        //hacer el nuevo movimiento
        Tablero cache=currentTablero;
        Movimiento movCache;
        movCache.row=emptySpaces[i][0];
        movCache.col=emptySpaces[i][1];
        cache.makePlay(emptySpaces[i][0],emptySpaces[i][1],jugador);
        //ver a quien le toca jugar
        if(jugador=='O'){
            movCache.score=miniMax(cache, 'X');
        }
        else{
            movCache.score=miniMax(cache,'O');
        }
        moves.push_back(movCache);
    }
    //Ver la mejor movida
    if(jugador=='O'){
        //Regresar el mayor de los movimientos
        for(std::vector<Movimiento>::iterator i=moves.begin();i!=moves.end();i++){
            if(mayor < (*i).score){
                mayor = (*i).score;
            }
        }
        //regresar resultado
        return mayor;
    }
    else{
        //regresar el menor de los movimientos
        for(std::vector<Movimiento>::iterator i=moves.begin();i!=moves.end();i++){
            if(menor > (*i).score){
                menor= (*i).score;
            }
        }
        return menor;
    }
}
//Declaracion del algoritmo de minMax
vector<int> getBestMove(Tablero currentTablero){
    //Declaracion de variables
    std::vector< std::vector<int> > emptySpaces= currentTablero.emptySpaces();
    std::vector<int> peso;
    std::vector<int> returnVec;
    int mayor=INT_MIN;
    int indexMayor=0;
    int pesoCache=0;
    //Ciclo for para llenar el tablero con los movimientos posibles
    for(int i=0; i<currentTablero.numberOfEmptySpaces(); i++){
        Tablero newTablero=currentTablero;
        //hacer la jugada
        newTablero.makePlay(emptySpaces[i][0],emptySpaces[i][1],'O');
        //llamar funcion minimax para conseguir el mejor movimiento
        pesoCache=miniMax(newTablero, 'X');
        std::cout<<"Movimiento [" << emptySpaces[i][0] << "] [" << emptySpaces[i][1] << "] tiene un peso de: " << pesoCache <<endl;
        peso.push_back(pesoCache);
    }
    //Ciclo for para conseguir el menor peso
    for(int i=0; i<currentTablero.numberOfEmptySpaces(); i++){
        if(mayor<peso[i]){
            mayor=peso[i];
            indexMayor=i;
        }
    }
    returnVec.push_back(emptySpaces[indexMayor][0]);
    returnVec.push_back(emptySpaces[indexMayor][1]);
    return returnVec;
}
int main(){
  //Declaracion de variables
  Tablero mainTab;
  int reg,col;
  vector<int> computer;
  cout<<"Loading TIC TAC TOE GAME!..." <<endl;
  while(mainTab.getWiner()=='N' && !mainTab.gameOver()){
    cout<<"Current game" <<endl;
    cout<<mainTab;
    cout<<"Waiting for User Input (Row,Col)" <<endl;
    cin>>reg>>col;
    if(!mainTab.makePlay(reg,col,'X')){
      cout<<"Invalid User Move, Try Again" << endl;
    }
    else if(!mainTab.gameOver()){
      cout<< "Computer Turn....." << endl;
      computer = getBestMove(mainTab);
      if(!mainTab.makePlay(computer[0],computer[1],'O')){
        cout<<"Internal Error! Invalid Computer Move!" << endl;
        cout<<"Terminating Game!" <<endl;
      }
      else{
        cout<<"Computer Done!"<<endl;
      }
    }
  }
  cout<<"GAMEOVER!" <<endl;
  cout << mainTab;
  //Display winner
  cout<<"The winner is: " << mainTab.getWiner() << endl;
  return 0;
}