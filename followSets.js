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
	'EXPRESSAOLOGICA': ['<entao>', '<faca>', '<id>', '<leia>', '<escreva>', '<se>', '<para>', '<enquanto>', '<fimalgoritmo>', '<senao>', '<fimpara>', '<fimenquanto>', '<str>', '<num>', '<verdadeiro>', '<falso>', '<del|,>', '<del|)>'],
	'DATA': ['<id>', '<leia>', '<escreva>', '<se>', '<para>', '<enquanto>', '<fimalgoritmo>', '<senao>', '<fimpara>', '<fimenquanto>', '<str>', '<num>', '<verdadeiro>', '<falso>', '<del|,>', '<del|)>', '<entao>', '<faca>'],
	'EXPRESSAO': ['<id>', '<leia>', '<escreva>', '<se>', '<para>', '<enquanto>', '<fimalgoritmo>', '<senao>', '<fimpara>', '<fimenquanto>', '<str>', '<num>', '<verdadeiro>', '<falso>', '<del|,>', '<del|)>', '<entao>', '<faca>'],
	'LOGICOP': ['<num>', '<str>', '<verdadeiro>', '<falso>', '<id>'],
	'OP': ['<num>', '<str>', '<verdadeiro>', '<falso>', '<id>']
}