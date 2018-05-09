var followSets = {
	'A': ['$'],
	'LISTADECLAR': ['<inicio>'],
	'UNIDECLAR': ['<var>', '<id>', '<del|,>', '<del|:>', '<inicio>'],
	'MULTIDECLAR': ['<var>', '<id>', '<del|,>', '<del|:>', '<inicio>'],
	'TIPO': ['<var>', '<id>', '<del|,>', '<del|:>', '<inicio>'],
	'IDLIST': ['<del|:>', '<del|)>'],
	'CODIGO': ['<fimalgoritmo>', '<senao>', '<fimpara>', '<fimenquanto>'],
	'COMANDO': ['<id>', '<leia>', '<escreva>', '<se>', '<para>', '<enquanto>', '<fimalgoritmo>', '<senao>', '<fimpara>', '<fimenquanto>'],
	'PASSO': ['<faca>'],
	'ATRIBUICAO': ['<id>', '<leia>', '<escreva>', '<se>', '<para>', '<enquanto>', '<fimalgoritmo>', '<senao>', '<fimpara>', '<fimenquanto>'],
	'STROUT': ['<del|)>'],
	'EXPRESSAOLOGICA': ['<entao>', '<faca>'],
	'DATA': ['<id>', '<leia>', '<escreva>', '<se>', '<para>', '<enquanto>', '<fimalgoritmo>', '<senao>', '<fimpara>', '<fimenquanto>', '<num>', '<str>', '<verdadeiro>', '<falso>', '<op|+>', '<op|->', '<op|*>', '<op|/>', '<op|mod>', '<op|exp>', '<lop|>>', '<lop|>=>', '<lop|<>', '<lop|<=>', '<lop|=>', '<lop|<>>', '<lop|e>', '<lop|ou>'],
	'EXPRESSAO': ['<id>', '<leia>', '<escreva>', '<se>', '<para>', '<enquanto>', '<fimalgoritmo>', '<senao>', '<fimpara>', '<fimenquanto>', '<lop|>>', '<lop|>=>', '<lop|<>', '<lop|<=>', '<lop|=>', '<lop|<>>', '<lop|e>', '<lop|ou>'],
	'LOGICOP': ['<id>', '<num>', '<str>', '<verdadeiro>', '<falso>', '<op|+>', '<op|->', '<op|*>', '<op|/>', '<op|mod>', '<op|exp>', '<lop|>>', '<lop|>=>', '<lop|<>', '<lop|<=>', '<lop|=>', '<lop|<>>', '<lop|e>', '<lop|ou>', '<entao>', '<faca>'],
	'OP': ['<id>', '<num>', '<str>', '<verdadeiro>', '<falso>']
}