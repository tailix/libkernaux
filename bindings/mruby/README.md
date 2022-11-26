::KernAux
=========

[![Build status](https://github.com/tailix/libkernaux/actions/workflows/mruby.yml/badge.svg)](https://github.com/tailix/libkernaux/actions/workflows/mruby.yml)
[![Build status (FreeBSD)](https://api.cirrus-ci.com/github/tailix/libkernaux.svg?task=mruby%20(FreeBSD))](https://cirrus-ci.com/github/tailix/libkernaux)

Binding to [libkernaux](https://github.com/tailix/libkernaux) - auxiliary
library for kernel development.



Install
-------

Add the following to your `build_config.rb`:

```ruby
MRuby::Build.new do |conf|
  # ...
  conf.gem github: 'tailix/libkernaux',
           path: 'bindings/mruby',
           branch: 'v0.5.0',
           checksum_hash: 'eda0b63f8dc7a5a6b86763bfe5797a343b4bc746'
  # ...
end
```
