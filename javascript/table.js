// Special "empty" symbol.
var EPSILON = '/e/'

/**
 * Given a grammar builds a LL(1) parsing table based on the
 * First and Follow sets of this grammar.
 */
function buildParsingTable (grammar) {
  var parsingTable = {}

  for (var k in grammar) {
    var production = grammar[k]
    var LHS = getLHS(production)
    var RHS = getRHS(production)
    var productionNumber = Number(k)

    // Init columns for this non-terminal.
    if (!parsingTable[LHS]) {
      parsingTable[LHS] = {}
    }

    // All productions goes under the terminal column, if
    // this terminal is not epsilon.
    if (RHS[0] !== EPSILON) {
      var tttt = getFirstSetOfRHS(RHS)
      tttt.forEach(function (terminal) {
        parsingTable[LHS][terminal] = productionNumber
      })
    } else {
      // Otherwise, this ε-production goes under the columns from
      // the Follow set.
      followSets[LHS].forEach(function (terminal) {
        parsingTable[LHS][terminal] = productionNumber
      })
    }
  }

  return parsingTable
}

/**
 * Given production `S -> F`, returns `S`.
 */
function getLHS (production) {
  // return production.split('->')[0].replace(/\s+/g, '');
  return production[0]
}

/**
 * Given production `S -> F`, returns `F`.
 */
function getRHS (production) {
  // return production.split('->')[1].replace(/\s+/g, '');
  return production.slice(2)
}

/**
 * Returns First set of RHS.
 */
function getFirstSetOfRHS (RHS) {
  // For simplicity, in this educational parser, we assume that
  // the first symbol (if it's a non-terminal) cannot produces `ε`.
  // Since in real parser, we need to get the First set of the whole RHS.
  // This means, that if `B` in the production `X -> BC` can be `ε`, then
  // the First set should of course include First(C) as well, i.e. RHS[1], etc.
  //
  // That is, in a real parser, one usually combines steps of building a
  // parsing table, First and Follow sets in one step: when a parsing table
  // needs the First set of a RHS, it's calculated in place.
  //
  // But here we just return First of RHS[0].
  //

  return firstSets[RHS[0]]
}

// Testing

// ----------------------------------------------------------------------
// Example 1 of a simple grammar, generates: a, or (a + a), etc.
// ----------------------------------------------------------------------

// We just manually define our First and Follow sets for a given grammar,
// see again diff (2) where we automatically generated these sets.
/*
var grammar = {
  1: ['S', '->', 'F'],
  2: ['S', '->', '(', 'S', '+', 'F', ')'],
  3: ['F', '->', 'a']
}

var firstSets = {
  'S': ['a', '('],
  'F': ['a'],
  'a': ['a'],
  '(': ['(']
}

var followSets = {
  'S': ['$', '+'],
  'F': ['$', '+', ')']
}

console.log(buildParsingTable(grammar))

// Results:

// S: { a: 1, '(': 2 }
// F: { a: 3 }

// That corresponds to the following table:

// +------------------+
// |    (  )  a  +  $ |
// +------------------+
// | S  2  -  1  -  - |
// | F  -  -  3  -  - |
// +------------------+
*/
// ----------------------------------------------------------------------
// Example 2, for the "calculator" grammar, e.g. (a + a) * a.
// ----------------------------------------------------------------------

/*
var grammar = {
  1: ['E', '->', 'T', 'X'],
  2: ['X', '->', '+', 'T', 'X'],
  3: ['X', '->', 'ε'],
  4: ['T', '->', 'F', 'Y'],
  5: ['Y', '->', '*', 'F', 'Y'],
  6: ['Y', '->', 'ε'],
  7: ['F', '->', 'a'],
  8: ['F', '->', '(', 'E', ')']
}

var firstSets = {
  'E': ['a', '('],
  'T': ['a', '('],
  'F': ['a', '('],
  'a': ['a'],
  '(': ['('],
  'X': ['+', 'ε'],
  '+': ['+'],
  'Y': ['*', 'ε'],
  '*': ['*']
}

var followSets = {
  'E': ['$', ')'],
  'X': ['$', ')'],
  'T': ['+', '$', ')'],
  'Y': ['+', '$', ')'],
  'F': ['*', '+', '$', ')']
}

console.log(buildParsingTable(grammar))

// Results:

// E: { a: 1, '(': 1 },
// X: { '+': 2, '$': 3, ')': 3 },
// T: { a: 4, '(': 4 },
// Y: { '*': 5, '+': 6, '$': 6, ')': 6 },
// F: { a: 7, '(': 8 }

// That corresponds to the following table:

// +---------------------+
// |    a  +  *  (  )  $ |
// +---------------------+
// | E  1  -  -  1  -  - |
// | X  -  2  -  -  3  3 |
// | T  4  -  -  4  -  - |
// | Y  -  6  5  -  6  6 |
// | F  7  -  -  8  -  - |
// +---------------------+
*/

var grammar = {
  1: ['A', '->', '<algoritmo>', '<str>', 'LISTADECLAR', '<inicio>', 'CODIGO', '<fimalgoritmo>', '/e/'],
  2: ['LISTADECLAR', '->', 'UNIDECLAR', 'LISTADECLAR'],
  3: ['LISTADECLAR', '->', 'MULTIDECLAR', 'LISTADECLAR'],
  4: ['LISTADECLAR', '->', '/e/'],
  5: ['UNIDECLAR', '->', '<var>', '<id>', '<del|:>', 'TIPO'],
  6: ['MULTIDECLAR', '->', 'IDLIST', '<del|:>', 'TIPO'],
  7: ['TIPO', '->', '<inteiro>'],
  8: ['TIPO', '->', '<logico>'],
  9: ['IDLIST', '->', '<id>', 'IDLIST'],
  10: ['IDLIST', '->', '<del|,>', '<id>', 'IDLIST'],
  11: ['IDLIST', '->', '/e/'],
  12: ['CODIGO', '->', 'COMANDO', 'CODIGO'],
  13: ['CODIGO', '->', '/e/'],
  14: ['COMANDO', '->', '<id>', '<op|<->', 'EXPRESSAO'],
  15: ['COMANDO', '->', '<leia>', '<del|(>', 'IDLIST', '<del|)>'],
  16: ['COMANDO', '->', '<escreva>', '<del|(>', 'STROUT', '<del|)>'],
  17: ['COMANDO', '->', '<se>', 'EXPRESSAOLOGICA', '<entao>', 'CODIGO', '<senao>', 'CODIGO', '<fimse>', '/e/'],
  18: ['COMANDO', '->', '<para>', '<id>', '<de>', '<num>', '<ate>', '<num>', 'PASSO', '<faca>', 'CODIGO', '<fimpara>', '/e/'],
  19: ['COMANDO', '->', '<enquanto>', 'EXPRESSAOLOGICA', '<faca>', 'CODIGO', '<fimenquanto>', '/e/'],
  20: ['PASSO', '->', '<passo>', '<num>'],
  21: ['PASSO', '->', '/e/'],
  22: ['EXPRESSAO', '->', 'DATA', 'OPERANDO'],
  23: ['OPERANDO', '->', 'OP', 'DATA'],
  24: ['OPERANDO', '->', '/e/'],
  25: ['STROUT', '->', 'PRINTABLE', 'STROUT'],
  26: ['STROUT', '->', '<del|,>', 'PRINTABLE', 'STROUT'],
  27: ['STROUT', '->', '/e/'],
  28: ['PRINTABLE', '->', '<id>'],
  29: ['PRINTABLE', '->', '<str>'],
  30: ['EXPRESSAOLOGICA', '->', 'DATA', 'EXPRESSAOLOGICA'],
  31: ['EXPRESSAOLOGICA', '->', 'LOGICOP', 'DATA', 'EXPRESSAOLOGICA'],
  32: ['EXPRESSAOLOGICA', '->', '/e/'],
  33: ['DATA', '->', '<num>'],
  34: ['DATA', '->', '<str>'],
  35: ['DATA', '->', '<verdadeiro>'],
  36: ['DATA', '->', '<falso>'],
  37: ['DATA', '->', '<id>'],
  38: ['LOGICOP', '->', '<lop|>>'],
  39: ['LOGICOP', '->', '<lop|>=>'],
  40: ['LOGICOP', '->', '<lop|<>'],
  41: ['LOGICOP', '->', '<lop|<=>'],
  42: ['LOGICOP', '->', '<lop|=>'],
  43: ['LOGICOP', '->', '<lop|<>>'],
  44: ['LOGICOP', '->', '<lop|e>'],
  45: ['LOGICOP', '->', '<lop|ou>'],
  46: ['OP', '->', '<op|+>'],
  47: ['OP', '->', '<op|->'],
  48: ['OP', '->', '<op|*>'],
  49: ['OP', '->', '<op|/>'],
  50: ['OP', '->', '<op|mod>'],
  51: ['OP', '->', '<op|exp>'],
  52: ['OP', '->', 'LOGICOP']
}

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
  'EXPRESSAO': ['<num>', '<str>', '<verdadeiro>', '<falso>', '<id>'],
  'DATA': ['<num>', '<str>', '<verdadeiro>', '<falso>', '<id>'],
  '<num>': ['<num>'],
  '<str>': ['<str>'],
  '<verdadeiro>': ['<verdadeiro>'],
  '<falso>': ['<falso>'],
  'OPERANDO': ['<op|+>', '<op|->', '<op|*>', '<op|/>', '<op|mod>', '<op|exp>', '<lop|>>', '<lop|>=>', '<lop|<>', '<lop|<=>', '<lop|=>', '<lop|<>>', '<lop|e>', '<lop|ou>', '/e/'],
  'OP': ['<op|+>', '<op|->', '<op|*>', '<op|/>', '<op|mod>', '<op|exp>', '<lop|>>', '<lop|>=>', '<lop|<>', '<lop|<=>', '<lop|=>', '<lop|<>>', '<lop|e>', '<lop|ou>'],
  '<op|+>': ['<op|+>'],
  '<op|->': ['<op|->'],
  '<op|*>': ['<op|*>'],
  '<op|/>': ['<op|/>'],
  '<op|mod>': ['<op|mod>'],
  '<op|exp>': ['<op|exp>'],
  'LOGICOP': ['<lop|>>', '<lop|>=>', '<lop|<>', '<lop|<=>', '<lop|=>', '<lop|<>>', '<lop|e>', '<lop|ou>'],
  '<lop|>>': ['<lop|>>'],
  '<lop|>=>': ['<lop|>=>'],
  '<lop|<>': ['<lop|<>'],
  '<lop|<=>': ['<lop|<=>'],
  '<lop|=>': ['<lop|=>'],
  '<lop|<>>': ['<lop|<>>'],
  '<lop|e>': ['<lop|e>'],
  '<lop|ou>': ['<lop|ou>'],
  'STROUT': ['<id>', '<str>', '<del|,>', '/e/'],
  'PRINTABLE': ['<id>', '<str>'],
  'EXPRESSAOLOGICA': ['<num>', '<str>', '<verdadeiro>', '<falso>', '<id>', '<lop|>>', '<lop|>=>', '<lop|<>', '<lop|<=>', '<lop|=>', '<lop|<>>', '<lop|e>', '<lop|ou>', '/e/']
}

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
  'EXPRESSAO': ['<id>', '<leia>', '<escreva>', '<se>', '<para>', '<enquanto>', '<fimalgoritmo>', '<senao>', '<fimpara>', '<fimenquanto>'],
  'OPERANDO': ['<id>', '<leia>', '<escreva>', '<se>', '<para>', '<enquanto>', '<fimalgoritmo>', '<senao>', '<fimpara>', '<fimenquanto>'],
  'STROUT': ['<del|)>'],
  'PRINTABLE': ['<id>', '<str>', '<del|,>', '<del|)>'],
  'EXPRESSAOLOGICA': ['<entao>', '<faca>'],
  'DATA': ['<op|+>', '<op|->', '<op|*>', '<op|/>', '<op|mod>', '<op|exp>', '<lop|>>', '<lop|>=>', '<lop|<>', '<lop|<=>', '<lop|=>', '<lop|<>>', '<lop|e>', '<lop|ou>', '<id>', '<leia>', '<escreva>', '<se>', '<para>', '<enquanto>', '<fimalgoritmo>', '<senao>', '<fimpara>', '<fimenquanto>', '<num>', '<str>', '<verdadeiro>', '<falso>', '<entao>', '<faca>'],
  'LOGICOP': ['<num>', '<str>', '<verdadeiro>', '<falso>', '<id>'],
  'OP': ['<num>', '<str>', '<verdadeiro>', '<falso>', '<id>']
}

console.log(buildParsingTable(grammar))
