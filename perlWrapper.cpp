
#include <EXTERN.h>
#include <perl.h>
#include <iostream>
#include <string.h>
#include <stddef.h>
#include <fstream>
#include "perlWrapper.h"

perlWrapper::perlWrapper (int argc, char **argv, char **env)
{
  PERL_SYS_INIT3(&argc, &argv, &env);

  // criacao de um interpretador
  my_perl = perl_alloc();
  perl_construct (my_perl);
  PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
}

perlWrapper::~perlWrapper()
{
  // limpeza
  perl_destruct (my_perl);
  perl_free (my_perl);

  //termino
  PERL_SYS_TERM ();
}

void perlWrapper::executarInterpretadorPerl (char *arquivo)
{
  my_argv[0] = (char *) "";
  my_argv[1] = (char *) arquivo;

  perl_parse(my_perl, 0, 2, my_argv, (char**)NULL);
  perl_run(my_perl);
}

string perlWrapper::funcaoTipoA (string nomeArquivo, string funcaoPerl, int op)
{
  dSP;                                // inicializa o ponteiro da pilha
  ENTER;                              // e tudo criado depois
  SAVETMPS                            // variavel temp
  PUSHMARK(SP);                       // lembra do ponteiro de pilha
  // USO CORRETO DO c_str () ???
  XPUSHs(sv_2mortal(newSVpv(nomeArquivo.c_str (), nomeArquivo.length () )));  // coloca o primeiro parametro na pilha
  PUTBACK;                            // faz o ponteiro da pilha make local se tornar global
  // USO CORRETO DO c_str () ???
  call_pv (funcaoPerl.c_str (), G_SCALAR);   // chama a funcao
  SPAGAIN;                            // reinicializa o ponteiro da pilha  
 
  string resultado;
 
  if (op == 2)
    resultado = POPi;               // tira o valor de retorno da pilha
  
  if (op == 3)
  {
    string *arrayPalavras = POPi;
    int indice = 0;    

    resultado = "arquivoPalavrasNaoEncontradas.txt";
    ofstream arquivo; 
    arquivo.open (resultado);

    while ( (arrayPalavras[indice]).compare("\0") != 0)
    {
      arquivo << arrayPalavras[indice] << endl;
      indice++;
    }
    
    arquivo.close ();  
  }

  PUTBACK;      
  FREETMPS;                          // libera o valor de retorno
  LEAVE;                              // e o XPUSHed "mortal" args

  return resultado;  
}


void perlWrapper::funcaoTipoB (string arquivoInput, string par2, string par3, string arquivoOutput, string funcaoPerl)
{
  dSP;                                // inicializa o ponteiro da pilha
  ENTER;                              // e tudo criado depois
  SAVETMPS                            // variavel temp
  PUSHMARK(SP);                       // lembra do ponteiro de pilha
  XPUSHs(sv_2mortal(newSVpv(arquivoInput.c_str (), arquivoInput.length () )));  // coloca o primeiro parametro na pilha
  XPUSHs(sv_2mortal(newSVpv(par2.c_str (), par2.length () )));  // coloca o segundo parametro na pilha
// caso op == 5, soh sao passados dois parametros, logo par3 == NULL
  if (par3.compare(NULL) != 0)
    XPUSHs(sv_2mortal(newSVpv(par3.c_str (), par3.length () )));  // coloca o terceiro parametro na pilha
  XPUSHs(sv_2mortal(newSVpv(arquivoOutput.c_str (), arquivoOutput.length () )));
  PUTBACK;                            // faz o ponteiro da pilha make local se tornar global
  call_pv (funcaoPerl, G_SCALAR);   // chama a funcao
  SPAGAIN;                            // reinicializa o ponteiro da pilha  

  // NAO TEM RETORNO, COMO FICA ESSE PEDACO DA FUNCAO????  
  int resultado = POPi;               // tira o valor de retorno da pilha 
  PUTBACK;      
  FREETMPS;                          // libera o valor de retorno
  LEAVE;                              // e o XPUSHed "mortal" args

}


double perlWrapper::funcaoTipoC (string arquivoInput, string arquivoOutput, string funcaoPerl)
{
  dSP;                                // inicializa o ponteiro da pilha
  ENTER;                              // e tudo criado depois
  SAVETMPS                            // variavel temp
  PUSHMARK(SP);                       // lembra do ponteiro de pilha
  XPUSHs(sv_2mortal(newSVpv (arquivoInput.c_str (), arquivoInput.length () )));  // coloca o primeiro parametro na pilha
  if (arquivoOutput.compare(NULL) != 0)
    XPUSHs(sv_2mortal(newSVpv (arquivoOutput.c_str (), arquivoOutput.length () ))); 
  PUTBACK;                            // faz o ponteiro da pilha make local se tornar global
  // USO CORRETO DO c_str () ???
  call_pv (funcaoPerl.c_str (), G_SCALAR);   // chama a funcao
  SPAGAIN;                            // reinicializa o ponteiro da pilha  
  
  double resultado = POPi;               // tira o valor de retorno da pilha
  
  PUTBACK;      
  FREETMPS;                          // libera o valor de retorno
  LEAVE;                              // e o XPUSHed "mortal" args

  return resultado;  
}

