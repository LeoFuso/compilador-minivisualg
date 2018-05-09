/**
 * = LL parser =
 *
 * by Dmitry Soshnikov <dmitry.soshnikov@gmail.com>
 * MIT Style license
 *
 * Often one can see manually written LL parsers implemented as
 * recursive descent. Approach in this diff is a classical parse table
 * state machine.
 *
 *  LL parser consists of:
 *
 * 1. input buffer (source code)
 * 2. stack
 * 3. parsing table (state machine)
 *
 * Parsing table:
 *
 *   Table is used to get the next production number to apply, based on current
 *   symbol from the buffer, and the symbol (terminal or non-terminal)
 *   on top of the stack.
 *
 *   - Rows in the table are non-terminals
 *   - Columns are terminals
 *
 * Parsing algorithm:
 *
 *   - if the top of the stack is *terminal*, and matches current symbol in
 *     buffer, then just discard it from the stack, and move cursor further.
 *     (if doesn't match -- parse error).
 *
 *   - Else (it must be a non-terminal), replace it with an
 *     alternative production, corresponding to the production number.
 *     (if no production -- parse error).
 *
 * $ - is a special symbol used to mark bottom of the stack
 *     and end of the buffer.
 *
 * S - is a start symbol.
 *
 * At the beginning stack is:
 *
 * [S, $]
 *
 * Example:
 *
 * Grammar:
 *
 *   1. S -> F
 *   2. S -> (S + F)
 *   3. F -> a
 *
 * Input:
 *
 *   (a + a)
 *
 * Parse table:
 *
 *   +------------------+
 *   |    (  )  a  +  $ |
 *   +------------------+
 *   | S  2  -  1  -  - |
 *   | F  -  -  3  -  - |
 *   +------------------+
 *
 * The production rules which are applied to parse `(a + a)` are: 2, 1, 3, 3:
 *
 * S -> ( S + F ) -> ( F + F ) -> ( a + F ) -> ( a + a )
 *
 * We see that each time the *left most* non-terminal is replaced. Hence, the
 * name of the parser: LL - scan source from Left to right, and apply the
 * Left most derivation.
 */

/**
 * Our grammar representation. Key is a production number from
 * the grammar, the value is: 0 - LHS, 1 - RHS of the production.
 */
/*
var grammar = {
  1: ['S', 'F'], // 1. S -> F
  2: ['S', '(S + F)'], // 2. S -> (S + F)
  3: ['F', 'a'] // 3. F -> a
}
*/
/*
var grammar = {
  1: ['S', 'F'], // 1. S -> F
  2: ['S', '(', 'S', '+', 'F', ')'], // 2. S -> (S + F)
  3: ['F', 'a'] // 3. F -> a
}
*/
var EPSILON = '/e/'

// Lembre de tirar os '->',
var grammar = {
  1: ['A', '<algoritmo>', '<str>', 'LISTADECLAR', '<inicio>', 'CODIGO', '<fimalgoritmo>'],
  2: ['LISTADECLAR', 'UNIDECLAR', 'LISTADECLAR'],
  3: ['LISTADECLAR', 'MULTIDECLAR', 'LISTADECLAR'],
  4: ['LISTADECLAR', '/e/'],
  5: ['UNIDECLAR', '<var>', '<id>', '<del|:>', 'TIPO'],
  6: ['MULTIDECLAR', 'IDLIST', '<del|:>', 'TIPO'],
  7: ['TIPO', '<inteiro>'],
  8: ['TIPO', '<logico>'],
  9: ['IDLIST', '<id>', 'IDLIST'],
  10: ['IDLIST', '<del|,>', '<id>', 'IDLIST'],
  11: ['IDLIST', '/e/'],
  12: ['CODIGO', 'COMANDO', 'CODIGO'],
  13: ['CODIGO', '/e/'],
  14: ['COMANDO', 'ATRIBUICAO'],
  15: ['COMANDO', '<leia>', '<del|(>', 'IDLIST', '<del|)>'],
  16: ['COMANDO', '<escreva>', '<del|(>', 'STROUT', '<del|)>'],
  17: ['COMANDO', '<se>', 'EXPRESSAOLOGICA', '<entao>', 'CODIGO', '<senao>', 'CODIGO', '<fimse>'],
  18: ['COMANDO', '<para>', '<id>', '<de>', '<num>', '<ate>', '<num>', 'PASSO', '<faca>', 'CODIGO', '<fimpara>'],
  19: ['COMANDO', '<enquanto>', 'EXPRESSAOLOGICA', '<faca>', 'CODIGO', '<fimenquanto>'],
  20: ['PASSO', '<passo>', '<num>'],
  21: ['PASSO', '/e/'],
  22: ['ATRIBUICAO', '<id>', '<op|<->', 'DATA'],
  23: ['ATRIBUICAO', '<id>', '<op|<->', 'EXPRESSAO'],
  24: ['STROUT', '<str>', 'STROUT'],
  25: ['STROUT', '<id>', 'STROUT'],
  26: ['STROUT', '<del|,>', '<id>', 'STROUT'],
  27: ['STROUT', '<del|,>', '<str>', 'STROUT'],
  28: ['STROUT', '/e/'],
  29: ['EXPRESSAOLOGICA', 'EXPRESSAO', 'LOGICOP', 'EXPRESSAO'],
  30: ['DATA', '<num>'],
  31: ['DATA', '<str>'],
  32: ['DATA', '<verdadeiro>'],
  33: ['DATA', '<falso>'],
  34: ['EXPRESSAO', '<id>', 'EXPRESSAO'],
  35: ['EXPRESSAO', 'DATA', 'EXPRESSAO'],
  36: ['EXPRESSAO', 'OP', '<id>', 'EXPRESSAO'],
  37: ['EXPRESSAO', 'OP', 'DATA', 'EXPRESSAO'],
  38: ['EXPRESSAO', '/e/'],
  39: ['LOGICOP', '<lop|>>'],
  40: ['LOGICOP', '<lop|>=>'],
  41: ['LOGICOP', '<lop|<>'],
  42: ['LOGICOP', '<lop|<=>'],
  43: ['LOGICOP', '<lop|=>'],
  44: ['LOGICOP', '<lop|<>>'],
  45: ['LOGICOP', '<lop|e>'],
  46: ['LOGICOP', '<lop|ou>'],
  47: ['OP', '<op|+>'],
  48: ['OP', '<op|->'],
  49: ['OP', '<op|*>'],
  50: ['OP', '<op|/>'],
  51: ['OP', '<op|mod>'],
  52: ['OP', '<op|exp>'],
  53: ['OP', 'LOGICOP']
}

/**
 * Initial stack: bottom is the "end of the stack" ($),
 * and the start symbol ('S' in our case) is there too.
 */
var stack = ['A', '$']

function parse (source) {
  return parseFromTable(source, buildTable(grammar, source))
}

function printGrammar (grammar) {
  console.log('Grammar:\n')
  for (var k in grammar) {
    console.log('  ' + k + '.', grammar[k][0], '->', grammar[k][1])
  }
  console.log('')
}

/**
 * Builds a state-machine table where table[non-terminal][terminal]
 * coordinates determine which next production rule to apply.
 */
function buildTable (grammar, source) {
  // For now we assume a correct table was already built from
  // the grammar and source for us. We'll cover how to build it
  // automatically in the next lessons (see "first" and "follow"
  // sets topic). We encode only valid rules here and skip all other
  // (they return `undefined` meaning a parse error).
  //
  // +------------------+
  // |    (  )  a  +  $ |
  // +------------------+
  // | S  2  -  1  -  - |
  // | F  -  -  3  -  - |
  // +------------------+
  //
  /*
  return {
    'S': {
      '(': 2,
      'a': 1
    },
    'F': {
      'a': 3
    }
  }
  */
  return {
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
}

var productionNumbers = []

/**
 * Parses a source using parse table.
 * Doesn't build a parse tree yet, but just checks a source
 * string for acceptance (prints production rules appled in case
 * of successful parse, or throws on parse errors).
 */
function parseFromTable (source, table) {
  printGrammar(grammar)
  console.log('Source:', source)
  for (var cursor = 0; cursor < source.length;) {
    var current = source[cursor]
    console.log('---')
    console.log('STACK: ' + stack)
    console.log('Current: ' + current)
    var top = stack.shift()
    if (top === EPSILON) {
      top = stack.shift()
    }
    // Terminal is on the stack, just advance.
    if (isTerminal(top, table) && top === current) {
      // We already shifted the symbol from the stack,
      // so just advance the cursor.
      cursor++
      continue
    }
    // Else, it's a non-terminal, do derivation (replace it
    // in the stack with corresponding production).
    var productionElements = getProduction(table, top, current)
    stack.unshift.apply(stack, productionElements)
  }
  console.log('Accepted. Productions:', productionNumbers.join(', '), '\n')
}

function isTerminal (symbol, table) {
  var isTerminalVerificate = !table.hasOwnProperty(symbol)
  return isTerminalVerificate
}

function getProduction (table, top, current) {
  // Seleciona o numero da producao (regra) cruzando o nao terminal 'top', com o atual terminal 'current'
  console.log('T: ' + top + ' C: ' + current)
  var nextProductionNumber = table[top][current]

  // Se nao achar uma producao na tabela, current é um token errado
  if (!nextProductionNumber) {
    throw Error('Parse error, unexpected token: ' + current)
  }

  var nextProduction = grammar[nextProductionNumber]

  productionNumbers.push(nextProductionNumber)

  // Return an array of symbols from a production, e.g.
  // '(', 'S', '+', 'F', ')' for '(S + F)', since
  // each symbol should be pushed onto the stack.
  // return nextProduction[1].split(/\s*/)
  return nextProduction.slice(1)
}

// Test:

var alg = '<algoritmo> <str> <var> <id> <del|:> <inteiro> <var> <id> <del|:> <logico> <id> <del|,> <id> <del|:> <inteiro> <inicio> <id> <op|<-> <num> <id> <op|<-> <num> <para> <id> <de> <num> <ate> <num> <passo> <num> <faca> <escreva> <del|(> <id> <del|)> <leia> <del|(> <id> <del|)> <se> <id> <lop|>> <num> <entao> <id> <op|<-> <id> <op|+> <num> <fimse> <fimpara> <escreva> <del|(> <id> <del|)> <fimalgoritmo>'.split(' ')

parse(alg)

// Output:

// Grammar:
//
//   1. S -> F
//   2. S -> (S + F)
//   3. F -> a
//
// Source: (a + a)
// Accepted. Productions: 2, 1, 3, 3
