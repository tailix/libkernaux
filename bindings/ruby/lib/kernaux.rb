# frozen_string_literal: true

##
# Binding to [libkernaux](https://github.com/tailix/libkernaux) - auxiliary
# library for kernel development.
#
module KernAux
end

require_relative 'kernaux/version'

# Native extensions
require_relative 'kernaux/default'

# Non-standard directory structure
require_relative 'kernaux/assert'
require_relative 'kernaux/cmdline'
require_relative 'kernaux/errors'
require_relative 'kernaux/ntoa'
