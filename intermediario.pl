
use warnings;
use strict;

use File::Basename;
use lib dirname (__FILE__) . "/modulo";

use funcoesPerl;

sub criarArquivoPalavrasNaoEncontradas {
  
  my $arquivoInput = $_[0];
  chomp $arquivoInput;
  my $indiceNaoEncontradas = 0;
  my @arrayInput = importarArquivoParaArray ($arquivoInput);
  my @arrayNaoEncontradas = verificarArrayPalavrasNoDicionario (@arrayInput); 
  
  my $arquivoPalavrasNaoEncontradas = "arquivoPalavrasNaoEncontradas.txt";

  open(ESCRITA, ">", $arquivoPalavrasNaoEncontradas) or die $!;
  
  # escrever no arquivo as palavras nao encontradas no dicionario
  foreach (@arrayNaoEncontradas)
  {
    my $indice; 
    #caso seja a primeira ocorrencia da palavra
    my $repetida = 0; 
    for ($indice = 0; $indice < $indiceNaoEncontradas; $indice++)
    {
      if ((@arrayNaoEncontradas [$indice] cmp @arrayNaoEncontradas [$indiceNaoEncontradas]) == 0)
      {
        #caso exista mais de uma ocorrencia da palavra
        $repetida = 1;
      }
    }

    if ($repetida == 0)
    {
      print ESCRITA ($arrayNaoEncontradas[$indiceNaoEncontradas]);
      print ESCRITA "\n";
    }
      $indiceNaoEncontradas += 1;
  }

  close(ESCRITA);
  return $arquivoPalavrasNaoEncontradas;
}
  
1;
