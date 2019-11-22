#include <EXTERN.h>
#include <perl.h>
#include <iostream>
#include <string>
#include <fstream>
#include <exception>

#include "menu.h"
#include "perlWrapper.h"
#include "interface.h"

#ifdef __cplusplus__
  #include <cstdlib>
#else
  #include <stdlib.h>
#endif

using namespace std;

Interface::Interface () : Menu(), perlWrapper (0, NULL, NULL){}

void Interface::exibirMenuOperacoes () 
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

void Interface::executarInterface ()
{
  if (system("CLS")) system("clear");
  while (getOperacao() != 1)
  {
    exibirMenuOperacoes ();    
    setOperacao ();
    chamarFuncaoPerl();
  }
}

void Interface::chamarFuncaoPerl ()
{
  string erroInput; 
  fstream testarArquivo;  

  if (getOperacao () == 1) 
    cout << "Fim do programa.\n\n" << endl;

  if (getOperacao () == 2)
  {
    string palavra;
    string encontrada;

    try
    {
      cout << "Verificar palavra no dicionario\n\n"
            << "Insira a palavra:\n" << endl;
      cin >> palavra;  
      
      if (inputNumerico(palavra))
        throw 0; 

      encontrada = perlWrapper::funcaoTipoA (palavra, "verificarPalavraNoDicionario", 2);
      if ((encontrada.compare("nao_encontrada")) == 0)
      {
        cout<< "Palavra nao foi encontrada no dicionario\n\n" << endl;
      } 
      else
      {
       cout<< "Expressao \"" << encontrada << "\" foi encontrada no dicionario\n\n" << endl;
      }
      return;
    }
    catch (int)
    {
      cout << "Entrada nao compativel com o esperado\n" << endl;
      cout << "Entrada deve ser uma palavra\n\n" << endl;
      return;
    }
  }
  
  if (getOperacao () == 3)
  { 
    string arquivoInput;  

    try {
    cout << "Analisar ortograficamente texto\n\n"  
         << "Insira o nome do arquivo que deseja analisar:" << endl;
    cin >> arquivoInput;
    
    testarArquivo.open (arquivoInput.c_str (), ios::out | ios::in);
    if (!testarArquivo.is_open ())
      throw arquivoInput;
    testarArquivo.close ();

    string arquivoOutput = perlWrapper::funcaoTipoA (arquivoInput, "criarArquivoPalavrasNaoEncontradas", 3);

    cout <<  "O arquivo com as palavras nao encontradas esta em \""<< arquivoOutput <<"\"" << endl;

    return;
    }
    catch (string) {
      cout << "Erro: arquivo nao encontrado\n\n" << endl;
      return;
    }
  }
  if (getOperacao () == 4)
  {
    string arquivoInput;
    string original;
    string substituto;
    
    try
    {
      cout << "Substituir expressao em arquivo\n\n" 
           << "Insira o nome do arquivo que deseja modificar:\n" << endl;
      cin >> arquivoInput;

    testarArquivo.open (arquivoInput.c_str (), ios::out | ios::in);
    if (!testarArquivo.is_open ())
      throw arquivoInput;
    testarArquivo.close ();

      cout << "\nInsira a expressao original que deseja substituir:\n" << endl;
      cin >> original;
      cout << "\nE o substituto:\n";
      cin >> substituto;
      
      string arquivoAlterado = "alteracoes.bak";
      perlWrapper::funcaoTipoB (arquivoInput, original, substituto, arquivoAlterado, "substituirExpressaoEmArquivo", 4);
    
      cout <<  "O arquivo alterado esta em 'alteracoes.bak'.\n" << endl;
      return;
    }
    catch (string)
    {
      cout << "Erro: arquivo nao encontrado\n\n" << endl;
      return;
    }
  }

  if (getOperacao () == 5)
  {
    string arquivoInput;
    string blackList = "blackList.txt";
    string arquivoOutput;
    try 
    {
      cout << "Censurar expressoes inadequadas\n\n" << endl; 
      
      cout << "Insira o nome do arquivo que deseja analisar:" << endl;
      cin >> arquivoInput;
      
      testarArquivo.open (arquivoInput.c_str (), ios::out | ios::in);
      if (!testarArquivo.is_open ())
        throw arquivoInput;
      testarArquivo.close ();

      cout << "Insira o nome do arquivo que deseja armazenar as mudancas:\n";
      cout << "Importante: o nome desse arquivo precisa ser diferente do analisado!" << endl;
      cin >> arquivoOutput;

      if (arquivoInput.compare(arquivoOutput) == 0)
        cout << "Erro: arquivos com o mesmo nome!\n\n" << endl;
        
      else
      {
        testarArquivo.open (arquivoOutput.c_str (), ios::out);
        if (!testarArquivo.is_open ())
          throw arquivoOutput;
        testarArquivo.close ();

         perlWrapper::funcaoTipoB (arquivoInput, blackList, "NULL", arquivoOutput, "censurarExpressoesInadequadas", 5);

        cout << "O arquivo censurado encontra-se em: " << arquivoOutput << "\n\n" << endl;
      }
      return;
    }
    catch (string arquivo)
    {
      cout << "Erro ao abrir arquivo" << arquivo << "\n\n" << endl;
      return;
    }
    
  }

  if (getOperacao () == 6)
  {
    string arquivoInput;
    double porcentagem; 
    try 
    { 
      cout << "Porcentagem de erro do texto\n\n" << endl;
      cout << "Insira o nome do arquivo que deseja analisar:" << endl;
      cin >> arquivoInput;
     
      testarArquivo.open (arquivoInput.c_str (), ios::out | ios::in);
      if (!testarArquivo.is_open ())
        throw arquivoInput;
      testarArquivo.close ();
 
      porcentagem =  perlWrapper::funcaoTipoC(arquivoInput, "NULL", "porcentagemErro", 6);
      porcentagem = 100*porcentagem;
      cout << "Porcentagem de erro:" << porcentagem << "\n\n" << endl; 
      
      return;
    }
    catch (string)
    {
      cout << "Erro: arquivo nao encontrado\n" << endl;
      return;
    }
  }
  if (getOperacao () == 7)
  {
    string arquivoPalavraInput;
    string arquivoConsultaInput;
    double porcentagem; 
    try
    { 
      cout << "Porcentagem semelhanca entre dois textos\n\n" << endl;
      cout << "Insira o nome do arquivo que deseja analisar:" << endl;
      cin >> arquivoPalavraInput;
      
      testarArquivo.open (arquivoPalavraInput.c_str (), ios::out | ios::in);
      if (!testarArquivo.is_open ())
        throw arquivoPalavraInput;
      testarArquivo.close ();
      
      cout << "Insira o nome do arquivo que deseja consultar:" << endl;
      cin >> arquivoConsultaInput;
      
      testarArquivo.open (arquivoConsultaInput.c_str (), ios::out | ios::in);
      if (!testarArquivo.is_open ())
        throw arquivoConsultaInput;
      testarArquivo.close ();

      porcentagem =  perlWrapper::funcaoTipoC(arquivoPalavraInput, arquivoConsultaInput, "porcentagemSemelhanca", 7);
      porcentagem = 100*porcentagem;
      cout << "Porcentagem semelhanca:" << porcentagem << "\n\n" << endl; 
  
      return;
    }
    catch (string)
    {
      cout << "Erro: arquivo nao encontrado\n" << endl;
      return;
    } 
  }
} // end chamarFuncaoPerl


bool Interface::inputNumerico (string input) 
{ 
  int indice;
  for (indice = 0; indice < input.length(); indice++) 
    if (isdigit(input[indice]) == true) 
      return true; 
  
    return false; 
} 
  









