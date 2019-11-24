
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

string perlWrapper::funcaoTipoA (string parametro1, string funcaoPerl, int op)
{
  dSP;
  ENTER;
  SAVETMPS;
  PUSHMARK (SP);

  XPUSHs (sv_2mortal (newSVpv (parametro1.c_str (), parametro1.length ()) ));

  PUTBACK;

  call_pv (funcaoPerl.c_str (), G_SCALAR);
  SPAGAIN;

 
  string resultado;

  if ((op == 2) || (op == 3)) 
    resultado = POPp;               // tira o valor de retorno da pilha
  
  PUTBACK;
  FREETMPS;
  LEAVE;

  return resultado;
}

void perlWrapper::funcaoTipoB (string arquivoInput, string parametro2, string parametro3, string arquivoOutput, string funcaoPerl, int op)
{
  dSP;                                
  ENTER;                              
  SAVETMPS;                            
  PUSHMARK(SP);                       
  XPUSHs(sv_2mortal(newSVpv(arquivoInput.c_str (), arquivoInput.length () )));  
  XPUSHs(sv_2mortal(newSVpv(parametro2.c_str (), parametro2.length () )));  
  if (op == 4)
    XPUSHs(sv_2mortal(newSVpv(parametro3.c_str (), parametro3.length () )));  
  XPUSHs(sv_2mortal(newSVpv(arquivoOutput.c_str (), arquivoOutput.length () )));
  PUTBACK;                            
  call_pv (funcaoPerl.c_str (), G_SCALAR);   
  SPAGAIN;                            

  PUTBACK;      
  FREETMPS;                          
  LEAVE;                              

}

double perlWrapper::funcaoTipoC (string arquivoInput, string arquivoOutput, string funcaoPerl, int op)
{
  dSP;                                
  ENTER;                              
  SAVETMPS;                           
  PUSHMARK(SP);                       
  XPUSHs(sv_2mortal(newSVpv (arquivoInput.c_str (), arquivoInput.length () )));  
  if (op == 7)  
    XPUSHs(sv_2mortal(newSVpv (arquivoOutput.c_str (), arquivoOutput.length () ))); 
    

  PUTBACK;                            

  call_pv (funcaoPerl.c_str (), G_SCALAR);   
  SPAGAIN;                        
  
  double resultado = POPn;               
  
  PUTBACK;      
  FREETMPS;                          
  LEAVE;                              

  return resultado;  
}
