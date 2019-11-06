
#ifndef INTERFACE
#define INTERFACE

#include <EXTERN.h>
#include <perl.h>
#include <iostream>
#include <string>

#include "menu.h"
#include "perlWrapper.h"

using namespace std;

class Interface : public Menu, public perlWrapper {
  public:
    Interface ();

    void exibirMenuOperacoes ();
    void chamarFuncaoPerl ();  

  private:  

};

#endif
