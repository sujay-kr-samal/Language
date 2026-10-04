# The Idea

We learn programming languages. We write programs. We use compilers, interpreters, libraries, operating systems, and frameworks built by people before us.

But at some point, a different question appears:

> **“What if I built one myself?”**

That was the beginning of this project.

I didn’t start with the goal of creating the next Python, Java, or Rust. I simply wanted to understand what actually happens between the code I write and the computer that eventually executes it.

Those questions led me deeper.

I discovered that a programming language is not simply a collection of special words and symbols. Behind a language is a complete system made up of a lexer, a parser, an abstract syntax tree, an interpreter, or compiler, a runtime, error handling, and eventually much more.

So I decided to build one.

And I decided to build it in **C**.

I wanted the language to imitate existing programming languages while using different keywords. I wanted it to have its own identity while still being practical enough to build real software.

C is not the easiest language for building a programming language. It doesn't automatically manage memory for me, provide a sophisticated standard library, or hide the details of how data is represented.

But it is fast.

More importantly, it keeps me close to the machine.

That is exactly why I chose it.

If I was going to learn how a programming language works, I wanted to understand the things happening underneath it.

I wanted to understand the memory.

I wanted to understand the data structures.

I wanted to understand how source code becomes tokens, how tokens become a structure, and how that structure eventually becomes something the computer can execute.

This book documents that process.

It is not a story about building a perfect language.

It is a story about building one **from the ground up**.

There will be mistakes.

There will be broken code.

There will be compiler errors that make no sense at first.

There will be features that need to be redesigned.

Some ideas will work. Others will be abandoned.

And that is part of the point.

A programming language doesn't appear fully formed.

It evolves.

The first version might only understand:

```text
say("Hello")
```

Then it learns numbers.

Then variables.

Then expressions.

Then conditions.

Then loops.

Then functions.

Eventually, the language begins to feel less like a collection of C structures and more like a system of its own.

That transformation is what I want to document.

Not just **what** I built, but **why** I built each part, what I learned from it, and what went wrong along the way.

Because the real goal was never simply to have a programming language.

The goal was to understand how one is made.

And once I understood that, I could start asking a much bigger question:

> **If I can build the language, what else can I build?**

That question is where this book begins.