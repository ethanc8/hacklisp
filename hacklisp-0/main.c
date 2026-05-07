// MARK - Basic syntax
#if JACK
	#define i16 int
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

#define Atom i16

#define Error i16
#define Error_OK 0
#define Error_Syntax 1

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

static Error error;



// MARK - Function declarations

#if JACK
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

#else
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
	#define println_literal print_literal_
	void println_literal(STRING s);
	#define throw_error throw_error_
	void throw_error(STRING s);

	#define newline newline_
	void newline();

	#define nextToken nextToken_
	BOOL nextToken();
	#define processLine processLine_
	void processLine();
	#define nextToken nextToken_
	BOOL nextToken();
#endif

// MARK - Main function
#if JACK
function void main() {
	var char c;
	var i16 i;

	// 2048 is the base of the heap
	let RAM = 0;
	let line = 2048; // 2048 to 2111 (64 characters)
	let curTok_data = 2112; // 2112 to 2175 (64 characters)

	let error = Error_OK;

	let curTok_idx = 0;

	do Output.printString("HackLISP-0");
	do Output.println();

	while(YES) {
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

		let curTok_idx = 0;

		do processLine();
	}
	return;
}
#else
int main(int argc, char** argv) {
	let curTok_data = malloc(64);

	let error = Error_OK;

	let curTok_idx = 0;

	do printf("HackLISP-0\n");
	while(YES) {
		let line = readline("> ");
		let curTok_idx = 0;

		do processLine();
	}
}
#endif

// MARK - Normal functions

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
		var int i;

		let i = 0;

		let c = s[i];
		while(NEQ(c, 0)) {
			do Output.printChar(c);

			let i = i + 1;
			let c = s[i];
		}
	#else
		do puts(s);
	#endif
	return;
}

// Prints the string s of the given length
function void print_STRING_length_(STRING s, i16 length) {
	var char c;
	var int i;

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
		var int i;

		let i = 0;

		let c = s[i];
		while(NEQ(c, 0)) {
			do Output.printChar(c);

			let i = i + 1;
			let c = s[i];
		}

		do Output.println();
	#else
		do puts(s);
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
		do puts(s);
		return;
	}
	function void println_literal_(STRING s) {
		do puts(s);
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
		return;
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
	while(nextToken()) {
		// Debugging the tokenizer
		do print_STRING_length(curTok_data, curTok_length);
		do print_char(KEYCODE_SPACE);
		// printf("type %"PRIi16" value `%.*s`\n", curTok_type, curTok_length, curTok_data);
	}

	do newline();

	return;
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
