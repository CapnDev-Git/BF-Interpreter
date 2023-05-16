# Brainf\*ck Interpreter

Code in C by FLECHTNER Eliott.

Consists of a Brainf\*ck language interpreter.

Developed in the context of [Advanced OS &amp; Virtualization](http://syllabus.sic.shibaura-it.ac.jp/syllabus/2023/din/138807.html?g=101) class by Instructor [**福田 浩章**](http://resea.shibaura-it.ac.jp/?2830ea708a1eddbb7e8bb6c2a366b751) (FUKUDA Hiroaki) at [**芝浦工業大学**](https://www.shibaura-it.ac.jp/en/) (Shibaura Institute of Technology) in 東京都 (Tōkyō-to, Japan).

## How to use

### Compilation Librairies

This project uses [Makefiles](<https://www.wikiwand.com/en/Make_(software)>) to compile and create an executable.

### C Librairies

No external librairies are necessary except the following C headers:

- err.h
- stdio.h
- stdlib.h
- string.h

### Tokens specification
- \> = Increment the data pointer by one (to point to the next cell to the right).
- \< = Decrement the data pointer by one (to point to the next cell to the left).
- \+ = Increment the byte at the data pointer by one.
- \- = Decrement the byte at the data pointer by one.
- \. = Output the byte at the data pointer.
- \, = Accept one byte of input, storing its value in the byte at the data pointer.
- \[ = If the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching \] command.
- \] = If the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching \[ command.

### Compilation

To compile the project, you need to run the following command:

```bash
make
```

### Execution

To execute the program, the following syntax should be used:

```bash
# Prints out the size of the program, the program itself and
# the output interpreted by the executable.
./bf <file>
```

### Tests example
```bash
./bf ./tests/test.bf
./bf ./tests/test2.bf
./bf ./tests/test5.bf
./bf ./tests/test8.bf
```

### Cleaning

To clean the project, you need to run the following command:

```bash
make clean # To clean the project
```
