#include <EXTERN.h>
#include <perl.h>
#include <iostream>
#include <string>

#include "menu.h"
#include "perlWrapper.h"
#include "interface.h"

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
  
  if (getOperacao () == 1) 
    cout << "Fim do programa.\n" << endl;

  if (getOperacao () == 2)
  {
    string palavra;
    string encontrada;
    {
      cout << "Verificar palavra no dicionario\n\n"
            << "Insira a palavra:\n" << endl;
      cin >> palavra;  

      cout << palavra << endl;

        
      encontrada = perlWrapper::funcaoTipoA (palavra, "verificarPalavraNoDicionario", 2);
      if ((encontrada.compare("nao_encontrada")) == 0)
      {
        cout<< "Palavra nao foi encontrada no dicionario\n\n" << endl;
      } 
      else
      {
       cout<< "Expressao \"" << encontrada << "\" foi encontrada no dicionario\n\n" << endl;
      }
    }
    /*
    {
      cout << "Entrada nao compativel com o esperado\n" << endl;
      cout << "Selecione enter para voltar ao menu" <<endl;
      cin >> erroInput;
    }
    */
  }
  if (getOperacao () == 3)
  { 
    string arquivoInput;  
    cout << "Analisar ortograficamente texto\n\n"  
         << "Insira o nome do arquivo que deseja analisar:" << endl;
    cin >> arquivoInput;

    string arquivoOutput = perlWrapper::funcaoTipoA (arquivoInput, "criarArquivoPalavrasNaoEncontradas", 3);

    cout <<  "O arquivo alterado esta em \""<< arquivoOutput <<"\"" << endl;

  }
  if (getOperacao () == 4)
  {
    string arquivoInput;
    string original;
    string substituto;
    
    {
      cout << "Substituir expressao em arquivo\n\n" 
           << "Insira o nome do arquivo que deseja modificar:\n" << endl;
      cin >> arquivoInput;

      cout << "\nInsira a expressao original que deseja substituir:\n" << endl;
      cin >> original;
      cout << "\nE o substituto:\n";
      cin >> substituto;
      
      string arquivoAlterado = "alteracoes.bak";
      perlWrapper::funcaoTipoB (arquivoInput, original, substituto, arquivoAlterado, "substituirExpressaoEmArquivo", 4);
    
      cout <<  "O arquivo alterado esta em 'alteracoes.bak'.\n" << endl;
    }
    /*
    {
      cout << "Erro: arquivo nao encontrado\n" << endl;
      cout << "Selecione enter para voltar ao menu" <<endl;
      cin >> erroInput;
    }
    */
  }

  if (getOperacao () == 5)
  {
    string arquivoInput;
    string blackList = "blackList.txt";
    string arquivoOutput; 
    {
      cout << "Censurar expressoes inadequadas\n\n" << endl; 
      
      cout << "Insira o nome do arquivo que deseja analisar:" << endl;
      cin >> arquivoInput;
      cout << "Insira o nome do arquivo que deseja armazenar as mudancas:\n";
      cout << "Importante: o nome desse arquivo precisa ser diferente do analisado!" << endl;
      cin >> arquivoOutput;
      if (arquivoInput.compare(arquivoOutput) == 0)
      {
        cout << "Erro: arquivos com o mesmo nome!\n\n" << endl;
      }  
      else
      {
       perlWrapper::funcaoTipoB (arquivoInput, blackList, "NULL", arquivoOutput, "censurarExpressoesInadequadas", 5);
      }
    }
    /*
    {
      cout << "Erro: arquivo nao encontrado\n" << endl;
      cout << "Selecione enter para voltar ao menu" <<endl;
      cin >> erroInput;
    }
    */
  }

  if (getOperacao () == 6)
  {
    string arquivoInput;
    double porcentagem; 
   
    { 
      cout << "Insira o nome do arquivo que deseja analisar:" << endl;
      cin >> arquivoInput;
      cout << "aqui foi\n\n";
      cout << "arquivo input:" << arquivoInput << endl;
      porcentagem =  perlWrapper::funcaoTipoC(arquivoInput, "NULL", "porcentagemErro", 6);
      porcentagem = 100*porcentagem;
      cout << "Porcentagem de erro:";
      cout << porcentagem << endl; 
    }
    /*
    {
      cout << "Erro: arquivo nao encontrado\n" << endl;
      cout << "Selecione enter para voltar ao menu" <<endl;
      cin >> erroInput;
    }
    */
  }
  if (getOperacao () == 7)
  {
    string arquivoPalavraInput;
    string arquivoConsultaInput;
    double porcentagem; 
    { 
      cout << "Insira o nome do arquivo que deseja analisar:" << endl;
      cin >> arquivoPalavraInput;
      cout << "Insira o nome do arquivo que deseja consultar:" << endl;
      cin >> arquivoConsultaInput;
      porcentagem =  perlWrapper::funcaoTipoC(arquivoPalavraInput, arquivoConsultaInput, "porcentagemSemelhanca", 7);
      porcentagem = 100*porcentagem;
      cout << "Porcentagem semelhanca:";
      cout << porcentagem << endl; 
    }
    /*
    {
      cout << "Erro: arquivo nao encontrado\n" << endl;
      cout << "Selecione enter para voltar ao menu" <<endl;
      cin >> erroInput;
    } 
    */   
  }
} // end chamarFuncaoPerl
