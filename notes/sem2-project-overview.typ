#import "@local/ethan-standard-style:0.1.0": *
#show: ethan-standard-style

#set text(
	font: "New Computer Modern",
	weight: 500,
	size: 11pt
)

#show math.equation: set text(
	font: "New Computer Modern Math",
	weight: 500,
	features: (
		// Round emptyset
		cv01: 1,
		// Blackboard bold from Computer Modern
		ss03: 1,
		// ss05: 1,
	)
)

#let title(arg) = [
	#set text(size: 17pt, weight: "bold")
	// #set align(center)

	#arg
]

#show link: set text(fill: blue)

#import "@preview/fletcher:0.5.8" as fletcher: diagram, node, edge
#import fletcher.shapes: diamond

#title[
	Bootstrapping via Lisp
]

*Ethan Charoenpitaks* \
Illinois Mathematics and Science Academy \
Aurora, Illinois, United States \
#link("mailto:echaroenpitaks@imsa.edu")

= Exposition

Modern open-source operating systems are built using different open-source operating systems. If a "trusting trust" attack was performed many years ago on a common open-source operating system, the attacker's attack may have spread to all existing compilers and OSes. Other similar risks also prevail. Bootstrapping from a verifiable and extremely small binary seed, only trusting human-readable source code beyond that point, will allow the achievement of a computing system that is trustable.

While this exercise has been achieved on modern x86\_64 systems, x86\_64 systems include large amounts of proprietary code and firmware, along with "Management Engines" or similar high-privileged CPUs that can engage in attacks against the trusted code. Additionally, even if an x86\_64 system were completely open, it is not really feasible for a typical high school student or undergraduate to understand the system from the logical level up. Bootstrapping to an assembler on the Hack computer will allow people to have a simple computer that can achieve some useful tasks, that they can fully understand and trust.

In semester 1's capstone project, I was able to convert the Hack computer to Verilog so it could be run on an FPGA. Future work on the hardware side could involve fabricating the Hack computer as an IC, or making it out of independent multiple-NAND-gate ICs (which has been demonstrated on Hackaday before) or out of vacuum tubes.

For semester 2, I intend to bootstrap to a "high-level" programming language from the Hack computer. The simplest programming language that can reasonably be described as high-level is Lisp. In #link("https://justine.lol/sectorlisp/jmc.pdf")[Paul Graham, "The Roots of Lisp"], he describes how Lisp can provide a high-level programming language with only the following primitive operators:
- `(quote x)`
- `(atom x)`
- `(eq x y)`
- `(car x)`
- `(cdr x)`
- `(cons x y)`
- `(cond (p1 e1) ... (pn en))`
- `(lambda (p1 ... pn) e)`

These can be used to build the "metacircular evaluator" -- a simple, readable program that can implement this barebones language.

The #link("https://justine.lol/sectorlisp2/")[SectorLISP project showed] that it's possible to build such a Lisp, with a garbage collector (!), in 436 bytes of i8086 machine code, using a few clever tricks. Even without supporting numbers, you can use its support for `NIL` in order to make binary numbers, and then in relatively few lines of code you can define arithmetic and symbolically differentiate common expressions. Clearly, this is a high-level language.

The goal of this project is to use a simple LISP dialect inspired by the above, titled HackLISP-0, which can be implemented rather easily on many platforms (but for now we will just do Hack). This could be extended to higher-level languages HackLISP-$n$, which could be bootstrapped to via HackLISP-$(n-1)$; eventually, we might get to a modern LISP such as Scheme or Common Lisp, to Mes Scheme in which we could eventually bootstrap to `tcc` and then to `gcc`, or get to our own LISP dialect in which we could build useful applications.

= Plan

== Step 0 -- Specifying the HackLISP-0 language

HackLISP-0 will be a language which is very basic, so that it can be easily implemented in assembly. However, it needs to be at least a bit better than SectorLISP; we at least need integers and the ability to read and write memory addresses directly. Figuring this out in advance will make the implementation of the language go much smoother, and allow end users to more easily make use of the language.

== Step 1 -- Implementing the HackLISP-0 interpreter in a C/Jack polyglot

This step is in order to allow me to flesh out all the implementation details in C (so that I may make use of tools like `clangd` and run it at a high speed on my laptop), and then in Jack I can validate that it will work on the Hack computer and deal with the details of taking input and emitting output. It will be written in a polyglot of C and Jack, using the C preprocessor to emit valid C or Jack based on preprocessor flags.

This will provide an interpreter, as that is easier than a compiler (especially when it is rewritten in Hack assembly). Although SectorLISP with GC can fit in 436 bytes of i8086 machine code, the complexity of GC is not necessary for a language that will solely be used to bootstrap HackLISP-$n$ with $n >= 1$.

== Step 2 -- basic validation of HackLISP-0

I will write some very basic programs in HackLISP in order to verify that it functions correctly. 

= Stretch goals

These are things I'd like to do soon, but I'm not sure what I'd do first and it's unlikely these would get finished during the 2-week capstone period.

== Implementing the HackLISP-0 language in Hack assembly

This was originally supposed to be Step 2, but the implementation in C/Jack might take up most of the time, and I realized that improving the language (see the next section) might be more important or bring up more interesting problems than just reimplementing it in Hack assembly.

However, this step is certainly necessary to complete the bootstrap chain, and I expect that even if I do not reach this with in the two weeks allotted for the capstone project, I will finish this at some point.

== HackLISP-1 language interpreter/compiler in HackLISP-0

Jeremiah Orians, one of the key contributors to the project to bootstrap modern GNU/Linux on x86_64 #link("https://github.com/oriansj/talk-notes/blob/master/bootstrappable.org")[mentioned] his reasons for not using LISP for the beginning of the bootstrap:

#quote(block: true)[
	LISP primitives defined in McCarthy’s 1960 paper \[Turns out he missed many essential things\] with some modern improvements like Lexical scope, let expressions and raw string support. Turns out you need proper LISP macros in order to produce something useful in bootstrapping. Adding LISP macros in assembly simply is a task no one wants to do.  
]

Thus, it seems rather likely that if I want to bootstrap to a more complex system, I will need a much more useful LISP. 

Beyond just implementing an interpreter for that LISP, we will need a compiler and a garbage collector; otherwise, higher-level programs will end up being run on interpreters inside interpreters inside interpreters; the Hack platform is far too weak to support such a nested interpreter and still have the programs run at acceptable speeds. Additionally, such a setup would quickly run out of memory. 

== Writing useful programs in HackLISP-0 or \-1

This would demonstrate that this bootstrap path actually gets us to something useful. Examples of things we could do:

- A text editor
- A language server (which could work with the text editor)
- A speech synthesis engine
- A filesystem
- A database

= Challenges

The design of the LISP interpreter is quite complex, although simpler than for many other languages. To help me, I will make extensive use of the many existing miniature LISP interpreters and the associated tutorials, but I expect that HackLISP-0 will necessarily not be a pure port of one of those interpreters, but will require its own design differences to accomodate the exact needs of being easily implementable in assembly on a 16-bit computer without floating points.

I am very used to developing the compiler and interpreter with test cases. While HackLISP-0 will not be exactly the same as the Make-a-lisp language, I will probably use many of the test cases from the Make-a-lisp project.

It's possible that my attempt at C/Jack polyglot will fail or become unworkable; in that case, although development will become more inconvenient, I will probably turn it into a pure Jack program.
