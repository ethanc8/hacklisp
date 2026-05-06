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
#endif // JACK

#define Atom i16
#define Error i16
#define Error_OK 0
#define Error_Syntax 1

#define bool i16

#if JACK
	#define YES -1
	#define NO 0
#else
	#define YES (bool)1
	#define NO 0
#endif

#if JACK
	static Array RAM;
#else
	i16 RAM[24577];
#endif

#if JACK
function i16 main() {
	let RAM = 0;

	Output.printString("Hello, world!");
	Output.println();
}
#else
int main(int argc, char** argv) {
	printf("HackLISP-0\n");
	while(true) {
		char* line = readline("> ");
	}
}
#endif


#if JACK
	} // class Main
#endif
