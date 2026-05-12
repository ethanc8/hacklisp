# HackLISP-0

[Manual](https://github.com/ethanc8/hacklisp/raw/trunk/notes/hacklisp-0/manual.pdf)

[Slideshow](https://github.com/ethanc8/hacklisp/raw/trunk/notes/hacklisp-0/slides.pdf)

## Try it out yourself

### On your CPU

#### With pixi package manager (recommended)

Only tested on GNU/Linux!

```bash
curl -fsSL https://pixi.sh/install.sh | sh
cd hacklisp-0
pixi install
pixi shell
./build.sh
./hacklisp-0 # opens REPL
./hacklisp-0 examples/hello.lisp # runs full program
```

#### With your system package manager

1. Install a version of clang supporting C23.
2. Install GNU readline.
3. 
  ```bash
  cd hacklisp-0
  ./build.sh
  ./hacklisp-0 # opens REPL
  ./hacklisp-0 examples/hello.lisp # runs full program
  ```

### On the simulated Hack CPU

1. 
  ```bash
  curl -fsSL https://pixi.sh/install.sh | sh
  cd hacklisp-0
  pixi install
  pixi shell
  ./buildjack.sh
  ```
2. Open <https://nand2tetris.github.io/web-ide/compiler>
3. Upload the hacklisp-0 folder.
4. Press "Compile".
5. Press "Run".
6. Set the speed to max, and press the button that looks like a fast-forward.
7. Press "Enable Keyboard".




