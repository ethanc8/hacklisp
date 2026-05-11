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
// Gets the value of the integer pointed to by o.
#define GET_INTEGER_VALUE(o) (RAM[o + 1])

#define IS_NIL(o) (EQ(o, atomStackBase))
#define IS_NONNIL(o) (NEQ(o, atomStackBase))

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
#define KEYCODE_EXCL 33
#define KEYCODE_QUOT 34
#define KEYCODE_NUM 35
#define KEYCODE_DOLLAR 36
#define KEYCODE_PERCENT 37
#define KEYCODE_AMPERSAND 38
#define KEYCODE_APOSTROPHE 39
#define KEYCODE_LEFTPAREN 40
#define KEYCODE_RIGHTPAREN 41
#define KEYCODE_ASTERISK 42
#define KEYCODE_PLUS 43
#define KEYCODE_COMMA 44
#define KEYCODE_MINUS 45
#define KEYCODE_DOT 46
#define KEYCODE_SLASH 47

#define KEYCODE_0 48
#define KEYCODE_1 49
#define KEYCODE_2 50
#define KEYCODE_3 51
#define KEYCODE_4 52
#define KEYCODE_5 53
#define KEYCODE_6 54
#define KEYCODE_7 55
#define KEYCODE_8 56
#define KEYCODE_9 57
#define IS_DIGIT(c) (GT(c, 47) and LT(c, 58))

#define KEYCODE_COLON 58
#define KEYCODE_SEMICOLON 59
#define KEYCODE_LT 60
#define KEYCODE_EQ 61
#define KEYCODE_GT 62
#define KEYCODE_QUESTION 63
#define KEYCODE_AT 64

#define KEYCODE_A 65
#define KEYCODE_B 66
#define KEYCODE_C 67
#define KEYCODE_D 68
#define KEYCODE_E 69
#define KEYCODE_F 70
#define KEYCODE_G 71
#define KEYCODE_H 72
#define KEYCODE_I 73
#define KEYCODE_J 74
#define KEYCODE_K 75
#define KEYCODE_L 76
#define KEYCODE_M 77
#define KEYCODE_N 78
#define KEYCODE_O 79
#define KEYCODE_P 80
#define KEYCODE_Q 81
#define KEYCODE_R 82
#define KEYCODE_S 83
#define KEYCODE_T 84
#define KEYCODE_U 85
#define KEYCODE_V 86
#define KEYCODE_W 87
#define KEYCODE_X 88
#define KEYCODE_Y 89
#define KEYCODE_Z 90
#define IS_UPPER(c) (GT(c, 64) and LT(c, 91))

#define KEYCODE_LSQB 91
#define KEYCODE_BACKSLASH 92
#define KEYCODE_RSQB 93
#define KEYCODE_CARET 94
#define KEYCODE_UNDERSCORE 95
#define KEYCODE_GRAVE 96

#define KEYCODE_a 97
#define KEYCODE_b 98
#define KEYCODE_c 99
#define KEYCODE_d 100
#define KEYCODE_e 101
#define KEYCODE_f 102
#define KEYCODE_g 103
#define KEYCODE_h 104
#define KEYCODE_i 105
#define KEYCODE_j 106
#define KEYCODE_k 107
#define KEYCODE_l 108
#define KEYCODE_m 109
#define KEYCODE_n 110
#define KEYCODE_o 111
#define KEYCODE_p 112
#define KEYCODE_q 113
#define KEYCODE_r 114
#define KEYCODE_s 115
#define KEYCODE_t 116
#define KEYCODE_u 117
#define KEYCODE_v 118
#define KEYCODE_w 119
#define KEYCODE_x 120
#define KEYCODE_y 121
#define KEYCODE_z 122
#define IS_LOWER(c) (GT(c, 96) and LT(c, 123))

#define KEYCODE_LCUB 123
#define KEYCODE_VERBAR 124
#define KEYCODE_RCUB 125
#define KEYCODE_TILDE 126

#if JACK
	#define KEYCODE_NEWLINE 128

	#define IS_WHITESPACE(c) ((c = KEYCODE_SPACE) | (c = KEYCODE_NEWLINE))
	#define IS_NEWLINE(c) (c = KEYCODE_NEWLINE)
#else
	#define KEYCODE_TAB 9
	#define KEYCODE_LF 10
	#define KEYCODE_VT 11
	#define KEYCODE_FF 12
	#define KEYCODE_CR 13

	#define IS_WHITESPACE(c) ((c == KEYCODE_SPACE) || (c == KEYCODE_TAB) || (c == KEYCODE_LF) || (c == KEYCODE_VT) || (c == KEYCODE_FF) || (c == KEYCODE_CR))
	#define IS_NEWLINE(c) ((c == KEYCODE_LF) || (c == KEYCODE_CR))
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

// An alist containing the builtin constants.
static Object builtins;

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

	#define read Main.read_
	#define nextToken Main.nextToken_

	#define printObject Main.printObject_
	#define printTail Main.printTail_
	#define debugObject Main.debugObject_

	#define parseObject Main.parseObject_

	#define cons Main.cons_
	#define parseList Main.parseList_

	#define STRING_to_i16 Main.STRING_to_i16_

	#define parseInteger Main.parseInteger_
	#define internInteger Main.internInteger_
	#define internSymbol Main.internSymbol_

	#define evcon Main.evcon_
	#define evlis Main.evlis_
	#define lookup Main.lookup_
	#define pairlis Main.pairlis_
	#define eval Main.eval_
	#define apply Main.apply_
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
	#define read read_
	Object read();

	#define printObject printObject_
	void printObject(Object o);
	#define printTail printTail_
	void printTail(Object o);
	#define debugObject debugObject_
	void debugObject(Object o);

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

	#define evcon evcon_
	Object evcon(Object, Object);
	#define evlis evlis_
	Object evlis(Object, Object);
	#define lookup lookup_
	Object lookup(Object, Object);
	#define pairlis pairlis_
	Object pairlis(Object, Object, Object);
	#define eval eval_
	Object eval(Object, Object);
	#define apply apply_
	Object apply(Object, Object, Object);
#endif

// MARK - Main function
#if JACK
function void main() {
#else
int main(int argc, char** argv) {
#endif
	#if JACK
		// Heap is 2048~16383
		let RAM = 0;

		let line = 2048; // 2048 to 2111 (64 characters)
		let curTok_data = 2112; // 2112 to 2175 (64 characters)
	#else
		let curTok_data = malloc(64);
	#endif

	let atomStackTop = atomStackBase;
	let pairStackTop = pairStackBase;

	// Intern builtin symbols
	#define NIL (atomStackBase + 0)
	let RAM[atomStackBase + 0] = KEYCODE_N;
	let RAM[atomStackBase + 1] = KEYCODE_I;
	let RAM[atomStackBase + 2] = KEYCODE_L;
	let RAM[atomStackBase + 3] = 0;
	#define TRUE (atomStackBase + 4)
	let RAM[atomStackBase + 4] = KEYCODE_T;
	let RAM[atomStackBase + 5] = KEYCODE_R;
	let RAM[atomStackBase + 6] = KEYCODE_U;
	let RAM[atomStackBase + 7] = KEYCODE_E;
	let RAM[atomStackBase + 8] = 0;
	#define kQuote (atomStackBase + 9)
	let RAM[atomStackBase + 9] = KEYCODE_q;
	let RAM[atomStackBase + 10] = KEYCODE_u;
	let RAM[atomStackBase + 11] = KEYCODE_o;
	let RAM[atomStackBase + 12] = KEYCODE_t;
	let RAM[atomStackBase + 13] = KEYCODE_e;
	let RAM[atomStackBase + 14] = 0;
	#define kCond (atomStackBase + 15)
	let RAM[atomStackBase + 15] = KEYCODE_c;
	let RAM[atomStackBase + 16] = KEYCODE_o;
	let RAM[atomStackBase + 17] = KEYCODE_n;
	let RAM[atomStackBase + 18] = KEYCODE_d;
	let RAM[atomStackBase + 19] = 0;
	#define kEq (atomStackBase + 20)
	let RAM[atomStackBase + 20] = KEYCODE_EQ;
	let RAM[atomStackBase + 21] = 0;
	#define kCons (atomStackBase + 22)
	let RAM[atomStackBase + 22] = KEYCODE_c;
	let RAM[atomStackBase + 23] = KEYCODE_o;
	let RAM[atomStackBase + 24] = KEYCODE_n;
	let RAM[atomStackBase + 25] = KEYCODE_s;
	let RAM[atomStackBase + 26] = 0;
	#define kAtom (atomStackBase + 27)
	let RAM[atomStackBase + 27] = KEYCODE_a;
	let RAM[atomStackBase + 28] = KEYCODE_t;
	let RAM[atomStackBase + 29] = KEYCODE_o;
	let RAM[atomStackBase + 30] = KEYCODE_m;
	let RAM[atomStackBase + 31] = KEYCODE_QUESTION;
	let RAM[atomStackBase + 32] = 0;
	#define kHead (atomStackBase + 33)
	let RAM[atomStackBase + 33] = KEYCODE_h;
	let RAM[atomStackBase + 34] = KEYCODE_e;
	let RAM[atomStackBase + 35] = KEYCODE_a;
	let RAM[atomStackBase + 36] = KEYCODE_d;
	let RAM[atomStackBase + 37] = 0;
	#define kTail (atomStackBase + 38)
	let RAM[atomStackBase + 38] = KEYCODE_t;
	let RAM[atomStackBase + 39] = KEYCODE_a;
	let RAM[atomStackBase + 40] = KEYCODE_i;
	let RAM[atomStackBase + 41] = KEYCODE_l;
	let RAM[atomStackBase + 42] = 0;
	#define kLambda (atomStackBase + 43)
	let RAM[atomStackBase + 43] = KEYCODE_l;
	let RAM[atomStackBase + 44] = KEYCODE_a;
	let RAM[atomStackBase + 45] = KEYCODE_m;
	let RAM[atomStackBase + 46] = KEYCODE_b;
	let RAM[atomStackBase + 47] = KEYCODE_d;
	let RAM[atomStackBase + 48] = KEYCODE_a;
	let RAM[atomStackBase + 49] = 0;
	#define kRead (atomStackBase + 50)
	let RAM[atomStackBase + 50] = KEYCODE_r;
	let RAM[atomStackBase + 51] = KEYCODE_e;
	let RAM[atomStackBase + 52] = KEYCODE_a;
	let RAM[atomStackBase + 53] = KEYCODE_d;
	let RAM[atomStackBase + 54] = 0;
	#define kPrint (atomStackBase + 55)
	let RAM[atomStackBase + 55] = KEYCODE_p;
	let RAM[atomStackBase + 56] = KEYCODE_r;
	let RAM[atomStackBase + 57] = KEYCODE_i;
	let RAM[atomStackBase + 58] = KEYCODE_n;
	let RAM[atomStackBase + 59] = KEYCODE_t;
	let RAM[atomStackBase + 60] = 0;
	#define kInteger (atomStackBase + 61)
	let RAM[atomStackBase + 61] = KEYCODE_i;
	let RAM[atomStackBase + 62] = KEYCODE_n;
	let RAM[atomStackBase + 63] = KEYCODE_t;
	let RAM[atomStackBase + 64] = KEYCODE_e;
	let RAM[atomStackBase + 65] = KEYCODE_g;
	let RAM[atomStackBase + 66] = KEYCODE_e;
	let RAM[atomStackBase + 67] = KEYCODE_r;
	let RAM[atomStackBase + 68] = KEYCODE_QUESTION;
	let RAM[atomStackBase + 69] = 0;

	let atomStackTop = atomStackBase + 70;

	// (
	//   (NIL . NIL)
	//   (TRUE . TRUE)
	// )
	let builtins = cons(
		cons(NIL, NIL),
		cons(
			cons(TRUE, TRUE),
			NIL
		)
	);
	

	let curTok_length = 3;

	do internSymbol();

	// User interface

	#if !JACK
		if(argc > 1) {
			// Following was written by Claude.
			FILE* f = fopen(argv[1], "rb");
			if (!f) {
				throw_error("Could not open file!");
			}

			// Seek to end to get file size
			fseek(f, 0, SEEK_END);
			long size = ftell(f);
			rewind(f);  // or fseek(f, 0, SEEK_SET)

			// Allocate buffer (+1 for optional null terminator)
			let line = malloc(size + 1);
			if (!line) {
					fclose(f);
					throw_error("Could not alloc enough memory to store the file");
			}

			// Read the entire file in one shot
			long bytes_read = fread(line, 1, size, f);
			fclose(f);

			if (bytes_read != size) {
					free(line);
					throw_error("Number of bytes read from the file != size of the file");
			}

			line[size] = '\0';  // Null-terminate (safe for text files)

			do nextToken();
			do eval(parseObject(), builtins);
		} else
	#endif
	if(YES) {
		do print_literal("HackLISP-0");
		do newline();
		while(YES) {
			do print_literal("> ");
			do printObject(eval(read(), builtins));
			do newline();
		}
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

// Reads a line, and returns it after parsing.
function Object read_() {
	#if JACK
		var i16 i;
		var char c;

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
		let line = readline("");
	#endif

	let curTok_idx = 0;
	do nextToken();
	return parseObject();
}

function void printObject_(Object o) {
	if(IS_ATOM(o)) {
		if(IS_INTEGER(o)) {
			do print_i16(GET_INTEGER_VALUE(o));
		} else {
			do print_i16_ptr_as_string(o);
		}
	} else {
		do print_literal("(");
		do printObject(head(o));
		do printTail(tail(o));
		do print_literal(")");
	}

	return;
}

function void printTail_(Object o) {
  if(IS_NIL(o)) {
    // proper list end — print nothing, the ")" is added by the caller
		return;
  }

	if(IS_ATOM(o)) {
    // improper list — fall back to dot notation for the tail
    do print_literal(" . ");
    do printObject(o);
		return;
  }
	
	// another cons cell — continue the list with a space
	do print_literal(" ");
	do printObject(head(o));
	do printTail(tail(o));
	return;
}

function void debugObject_(Object o) {
	if(IS_ATOM(o)) {
		if(IS_INTEGER(o)) {
			do print_literal("[INTEGER at ");
			do print_i16(o);
			do print_literal("]");

			do print_i16(GET_INTEGER_VALUE(o));
		} else {
			do print_literal("[SYMBOL at ");
			do print_i16(o);
			do print_literal("]");

			do print_i16_ptr_as_string(o);
		}
	} else {
		do print_literal("[LIST at ");
		do print_i16(o);
		do print_literal("]");

		do print_literal("(");
		do debugObject(head(o));
		do print_literal(" . ");
		do debugObject(tail(o));
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

	// Eat comments
	if(EQ(c, KEYCODE_SEMICOLON)) {
		while(not (IS_NEWLINE(c) or EQ(c, 0))) {
			let curTok_idx = curTok_idx + 1;

			let c = line[curTok_idx];
		}
		return nextToken();
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

// Evaluates a conditional expression c, in the environment env.
// c is a list of (TEST BODY) [non-dotted] lists
//   i.e. (TEST . (BODY . NIL))
// env is, of course, an environment specified as an alist.
//
// evcon iterates in order through the elements of c and 
// evals the first expression of each pair. If it returns a nonnull
// value, the body is evaluated and returned. 
function Object evcon_(Object c, Object env) {

	// This is reversed, because it's cheaper to check for nil
	// than to check for nonnil.
	// i.e. the nil branch is what was the else branch in LISP 1.5
  if(IS_NIL(eval(head(head(c)), env))) {
		// T -> evcon[cdr[c];a]]
		// If it's nil, go on to the next expression
		return evcon(tail(c), env);
  } else {
		// [eval[caar[c];a] -> eval[cadar[c];a];
		// The result is nonnil, so evaluate and return the BODY.
    return eval(head(tail(head(c))), env);
  }
}

// Loops through each expression in exprs and evaluates it.
// Returns a list of the evaluated expressions.
// 
// Examples:
//   (evlis '(a b c) '((a . 1)(b . 2)(c . 3)) -> '(1 2 3)
function Object evlis_(Object exprs, Object env) {
	// LISP 1.5:
	//   evlis[m;a] = [null[m] -> NIL;
	//                 T -> cons [eval[car [m];a];evlis[cdr [m];a]]]
	if(IS_NIL(exprs)) {
		return NIL;
	} else {
		// Evaluate the first expression, then
		// hand the tail off to evlis.
		return cons(eval(head(exprs), env),
                  evlis(tail(exprs), env));
	}
}

// Searches an alist for a given key.
// Returns the value for said key.
//
// Called "assoc" in some implementations.
function Object lookup_(Object key, Object alist) {
	if(EQ(alist, NIL)) {
		do print_literal("Attempted to lookup `");
		do printObject(key);
		do print_literal("`");
		do newline();
		do throw_error("Lookup failed.");
	}
	// If the first key-value pair in alist matches,
	// then return the value.
  if(EQ(key, head(head(alist)))) {
		return tail(head(alist));
	}

	// Otherwise, search the tail of the list.
  return lookup(key, tail(alist));
}

// "Zips" two lists (x and y) together, and appends a.
// 
// Example:
//   pairlis[(A B C); (U V W); ((D . X) (E . Y))] =
//     ((A . U) (B . V) (C . W) (D . X) (E . Y))
// 
// From LISP 1.5 manual:
//   This function gives the list of pairs of corresponding elements of
//   the lists x and y, and appends this to the list a.
function Object pairlis_(Object x, Object y, Object a) {
	// In LISP 1.5:
	//   pairlis [x; y; a] = [
	//     null[x] -> a; 
	//     T -> cons[cons[car[x]; car[y]];
  //               pairlis[cdr[x]; cdr [y]; a]]
	//   ]

	// If x is nil, just return the thing to append to.
  if(IS_NIL(x)) {
		return a;
	} else {
		// Zip the first two terms, then
		// hand the tails of both lists back to pairlis.
		return cons(cons(head(x), head(y)),
		            pairlis(tail(x), tail(y), a));
	}
}

// Evaluates the expression e in the environment env.
// env is an alist (association list) -- a list of (key . value) pairs
function Object eval_(Object e, Object env) {
	// print_literal("dbg: (eval e:");
	// printObject(e);
	// print_literal(" env:");
	// printObject(env);
	// print_literal(")");
	// newline();

  if (IS_NIL(e)) { return e; }
	if (IS_INTEGER(e)) { return e; }
  if (IS_ATOM(e)) { return lookup(e, env); }

	// If e is a list (quote ___), return ___.
	// We use head(tail(e)) because it's actually (quote . (___ . NIL))
  if (EQ(head(e), kQuote)) { return head(tail(e)); }

	// If e is a conditional, punt to evcon to evaluate it.
  if (EQ(head(e), kCond)) { return evcon(tail(e), env); }

	// If the above fails,
	//   head(e) is the first item (so the function name)
	//   use evlis to evaluate the rest of the items
	//   call apply to apply the function against the values
  return apply(head(e), evlis(tail(e), env), env);
}

// Applies the function f to the argument x, in the environment env.
function Object apply_(Object f, Object x, Object env) {
	// print_literal("dbg: (apply f:");
	// printObject(f);
	// print_literal(" x:");
	// printObject(x);
	// print_literal(" env:");
	// printObject(env);
	// print_literal(")");
	// newline();


	// If the first element is a list...
	// We assume f is a lambda-expression of form
	//   (lambda ARGS RETVAL)
	// then run: (LISP 1.5)
	//   eval[RETVAL; pairlis[ARGS; x; env]]
	// i.e. we use pairlis to bind the args in the environment,
	// then evaluate it.
	//
	// We skip checking that it starts with `lambda` to reduce the code size
	// and the runtime.
  if(IS_PAIR(f)) {
		return eval(head(tail(tail(f))), pairlis(head(tail(f)), x, env));
	}

	// Otherwise it's probably a builtin.
	if(EQ(f, kEq)) {
		if(EQ(head(x), head(tail(x)))) {
			return TRUE;
		} else {
			return NIL;
		}
	}
  if(EQ(f, kCons)) {
		return cons(head(x), head(tail(x)));
	}
	if(EQ(f, kInteger)) {
		if(IS_INTEGER(head(x))) {
			return TRUE;
		} else {
			return NIL;
		}
	}
  if(EQ(f, kAtom)) {
		if(IS_ATOM(head(x))) {
			return TRUE;
		} else {
			return NIL;
		}
	}
  if(EQ(f, kHead)) {
		return head(head(x));
	}
  if(EQ(f, kTail)) {
		return tail(head(x));
	}
	if(EQ(f, kRead)) {
		return read();
	}
	if(EQ(f, kPrint)) {
		if(IS_NIL(x)) {
			do newline();
		} else {
			do printObject(head(x));
		}
		return x;
	}
	

	// Otherwise assume f is a variable bound to some function or builtin.
  return apply(lookup(f, env), x, env);
}


#if JACK
	} // class Main
#endif
