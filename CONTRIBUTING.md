Common
------

* Add your name to [COPYING](/COPYING).
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
static void FooBar_do_something(FooBar foobar);

// ...

struct FooBar foobar = FooBar_create();
FooBar foobar_ptr = &foobar;
FooBar_do_something(&foobar);
```

```c
typedef struct FooBar { int car; } FooBar[1];

static struct FooBar FooBar_create();
static void FooBar FooBar_init(FooBar foobar);

static void FooBar_do_something(FooBar foobar);

// ...

FooBar foobar = { FooBar_create() };
// or
FooBar foobar;
FooBar_init(foobar);

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
