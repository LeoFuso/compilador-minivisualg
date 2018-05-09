// Special "empty" symbol.
var EPSILON = '/e/'

/**
 * Given a grammar builds a LL(1) parsing table based on the
 * First and Follow sets of this grammar.
 */
function buildParsingTable(grammar) {
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
function getLHS(production) {
  // return production.split('->')[0].replace(/\s+/g, '');
  return production[0]
}

/**
 * Given production `S -> F`, returns `F`.
 */
function getRHS(production) {
  // return production.split('->')[1].replace(/\s+/g, '');
  return production.slice(2)
}

/**
 * Returns First set of RHS.
 */
function getFirstSetOfRHS(RHS) {
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
  1: ['A', '->', '<algoritmo>', '<str>', 'B', '<inicio>', 'C', '<fimalgoritmo>'],
  2: ['B', '->', 'D', 'B'],
  3: ['B', '->', 'F', 'B'],
  4: ['B', '->', '/e/'],
  5: ['D', '->', '<var>', '<id>', '<del|:>', 'E'],
  6: ['F', '->', 'G', '<del|:>', 'E'],
  7: ['E', '->', '<inteiro>'],
  8: ['E', '->', '<logico>'],
  9: ['G', '->', '<id>', 'G'],
  10: ['G', '->', '<del|,>', '<id>', 'G'],
  11: ['G', '->', '/e/'],
  12: ['C', '->', 'H', 'C'],
  13: ['C', '->', '/e/'],
  14: ['H', '->', 'I'],
  15: ['H', '->', '<leia>', '<del|(>', 'G', '<del|)>'],
  16: ['H', '->', '<escreva>', '<del|(>', 'J', '<del|)>'],
  17: ['H', '->', '<se>', 'K', '<entao>', 'C', '<senao>', 'C', '<fimse>'],
  18: ['H', '->', '<para>', '<id>', '<de>', '<num>', '<ate>', '<num>', '<passo>', '<num>', '<faca>', 'C', '<fimpara>'],
  19: ['H', '->', '<para>', '<id>', '<de>', '<num>', '<ate>', '<num>', '<faca>', 'C', '<fimpara>'],
  20: ['H', '->', '<enquanto>', 'K', '<faca>', 'C', '<fimenquanto>'],
  21: ['I', '->', '<id>', '<op|<->', 'L'],
  22: ['I', '->', '<id>', '<op|<->', 'M'],
  23: ['J', '->', '<str>', 'J'],
  24: ['J', '->', '<id>', 'J'],
  25: ['J', '->', '<del|,>', '<id>', 'J'],
  26: ['J', '->', '<del|,>', '<str>', 'J'],
  27: ['J', '->', '/e/'],
  28: ['K', '->', 'M', 'N', 'M'],
  29: ['L', '->', '<num>'],
  30: ['L', '->', '<str>'],
  31: ['L', '->', '<verdadeiro>'],
  32: ['L', '->', '<falso>'],
  33: ['M', '->', '<id>', 'M'],
  34: ['M', '->', 'L', 'M'],
  35: ['M', '->', 'O', '<id>', 'M'],
  36: ['M', '->', 'O', 'L', 'M'],
  37: ['M', '->', '/e/'],
  38: ['N', '->', '<lop|>>'],
  39: ['N', '->', '<lop|>=>'],
  40: ['N', '->', '<lop|<>'],
  41: ['N', '->', '<lop|<=>'],
  42: ['N', '->', '<lop|=>'],
  43: ['N', '->', '<lop|<>>'],
  44: ['N', '->', '<lop|e>'],
  45: ['N', '->', '<lop|ou>'],
  46: ['O', '->', '<op|+>'],
  47: ['O', '->', '<op|->'],
  48: ['O', '->', '<op|*>'],
  49: ['O', '->', '<op|/>'],
  50: ['O', '->', '<op|mod>'],
  51: ['O', '->', '<op|exp>'],
  52: ['O', '->', 'N']
}

var firstSets = {
  'A': ['<algoritmo>'],
  '<algoritmo>': ['<algoritmo>'],
  'B': ['<var>', '<id>', '<del|,>', '<del|:>', '/e/'],
  'D': ['<var>'],
  '<var>': ['<var>'],
  'F': ['<id>', '<del|,>', '<del|:>'],
  'G': ['<id>', '<del|,>', '/e/'],
  '<id>': ['<id>'],
  '<del|,>': ['<del|,>'],
  '<del|:>': ['<del|:>'],
  'E': ['<inteiro>', '<logico>'],
  '<inteiro>': ['<inteiro>'],
  '<logico>': ['<logico>'],
  'C': ['<id>', '<leia>', '<escreva>', '<se>', '<para>', '<enquanto>', '/e/'],
  'H': ['<id>', '<leia>', '<escreva>', '<se>', '<para>', '<enquanto>'],
  'I': ['<id>'],
  '<leia>': ['<leia>'],
  '<escreva>': ['<escreva>'],
  '<se>': ['<se>'],
  '<para>': ['<para>'],
  '<enquanto>': ['<enquanto>'],
  'J': ['<str>', '<id>', '<del|,>', '/e/'],
  '<str>': ['<str>'],
  'K': ['<id>', '<num>', '<str>', '<verdadeiro>', '<falso>', '<op|+>', '<op|->', '<op|*>', '<op|/>', '<op|mod>', '<op|exp>', '<lop|>>', '<lop|>=>', '<lop|<>', '<lop|<=>', '<lop|=>', '<lop|<>>', '<lop|e>', '<lop|ou>'],
  'M': ['<id>', '<num>', '<str>', '<verdadeiro>', '<falso>', '<op|+>', '<op|->', '<op|*>', '<op|/>', '<op|mod>', '<op|exp>', '<lop|>>', '<lop|>=>', '<lop|<>', '<lop|<=>', '<lop|=>', '<lop|<>>', '<lop|e>', '<lop|ou>', '/e/'],
  'L': ['<num>', '<str>', '<verdadeiro>', '<falso>'],
  '<num>': ['<num>'],
  '<verdadeiro>': ['<verdadeiro>'],
  '<falso>': ['<falso>'],
  'O': ['<op|+>', '<op|->', '<op|*>', '<op|/>', '<op|mod>', '<op|exp>', '<lop|>>', '<lop|>=>', '<lop|<>', '<lop|<=>', '<lop|=>', '<lop|<>>', '<lop|e>', '<lop|ou>'],
  '<op|+>': ['<op|+>'],
  '<op|->': ['<op|->'],
  '<op|*>': ['<op|*>'],
  '<op|/>': ['<op|/>'],
  '<op|mod>': ['<op|mod>'],
  '<op|exp>': ['<op|exp>'],
  'N': ['<lop|>>', '<lop|>=>', '<lop|<>', '<lop|<=>', '<lop|=>', '<lop|<>>', '<lop|e>', '<lop|ou>'],
  '<lop|>>': ['<lop|>>'],
  '<lop|>=>': ['<lop|>=>'],
  '<lop|<>': ['<lop|<>'],
  '<lop|<=>': ['<lop|<=>'],
  '<lop|=>': ['<lop|=>'],
  '<lop|<>>': ['<lop|<>>'],
  '<lop|e>': ['<lop|e>'],
  '<lop|ou>': ['<lop|ou>']
}

var followSets = {
  'A': ['$'],
  'B': ['<inicio>'],
  'D': ['<var>', '<id>', '<del|,>', '<del|:>', '<inicio>'],
  'F': ['<var>', '<id>', '<del|,>', '<del|:>', '<inicio>'],
  'E': ['<var>', '<id>', '<del|,>', '<del|:>', '<inicio>'],
  'G': ['<del|:>', '<del|)>'],
  'C': ['<fimalgoritmo>', '<senao>', '<fimpara>', '<fimenquanto>'],
  'H': ['<id>', '<leia>', '<escreva>', '<se>', '<para>', '<enquanto>', '<fimalgoritmo>', '<senao>', '<fimpara>', '<fimenquanto>'],
  'I': ['<id>', '<leia>', '<escreva>', '<se>', '<para>', '<enquanto>', '<fimalgoritmo>', '<senao>', '<fimpara>', '<fimenquanto>'],
  'J': ['<del|)>'],
  'K': ['<entao>', '<faca>'],
  'L': ['<id>', '<leia>', '<escreva>', '<se>', '<para>', '<enquanto>', '<fimalgoritmo>', '<senao>', '<fimpara>', '<fimenquanto>', '<num>', '<str>', '<verdadeiro>', '<falso>', '<op|+>', '<op|->', '<op|*>', '<op|/>', '<op|mod>', '<op|exp>', '<lop|>>', '<lop|>=>', '<lop|<>', '<lop|<=>', '<lop|=>', '<lop|<>>', '<lop|e>', '<lop|ou>'],
  'M': ['<id>', '<leia>', '<escreva>', '<se>', '<para>', '<enquanto>', '<fimalgoritmo>', '<senao>', '<fimpara>', '<fimenquanto>', '<lop|>>', '<lop|>=>', '<lop|<>', '<lop|<=>', '<lop|=>', '<lop|<>>', '<lop|e>', '<lop|ou>'],
  'N': ['<id>', '<num>', '<str>', '<verdadeiro>', '<falso>', '<op|+>', '<op|->', '<op|*>', '<op|/>', '<op|mod>', '<op|exp>', '<lop|>>', '<lop|>=>', '<lop|<>', '<lop|<=>', '<lop|=>', '<lop|<>>', '<lop|e>', '<lop|ou>', '<entao>', '<faca>'],
  'O': ['<id>', '<num>', '<str>', '<verdadeiro>', '<falso>']
}

console.log(buildParsingTable(grammar))