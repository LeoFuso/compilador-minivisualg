var table = {
	A: {
		'<algoritmo>': 1
	},
	LISTADECLAR: {
		'<var>': 2,
		'<id>': 3,
		'<del|,>': 3,
		'<del|:>': 3,
		'<inicio>': 4
	},
	UNIDECLAR: {
		'<var>': 5
	},
	MULTIDECLAR: {
		'<id>': 6,
		'<del|,>': 6,
		'/e/': 6
	},
	TIPO: {
		'<inteiro>': 7,
		'<logico>': 8
	},
	IDLIST: {
		'<id>': 9,
		'<del|,>': 10,
		'<del|:>': 11,
		'<del|)>': 11
	},
	CODIGO: {
		'<id>': 12,
		'<leia>': 12,
		'<escreva>': 12,
		'<se>': 12,
		'<para>': 12,
		'<enquanto>': 12,
		'<fimalgoritmo>': 13,
		'<senao>': 13,
		'<fimpara>': 13,
		'<fimenquanto>': 13
	},
	COMANDO: {
		'<id>': 14,
		'<leia>': 15,
		'<escreva>': 16,
		'<se>': 17,
		'<para>': 18,
		'<enquanto>': 19
	},
	PASSO: {
		'<passo>': 20,
		'<faca>': 21
	},
	ATRIBUICAO: {
		'<id>': 23
	},
	STROUT: {
		'<str>': 24,
		'<id>': 25,
		'<del|,>': 27,
		'<del|)>': 28
	},
	EXPRESSAOLOGICA: {
		'<id>': 29,
		'<num>': 29,
		'<str>': 29,
		'<verdadeiro>': 29,
		'<falso>': 29,
		'<op|+>': 29,
		'<op|->': 29,
		'<op|*>': 29,
		'<op|/>': 29,
		'<op|mod>': 29,
		'<op|exp>': 29,
		'<lop|>>': 29,
		'<lop|>=>': 29,
		'<lop|<>': 29,
		'<lop|<=>': 29,
		'<lop|=>': 29,
		'<lop|<>>': 29,
		'<lop|e>': 29,
		'<lop|ou>': 29,
		'/e/': 29
	},
	DATA: {
		'<num>': 30,
		'<str>': 31,
		'<verdadeiro>': 32,
		'<falso>': 33
	},
	EXPRESSAO: {
		'<id>': 38,
		'<num>': 35,
		'<str>': 35,
		'<verdadeiro>': 35,
		'<falso>': 35,
		'<op|+>': 37,
		'<op|->': 37,
		'<op|*>': 37,
		'<op|/>': 37,
		'<op|mod>': 37,
		'<op|exp>': 37,
		'<lop|>>': 38,
		'<lop|>=>': 38,
		'<lop|<>': 38,
		'<lop|<=>': 38,
		'<lop|=>': 38,
		'<lop|<>>': 38,
		'<lop|e>': 38,
		'<lop|ou>': 38,
		'<leia>': 38,
		'<escreva>': 38,
		'<se>': 38,
		'<para>': 38,
		'<enquanto>': 38,
		'<fimalgoritmo>': 38,
		'<senao>': 38,
		'<fimpara>': 38,
		'<fimenquanto>': 38
	},
	LOGICOP: {
		'<lop|>>': 39,
		'<lop|>=>': 40,
		'<lop|<>': 41,
		'<lop|<=>': 42,
		'<lop|=>': 43,
		'<lop|<>>': 44,
		'<lop|e>': 45,
		'<lop|ou>': 46
	},
	OP: {
		'<op|+>': 47,
		'<op|->': 48,
		'<op|*>': 49,
		'<op|/>': 50,
		'<op|mod>': 51,
		'<op|exp>': 52,
		'<lop|>>': 53,
		'<lop|>=>': 53,
		'<lop|<>': 53,
		'<lop|<=>': 53,
		'<lop|=>': 53,
		'<lop|<>>': 53,
		'<lop|e>': 53,
		'<lop|ou>': 53
	}
}