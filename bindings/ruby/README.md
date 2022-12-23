::KernAux
=========

[![Build status](https://github.com/tailix/libkernaux/actions/workflows/ruby.yml/badge.svg)](https://github.com/tailix/libkernaux/actions/workflows/ruby.yml)
[![Build status (FreeBSD)](https://api.cirrus-ci.com/github/tailix/libkernaux.svg?task=Ruby%20(FreeBSD))](https://cirrus-ci.com/github/tailix/libkernaux)

Binding to [libkernaux](https://github.com/tailix/libkernaux) - auxiliary
library for kernel development.



Install
-------

Add the following to your `Gemfile`:

```ruby
gem 'kernaux', '~> 0.7.0'
```

Or add the following to your `*.gemspec`:

```ruby
Gem::Specification.new do |spec|
  # ...
  spec.add_runtime_dependency 'kernaux', '~> 0.7.0'
  # ...
end
```
