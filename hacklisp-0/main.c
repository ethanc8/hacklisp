// MARK - Basic syntax
#if JACK
	#define i16 int
	#define _Noreturn

	class Main {
#else
	#include <stdio.h>
	#include <inttypes.h>
	#include <readline/readline.h>
	#include <stdlib.h>

	#define function
	#define var
	#define let
	#define do
	#define static

	#define i16 int16_t

	typedef i16* Array;
#endif // JACK

// MARK - Operator definitions
#if JACK
	#define EQ(a, b) (a = b)	
	#define NEQ(a, b) (~(a = b))
	#define LT(a, b) (a < b)	
	#define LEQ(a, b) (~(a > b))
	#define GT(a, b) (a > b)	
	#define GEQ(a, b) (~(a < b))

	#define and &
	#define or |
	#define not ~
#else
	#define EQ(a, b) (a == b)	
	#define NEQ(a, b) (a != b)
	#define LT(a, b) (a < b)	
	#define LEQ(a, b) (a <= b)
	#define GT(a, b) (a > b)	
	#define GEQ(a, b) (a >= b)

	#define and &&
	#define or ||
	#define not !
#endif

// MARK - Type/enum definitions
// STRING is an array of char, not the Jack String class
#if JACK
	#define STRING Array
#else
	typedef char* STRING;
#endif

// The address of the object, relative to RAM.
#define Object i16
// same as car and cdr, for a pair
#define head(o) RAM[o]
#define tail(o) RAM[o + 1]

// checks if an object is on atom or pair stack
#define IS_ATOM(o) (o > pairStackBase)
#define IS_PAIR(o) (o < atomStackBase)

#define TAG_INTEGER -1

#define IS_INTEGER(o) (EQ(RAM[o], TAG_INTEGER))

#define NIL atomStackBase
#define nilp(o) (EQ(o, atomStackBase))

#define TokenType i16
#define TokenType_LeftParen 0
#define TokenType_RightParen 1
#define TokenType_Symbol 2
#define TokenType_Integer 3
#define TokenType_Dot 4

#define BOOL i16

#if JACK
	#define YES -1
	#define NO 0
#else
	#define YES (BOOL)1
	#define NO 0
#endif

// Keycodes - ASCII 32 to 127
#define KEYCODE_SPACE 32
#define KEYCODE_LEFTPAREN 40
#define KEYCODE_RIGHTPAREN 41
#define KEYCODE_DOT 46

#define KEYCODE_0 48
#define KEYCODE_9 57
#define IS_DIGIT(c) (GT(c, 47) and LT(c, 58))

#define KEYCODE_A 65
#define KEYCODE_N 78
#define KEYCODE_I 73
#define KEYCODE_L 76
#define KEYCODE_Z 90
#define IS_UPPER(c) (GT(c, 64) and LT(c, 91))

#define KEYCODE_a 97
#define KEYCODE_z 122
#define IS_LOWER(c) (GT(c, 96) and LT(c, 123))

#if JACK
	#define KEYCODE_NEWLINE 128

	#define IS_WHITESPACE(c) ((c = KEYCODE_SPACE) | (c = KEYCODE_NEWLINE))
#else
	#define KEYCODE_TAB 9
	#define KEYCODE_LF 10
	#define KEYCODE_LT 11
	#define KEYCODE_FF 12
	#define KEYCODE_CR 32

	#define IS_WHITESPACE(c) ((c == KEYCODE_SPACE) || (c == KEYCODE_TAB) || (c == KEYCODE_LF) || (c == KEYCODE_LT) || (c == KEYCODE_FF) || (c == KEYCODE_CR))
#endif

// MARK - Global variables
#if JACK
	// Pointer to 0
	static Array RAM;
#else
	// Pointer to 0
	i16 RAM[24577];
#endif

// The line currently being processed
static STRING line;

// The type of the current token
static TokenType curTok_type;
// The length of the current token
static i16 curTok_length;
// The data of the current token
static STRING curTok_data;
// The location of the token in the line that it was processed in
static i16 curTok_idx;

// Reserve 2048~2239 (64*3 words) for interpreter internal state

// 2240~16383 is left
#define atomStackBase 9312
#define pairStackBase 9310

static Object atomStackTop;
static Object pairStackTop;

// MARK - Function declarations

#if JACK
	#define print_i16 Main.print_i16_
	#define print_Array_as_ptr Main.print_Array_as_ptr_
	#define print_i16_ptr_as_string Main.print_i16_ptr_as_string_
	#define print_char Main.print_char_
	#define print_STRING Main.print_STRING_
	#define print_STRING_length Main.print_STRING_length_
	#define println_STRING Main.println_STRING_

	#define print_literal Main.print_literal_
	#define println_literal Main.println_literal_
	#define throw_error Main.throw_error_

	#define newline Main.newline_

	#define processLine Main.processLine_
	#define nextToken Main.nextToken_

	#define printObject Main.printObject_
	#define parseObject Main.parseObject_

	#define cons Main.cons_
	#define parseList Main.parseList_

	#define STRING_to_i16 Main.STRING_to_i16_

	#define parseInteger Main.parseInteger_
	#define internInteger Main.internInteger_
	#define internSymbol Main.internSymbol_
#else
	#define print_i16 print_i16_
	void print_i16(i16 x);
	#define print_Array_as_ptr print_Array_as_ptr_
	void print_Array_as_ptr(Array x);
	#define print_i16_ptr_as_string print_i16_ptr_as_string_
	void print_i16_ptr_as_string(i16 x);
	#define print_char print_char_
	void print_char(char c);
	#define print_STRING print_STRING_
	void print_STRING(STRING s);
	#define print_STRING_length print_STRING_length_
	void print_STRING_length(STRING s, i16 length);
	#define println_STRING println_STRING_
	void println_STRING(STRING s);

	#define print_literal print_literal_
	void print_literal(STRING s);
	#define println_literal println_literal_
	void println_literal(STRING s);
	#define throw_error throw_error_
	_Noreturn void throw_error(STRING s);

	#define newline newline_
	void newline();

	#define nextToken nextToken_
	BOOL nextToken();
	#define processLine processLine_
	void processLine();

	#define printObject printObject_
	void printObject(Object o);

	#define parseObject parseObject_
	Object parseObject();

	#define parseObject parseObject_
	Object parseObject();
	#define cons cons_
	Object cons(Object head, Object tail);
	#define parseList parseList_
	Object parseList();

	#define STRING_to_i16 STRING_to_i16_
	i16 STRING_to_i16(STRING s, i16 length);

	#define parseInteger parseInteger_
	Object parseInteger();
	#define internInteger internInteger_
	Object internInteger(i16 x);
	#define internSymbol internSymbol_
	Object internSymbol();
#endif

// MARK - Main function
#if JACK
function void main() {
#else
int main(int argc, char** argv) {
#endif
	#if JACK
		var char c;
		var i16 i;

		// Heap is 2048~16383
		let RAM = 0;

		let line = 2048; // 2048 to 2111 (64 characters)
		let curTok_data = 2112; // 2112 to 2175 (64 characters)
	#else
		let curTok_data = malloc(64);
	#endif

	let atomStackTop = atomStackBase;
	let pairStackTop = pairStackBase;

	// Intern "NIL"
	let curTok_data[0] = KEYCODE_N;
	let curTok_data[1] = KEYCODE_I;
	let curTok_data[2] = KEYCODE_L;

	let curTok_length = 3;

	do internSymbol();

	// User interface
	do println_literal("HackLISP-0");

	while(YES) {
		#if JACK
			do Output.printString("> ");
			let i = 0;

			let c = Keyboard.readChar();
			while(NEQ(c, KEYCODE_NEWLINE) and LEQ(i, 62)) {
				let line[i] = c;

				let i = i + 1;
				let c = Keyboard.readChar();
			}
			let line[i] = 0;
			do Output.println();
		#else
			let line = readline("> ");
		#endif

		do processLine();
	}
	#if JACK
		return;
	#else
		return 0;
	#endif
}

// MARK - Normal functions

// Prints the character c.
function void print_i16_(i16 x) {
	#if JACK
		do Output.printInt(x);
	#else
		do printf("%"PRIi16, x);
	#endif
	return;
}

// Prints the character c.
function void print_Array_as_ptr_(Array x) {
	#if JACK
		do Output.printInt(x);
	#else
		do printf("%p", x);
	#endif
	return;
}

// Prints the character c.
function void print_i16_ptr_as_string_(i16 s) {
	var char c;
	var i16 i;

	let i = 0;

	let c = RAM[s + i];
	while(NEQ(c, 0)) {
		#if JACK
			do Output.printChar(c);
		#else
			do putchar(c);
		#endif

		let i = i + 1;
		let c = RAM[s + i];
	}
	return;
}

// Prints the character c.
function void print_char_(char c) {
	#if JACK
		do Output.printChar(c);
	#else
		do putchar(c);
	#endif
	return;
}

// Prints the string s until '\0'
function void print_STRING_(STRING s) {
	#if JACK
		var char c;
		var i16 i;

		let i = 0;

		let c = s[i];
		while(NEQ(c, 0)) {
			do Output.printChar(c);

			let i = i + 1;
			let c = s[i];
		}
	#else
		do fputs(s, stdout);
	#endif
	return;
}

// Prints the string s of the given length
function void print_STRING_length_(STRING s, i16 length) {
	var char c;
	var i16 i;

	let i = 0;

	let c = s[i];
	while(i < length) {
		#if JACK
			do Output.printChar(c);
		#else
			do putchar(c);
		#endif

		let i = i + 1;
		let c = s[i];
	}
	return;
}

// Prints the string s and starts a new line in the output.
function void println_STRING_(STRING s) {
	#if JACK
		var char c;
		var i16 i;

		let i = 0;

		let c = s[i];
		while(NEQ(c, 0)) {
			do Output.printChar(c);

			let i = i + 1;
			let c = s[i];
		}

		do Output.println();
	#else
		do fputs(s, stdout);
		do putchar('\n');
	#endif
	return;
}

// Prints the given string literal to the console
#if JACK
	function void print_literal_(String s) {
		do Output.printString(s);
		return;
	}

	function void println_literal_(String s) {
		do Output.printString(s);
		do Output.println();
		return;
	}
#else
	function void print_literal_(STRING s) {
		do fputs(s, stdout);
		return;
	}
	function void println_literal_(STRING s) {
		do fputs(s, stdout);
		do putchar('\n');
		return;
	}
#endif

// Prints the given error message to the console, and exits the program.
#if JACK
	function void throw_error_(String s) {
		do Output.println();
		do Output.printString("ERROR: ");
		do Output.printString(s);
		do Output.println();
		do Sys.halt();
		return;
	}
#else
	function void throw_error_(STRING s) {
		do fprintf(stderr, "\nERROR: %s\n", s);
		do exit(1);
	}
#endif

// Starts a new line in the output.
function void newline_() {
	#if JACK
		do Output.println();
	#else
		do putchar('\n');
	#endif
	return;
}

// Processes the line stored in the global variable `line`.
function void processLine_() {
	var Object object;

	let curTok_idx = 0;
	// // Debugging the tokenizer
	// while(nextToken()) {
	// 	do print_STRING_length(curTok_data, curTok_length);
	// 	do print_char(KEYCODE_SPACE);
	// 	// printf("type %"PRIi16" value `%.*s`\n", curTok_type, curTok_length, curTok_data);
	// }

	do nextToken();
	let object = parseObject();

	do printObject(object);

	// if(IS_INTEGER(object)) {
	// 	do print_literal("Integer ");
	// 	do print_i16(object);
	// 	do print_literal(" value '");
	// 	do print_i16(RAM[object + 1]);
	// 	do print_literal("'");
	// } else {
	// 	do print_literal("Symbol ");
	// 	do print_i16(object);
	// 	do print_literal(" value '");
	// 	do print_i16_ptr_as_string(object);
	// 	do print_literal("'");
	// }

	do newline();

	return;
}

function void printObject_(Object o) {
	if(IS_ATOM(o)) {
		if(IS_INTEGER(o)) {
			do print_i16(RAM[o + 1]);
		} else {
			do print_i16_ptr_as_string(o);
		}
	} else {
		do print_literal("(");
		do printObject(head(o));
		do print_literal(" . ");
		do printObject(tail(o));
		do print_literal(")");
	}

	return;
}

// Returns the address of the object starting with curTok.
function Object parseObject_() {
	if(EQ(curTok_type, TokenType_LeftParen)) {
		return parseList();
	}

	if(EQ(curTok_type, TokenType_Integer)) {
		return parseInteger();
	}

	if(EQ(curTok_type, TokenType_Symbol)) {
		return internSymbol();
	}

	do throw_error("parseObject: Object must be a list, integer, or symbol");
	return 0;
}

// Builds a pair with the given head and tail.
function Object cons_(Object head, Object tail) {
	var Object pair;

	let pair = pairStackTop;

	let head(pair) = head;
	let tail(pair) = tail;

	let pairStackTop = pairStackTop - 2;

	return pair;
}

// Turns the list starting with curTok into a linked list.
// curTok can either be `(`, or part of a previous list.
// It will advance curTok to the next token, and treat that next token
// as the head of the list.
// At the end of this function, curTok will be `)`.
function Object parseList_() {
	var Object tail;

	// curTok is `(`
	if(nextToken()) {
		// curTok is now the head.

		// If it's a dot, return the thing after the dot.
		if(EQ(curTok_type, TokenType_Dot)) {
			if(nextToken()) {
				let tail = parseObject();
				if(nextToken()) {
					if(EQ(curTok_type, TokenType_RightParen)) {
						return tail;
					} else {
						do throw_error("parseList: Dotted list must end with closing parenthesis after the tail");
						return NIL;
					}
				} else {
					do throw_error("parseList: Dotted list must end with closing parenthesis after the tail");
					return NIL;
				}
			} else {
				do throw_error("parseList: There is nothing after the dot");
				return NIL;
			}
		}

		// If it's a right paren, this must be the tail of some list
		// so we return NIL.
		// Empty lists are equivalent to NIL.
		if(EQ(curTok_type, TokenType_RightParen)) {
			return NIL;
		}

		return cons(parseObject(), parseList());
	} else {
		do throw_error("parseList: Reached end of input; perhaps you forgot a closing parenthesis?");
		return NIL;
	}
}

// Converts a STRING with some length to a nonnegtive integer.
function i16 STRING_to_i16_(STRING s, i16 length) {
	var int retval;
	var int i;

	let retval = 0;
	let i = 0;

	if(EQ(length, 0)) {
		return 0;
	}

	while(i < length) {
		// Check for nonnumeric characters
		if(s[i] > 57) {
			return retval;
		}
		if(s[i] < 48) {
			return retval;
		}
		// ASCII 48 is "0"
		let retval = retval * 10 + (s[i] - 48);

		let i = i + 1;
	}

	return retval;
}

// Interns the integer at curTok onto the atom stack. 
function Object parseInteger_() {
	return internInteger(STRING_to_i16(curTok_data, curTok_length));
}

// Interns the passed integer onto the atom stack. 
function Object internInteger_(i16 x) {
	var Object stackIdx;
	var Object retval;
	var BOOL shouldBreak;

	// Try to find the integer in the atom stack.
	let stackIdx = atomStackBase;
	let shouldBreak = NO;
	// Loop through the characters on the atom stack
	while(LT(stackIdx, atomStackTop)) {
		if(EQ(RAM[stackIdx], TAG_INTEGER)) {
			if(EQ(RAM[stackIdx + 1], x)) {
				return stackIdx; // point to TAG_INTEGER
			}
			let stackIdx = stackIdx + 3; // skip tag + value + null
		} else {
			// skip symbol
			while(NEQ(RAM[stackIdx], 0)) {
				let stackIdx = stackIdx + 1;
			}
			let stackIdx = stackIdx + 1; // eat the null
		}
	}

	let retval = atomStackTop;

	// Let's intern the symbol now.
	let RAM[atomStackTop] = TAG_INTEGER;
	let RAM[atomStackTop + 1] = x;

	// Add null terminator
	// We need this so that the symbol interning works properly.
	let RAM[atomStackTop + 2] = 0;

	let atomStackTop = atomStackTop + 3;
	return retval;
}

// Interns the symbol at curTok onto the atom stack. 
function Object internSymbol_() {
	var Object stackIdx;
	var i16 tokIdx;
	var Object retval;
	var BOOL shouldBreak;

	// Try to find the symbol in the atom stack.
	let stackIdx = atomStackBase;
	let tokIdx = 0;
	let shouldBreak = NO;
	// Loop through the characters on the atom stack
	while(LT(stackIdx, atomStackTop)) {
		let tokIdx = 0;
		let shouldBreak = NO;

		// Loop through the token
		while(LT(tokIdx, curTok_length) and (not shouldBreak)) {
			// Break if mismatch
			if(NEQ(RAM[stackIdx], curTok_data[tokIdx])) {
				let shouldBreak = YES;
			} else { // Then they match up to this point
				// Advance both stackIdx and tokIdx
				let stackIdx = stackIdx + 1;
				let tokIdx = tokIdx + 1;
			}
		}

		// If we got here without breaking, then it matched, so return the
		// already-interned symbol
		if(not shouldBreak) {
			if(EQ(RAM[stackIdx], 0)) {
        return stackIdx - tokIdx;
			}
			// else: token is a prefix of this stack symbol, not a match
			// fall through to skip
		}

		// Skip remainder of the non-matching symbol.
		while(NEQ(RAM[stackIdx], 0) and LT(stackIdx, atomStackTop)) {
			let stackIdx = stackIdx + 1;
		}

		// stackIdx now points to the last null in this symbol. Increment it by 1 to point to the next thing.
		let stackIdx = stackIdx + 1;
	}

	// If we got here, there were no matches.
	let tokIdx = 0;
	let retval = stackIdx;

	// Let's intern the symbol now.
	while(LT(tokIdx, curTok_length)) {
		let RAM[stackIdx] = curTok_data[tokIdx];

		// Advance both stackIdx and tokIdx
		let stackIdx = stackIdx + 1;
		let tokIdx = tokIdx + 1;
	}

	// Add null terminator
	let RAM[stackIdx] = 0;

	let atomStackTop = stackIdx + 1;
	return retval;
}

// Starts tokenizing line at curTok_idx
// Puts the next token into curTok (type, length, data)
// Returns YES if there is another token, otherwise NO
function BOOL nextToken_() {
	var char c;

	// Eat whitespace
	let c = line[curTok_idx];
	while(IS_WHITESPACE(c)) {
		let curTok_idx = curTok_idx + 1;

		let c = line[curTok_idx];
	}

	// Check if end of string
	if(EQ(c, 0)) {
		return NO;
	}

	let curTok_data = line + curTok_idx;

	// Check for `(` or `)`
	if(EQ(c, KEYCODE_LEFTPAREN)) {
		let curTok_length = 1;
		let curTok_type = TokenType_LeftParen;

		let curTok_idx = curTok_idx + 1;
		return YES;
	}

	if(EQ(c, KEYCODE_RIGHTPAREN)) {
		let curTok_length = 1;
		let curTok_type = TokenType_RightParen;

		let curTok_idx = curTok_idx + 1;
		return YES;
	}

	if(EQ(c, KEYCODE_DOT)) {
		let curTok_length = 1;
		let curTok_type = TokenType_Dot;

		let curTok_idx = curTok_idx + 1;
		return YES;
	}

	// It's integer or symbol.
	let curTok_length = 0;
	
	// Integer constant
	if(IS_DIGIT(c)) {
		let curTok_type = TokenType_Integer;

		while(IS_DIGIT(c)) {
			let curTok_length = curTok_length + 1;

			let curTok_idx = curTok_idx + 1;
			let c = line[curTok_idx];
		}

		// Make sure the next thing is whitespace or a paren, or the end.
		if(not(IS_WHITESPACE(c) or EQ(c, KEYCODE_LEFTPAREN) or EQ(c, KEYCODE_RIGHTPAREN) or EQ(c, 0))) {
			do throw_error("Integer constant must be followed by whitespace or paren.");
		}

		return YES;
	}

	// Otherwise it's a symbol.
	// Symbols can have any ASCII characters other than ( ),
	// and must not start with a number.
	
	let curTok_type = TokenType_Symbol;

	while(not(IS_WHITESPACE(c) or EQ(c, KEYCODE_LEFTPAREN) or EQ(c, KEYCODE_RIGHTPAREN) or EQ(c, 0))) {
		let curTok_length = curTok_length + 1;

		let curTok_idx = curTok_idx + 1;
		let c = line[curTok_idx];
	}

	return YES;
}


#if JACK
	} // class Main
#endif
