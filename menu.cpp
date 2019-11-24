#include <EXTERN.h>
#include <perl.h>
#include <iostream>
#include <string>
#include "menu.h"

Menu::Menu () : operacao (0) {}


void Menu::exibirOperacoes ()
{
  cout << "Selecione uma operacao: \n" 
       << "1 - Sair do programa\n" 
       << "2 - Verificar palavra no dicionario\n"
       << "3 - Analisar ortograficamente texto\n"
       << "4 - Substituir expressao em arquivo\n"
       << "5 - Censurar expressoes inadequadas\n" 
       << "6 - Porcentagem de erro do texto\n"
       << "7 - Porcentagem semelhanca entre dois textos\n" << endl;
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


