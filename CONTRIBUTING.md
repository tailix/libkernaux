Common
------

* Add your name to [COPYING](/COPYING).
* Don't add your name to `AUTHORS` - it's for maintainers.
* Add copyright notice in the beginning of changed files except the headers.
* If you change the behavior (even just fix a bug) of **libkernaux** (stable) or
  [libc](/libc), add a record to [ChangeLog](/ChangeLog).

Prohibitions:

* Don't commit binary files
* Don't commit configuration files of your editor or IDE
* Don't use encodings other than ASCII and UTF-8
* Don't use alphabets other than Latin
* Don't use languages other than English
* Don't use tabulations (I don't hate tabs, but people can not use them
  properly)
* Don't leave trailing whitespaces
* Don't forget the newline character in the end of files

The following statements are recommendations, but highly encouraged:

* Write documentation
* Write tests
* Keep lines less than 80 characters long for better experience on split screen

### Things to review periodically

* `git grep -i fixme`
* `git grep -i todo`
* `git grep -i cppcheck-suppress`
* `git grep -i rubocop:disable`

### Programming mistakes

* Always check documentation, manuals and specifications

Avoid stupid errors with:

* Manual memory management
  * `malloc` may return `NULL`
  * Memory leak (forget to `free`)
  * Use after `free`/`realloc`
  * Double `free`/`realloc`
  * `free`ing/`realloc`ating unallocated memory
  * Changing the original pointer to the allocated memory (use `const`!)
* `NULL` pointers and `nil`/`None`/whatever objects
* Division by zero
* Pointer arithmetic - consider type size
* Type sizes (like `long` on 32-bit and 64-bit)
* Integer arithmetic overflow
* Bit shift
* Endianness (byte order)
* Data packing
* Data alignment
* Thread safety
* Undefined behavior
* Logical expressions (tautology, whatever)
* Checking for an error (return value, pointer argument, whatever)
* Use of not fully initialized data
* Not reading beyond a buffer, array or string
  * The index of the last item, which is less than the buffer size
  * Negative indices
  * The terminating null character in a string
* Allowed values of arguments
* Possible values of parameters
* Operator precedence
* Default case in switch statements
* Braces (curly brackets) around code blocks



C language
----------

Use **cppcheck**.

* Name regular functions (*not methods*) and variables in lower snake case
  (example: `foo_bar`).
* Name macros in upper snake case (example: `FOO_BAR`).
* Name types (*structures, unions, enumerations and type definitions*) in Pascal
  case (example: `FooBar`).
* Name nested types in Pascal case and with the prefix of the surrounding type
  in Pascal case, separate type names with underscores (example:
  `FooBar_CarCdr`).
* Name methods (*functions that belong to a specific type*) in lower snake case
  and with the prefix of the type name in Pascal case (example:
  `FooBar_car_cdr`).

* Name public (*defined in the headers and exported as symbols*) regular
  functions (*not methods*) and variables with the prefix `kernaux_` (example:
  `kernaux_foo_bar`).
* Name public (*defined in the headers*) macros with the prefix `KERNAUX_`
  (example: `KERNAUX_FOO_BAR`).
* Name public (*defined in the headers*) types with the prefix `KernAux_`
  (example: `KernAux_FooBar`).
* Name public (*defined in the headers*) with the prefix `KernAux_` and with the
  prefix of the surrounding type, separate type names with underscore (example:
  `KernAux_FooBar_CarCdr`).
* Name public (*defined in the headers*) methods with the prefix `KernAux_` and
  with the prefix of the type name (example: `KernAux_FooBar_car_cdr`).

* Use postfix `size` for a byte size.
* Use postfix `slen` for C string length without terminating `\0` character
  (size - 1).
* Use postfix `count` for a number of elements in an array.

* Create `typedef`s with the names of related `struct`s. Use this name with a
  prefix `struct` to declare the data itself, withoth the prefix to declare
  a pointer or an array:

```c
typedef struct FooBar { int car; } *FooBar;

static struct FooBar FooBar_create();
static void FooBar FooBar_init(FooBar foobar);

static void FooBar_do_something(FooBar foobar);

// Initialize:
struct FooBar foobar = FooBar_create();
// or
struct FooBar foobar;
FooBar_init(&foobar);

// Use:
FooBar foobar_ptr = &foobar;
FooBar_do_something(&foobar);
```

```c
typedef struct FooBar { int car; } FooBar[1];

static struct FooBar FooBar_create();
static void FooBar FooBar_init(FooBar foobar);

static void FooBar_do_something(FooBar foobar);

// Initialize:
FooBar foobar = { FooBar_create() };
// or
FooBar foobar;
FooBar_init(foobar);

// Use:
FooBar_do_something(foobar);
```

* Mark variables and parameters with `const` if you don't plan to modify them
* Only omit braces (curly brackets) of a block if it's statement is placed on
  the same line as conditional statement:

```c
// Good:
if (foo) return bar;
if (foo) {
    return bar;
}

// Bad:
if (foo)
    return bar;
```



Python
------

Nothing here yet.



Ruby
----

* Freeze objects if you don't plan to modify them

### Matz's Ruby interpreter

Use **RuboCop**. See [bindings/ruby/.rubocop.yml](/bindings/ruby/.rubocop.yml)

### mruby

Use **RuboCop**. See [bindings/mruby/.rubocop.yml](/bindings/mruby/.rubocop.yml)



Rust
----

Use **rustfmt** and **Clippy**.
See [bindings/rust/rustfmt.toml](/bindings/rust/rustfmt.toml)
