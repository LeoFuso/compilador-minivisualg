// Special "empty" symbol.
var EPSILON = 'ε';

/**
 * Given a grammar builds a LL(1) parsing table based on the
 * First and Follow sets of this grammar.
 */
function buildParsingTable(grammar) {
	var parsingTable = {};

	for (var k in grammar) {
		var production = grammar[k];
		var LHS = getLHS(production);
		var RHS = getRHS(production);
		var productionNumber = Number(k);

		// Init columns for this non-terminal.
		if (!parsingTable[LHS]) {
			parsingTable[LHS] = {};
		}

		// All productions goes under the terminal column, if
		// this terminal is not epsilon.
		if (RHS[0] !== EPSILON) {
			var tttt = getFirstSetOfRHS(RHS);
			tttt.forEach(function (terminal) {
				parsingTable[LHS][terminal] = productionNumber;
			});
		} else {
			// Otherwise, this ε-production goes under the columns from
			// the Follow set.
			followSets[LHS].forEach(function (terminal) {
				parsingTable[LHS][terminal] = productionNumber;
			});
		}
	}

	return parsingTable;
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

	return firstSets[RHS[0]];
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
	3: ['F', '->', 'a'],
};

// See https://gist.github.com/DmitrySoshnikov/924ceefb1784b30c5ca6
// for the sets construction.

var firstSets = {
	'S' : [ 'a', '(' ],
	'F' : [ 'a' ],
	'a' : [ 'a' ],
	'(' : [ '(' ]
};

var followSets = {
	'S' : [ '$', '+' ],
	'F' : [ '$', '+', ')' ]
};

console.log(buildParsingTable(grammar));

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

var grammar = {
	1: ['E', '->', 'T', 'X'],
	2: ['X', '->', '+', 'T', 'X'],
	3: ['X', '->', 'ε'],
	4: ['T', '->', 'F', 'Y'],
	5: ['Y', '->', '*', 'F', 'Y'],
	6: ['Y', '->', 'ε'],
	7: ['F', '->', 'a'],
	8: ['F', '->', '(', 'E', ')'],
};

// See https://gist.github.com/DmitrySoshnikov/924ceefb1784b30c5ca6
// for the sets construction.

var firstSets = {
	'E': ['a', '('],
	'T': ['a', '('],
	'F': ['a', '('],
	'a': ['a'],
	'(': ['('],
	'X': ['+', 'ε'],
	'+': ['+'],
	'Y': ['*', 'ε'],
	'*': ['*'],
};

var followSets = {
	'E': ['$', ')'],
	'X': ['$', ')'],
	'T': ['+', '$', ')'],
	'Y': ['+', '$', ')'],
	'F': ['*', '+', '$', ')'],
};

console.log(buildParsingTable(grammar));

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