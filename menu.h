
#ifndef MENU
#define MENU

#include <EXTERN.h>
#include <perl.h>
#include <iostream>
#include <string>

using namespace std;

class Menu {
  public:
    Menu ();
    ~Menu ();

    void exibirOperacoes ();
    void setOperacao (); 
    int getOperacao ();

  private:  
    unsigned int operacao;    

};

#endif
