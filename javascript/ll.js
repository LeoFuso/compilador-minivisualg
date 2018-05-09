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
var grammar = {
  1: ['A', '<algoritmo>', '<str>', 'B', '<inicio>', 'C', '<fimalgoritmo>'],
  2: ['B', 'D', 'B'],
  3: ['B', 'F', 'B'],
  4: ['B', '/e/'],
  5: ['D', '<var>', '<id>', '<del|:>', 'E'],
  6: ['F', 'G', '<del|:>', 'E'],
  7: ['E', '<inteiro>'],
  8: ['E', '<logico>'],
  9: ['G', '<id>', 'G'],
  10: ['G', '<del|,>', '<id>', 'G'],
  11: ['G', '/e/'],
  12: ['C', 'H', 'C'],
  13: ['C', '/e/'],
  14: ['H', 'I'],
  15: ['H', '<leia>', '<del|(>', 'G', '<del|)>'],
  16: ['H', '<escreva>', '<del|(>', 'J', '<del|)>'],
  17: ['H', '<se>', 'K', '<entao>', 'C', '<senao>', 'C', '<fimse>'],
  18: ['H', '<para>', '<id>', '<de>', '<num>', '<ate>', '<num>', '<passo>', '<num>', '<faca>', 'C', '<fimpara>'],
  19: ['H', '<para>', '<id>', '<de>', '<num>', '<ate>', '<num>', '<faca>', 'C', '<fimpara>'],
  20: ['H', '<enquanto>', 'K', '<faca>', 'C', '<fimenquanto>'],
  21: ['I', '<id>', '<op|<->', 'L'],
  22: ['I', '<id>', '<op|<->', 'M'],
  23: ['J', '<str>', 'J'],
  24: ['J', '<id>', 'J'],
  25: ['J', '<del|,>', '<id>', 'J'],
  26: ['J', '<del|,>', '<str>', 'J'],
  27: ['J', '/e/'],
  28: ['K', 'M', 'N', 'M'],
  29: ['L', '<num>'],
  30: ['L', '<str>'],
  31: ['L', '<verdadeiro>'],
  32: ['L', '<falso>'],
  33: ['M', '<id>', 'M'],
  34: ['M', 'L', 'M'],
  35: ['M', 'O', '<id>', 'M'],
  36: ['M', 'O', 'L', 'M'],
  37: ['M', '/e/'],
  38: ['N', '<lop|>>'],
  39: ['N', '<lop|>=>'],
  40: ['N', '<lop|<>'],
  41: ['N', '<lop|<=>'],
  42: ['N', '<lop|=>'],
  43: ['N', '<lop|<>>'],
  44: ['N', '<lop|e>'],
  45: ['N', '<lop|ou>'],
  46: ['O', '<op|+>'],
  47: ['O', '<op|->'],
  48: ['O', '<op|*>'],
  49: ['O', '<op|/>'],
  50: ['O', '<op|mod>'],
  51: ['O', '<op|exp>'],
  52: ['O', 'N']
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
    B: {
      '<var>': 2,
      '<id>': 3,
      '<del|,>': 3,
      '<del|:>': 3,
      '<inicio>': 4
    },
    D: {
      '<var>': 5
    },
    F: {
      '<id>': 6,
      '<del|,>': 6,
      '/e/': 6
    },
    E: {
      '<inteiro>': 7,
      '<logico>': 8
    },
    G: {
      '<id>': 9,
      '<del|,>': 10,
      '<del|:>': 11,
      '<del|)>': 11
    },
    C: {
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
    H: {
      '<id>': 14,
      '<leia>': 15,
      '<escreva>': 16,
      '<se>': 17,
      '<para>': 19,
      '<enquanto>': 20
    },
    I: {
      '<id>': 22
    },
    J: {
      '<str>': 23,
      '<id>': 24,
      '<del|,>': 26,
      '<del|)>': 27
    },
    K: {
      '<id>': 28,
      '<num>': 28,
      '<str>': 28,
      '<verdadeiro>': 28,
      '<falso>': 28,
      '<op|+>': 28,
      '<op|->': 28,
      '<op|*>': 28,
      '<op|/>': 28,
      '<op|mod>': 28,
      '<op|exp>': 28,
      '<lop|>>': 28,
      '<lop|>=>': 28,
      '<lop|<>': 28,
      '<lop|<=>': 28,
      '<lop|=>': 28,
      '<lop|<>>': 28,
      '<lop|e>': 28,
      '<lop|ou>': 28,
      '/e/': 28
    },
    L: {
      '<num>': 29,
      '<str>': 30,
      '<verdadeiro>': 31,
      '<falso>': 32
    },
    M: {
      '<id>': 37,
      '<num>': 34,
      '<str>': 34,
      '<verdadeiro>': 34,
      '<falso>': 34,
      '<op|+>': 36,
      '<op|->': 36,
      '<op|*>': 36,
      '<op|/>': 36,
      '<op|mod>': 36,
      '<op|exp>': 36,
      '<lop|>>': 37,
      '<lop|>=>': 37,
      '<lop|<>': 37,
      '<lop|<=>': 37,
      '<lop|=>': 37,
      '<lop|<>>': 37,
      '<lop|e>': 37,
      '<lop|ou>': 37,
      '<leia>': 37,
      '<escreva>': 37,
      '<se>': 37,
      '<para>': 37,
      '<enquanto>': 37,
      '<fimalgoritmo>': 37,
      '<senao>': 37,
      '<fimpara>': 37,
      '<fimenquanto>': 37
    },
    N: {
      '<lop|>>': 38,
      '<lop|>=>': 39,
      '<lop|<>': 40,
      '<lop|<=>': 41,
      '<lop|=>': 42,
      '<lop|<>>': 43,
      '<lop|e>': 44,
      '<lop|ou>': 45
    },
    O: {
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

var alg = '<algoritmo> <str> <var> <id> <del|:> <inteiro> <var> <id> <del|:> <logico> <id> <del|,> <id> <del|:> <inteiro> <inicio> <id> <op|<-> <num> <id> <op|<-> <num> <para> <id> <de> <num> <ate> <num> <passo> <num> <faca> <escreva> <del|(> <id> <del|)> <leia> <del|(> <id> <del|)> <se> <sal> <lop|>> <num> <entao> <id> <op|<-> <id> <op|+> <num> <fimse> <fimpara> <escreva> <del|(> <id> <del|)> <fimalgoritmo>'.split(' ')

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
