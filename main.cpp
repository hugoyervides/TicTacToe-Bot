#include <iostream>
#include "Tablero.h"
#include <vector>
#include <climits>
#include <time.h>

using namespace std;
//function to display welcome
void displayWelcome(){
  cout<<R"(  _______ _        _______           _______           ____        _   _
  |__   __(_)      |__   __|         |__   __|         |  _ \      | | | |
    | |   _  ___     | | __ _  ___     | | ___   ___  | |_) | ___ | |_| |
    | |  | |/ __|    | |/ _` |/ __|    | |/ _ \ / _ \ |  _ < / _ \| __| |
    | |  | | (__     | | (_| | (__     | | (_) |  __/ | |_) | (_) | |_|_|
   _|_|_ |_|\___|    |_|\__,_|\___| _  |_|\___/ \___| |____/ \___/ \__(_)
  / ____|              | |         | | |  _ \
  | |     _ __ ___  __ _| |_ ___  __| | | |_) |_   _
  | |    | '__/ _ \/ _` | __/ _ \/ _` | |  _ <| | | |
  | |____| | |  __/ (_| | ||  __/ (_| | | |_) | |_| |
  \_____|_|  \___|\__,_|\__\___|\__,_| |____/ \__, |
  __      ___      _                ____        __/ |           _     _
  \ \    / (_)    | |              / __ \      |___/           (_)   | |
  \ \  / / _  ___| |_ ___  _ __  | |  | |_   _  ___ _ ____   ___  __| | ___  ___
   \ \/ / | |/ __| __/ _ \| '__| | |  | | | | |/ _ \ '__\ \ / / |/ _` |/ _ \/ __|
    \  /  | | (__| || (_) | |    | |__| | |_| |  __/ |   \ V /| | (_| |  __/\__ \
     \/   |_|\___|\__\___/|_|     \____/ \__, |\___|_|    \_/ |_|\__,_|\___||___/
                                          __/ |
                                         |___/
  )" <<endl;
}

bool isOnCuadrant(Tablero game){
  vector<vector<char>> tablero=game.getJuego();
  if(tablero[0][1]=='O'){
    return true;
  }
  else if(tablero[1][0]=='O'){
    return true;
  }
  else if(tablero[1][2]=='O'){
    return true;
  }
  else if(tablero[2][1]=='O'){
    return true;
  }
  else{
    return false;
  }
}
//Funcion para ver si esta aplicando trampa
bool isOpponentUsingCheat(Tablero game){
  //get the vector
  vector<vector<char>> tablero=game.getJuego();
  //check if there are cheat
  if(((tablero[0][0]=='X'&&tablero[2][2]=='X')||(tablero[2][0]=='X'&&tablero[0][2]=='X'))&&tablero[1][1]=='O'){
    return true;
  }
  else{
    return false;
  }
}
//Funcion para ver si el oponente esta en una esquina
bool isOpponentInCorner(Tablero game){
  //get the matrix
  vector<vector<char>> tablero= game.getJuego();
  //ceck if there are an X in the corners
  if(tablero[0][0]=='X'){
    return true;
  }
  else if(tablero[0][2]=='X'){
    return true;
  }
  else if(tablero[2][0]=='X'){
    return true;
  }
  else if(tablero[2][2]=='X'){
    return true;
  }
  else{
    return false;
  }
}
//Funcion para calcuilar el nivel minimo
void getMinLevel(Tablero game ,int player, int &minLevel, int nivel){
  //cout<<nivel <<endl;
  //cout<<game <<endl;
  //ver si gano ya uno de los dos
  if(game.getWiner()=='O'){
      if(minLevel>nivel){
          minLevel=nivel;
      }
  }
  else if(game.getWiner()=='X'){
      if(minLevel>nivel){
          minLevel=nivel;
      }
  }
  else if(game.gameOver()){
      if(minLevel>nivel){
          minLevel=nivel;
      }
  }
  else{
    //llamada recursiva para otros posibles juegos
    for(int i =0; i<3; i++){
      for(int j=0; j<3 ;j++){
        //ver si es posible la jugada
        if(game.isMovePosible(i,j)){
          Tablero newTab;
          char play = (player%2==0)?'O':'X';
          newTab.setJuego(game.getJuego());
          newTab.makePlay(i,j,play);
          getMinLevel(newTab,player+1,minLevel,nivel+1);
        }
      }
    }
  }
}

//Funcion recursiva para calcular la siguiente mejor jugada
int getGameValue(Tablero game, int player, int maxLevel, int caso){
  if(maxLevel >= 0){
    //ver si gano ya uno de los dos
    if(game.getWiner()=='O'){
      return 1;
    }
    else if(game.getWiner()=='X'){
      return -1;
    }
    else if(game.gameOver()){
      return 0;
    }
    else{
      int s=0;
      //llamada recursiva para otros posibles juegos
      for(int i =0; i<3; i++){
        for(int j=0; j<3 ;j++){
          //ver si es posible la jugada
          if(game.isMovePosible(i,j)){
            Tablero newTab;
            char play = (player%2==0)?'O':'X';
            newTab.setJuego(game.getJuego());
            newTab.makePlay(i,j,play);
            s+=getGameValue(newTab,player+1,maxLevel-1, caso);
          }
        }
      }
      return s;
    }
  }
  else{
      return 0;
  }
}

vector< int > getBestMove(Tablero game){
  //Check if the player is in the corner
  if((isOpponentInCorner(game) && game.isMovePosible(1,1))){
    cout<<"Posible cheat detected! defeating!!" <<endl;
    vector<int> result;
    result.push_back(1);
    result.push_back(1);
    return result;
  }
  else if(isOpponentUsingCheat(game)&&(!isOnCuadrant(game))){
    vector<int>result;
    bool stillTrying = true;
    int randomNumber;
    cout<<"Posible cheat detected! defeating!!" <<endl;
    //gereate random move based on the cuadrant
    do{
      randomNumber=rand()%4+1;
      //try to make move
      switch(randomNumber){
        case 1:
            //try to make move
            if(game.isMovePosible(0,1)){
              result.push_back(0);
              result.push_back(1);
              stillTrying=false;
            }
        break;
        case 2:
          //try to make move
          if(game.isMovePosible(1,0)){
            result.push_back(1);
            result.push_back(0);
            stillTrying=false;
          }
        break;
        case 3:
          //try to make move
          if(game.isMovePosible(1,2)){
            result.push_back(1);
            result.push_back(2);
            stillTrying=false;
          }
        break;
        case 4:
          //try to make move
          if(game.isMovePosible(2,1)){
            result.push_back(2);
            result.push_back(1);
            stillTrying=false;
          }
        break;
      }
    }while(stillTrying);
    return result;
  }
  else{
    //declaracion de variables
    int caso =0;
    int maxLevel= INT_MAX;
    double maximo = INT_MIN;
    double value;
    vector<int> resultado;
    resultado.push_back(0);
    resultado.push_back(0);
    cout<<"Normal Play! generating all possible moves!" <<endl;
    //Ciclo for para generar juegos al azar
    for(int i=0; i<3; i++){
      for(int j=0; j<3; j++){
        //ver si la jugada es posible5
        if(game.isMovePosible(i,j)){
          Tablero newTabl;
          newTabl.setJuego(game.getJuego());
          newTabl.makePlay(i,j,'O');
          //conseguir valor miniomo
          getMinLevel(newTabl,1,maxLevel,0);
          //Condicion para ver el menor
          value=getGameValue(newTabl,1,maxLevel,caso);
          //Debuging
          std::cout<<"Move ("<<i<<","<<j<<") Probability: " << value <<std::endl;
          caso++;
          if(value > maximo){
             maximo=value;
             resultado[0]=i;
             resultado[1]=j;
         }
        }
      }
    }
    std::cout<<"Max depth level: " << maxLevel << std::endl;
    return resultado;
  }
}

int main(){
  //Declaracion de variables
  Tablero mainTab;
  int reg,col;
  vector<int> computer;
  displayWelcome();
  cout<<"Loading TIC TAC TOE GAME!..." <<endl;
  while(mainTab.getWiner()=='N' && !mainTab.gameOver()){
    cout<<"Current game" <<endl;
    cout<<mainTab;
    cout<<"Waiting for User Input (Row,Col)" <<endl;
    cin>>reg>>col;
    if(!mainTab.makePlay(reg,col,'X')){
      cout<<"Invalid User Move, Try Again" << endl;
    }
    else{
      cout<< "Computer Turn....." << endl;
      computer = getBestMove(mainTab);
      if(!mainTab.makePlay(computer[0],computer[1],'O')){
        cout<<"Invalid Computer Move, Try Again" << endl;
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
