#include "idvalidation.h"

int declared[10];

int
id_validation(struct Line **program, unsigned int lncnt) {
  int declaredOK = _chckDclrd(program,lncnt);
  return 1;
}

int
_chckDclrd(struct Line **program, unsigned int lncnt) {
  int declaration_state = 0;
  for(int i=0; i<lncnt; ++i)
    // printf(" >>%s:%s:%s<<\n", program[i]->tokens[j]->value, program[i]->tokens[j]->body, program[i]->tokens[j]->to_parse);
    // Estamos listando vars declaradas
    if(declaration_state == 0)
    {
      // Se chegamos em inicio, nao estamos mais declarando. Mudar estado para 1
      if(strcmp("<inicio>", program[i]->tokens[0]->body) == 1)
      {
        declaration_state = 1;
      }
      else
      {
        // Se conseguimos ID como primeiro token, declaracao unica,
        // recupera tipo e id
        if(strcmp("<var>", program[i]->tokens[0]->body))
        {
          // int id = (int) program[i]->tokens[1]->value - "0"; // VOODOOoooo..... que nao funciona eu acho.
          int id = (int) strtol(program[i]->tokens[1]->value, (char **) NULL, 10);
          int type = strcmp("<inteiro>",program[i]->tokens[3]->body); // 1 se for int, 0 se for bool
          declared[id] = type;
        }
        // multivar declare, mais dificil...
        else
        {
          for(int j=0; j<program[i]->numtkns;++j)
          {
            if(strcmp("<id>", program[i]->tokens[3]->to_parse) == 1)
            {
              int id = (int) strtol(program[i]->tokens[j]->value, (char **) NULL, 10);
              int type = strcmp("<inteiro>",program[i]->tokens[program[i]->numtkns-1]->body);
              declared[id] = type;
            }
          }
        }
      }
    }
    
    // Em teoria, se chegassemos aqui sem segfault, teriamos um array com as vars e seus tipos...
    
    for(int i=0; i<10; ++i)
    {
      printf("%d \n", declared[i]);
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