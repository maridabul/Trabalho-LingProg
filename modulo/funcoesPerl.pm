package funcoesPerl;
use 5.022001;
use warnings;
use strict;
use Exporter;

our @ISA = qw(Exporter);

our %EXPORT_TAGS = ( 'all' => [ qw(
	
) ] );

our @EXPORT_OK = ( @{ $EXPORT_TAGS{'all'} } );


our @EXPORT = qw(
  importarArquivoParaArray
  importarDicionarioParaArray 
  verificarPalavraNoDicionario
  verificarArrayPalavrasNoDicionario
  verificarPalavraEmArquivo
  verificarArrayPalavrasEmArquivo
  substituirExpressaoEmArquivo
  censurarExpressoesInadequadas
  verificarErrosPortuguesString    
  verificarErrosPortuguesArquivo
  porcentagemErro
  porcentagemSemelhanca
);

our $VERSION = '0.01';

# Funcao armazena cada palavra do arquivo desejado nos indices de um vetor. Esse vetor de palavras eh retornado quando a funcao for chamada. Espacos sao desconsiderados nessa funcao.
#
# @arrayPalavras = importarArquivoParaArray ("nomeArquivo");
#
sub importarArquivoParaArray {

  my $nomeArquivo = $_[0];
  my @arrayPalavras;
  my $indiceArray = 0;
  my $palavra;

  #open (my $arquivo, "<", $nomeArquivo) or die "Erro ao abrir arquivo: $!\n";
 # print ($nomeArquivo);
  open (my $arquivo, "<", $nomeArquivo) or die "Erro ao abrir arquivo: $!\n";
  seek ($arquivo, 0, 0);

  while (<$arquivo>)
  {
    for $palavra (split)
    {
      $palavra =~ s/[?!;,]//gi;
      @arrayPalavras [$indiceArray] = $palavra;
      $indiceArray++;
    }
  }

  #print (@arrayPalavras);
  close $arquivo or die "Erro ao fechar arquivo: $!\n";
  return @arrayPalavras;
}

# Mesma logica da funcao importarArquivoParaArray. Funcao armazena todas as palavras do dicionarioo nos indices de um vetor. Esse vetor de palavras eh retornado quando a funcao for chamada.
#
# @arrayDicionario = importarDicionarioParaArray ();
#
sub importarDicionarioParaArray {

  my @arrayPalavras;
  my $indiceArray = 0;
  my $palavra;

  open (my $dicionario, "<", "dicionario.dic") or die "Erro ao abrir arquivo: $!\n";
  seek ($dicionario, 0, 0);

  while (<$dicionario>)
  {
    for $palavra (split)
    {
      @arrayPalavras [$indiceArray] = $palavra;
      $indiceArray++;
    }
  }


  close $dicionario or die "Erro ao fechar arquivo: $!\n";
  return @arrayPalavras;
}

# Funcao retorna 0 caso a palavra nao seja encontrada no dicionario. Caso seja, retorna a propria palavra.
#
# $string = verificarPalavraNoDicionario ($palavra)
sub verificarPalavraNoDicionario {

  my $palavra = $_[0];
  my @arrayDicionario = importarDicionarioParaArray ();
  my $indiceArrayDicionario = 0;
  my $auxiliar;
  my $palavraEncontrada = "nao_encontrada"; 

  $indiceArrayDicionario = 0;
  foreach (@arrayDicionario)
  {
    $auxiliar = ($arrayDicionario[$indiceArrayDicionario]);
    if ($palavra =~ qr/^$auxiliar$/i)
    {
      $palavraEncontrada = $auxiliar;
    }
      $indiceArrayDicionario += 1;
  }

  return $palavraEncontrada;
}


# Funcao verifica para cada palavra armazenada no vetor se ela existe no dicionario. O vetor contendo as palavras nao encontradas sera retornado quando a funcao for chamada.
#
# @array = verificarArrayPalavrasNoDicionario (@arrayPalavras);
#
sub verificarArrayPalavrasNoDicionario {

  my @arrayPalavras = @_;
  my @arrayPalavraExiste;
  my @arrayDicionario = importarDicionarioParaArray ();
  my $indiceArrayPalavras = 0;
  my $indiceArrayDicionario = 0;
  my $auxiliar;
  my @arrayPalavrasNaoEncontradas;
  my $indiceArrayPalavrasNaoEncontradas = 0;
  my $palavraEncontrada;

  foreach (@arrayPalavras)
  {
    $indiceArrayDicionario = 0;
    $palavraEncontrada = 0; # FALSE
    foreach (@arrayDicionario)
    {
      $auxiliar = ($arrayDicionario [$indiceArrayDicionario]);
      if ($arrayPalavras [$indiceArrayPalavras] =~ qr/^$auxiliar$/i)
      {
        $palavraEncontrada = 1;
      }
      $indiceArrayDicionario += 1;
    }#for dicionario
    if ($palavraEncontrada == 0) # NAO ENCONTROU
    {
      $arrayPalavrasNaoEncontradas[$indiceArrayPalavrasNaoEncontradas] = $arrayPalavras[$indiceArrayPalavras];
      $indiceArrayPalavrasNaoEncontradas += 1;
    }
    $indiceArrayPalavras += 1;
  }

  return @arrayPalavrasNaoEncontradas;
}


# Funcao retorna 0 caso a palavra nao seja encontrada no arquivo. Caso seja, retorna 1. Mesma logica da funcao verificarPalavraNoDicionario.
#
# $booleano = verificarPalavraEmArquivo ($palavra, "nomeArquivo")
sub verificarPalavraEmArquivo {

  my $palavra = $_[0];
  my $nomeArquivo = $_[1];
  my @arrayArquivo = importarArquivoParaArray ($nomeArquivo);
  my $indiceArrayArquivo = 0;
  my $auxiliar;
  my $palavraEncontrada = 0; 

  $indiceArrayArquivo = 0;
  print $_[0];
  foreach (@arrayArquivo)
  {
    $auxiliar = ($arrayArquivo[$indiceArrayArquivo]);
    if ($palavra =~ qr/^$auxiliar$/i)
    {
      $palavraEncontrada = 1;
    }
      $indiceArrayArquivo += 1;
  }

  return $palavraEncontrada;
}


# Funcao verifica para cada palavra armazenada no vetor se ela existe no arquivo. O vetor contendo as palavras nao encontradas sera retornado quando a funcao for chamada.
#
# @array = verificarPalavraNoDicionario ($arquivoPalavras, $arquivoConsulta);
#
sub verificarArrayPalavrasEmArquivo {

  my $arquivoConsulta = $_[1];
  my $arquivoPalavras = $_[0];
  my @arrayPalavraExiste;
  my @arrayConsulta = importarArquivoParaArray ($arquivoConsulta);
  my @arrayPalavras = importarArquivoParaArray ($arquivoPalavras);
  my $indiceArrayPalavras = 0;
  my $indiceArrayConsulta = 0;
  my $auxiliar;
  my @arrayPalavrasNaoEncontradas;
  my $indiceArrayPalavrasNaoEncontradas = 0;
  my $palavraEncontrada;

  foreach (@arrayPalavras)
  {
    $indiceArrayConsulta = 0;
    $palavraEncontrada = 0;
    foreach (@arrayConsulta)
    {
      $auxiliar = ($arrayConsulta[$indiceArrayConsulta]);
      if ($arrayPalavras [$indiceArrayPalavras] =~ qr/^$auxiliar$/i)
      {
        $palavraEncontrada = 1;
      }
      $indiceArrayConsulta += 1;
    }#for dicionario
    if ($palavraEncontrada == 0)
    {
      $arrayPalavrasNaoEncontradas[$indiceArrayPalavrasNaoEncontradas] = $arrayPalavras[$indiceArrayPalavras];
      $indiceArrayPalavrasNaoEncontradas += 1;
      $indiceArrayPalavras = 0;
    }
    $indiceArrayPalavras += 1;
  }

  return @arrayPalavrasNaoEncontradas;
}

# Funcao substitui cada ocorrencia de determinada expressao por outra no texto de um arquivo e armazena a alteracao em um novo arquivo.
#
# $arquivoModificado = substituirExpressaoEmArquivo ($arquivoOriginal, $original, $substituto, $arquivoAlterado);
#
sub substituirExpressaoEmArquivo{

  my $arquivoOriginal = $_[0];

  my $original = $_[1];
  my $substituto = $_[2];

  my $arquivoAlterado = $_[3];

  open(LEITURA, "<", $arquivoOriginal) or die $!;
  open(ESCRITA, ">", $arquivoAlterado) or die $!;
  
  while(<LEITURA>)
  {
      $_ =~ s/$original/$substituto/g;
      print ESCRITA $_;
  }
  close(LEITURA);
  close(ESCRITA);

  return $arquivoAlterado;
}

# Funcao substitui cada ocorrencia de palavras da blackList encontradas no arquivo original por "*****". Retorna o arquivo modificado.
#
# $alterado = censurador ($original, $blackList)
sub censurarExpressoesInadequadas{

  my $arquivoOriginal = $_[0];
  my $blackList = $_[1];

  my @arrayBlackList = importarArquivoParaArray ($blackList);

  my $indice = 0;
  my $censurado = "*****";
  my $auxiliar = $arrayBlackList[$indice];
  #feito fora do for pois a primeira vez eh a unica que tem $arquivoOriginal como argumento da funcao
  my $arquivoAlterado = $_[2];
  $arquivoAlterado = substituirExpressaoEmArquivo($arquivoOriginal, $auxiliar, $censurado, $arquivoAlterado);


  my $size = scalar @arrayBlackList;
  my $arquivoAuxiliar = "auxiliar.txt";
  for($indice = 1; $indice < $size; $indice++)
  {
    $auxiliar = ($arrayBlackList[$indice]);
    if (($indice%2) == 1)
    {
      $arquivoAuxiliar = substituirExpressaoEmArquivo($arquivoAlterado, $auxiliar, $censurado, $arquivoAuxiliar);
    }
    else
    {
      $arquivoAlterado = substituirExpressaoEmArquivo($arquivoAuxiliar, $auxiliar, $censurado, $arquivoAlterado);
    }
  }

  if (($indice%2) == 0)
  {
    $arquivoAlterado = $arquivoAuxiliar;
  }
  return $arquivoAlterado;
}

# Funcao utiliza regex para substituir os erros mais comuns de portugues e verificar se a palavra existe no dicionario. A funcao retorna a palavra, caso encontrada, ou 0.
#
# $escalar = verificarErrosPortuguesString($string);
#
sub verificarErrosPortuguesString{
  my $palavraNaoEncontrada = $_[0];
 # print $palavraNaoEncontrada;

  #erros mais comuns de portugues
  $palavraNaoEncontrada =~ s/[szcç]/[szçcs{2}]/gi;
  $palavraNaoEncontrada =~ s/[ie]/[ei]/gi;
  $palavraNaoEncontrada =~ s/[mn]/[mn]/gi;
  $palavraNaoEncontrada =~ s/[rr{2}]/[rr{2}]/gi;
  $palavraNaoEncontrada =~ s/ch/x/gi;
  $palavraNaoEncontrada =~ s/ano/ando/gi;
  $palavraNaoEncontrada =~ s/eno/endo/gi;
  $palavraNaoEncontrada =~ s/ino/indo/gi;
  $palavraNaoEncontrada =~ s/[gj]/[gj]/gi;

  my $encontrada = verificarPalavraNoDicionario ($palavraNaoEncontrada); 

  return $encontrada;
}

# Essa funcao recebe o arquivo. As palavras nao encontradas no dicionario serao armazenadas em um vetor. Esse vetor passara por uma funcao que corrige os possiveis erros de portugues.
#
# @arrayPalavrasEncontradas = verificarErrosPortuguesArquivo ("nomeArquivo")
sub verificarErrosPortuguesArquivo  
{
  my $arquivo = $_[0];
  my $auxiliar = "NADA";
  my @arrayPalavras = importarArquivoParaArray ($arquivo);
  my @arrayNaoEncontradas = verificarArrayPalavrasNoDicionario (@arrayPalavras);
  my @arrayRetorno;
  my $indice = 0;
  my $indiceRetorno = 0;
  my $BUFFER;
  my $auxiliar2;

  foreach (@arrayNaoEncontradas)
  {
    $auxiliar2 = $arrayNaoEncontradas[$indice];
    $auxiliar = verificarErrosPortuguesString ($auxiliar2);
   
    if ($auxiliar eq "nao_encontrada")
    {
      $arrayRetorno[$indice] = $auxiliar2; #$arrayNaoEncontradas[$indice];
    }
    else
    {
      $arrayRetorno[$indice] = $auxiliar; #palavra corrigida foi encontrada
    }
    $indice += 1;
    $indiceRetorno += 1;
  } 

  return @arrayRetorno;
}


# Funcao retorna a porcentagem de palavras nao encontradas no dicionario.
#
# $porcentagem = porcentagemErro ($arquivoOriginal)
#
sub porcentagemErro {
  
  my $arquivoPalavras = $_[0];
 
  my @arrayPalavras = importarArquivoParaArray($arquivoPalavras);
  my $tamanhoPalavrasTotais = scalar @arrayPalavras; 
  
  # funcao verificarArrayPalavrasEmArquivo retorna array de palavras nao encontradas. $tamanhoPalavrasNaoEncontradas = comprimento do array retornado pela funcao.
  my $tamanhoPalavrasNaoEncontradas = scalar verificarArrayPalavrasNoDicionario (@arrayPalavras);

  return ($tamanhoPalavrasNaoEncontradas/$tamanhoPalavrasTotais);
}

# Funcao retorna a porcentagem de palavras semelhantes entre dois arquivos.
#
# $porcentagem = porcentagemSemelhanca ($arquivoPalavras, $arquivoConsulta) 
#
sub porcentagemSemelhanca {
  
  my $arquivoConsulta = $_[1];
  my $arquivoPalavras = $_[0];
  
  my @arrayConsulta = importarArquivoParaArray ($arquivoConsulta);
  my $tamanhoConsulta = scalar @arrayConsulta;

  # funcao verificarArrayPalavrasEmArquivo retorna array de palavras nao encontradas. $tamanhoPalavrasNaoEncontradas = comprimento do array retornado pela funcao.
  my $tamanhoPalavrasNaoEncontradas = scalar verificarArrayPalavrasEmArquivo ($arquivoPalavras, $arquivoConsulta);

  return (1 - $tamanhoPalavrasNaoEncontradas/$tamanhoConsulta);
}

#sub criarArquivoPalavrasNaoEncontradas {
#  
#  my $arquivoInput = $_[0];
#  chomp $arquivoInput;
#  my $indiceNaoEncontradas = 0;
#  my @arrayInput = importarArquivoParaArray ($arquivoInput);
#  my @arrayNaoEncontradas = verificarArrayPalavrasNoDicionario (@arrayInput); 
#  
#  my $arquivoPalavrasNaoEncontradas = "arquivoPalavrasNaoEncontradas.txt";
#
#  open(ESCRITA, ">", $arquivoPalavrasNaoEncontradas) or die $!;
#  
#  # escrever no arquivo as palavras nao encontradas no dicionario
#  foreach (@arrayNaoEncontradas)
#  {
#    #$_ = $arrayNaoEncontradas[$indiceNaoEncontradas];
#    #print ESCRITA $_;
#    print ESCRITA ($arrayNaoEncontradas[$indiceNaoEncontradas]);
#    print ESCRITA "\n";
#    $indiceNaoEncontradas += 1;
#  }
#
#  close(ESCRITA);
#  return $arquivoPalavrasNaoEncontradas;
#}
