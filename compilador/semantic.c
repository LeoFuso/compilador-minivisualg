#include "semantic.h"

/**
  * typeTable[id] = idType
  * id: numero do id
  * idType: 1 = boolean; 0 = numeric; -1 = nao existe/inicializado
  **/
int typeTable[100];

int
_is_var_declared(struct Source *);

void
_build_typeTable(struct Source *);

int
semantic_analysis(struct Source *source)
{
	if (!_is_var_declared(source))
		return 0;

	_build_typeTable(source);

	return 1;
}

int
_is_var_declared(struct Source *source)
{
	struct Line **program = source->program;
	unsigned int var_num = source->var_num;
	int lncnt = source->line_num;

	int *declared = NULL;
	declared = (int *) calloc(var_num, sizeof(int));

	int is_declaring = 1;

	for (int i = 0; i < lncnt; ++i)
	{
		for (int j = 0; j < program[i]->numtkns; ++j)
		{
			if (is_declaring)
			{
				if (strcmp("inicio", program[i]->tokens[j]->value) == 0) // checa se chegamos em inicio
				{
					is_declaring = 0;
				}
				else if (strcmp("<id>", program[i]->tokens[j]->to_parse) == 0)// enquanto declaramos, se temos um id
				{
					int idIndex = (int) strtol(program[i]->tokens[j]->value, (char **) NULL, 10);
					declared[idIndex] = 1; // flag como declarada
				}
			}
				/* if we're not declaring */
			else if (strcmp("<id>", program[i]->tokens[j]->to_parse) == 0)
			{
				int idIndex = (int) strtol(program[i]->tokens[j]->value, (char **) NULL, 10);
				int wasDeclared = declared[idIndex];
				if (wasDeclared == 0)
					return 0;
			}
		}
	}
	return 1;
}

/**
  * Monta typeTable
  **/
void
_build_typeTable(struct Source *source)
{
	struct Line **program = source->program;
	int lncnt = source->line_num;

	for (int i = 0; i < 100; ++i)
		typeTable[i] = -1;
	for (int i = 0; i < lncnt; ++i)
	{
		if (program[i]->numtkns > 0)
		{
			if (strcmp("inicio", program[i]->tokens[0]->value) == 0)
				break;

			if (strcmp("var", program[i]->tokens[0]->value) == 0)
				typeTable[atoi(program[i]->tokens[1]->value)] =
					(strcmp("inteiro", program[i]->tokens[3]->value) == 0) ? 1 : 0;

			if (strcmp("<id>", program[i]->tokens[0]->to_parse) == 0)
				for (int j = 0; j < program[i]->numtkns - 2; j += 2)
					typeTable[atoi(program[i]->tokens[j]->value)] =
						(strcmp("inteiro", program[i]->tokens[program[i]->numtkns - 1]->value) == 0) ? 1 : 0;
		}
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