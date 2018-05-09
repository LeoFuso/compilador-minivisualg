var firstSets = {
	'A': ['<algoritmo>'],
	'<algoritmo>': ['<algoritmo>'],
	'LISTADECLAR': ['<var>', '<id>', '<del|,>', '<del|:>', '/e/'],
	'UNIDECLAR': ['<var>'],
	'<var>': ['<var>'],
	'MULTIDECLAR': ['<id>', '<del|,>', '<del|:>'],
	'IDLIST': ['<id>', '<del|,>', '/e/'],
	'<id>': ['<id>'],
	'<del|,>': ['<del|,>'],
	'<del|:>': ['<del|:>'],
	'TIPO': ['<inteiro>', '<logico>'],
	'<inteiro>': ['<inteiro>'],
	'<logico>': ['<logico>'],
	'CODIGO': ['<id>', '<leia>', '<escreva>', '<se>', '<para>', '<enquanto>', '/e/'],
	'COMANDO': ['<id>', '<leia>', '<escreva>', '<se>', '<para>', '<enquanto>'],
	'<leia>': ['<leia>'],
	'<escreva>': ['<escreva>'],
	'<se>': ['<se>'],
	'<para>': ['<para>'],
	'<enquanto>': ['<enquanto>'],
	'PASSO': ['<passo>', '/e/'],
	'<passo>': ['<passo>'],
	'STROUT': ['<num>', '<str>', '<verdadeiro>', '<falso>', '<id>', '<del|,>', '/e/'],
	'DATA': ['<num>', '<str>', '<verdadeiro>', '<falso>', '<id>'],
	'<num>': ['<num>'],
	'<str>': ['<str>'],
	'<verdadeiro>': ['<verdadeiro>'],
	'<falso>': ['<falso>'],
	'EXPRESSAO': ['<id>'],
	'EXPRESSAOLOGICA': ['<id>'],
	'LOGICOP': ['<lop|>>', '<lop|>=>', '<lop|<>', '<lop|<=>', '<lop|=>', '<lop|<>>', '<lop|e>', '<lop|ou>'],
	'<lop|>>': ['<lop|>>'],
	'<lop|>=>': ['<lop|>=>'],
	'<lop|<>': ['<lop|<>'],
	'<lop|<=>': ['<lop|<=>'],
	'<lop|=>': ['<lop|=>'],
	'<lop|<>>': ['<lop|<>>'],
	'<lop|e>': ['<lop|e>'],
	'<lop|ou>': ['<lop|ou>'],
	'OP': ['<op|+>', '<op|->', '<op|*>', '<op|/>', '<op|mod>', '<op|exp>', '<lop|>>', '<lop|>=>', '<lop|<>', '<lop|<=>', '<lop|=>', '<lop|<>>', '<lop|e>', '<lop|ou>'],
	'<op|+>': ['<op|+>'],
	'<op|->': ['<op|->'],
	'<op|*>': ['<op|*>'],
	'<op|/>': ['<op|/>'],
	'<op|mod>': ['<op|mod>'],
	'<op|exp>': ['<op|exp>']
}