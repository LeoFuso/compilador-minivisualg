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
  14: ['COMANDO', '<id>', '<op|<->', 'EXPRESSAO'],
  15: ['COMANDO', '<leia>', '<del|(>', 'IDLIST', '<del|)>'],
  16: ['COMANDO', '<escreva>', '<del|(>', 'STROUT', '<del|)>'],
  17: ['COMANDO', '<se>', 'EXPRESSAOLOGICA', '<entao>', 'CODIGO', '<senao>', 'CODIGO', '<fimse>'],
  18: ['COMANDO', '<para>', '<id>', '<de>', '<num>', '<ate>', '<num>', 'PASSO', '<faca>', 'CODIGO', '<fimpara>'],
  19: ['COMANDO', '<enquanto>', 'EXPRESSAOLOGICA', '<faca>', 'CODIGO', '<fimenquanto>'],
  20: ['PASSO', '<passo>', '<num>'],
  21: ['PASSO', '/e/'],
  22: ['EXPRESSAO', 'DATA', 'OPERANDO'],
  23: ['OPERANDO', 'OP', 'DATA'],
  24: ['OPERANDO', '/e/'],
  25: ['STROUT', 'PRINTABLE', 'STROUT'],
  26: ['STROUT', '<del|,>', 'PRINTABLE', 'STROUT'],
  27: ['STROUT', '/e/'],
  28: ['PRINTABLE', '<id>'],
  29: ['PRINTABLE', '<str>'],
  30: ['EXPRESSAOLOGICA', 'DATA', 'EXPRESSAOLOGICA'],
  31: ['EXPRESSAOLOGICA', 'LOGICOP', 'DATA', 'EXPRESSAOLOGICA'],
  32: ['EXPRESSAOLOGICA', '/e/'],
  33: ['DATA', '<num>'],
  34: ['DATA', '<str>'],
  35: ['DATA', '<verdadeiro>'],
  36: ['DATA', '<falso>'],
  37: ['DATA', '<id>'],
  38: ['LOGICOP', '<lop|>>'],
  39: ['LOGICOP', '<lop|>=>'],
  40: ['LOGICOP', '<lop|<>'],
  41: ['LOGICOP', '<lop|<=>'],
  42: ['LOGICOP', '<lop|=>'],
  43: ['LOGICOP', '<lop|<>>'],
  44: ['LOGICOP', '<lop|e>'],
  45: ['LOGICOP', '<lop|ou>'],
  46: ['OP', '<op|+>'],
  47: ['OP', '<op|->'],
  48: ['OP', '<op|*>'],
  49: ['OP', '<op|/>'],
  50: ['OP', '<op|mod>'],
  51: ['OP', '<op|exp>'],
  52: ['OP', 'LOGICOP']
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
    console.log('  ' + k + '.', grammar[k][0], ', =>' + grammar[k][1])
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
      '<fimse>': 13,
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
    EXPRESSAO: {
      '<num>': 22,
      '<str>': 22,
      '<verdadeiro>': 22,
      '<falso>': 22,
      '<id>': 22
    },
    OPERANDO: {
      '<op|+>': 23,
      '<op|->': 23,
      '<op|*>': 23,
      '<op|/>': 23,
      '<op|mod>': 23,
      '<op|exp>': 23,
      '<lop|>>': 23,
      '<lop|>=>': 23,
      '<lop|<>': 23,
      '<lop|<=>': 23,
      '<lop|=>': 23,
      '<lop|<>>': 23,
      '<lop|e>': 23,
      '<lop|ou>': 23,
      '<id>': 24,
      '<leia>': 24,
      '<escreva>': 24,
      '<se>': 24,
      '<para>': 24,
      '<enquanto>': 24,
      '<fimalgoritmo>': 24,
      '<senao>': 24,
      '<fimpara>': 24,
      '<fimenquanto>': 24
    },
    STROUT: {
      '<id>': 25,
      '<str>': 25,
      '<del|,>': 26,
      '<del|)>': 27
    },
    PRINTABLE: {
      '<id>': 28,
      '<str>': 29
    },
    EXPRESSAOLOGICA: {
      '<num>': 30,
      '<str>': 30,
      '<verdadeiro>': 30,
      '<falso>': 30,
      '<id>': 30,
      '<lop|>>': 31,
      '<lop|>=>': 31,
      '<lop|<>': 31,
      '<lop|<=>': 31,
      '<lop|=>': 31,
      '<lop|<>>': 31,
      '<lop|e>': 31,
      '<lop|ou>': 31,
      '<entao>': 32,
      '<faca>': 32
    },
    DATA: {
      '<num>': 33,
      '<str>': 34,
      '<verdadeiro>': 35,
      '<falso>': 36,
      '<id>': 37
    },
    LOGICOP: {
      '<lop|>>': 38,
      '<lop|>=>': 39,
      '<lop|<>': 40,
      '<lop|<=>': 41,
      '<lop|=>': 42,
      '<lop|<>>': 43,
      '<lop|e>': 44,
      '<lop|ou>': 45
    },
    OP: {
      '<op|+>': 46,
      '<op|->': 47,
      '<op|*>': 48,
      '<op|/>': 49,
      '<op|mod>': 50,
      '<op|exp>': 51,
      '<lop|>>': 52,
      '<lop|>=>': 52,
      '<lop|<>': 52,
      '<lop|<=>': 52,
      '<lop|=>': 52,
      '<lop|<>>': 52,
      '<lop|e>': 52,
      '<lop|ou>': 52
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
    console.log('Current: ' + current + ' AT: ' + cursor)
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

var alg = '<algoritmo> <str> <var> <id> <del|:> <inteiro> <var> <id> <del|:> <logico> <id> <del|,> <id> <del|:> <inteiro> <inicio> <id> <op|<-> <num> <id> <op|<-> <num> <para> <id> <de> <num> <ate> <num> <passo> <num> <faca> <escreva> <del|(> <id> <del|)> <leia> <del|(> <id> <del|)> <se> <id> <lop|>> <num> <entao> <id> <op|<-> <id> <op|+> <num> <senao> <fimse> <fimpara> <escreva> <del|(> <id> <del|)> <fimalgoritmo>'.split(' ')

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
