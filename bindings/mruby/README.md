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
           branch: 'v0.7.0',
           checksum_hash: '1cfff3fca3fc3f8990f43f0d6d5c91929c8f359c'
  # ...
end
```
