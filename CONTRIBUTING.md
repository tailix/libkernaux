Common
------

* Add your name to [COPYING](/COPYING).
* **Don't** add your name to `AUTHORS` - it's for maintainers.
* Add copyright notice in the beginning of changed files except the headers.
* If you change the behavior (even just fix a bug) of **libkernaux** (stable) or
  [libc](/libc), add a record to [ChangeLog](/ChangeLog).



C language
----------

* Name regular (*not methods*) functions and variables in lower snake case
  (example: `foo_bar`).
* Name macros in upper snake case (example: `FOO_BAR`).
* Name types (structures and type definitions) in Pascal case (example:
  `FooBar`).
* Name nested types in Pascal case and with the prefix of the surrounding type
  in Pascal case, separate type names with underscores (example:
  `FooBar_CarCdr`).
* Name methods (functions that belong to a specific type) in lower snake case
  and with the prefix of the type name in Pascal case (example:
  `FooBar_car_cdr`).

* Name public (*defined in the headers and exported as symbols*) regular (*not
  methods*) functions and variables with the prefix `kernaux_` (example:
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



Python
------

Nothing here yet.



Ruby
----

### Matz's Ruby interpreter

Use **RuboCop**. See [bindings/ruby/.rubocop.yml](/bindings/ruby/.rubocop.yml)

### mruby

Use **RuboCop**. See [bindings/mruby/.rubocop.yml](/bindings/mruby/.rubocop.yml)



Rust
----

Use **rustfmt** and **Clippy**.
See [bindings/rust/rustfmt.toml](/bindings/rust/rustfmt.toml)
