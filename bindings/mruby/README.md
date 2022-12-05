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
           branch: 'v0.6.1',
           checksum_hash: 'dfaf233b1a03de29a04560902010c6a31e37140a'
  # ...
end
```
