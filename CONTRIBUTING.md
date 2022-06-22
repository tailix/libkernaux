Common
------

* Add your name to [COPYING](/COPYING).
* **Don't** add your name to `AUTHORS` - it's for maintainers.
* Add copyright notice in the beginning of changed files except the headers.
* If you change the behavior (even just fix a bug) of **libkernaux** (stable) or
  [libc](/libc), add a record to [ChangeLog](/ChangeLog).



C language
----------

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
