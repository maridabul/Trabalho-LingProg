/* Adaptado de Aula 2 - página 207 dos slides de LingProg 
 * fonte: https://www.gta.ufrj.br/~miguel/docs/lingprog/aula2.pdf
 */

#ifndef PERL_WRAPPER
#define PERL_WRAPPER

#include <EXTERN.h>
#include <stddef.h>
#include <perl.h>
#include <iostream>
#include <string.h>

using namespace std;

class perlWrapper {
  public:
    perlWrapper (int argc, char **argv, char **env);
    ~perlWrapper ();

    void executarInterpretadorPerl (char *);
    
    //funcoes
    string funcaoTipoA (string, string, int);
    void funcaoTipoB (string, string, string, string, string, int);
    double funcaoTipoC (string, string, string, int);

  private:  
    PerlInterpreter *my_perl;
    char *my_argv [2];


};

#endif
