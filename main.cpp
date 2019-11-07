
#include "perlWrapper.h"
#include "menu.h"
#include "interface.h"

#include <iostream>
#include <string>

using namespace std;

int main ()
{
  Interface interface;

  interface.executarInterpretadorPerl ("funcoesPerl.pl");
  interface.executarInterface ();

  return 0;
}
