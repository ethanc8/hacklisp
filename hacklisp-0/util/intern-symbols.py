
symbols = [
	("NIL", "NIL"),
	("TRUE", "TRUE"),
	("quote", "kQuote"),
	("cond", "kCond"),
	("=", "kEq"),
	("cons", "kCons"),
	("atom?", "kAtom"),
	("head", "kHead"),
	("tail", "kTail"),
	("lambda", "kLambda"),
	("read", "kRead"),
	("print", "kPrint"),
	("integer?", "kInteger"),
]

offset = 0
for sym, macro in symbols:
	print(f"#define {macro} (atomStackBase + {offset})")
	
	for i in range(len(sym)):
		print(f"let RAM[atomStackBase + {offset}] = KEYCODE_{sym[i]};")
		offset += 1
	
	print(f"let RAM[atomStackBase + {offset}] = 0;")
	offset += 1
	
