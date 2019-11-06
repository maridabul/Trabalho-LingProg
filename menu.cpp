#include <EXTERN.h>
#include <perl.h>
#include <iostream>
#include <string>
#include "menu.h"


void Menu::exibirOperacoes ()
{
  cout << "Selecione uma operacao: \n" << endl;
}

int Menu::getOperacao ()
{
  return operacao;
}

void Menu::setOperacao () 
{
  bool input = false;

  while (input == false)
  {
    try
    {
      input = true;
      cin >> operacao;
    }
    catch (...)
    {
      cout << "Tente novamente:" << endl;
      input = false;
    }
  }
}


