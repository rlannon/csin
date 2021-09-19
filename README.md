# SINx86

This repository contains an updated toolchain for SIN using gcc as a compiler back-end. This is based off of the [SINx86](https://github.com/rlannon/SINx86) repository, which was itself based on another, earlier project. This is a part of the larger SIN Compiler Project which includes a [runtime environment](https://github.com/rlannon/SRE) and [standard library](https://github.com/rlannon/sinstdlib) in addition to this compiler.

SIN is a custom procedural programming language based on C, C++, and Python, designed as an exercise in compiler design. It was named in jest, after the Spanish word meaning "without" because if anyone were to ask you about the language, you would reply that it is without any real utility or purpose. This is purely an educational exercise in compiler development.

## About the Language

### Background

SIN is very C-like; it is strictly procedural, utilizes strict type safety, doesn't allow implicit conversions, and gives the programmer a decent amount of freedom over the environment should they choose to use it. However, programmers shouldn't _have_ to worry about manual resource management, especially when running in an environment that allows us to have a runtime do it for us (i.e., inside a modern OS). As such, SIN utilizes a runtime environment for automatic memory management, includes reference types (like C++), and even contains certain safety features like runtime bounds checks on array and string indexing.

The central idea of SIN is to create a language with a fairly readable syntax that allows more safety than C but without all of the complicated object-oriented features of languages like Java. That said, my goal is not to make a modern language competitor -- see the 'Goal of the Project' section for more.

### Sample

The following is an obligatory 'hello world!' sample, including the necessary boilerplate:

    include "stdio.sinh";
    def int main(alloc dynamic array<string> args) {
        @print("Hello, world!");
        return 0;
    }

Like Python, functions are defined with `def`, function calls look similar enough (though they are prefixed with `@` -- this is for a future language feature). Like C and Java, the entry point of entry program is 'main', though unlike Java (and like C), the return type and arguments for this function are not fixed. It's good practice to use a return type of `int` and a single argument `dynamic array<string> args`, but it's not strictly required (though the compiler will issue a warning).

For more information, check out the [guide](Basic%20Syntax).

## Goal of the Project

I cannot stress enough that this is a _learning exercise_ in compiler development, not an attempt to make the next Python or Rust. The purpose is not to create a particularly _good_ compiler, but a _functioning_ compiler, one that can be improved and expanded upon in the future. While I hope to improve the efficiency and overall funcionality of the compiler in the future, it is somewhat bodged together right now.

The fact that it's a learning exercise should explain why I decided to write a parser by hand instead of using yacc/lex/bison/some other tool; doing so would not have allowed me to learn how parsers (can) work as deeply as I did by writing this one. It should also explain why I'm compiling directly from an abstract syntax tree into assembly rather than using an intermediate representation like llvm, GNU RTL, or even C.

It also sort of explains why I am serializing the generated code into assembly only to immediately assemble that code. This is a pretty inefficient method, but again, the goal is to generate something functional and hopefully incrementally improve its efficiency down the line once I have a full proof of concept. This also helps me in debugging the code generator for a variety of reasons.

## Getting Started

### Installation / Build

Note that this project requires compilers for C++17 and C99.

### The SRE

In order to compile working SIN binaries, you will need a copy of the [SIN Runtime Environment](https://github.com/rlannon/SRE), a small library which provides necessary runtime support for the language. It must be statically-linked to all SIN programs in order for them to produce a working executable. Although the SRE is currently unfinished, it implements the necessary functionality for the langauge features which are currently supported by this code generator.

Currently, the SRE utilizes C++ for some functionality. As a result, a C++ compiler must be used to link SIN executables.

### The SIN Standard Library

SIN, like many other programming languages, has a standard library that includes various features that flesh out the language and integrate it with the host environment. Like the SRE, this library is located in a [separate repository](https://github.com/rlannon/sinstdlib). While it is not required to produce working binaries, it will ultimately serve to make the language more useful (as I/O with the environment is not included by default). As such, it is highly encouraged that any brave souls who decide to try out this programming language build and use the standard library.

Note that the aforementioned repo should be fairly portable, but as is the case with the the rest of the compiler project, I can't make any guarantees (for the time being) as the current focus is Linux.

### Using SIN

I intend on using [GitHub Pages](rlannon.github.com/SINx86) for introductory programming materials. Note that currently, not everything is up-to-date, and the site will be updated periodically.

To build projects, the following steps should be followed:

* Ensure `make` is installed
* Build the SRE using the provided makefile
* Build the compiler using the provided makefile
* Build all requisite `.sin` files for your project using the compiler
* Compile the generated C files using any C99 compiler.
* Link with G++ using `g++ <list object files> -L <path to SRE> -l SRE`, again optionally specifying the outfile with `-o` (default is `a.out`)

Note there is no reason you can't use `make` for SIN projects. Doing so would probably make life a whole lot easier!

#### Language Samples and Benchmarks

Included with this project are a folder of various sample SIN files to test the compiler's functionality. They can also serve as general syntax/usage references.

Within the samples folder is a folder called `benchmarks`, which includes various algorithms in SIN, Python, and C to test compile and execution times and serve as benchmark tests.

## Future Goals

I hope to use this project as a stepping stone to develop other languages and explore other features, such as compilers for object-oriented programming languages. For this project specifically, I hope to add in:

* Various compiler optimizations
* Debugging support
* VSCode integration (there's currently a [syntax highlighting extension!](https://github.com/rlannon/vscode-sin-lang))
* Native support for UTF-8 instead of ASCII

In the doc files you will also find a number of documents mentioning things that are not currently supported by the compiler but will be in the future (e.g., anonymous functions and tuples). I also intend on writing a superset of SIN in the future to include more language features and enable first-class concurrency.
