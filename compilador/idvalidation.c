#include "idvalidation.h"

int
id_validation(struct Line **program, unsigned int lncnt) {
  int declaration_state = 0;
  for(int i=0; i<lncnt; ++i)
    for(int j=0; j<program[i]->numtkns; ++j)
    {
      if(_tknIddclrEnd(program[i]->tokens[j]) == 1)
      {
        int declaration_state = 1;
      }
      printf(" >> %s <<\n", program[i]->tokens[j]->body);
    }
  return 1;
}

/*
SE declarando:
  para cada linha de declaracao:
    SE linha declarativa : popula array de tamanho 100 da seguinte maneira:
      array[idNum] = 0 se id numerica, 1 se id logica.
    SE linha <inicio>: nao estamos mais declarando
SE nao declarando:
  Percorre tudo checando se IDs que aparecem sao index iniciados no array (declarados)
  
  Para cada 3 tokens:
    se forem:
      IDnum <- IDbool
      IDbool <- IDnum
      IDbool <op>
      <op> IDbool
      IDnum <op> IDbool
      IDnum <lop> IDbool
      IDbool <op> IDnum
      IDbool <lop> IDnum
      IDnum <lop>
      <lop> IDnum
      <para> IDbool <de>
    solta erro
*/