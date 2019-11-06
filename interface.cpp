#include <EXTERN.h>
#include <perl.h>
#include <iostream>
#include <string>

#include "menu.h"
#include "perlWrapper.h"
#include "interface.h"

    Interface ();

    void chamarFuncaoPerl ();  

void exibirMenuOperacoes () 
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

void chamarFuncaoPerl ()
{
  

  if (getOperacao () == 2)
  {
    string palavra;
    string encontrada;
    cout << "Verificar palavra no dicionario\n\n"
          << "Insira a palavra:\n" << endl;
        
    encontrada = funcoesPerl::verificarPalavraNoDicionario($palavra);
    if (($encontrada cmp '0') == 0)
    {
      print "Palavra nao foi encontrada no dicionario\n\n";
    } 
    else
    {
      print "Expressao '";
      print $encontrada;
      print "' foi encontrada no dicionario\n\n";
  





  }

  if (getOperacao () == 4)
  {
    string arquivoInput;
    string original;
    string substituto;
    cout << "Substituir expressao em arquivo\n\n" 
         << "Insira o nome do arquivo que deseja modificar:\n" << endl;
    cin >> arquivoInput;

    cout << "\nInsira a expressao original que deseja substituir:\n" << endl;
    cin >> original;
    cout << "\nE o substituto:\n";
    cin >> substituto;
    
    string arquivoAlterado = "alteracoes.bak";
    perlWrapper::funcaoTipoB (arquivoInput, original, substituto, arquivoAlterado, substituirExpressaoEmArquivo);
  
    cout <<  "O arquivo alterado esta em 'alteracoes.bak'.\n" << endl;
  }

  if (getOperacao () == 5)
  {
    string arquivoInput;
    string blackList = "blackList.txt";
    string arquivoOutput; 
    cout << "Censurar expressoes inadequadas\n\n" << endl; 
    
    cout << "Insira o nome do arquivo que deseja analisar:" << endl;
    cin >> arquivoInput;

    cout << "Insira o nome do arquivo que deseja armazenar as mudancas:\n";
    cout << "Importante: o nome desse arquivo precisa ser diferente do analisado!" << endl;
    cin >> arquivoOutput;

    /*
        FAZER ANALISE DA ENTRADA

    #cmp retorna 0 se as strings forem iguais
    if (($arquivoOutput cmp $arquivoInput) == 0)
    {
      print "Erro: arquivos com mesmo nome!\n\n";
      exit;
    }
    else
    { 
    */

     perlWrapper::funcaoTipoB (arquivoInput, blackList, NULL, arquivoOutput, censurarExpressoesInadequadas);
  }

  if (getOperacao () == 6)
  {
    string arquivoInput;
    double porcentagem; 
    
    cout << "Insira o nome do arquivo que deseja analisar:" << endl;
    cin >> arquivoInput;
    
    porcentagem =  perlWrapper::funcaoTipoC(arquivoInput, NULL, porcentagemErro);
    porcentagem = 100*porcentagem;
    cout << "Porcentagem de erro:";
    cout << setprecision (2) << porcentagem << endl; 
    
  }
  
  if (getOperacao () == 7)
  {
    string arquivoPalavraInput;
    string arquivoConsultaInput;
    double porcentagem; 
    
    cout << "Insira o nome do arquivo que deseja analisar:" << endl;
    cin >> arquivoPalavraInput;
    
    cout << "Insira o nome do arquivo que deseja analisar:" << endl;
    cin >> arquivoConsultaInput;
    
    porcentagem =  perlWrapper::funcaoTipoC(arquivoPalavraInput, arquivoConsultaInput, porcentagemSemelhanca);
    porcentagem = 100*porcentagem;
    cout << "Porcentagem semelhanca:";
    cout << setprecision (2) << porcentagem << endl; 
    
}
