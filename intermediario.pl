
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
    #$_ = $arrayNaoEncontradas[$indiceNaoEncontradas];
    #print ESCRITA $_;
    print ESCRITA ($arrayNaoEncontradas[$indiceNaoEncontradas]);
    print ESCRITA "\n";
    $indiceNaoEncontradas += 1;
  }

  close(ESCRITA);
  return $arquivoPalavrasNaoEncontradas;
}
  
1;
