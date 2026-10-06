# DIVINE

**DIVINE** is an experimental programming language written in **C**.

The goal of DIVINE is to build a programming language from the ground up — starting with file reading, lexical analysis, parsing, AST construction, and interpretation.

> **Status:** Early development

## ✨ Current Pipeline

```text
.divine source
      ↓
 File Reader
      ↓
    Lexer
      ↓
    Parser
      ↓
     AST
      ↓
 Interpreter
      ↓
   Output
```

## 📁 Project Structure

```text
Language/
├── AST.c
├── AST.h
├── FileReader.c
├── Interpreter.c
├── Interpreter.h
├── Lexer.c
├── Lexer.h
├── Parser.c
├── Parser.h
├── main.c
├── CMakeLists.txt
├── README.md
└── tests/
    └── print.divine
```

## 🔥 Current Features

* `.divine` file support
* Source-file reading
* Lexical analysis
* Token generation
* Parsing
* Abstract Syntax Tree (AST)
* Basic interpreter
* `print()` statement
* String literals
* Number literals
* Identifier recognition

## 🪽 DIVINE Syntax

A basic DIVINE program currently looks like:

```divine
print("Hello, DIVINE!");
```

Multiple statements are supported:

```divine
print("Hello");
print("Welcome to DIVINE");
print(123);
```

Output:

```text
Hello
Welcome to DIVINE
123
```

## 🚀 Building

Compile the current implementation with:

```bash
gcc main.c FileReader.c Lexer.c Parser.c AST.c Interpreter.c -o divine
```

Then run a `.divine` file:

```bash
./divine tests/print.divine
```

Example:

```bash
./divine tests/print.divine
```

## 🧪 Example

`tests/print.divine`

```divine
print("Hey");
print("Welcome to DIVINE");
print(123);
```

Output:

```text
Hey
Welcome to DIVINE
123
```

## 🏗️ Architecture

### File Reader

Reads the `.divine` source file into memory.

```text
.divine → source text
```

### Lexer

Converts source text into tokens.

```text
print("Hey");
```

becomes approximately:

```text
PRINT
LEFT_PAREN
STRING
RIGHT_PAREN
SEMICOLON
EOF
```

### Parser

Converts tokens into an AST.

```text
Program
└── PrintStatement
    └── StringLiteral
        └── "Hey"
```

### AST

The AST represents the structure of a DIVINE program.

Current node types include:

```text
AST_PROGRAM
AST_PRINT
AST_STRING
AST_NUMBER
AST_IDENTIFIER
```

### Interpreter

The interpreter walks the AST and executes the program.

```text
AST
 ↓
Interpreter
 ↓
Output
```

## 🛠️ Roadmap

### Language Core

* [x] `.divine` file reader
* [x] Lexer
* [x] Parser
* [x] AST
* [x] Interpreter
* [x] `print()`
* [ ] Variables
* [ ] Immutable variables
* [ ] Mutable variables
* [ ] Assignment
* [ ] Arithmetic expressions
* [ ] Comparisons
* [ ] Boolean values
* [ ] Conditions
* [ ] Loops
* [ ] Functions
* [ ] Return values
* [ ] Arrays
* [ ] Objects / structures
* [ ] Modules

### Tooling

* [ ] Proper CLI
* [ ] Better error messages
* [ ] REPL
* [ ] Formatter
* [ ] Language server
* [ ] Syntax highlighting
* [ ] Package/module system

### Compiler

The current implementation is an interpreter.

Future possibilities include:

```text
DIVINE source
      ↓
     Lexer
      ↓
    Parser
      ↓
     AST
      ↓
 Intermediate Representation
      ↓
   Code Generation
      ↓
 Executable / Native Code
```

## 🎯 Project Goal

DIVINE is being developed from scratch to understand how programming languages work internally.

The project focuses on learning and implementing:

* Lexers
* Parsers
* ASTs
* Interpreters
* Runtime environments
* Memory management
* Language design
* Compiler architecture

The long-term goal is to evolve DIVINE from a small interpreted language into a complete programming language ecosystem.

## 📜 License

License information will be added as the project develops.

