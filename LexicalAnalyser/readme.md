# Lexical Analyzer for C-- (Subset of C++)

A lexical analyzer (lexer) for a subset of C++ called **C--**, supporting declaration/assignment statements, control structures (`if-else`, `while`), and basic expressions. Built from scratch in C++ using a Deterministic Finite Automaton (DFA).

---

## Features
- **Supported Tokens**:
  - **Data Types**: `int`, `char`
  - **Identifiers**: `[a-zA-Z_][a-zA-Z0-9_]*`
  - **Literals**: Integer (`[0-9]+`), Character (`'[^']'`)
  - **Operators**: 
    - Relational (`==`, `!=`, `<`, `>`, `<=`, `>=`)
    - Arithmetic (`+`, `-`, `*`, `/`, `%`, `=`)
  - **Control Keywords**: `if`, `else`, `while`
  - **Punctuation**: `;`, `{`, `}`, `(`, `)`
- **Line Preservation**: Output tokens mirror input line structure.
- **Error Handling**: Basic handling of unterminated character literals.

---

## To run:
- **C++ Compiler**: Supports C++11 or later (e.g., `g++`).
- **Build Tools**: `make` (for compiling via `Makefile`).
- Give input and output file as command line arguments

---

