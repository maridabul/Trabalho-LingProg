#include <EXTERN.h>
#include <perl.h>
#include <iostream>
#include <string>
#include <fstream>
#include <exception>

#include "menu.h"
#include "perlWrapper.h"
#include "interface.h"

Interface::Interface () : perlWrapper (0, NULL, NULL){}

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
  //fstream arquivoTeste;
  
  if (getOperacao () == 1) 
    cout << "Fim do programa.\n" << endl;

  if (getOperacao () == 2)
  {
    string palavra;
    string encontrada;
//    try
    {
      cout << "Verificar palavra no dicionario\n\n"
            << "Insira a palavra:\n" << endl;
      cin >> palavra;  

        
  //    encontrada = perlWrapper::funcaoTipoA (palavra, "verificarPalavraNoDicionario", 2);
      if ((encontrada.compare("nao_encontrada")) == 0)
      {
        cout<< "Palavra nao foi encontrada no dicionario\n\n" << endl;
      } 
      else
      {
       cout<< "Expressao \"" << encontrada << "\" foi encontrada no dicionario\n\n" << endl;
      }
    }
 //   catch (...)
    {
      cout << "Entrada nao compativel com o esperado\n" << endl;
      cout << "Selecione enter para voltar ao menu" <<endl;
      cin >> erroInput;
    }
  }
/*
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

      // analise do arquivo de entrada
      arquivoTeste.open (arquivoInput.c_str (), ios::in); // somente leitura
      if (!arquivoTeste.is_open ())
        throw arquivoTeste;
      arquivoTeste.close ();
      cout << "\nInsira a expressao original que deseja substituir:\n" << endl;
      cin >> original;
      cout << "\nE o substituto:\n";
      cin >> substituto;
      
      string arquivoAlterado = "alteracoes.bak";
      perlWrapper::funcaoTipoB (arquivoInput, original, substituto, arquivoAlterado, "substituirExpressaoEmArquivo");
    
      cout <<  "O arquivo alterado esta em 'alteracoes.bak'.\n" << endl;
    }
    catch (...)
    {
      cout << "Erro: arquivo nao encontrado\n" << endl;
      cout << "Selecione enter para voltar ao menu" <<endl;
      cin >> erroInput;
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
      arquivoTeste.open (arquivoInput.c_str (), ios::in); // somente leitura
      if (!arquivoTeste.is_open ())
        throw arquivoTeste;
      arquivoTeste.close ();
      cout << "Insira o nome do arquivo que deseja armazenar as mudancas:\n";
      cout << "Importante: o nome desse arquivo precisa ser diferente do analisado!" << endl;
      cin >> arquivoOutput;
      arquivoTeste.open (arquivoOutput.c_str (), ios::in | ios::out); // leitura ou escrita
      if (!arquivoTeste.is_open ())
        throw arquivoTeste;
      arquivoTeste.close ();
      if (arquivoInput.compare(arquivoOutput) == 0)
      {
        cout << "Erro: arquivos com o mesmo nome!\n\n" << endl;
      }  
      else
      {
       perlWrapper::funcaoTipoB (arquivoInput, blackList, NULL, arquivoOutput, "censurarExpressoesInadequadas");
      }
    }
    catch (...)
    {
      cout << "Erro: arquivo nao encontrado\n" << endl;
      cout << "Selecione enter para voltar ao menu" <<endl;
      cin >> erroInput;
    }
  }

  if (getOperacao () == 6)
  {
    string arquivoInput;
    double porcentagem; 
   
    try
    { 
      cout << "Insira o nome do arquivo que deseja analisar:" << endl;
      cin >> arquivoInput;
      arquivoTeste.open (arquivoInput.c_str (), ios::in); // somente leitura
      if (!arquivoTeste.is_open ())
        throw arquivoTeste;
      arquivoTeste.close ();
      porcentagem =  perlWrapper::funcaoTipoC(arquivoInput, NULL, "porcentagemErro");
      porcentagem = 100*porcentagem;
      cout << "Porcentagem de erro:";
      cout << setprecision (2) << porcentagem << endl; 
    }
    catch (...)
    {
      cout << "Erro: arquivo nao encontrado\n" << endl;
      cout << "Selecione enter para voltar ao menu" <<endl;
      cin >> erroInput;
    }
  }
  
  if (getOperacao () == 7)
  {
    string arquivoPalavraInput;
    string arquivoConsultaInput;
    double porcentagem; 
    try 
    { 
      cout << "Insira o nome do arquivo que deseja analisar:" << endl;
      cin >> arquivoPalavraInput;
      arquivoTeste.open (arquivoPalavraInput.c_str (), ios::in); // somente leitura
      if (!arquivoTeste.is_open ())
        throw arquivoTeste;
      arquivoTeste.close ();
      cout << "Insira o nome do arquivo que deseja consultar:" << endl;
      cin >> arquivoConsultaInput;
      arquivoTeste.open (arquivoConsultaInput.c_str (), ios::in); // somente leitura
      if (!arquivoTeste.is_open ())
        throw arquivoTeste;
      arquivoTeste.close ();
      porcentagem =  perlWrapper::funcaoTipoC(arquivoPalavraInput, arquivoConsultaInput, "porcentagemSemelhanca");
      porcentagem = 100*porcentagem;
      cout << "Porcentagem semelhanca:";
      cout << setprecision (2) << porcentagem << endl; 
    }
    catch (...)
    {
      cout << "Erro: arquivo nao encontrado\n" << endl;
      cout << "Selecione enter para voltar ao menu" <<endl;
      cin >> erroInput;
    }    
  }
*/
}

