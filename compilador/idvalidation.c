#include "idvalidation.h"

int typeTable[100];

int
id_validation(struct Line **program, unsigned int lncnt) {
  int declaredOK = _chckDclrd(program,lncnt);
  _buildTypeTable(program,lncnt);
  
  for(int i=0; i<15; ++i)
    printf("ty %d: %d\n", i, typeTable[i]);
    
    
   
  return 1;
}

/**
  * retorna 1 se OK, 0 se alguma var foi usada sem declarar
  **/
int
_chckDclrd(struct Line **program, unsigned int lncnt) {
  int declared[100];
  int isDeclaring = 1;
  for(int i=0; i<100; ++i)
    declared[i] = 0;
  for(int i=0; i<lncnt; ++i)
  {
    for(int j=0; j<program[i]->numtkns; ++j)
    {
      // printf("ola %d\n", isDeclaring);
      if(isDeclaring == 1) // Se estamos declarando
      {
        // printf(" inicio == %s\n", program[i]->tokens[j]->value);
        if(strcmp("inicio", program[i]->tokens[j]->value) == 0) // checa se chegamos em inicio
        {
          isDeclaring = 0;// se chagamos, nao estamos mais declarando
        }
        else if(strcmp("<id>", program[i]->tokens[j]->to_parse) == 0)// enquanto declaramos, se temos um id
        {
          printf(" !! Its a ID! %s !!\n", program[i]->tokens[j]->value);
          int idIndex = atoi(program[i]->tokens[j]->value);
          declared[idIndex] = 1; // flag como declarada
        }
      }
      else if(strcmp("<id>", program[i]->tokens[j]->to_parse) == 0)// se nao estivemos declarando
      {
        int idIndex = atoi(program[i]->tokens[j]->value);
        int wasDeclared = declared[idIndex];
        printf(" !! Its a ID! %s declared: %d !!\n", program[i]->tokens[j]->value, wasDeclared);
        if(wasDeclared == 0)
         return 0;
      }
      // printf(" >> %s:%s:%s <<\n", program[i]->tokens[j]->value, program[i]->tokens[j]->body, program[i]->tokens[j]->to_parse);    
    }
  }
  return 1;
}

void
_buildTypeTable(struct Line **program, unsigned int lncnt) {
  for(int i=0; i<100; ++i)
    typeTable[i] = 5;
  for(int i=0; i<lncnt; ++i)
  {
    if(strcmp("inicio", program[i]->tokens[0]->value) == 0)
      break;
    if(strcmp("var", program[i]->tokens[0]->value) == 0)
      typeTable[atoi(program[i]->tokens[1]->value)] = (strcmp("inteiro", program[i]->tokens[3]->value) == 0) ? 1 : 0;
    if(strcmp("<id>", program[i]->tokens[0]->to_parse) == 0)
      for(int j=0; j<program[i]->numtkns - 2; j+=2)
        typeTable[atoi(program[i]->tokens[j]->value)] = (strcmp("inteiro", program[i]->tokens[program[i]->numtkns - 1]->value) == 0) ? 1 : 0;
  }
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