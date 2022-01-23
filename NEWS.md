Releases
========



0.2.0 (2022-01-22)
------------------

### Breaking changes

* `./configure` - removed options to disable panic calls and returns in
  `<kernaux/assert.h>`.
* `<kernaux/assert.h>` - removed preprocessor directives that can disable panic
  calls and returns.

### New stable APIs

* `<kernaux/cmdline.h>` - simple command line parser.

### Other changes

* Now `./configure` options also follow semantic versioning.
* Bug fixes in `<kernaux/printf.h>`.



0.1.0 (2022-01-20)
------------------

Initial release.
