# frozen_string_literal: true

require_relative 'kernaux/version'

##
# Auxiliary library for kernel development.
#
module KernAux
  # Default callback for assertions
  DEFAULT_ASSERT_CB = lambda { |file, line, str|
    raise AssertError, "#{file}:#{line}:#{str}"
  }

  @assert_cb = DEFAULT_ASSERT_CB

  def self.panic(msg)
    file, line = caller(1..1).first.split(':')[0..1]
    assert_do file, Integer(line), msg
  end

  ##
  # Our base class for runtime errors.
  #
  class Error < RuntimeError; end

  ##
  # Raised when assertion has failed or panic has been called.
  #
  class AssertError < Error; end
end

# Native extension
require_relative 'kernaux/default'
