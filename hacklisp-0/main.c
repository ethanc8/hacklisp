// MARK - Basic syntax
#if JACK
	#define i16 int
	class Main {
#else
	#include <stdio.h>
	#include <inttypes.h>
	#include <readline/readline.h>

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

#define BOOL i16

#if JACK
	#define YES -1
	#define NO 0
#else
	#define YES (BOOL)1
	#define NO 0
#endif

#define KEYCODE_NEWLINE 128

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
// The data of the current token
static STRING curTok_data;

// MARK - Function declarations
#if JACK
#define processLine Main.processLineD
#else
void processLineD();
#define processLine processLineD
#endif

// MARK - Main function
#if JACK
function void main() {
	var char c;
	var i16 i;

	// 2048 is the base of the heap
	let RAM = 0;
	let line = 2048; // 2048 to 2111 (64 characters)

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
		do Output.println();

		do processLine();
	}
	return;
}
#else
int main(int argc, char** argv) {
	printf("HackLISP-0\n");
	while(YES) {
		let line = readline("> ");

		processLine();
	}
}
#endif

// MARK - Normal functions

// Processes the line stored in the global variable `line`.
function void processLineD() {
	

	return;
}


#if JACK
	} // class Main
#endif
