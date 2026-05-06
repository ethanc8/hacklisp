# 3 - Parser

## lwhjp

https://www.lwh.jp/lisp/parser.html

```c
typedef enum {
	Error_OK = 0,
	Error_Syntax
} Error;

int lex(const char *str, const char **start, const char **end)
{
	const char *ws = " \t\n";
	const char *delim = "() \t\n";
	const char *prefix = "()";

	str += strspn(str, ws);

	if (str[0] == '\0') {
		*start = *end = NULL;
		return Error_Syntax;
	}

	*start = str;

	if (strchr(prefix, str[0]) != NULL)
		*end = str + 1;
	else
		*end = str + strcspn(str, delim);

	return Error_OK;
}

int parse_simple(const char *start, const char *end, Atom *result)
{
	char *buf, *p;

	/* Is it an integer? */
	long val = strtol(start, &p, 10);
	if (p == end) {
		result->type = AtomType_Integer;
		result->value.integer = val;
		return Error_OK;
	}

	/* NIL or symbol */
	buf = malloc(end - start + 1);
	p = buf;
	while (start != end)
		*p++ = toupper(*start), ++start;
	*p = '\0';

	if (strcmp(buf, "NIL") == 0)
		*result = nil;
	else
		*result = make_sym(buf);

	free(buf);

	return Error_OK;
}

int read_list(const char *start, const char **end, Atom *result)
{
	Atom p;

	*end = start;
	p = *result = nil;

	for (;;) {
		const char *token;
		Atom item;
		Error err;

		err = lex(*end, &token, end);
		if (err)
			return err;

		if (token[0] == ')')
			return Error_OK;

		if (token[0] == '.' && *end - token == 1) {
			/* Improper list */
			if (nilp(p))
				return Error_Syntax;

			err = read_expr(*end, end, &item);
			if (err)
				return err;

			cdr(p) = item;

			/* Read the closing ')' */
			err = lex(*end, &token, end);
			if (!err && token[0] != ')')
				err = Error_Syntax;

			return err;
		}

		err = read_expr(token, end, &item);
		if (err)
			return err;

		if (nilp(p)) {
			/* First item */
			*result = cons(item, nil);
			p = *result;
		} else {
			cdr(p) = cons(item, nil);
			p = cdr(p);
		}
	}
}

int read_expr(const char *input, const char **end, Atom *result)
{
	const char *token;
	Error err;

	err = lex(input, &token, end);
	if (err)
		return err;

	if (token[0] == '(')
		return read_list(*end, end, result);
	else if (token[0] == ')')
		return Error_Syntax;
	else
		return parse_simple(token, *end, result);
}

int main(int argc, char **argv)
{
	char *input;

	while ((input = readline("> ")) != NULL) {
		const char *p = input;
		Error err;
		Atom expr;

		err = read_expr(p, &p, &expr);

		switch (err) {
		case Error_OK:
			print_expr(expr);
			putchar('\n');
			break;
		case Error_Syntax:
			puts("Syntax error");
			break;
		}

		free(input);
	}

	return 0;
}
```

## tinylisp

https://raw.githubusercontent.com/Robert-van-Engelen/tinylisp/main/tinylisp.pdf#page=21

## SectorLISP

```c
int cx; /* stores negative memory use */
int dx; /* stores lookahead character */

GetChar() {
  int c, t;
  static char *l, *p;
  if (l || (l = p = bestlineWithHistory("* ", "sectorlisp"))) {
    if (*p) {
      c = *p++ & 255;
    } else {
      free(l);
      l = p = 0;
      c = '\n';
    }
    t = dx;
    dx = c;
    return t;
  } else {
    PrintChar('\n');
    exit(0);
  }
}

Read() {
  return GetObject(GetToken());
}

// lexer
GetToken() {
  int c, i = 0;
  do {
		// If is ASCII printable character
		if ((c = GetChar()) > ' ') {
			// Then, add it to the token
			RAM[i++] = c;
		}
	} while (
		c <= ' ' // c is not printable
		|| (c > ')' && dx > ')'));
  RAM[i] = 0;
  return c;
}

GetObject(c) {
  if (c == '(') return GetList();
  return Intern();
}

GetList() {
  int c = GetToken();
  if (c == ')') return 0;
  return AddList(GetObject(c));
}

AddList(x) {
  return Cons(x, GetList());
}

Intern() {
  int i, j, x;
  for (i = 0; (x = M[i++]);) {
    for (j = 0;; ++j) {
      if (x != RAM[j]) break;
      if (!x) return i - j - 1;
      x = M[i++];
    }
    while (x)
      x = M[i++];
  }
  j = 0;
  x = --i;
  while ((M[i++] = RAM[j++]));
  return x;
}
```