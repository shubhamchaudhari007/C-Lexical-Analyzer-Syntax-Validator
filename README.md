# 🔍 C Lexical Analyzer & Syntax Validator

![Language](https://img.shields.io/badge/Language-C-blue)
![Status](https://img.shields.io/badge/Project%20Type-Compiler%20Component-brightgreen)
![License](https://img.shields.io/badge/License-MIT-yellow)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows-lightgrey)

---

## 📘 Overview

This project is a **C Lexical Analyzer and Syntax Validator**, designed to simulate the **lexical analysis phase of a compiler**.  
It scans a C source file, breaks it into **tokens**, identifies their types (keywords, identifiers, operators, etc.), and detects **syntax and lexical errors** such as:

- Unmatched or misplaced brackets `() {} []`
- Invalid numeric formats (binary, octal, hex, float)
- Unterminated strings and comments
- Ternary operator misplacement (`? :`)
- Invalid suffixes or malformed tokens

This project provides **line-wise color-coded output**, making it easy to debug and understand how a compiler processes C source code.

---

## 🧩 Features

### 🟦 **1. Lexical Tokenization**
Detects and classifies:
- **Keywords:** `int`, `float`, `while`, `return`, etc.
- **Identifiers:** User-defined variable and function names.
- **Constants:** Integer, Floating point, Hexadecimal, Binary, and Octal numbers.
- **Operators:** Arithmetic, Relational, Logical, Bitwise, Assignment, and Conditional operators.
- **Symbols:** `{`, `}`, `()`, `[]`, `;` etc.
- **String & Character Literals:** Proper validation with error reporting.

### 🟨 **2. Syntax Validation**
- **Bracket Checking:** Uses a stack-based mechanism to validate proper opening and closing of `()`, `{}`, and `[]`.
- **Ternary Operator Validation:** Ensures correct usage of `?` and `:` in conditional expressions.

### 🟥 **3. Error Detection**
Reports syntax errors such as:
- Invalid suffix on constants.
- Unterminated string or character literals.
- Unterminated or nested comments.
- Extra or missing brackets.
- Invalid floating or numeric constants.
- Ternary operator misplacement.

### 🟩 **4. Modular Code Structure**
The project is split into multiple files for clarity:
- `main.c` → Entry point, handles file operations.
- `analyzer.c` → Handles tokenization, categorization, and validation.
- `Info.c` → Contains helper functions for checking keywords, operators, brackets, etc.
- `Info.h` → Custom header defining macros, constants, and function prototypes.

---

## ⚙️ **Project Architecture**

📁 LexicalAnalyzer

│

├── 📄 main.c

├── 📄 tokensCheck.c

├── 📄 Functions.c

├── 📄 Info.h

├── 📄 test.c # (Sample input file for testing)

└── 📄 README.md


Each source file has a distinct purpose:

- **main.c:** Manages command-line arguments, file reading, and function calls.
- **analyzer.c:** Core token identification logic and error management.
- **Info.c:** Utility definitions, keyword arrays, and validation functions.
- **Info.h:** Header file containing macros, function declarations, and ANSI color codes.

---

## 🧠 **Core Concepts Implemented**

1. **Lexical Analysis:** Breaking source code into minimal units (tokens).  
2. **Finite Automata Concept:** Used implicitly for token pattern recognition.  
3. **Stack Implementation:** Used in bracket validation for balancing parentheses.  
4. **Error Reporting System:** Displays descriptive and color-coded error messages.  
5. **File Handling:** Uses standard I/O (`fgetc`, `fseek`, `rewind`) for line-by-line scanning.

---

## 🧰 **Technology Stack**

| Component | Description |
|------------|--------------|
| **Language** | C |
| **Compiler** | GCC |
| **Headers Used** | `<stdio.h>`, `<string.h>`, `<stdlib.h>` |
| **Custom Header** | `Info.h` |
| **OS Compatibility** | Windows, Linux |

---

## 🚀 **How to Run**

 🧾 Step 1 — Compile the Code
Use the GCC compiler to compile all files together:
```
gcc main.c Functions.c tokensCheck.c -o lexer
```

🧾 Step 2 — Execute the Program
```

Provide a C source file as input:
./lexer example.c
```

🧾 Step 3 — Output
```

The analyzer prints classified tokens and highlights syntax or lexical errors in a color-coded format such as:

Keyword : int
Identifier : main
Symbol : (
Symbol : )
Symbol : {
Keyword : int
Identifier : i
Operator : =
Numeric Constant : 10
Symbol : ;
Keyword : int
Identifier : ss
Operator : =
Numeric Constant : 10
Operator : >
Numeric Constant : 20
Operator : ?
Numeric Constant : 10
Operator : :
Numeric Constant : 20
Symbol : ;
Keyword : switch
Symbol : (
Identifier : size
Symbol : )
Symbol : {
Keyword : case
Numeric Constant : 4
Symbol : :
Identifier : printf
Symbol : (
String Literal : "Size is %d\n"
Operator : ,
Identifier : size
Symbol : )
Symbol : ;
Keyword : default
Symbol : :
Identifier : printf
Symbol : (

ERROR 
Line No 12 :  Missing Terminating Character  ->  "

```
---

## 🎨 Color Legend

Color	Meaning

🟩 Green	Keyword

🟨 Yellow	Identifier

🟪 Purple	Character Constant

🟧 Orange	String Literal

🩵 Cyan	Operator

🩶 Gray	Symbol

🩷 Magenta	Numeric Constant

🟥 Red	Error / Invalid Token

---

## 🧾 Sample Output
```

Keyword : int
Identifier : main
Symbol : (
Symbol : )
Symbol : {
Identifier : a
Operator : =
Numeric Constant : 10
Symbol : ;
Identifier : printf
Symbol : (
String Literal : "Value is 10"
Symbol : )
Symbol : ;
Symbol : }

```
---

## 📊 Learning Outcomes

Through this project, I explored:

The working of lexical analyzers in compiler design.

Building a modular compiler front-end component.

How tokens are categorized and validated.

Implementing error-handling and recovery in low-level language.

The connection between automata theory and compiler construction.

---

## 🧩 Future Enhancements

Add symbol table generation for variables and functions.

Implement intermediate code representation (ICR).

Extend validation for nested ternary operators.

Add support for preprocessor directives like #define and #include.

Integrate with parser and semantic analyzer to form a mini compiler.

---

## 🤝 Contributing

Contributions, issues, and feature requests are welcome!
Feel free to fork this repo, open an issue, or submit a pull request.

---


## 🪪 License

This project is licensed under the MIT License — you are free to use, modify, and distribute it for educational or personal purposes.
