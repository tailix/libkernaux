# frozen_string_literal: true

require_relative 'kernaux/version'

# Native extensions
require_relative 'kernaux/default'

##
# Binding to libkernaux - auxiliary library for kernel development.
#
module KernAux
  # Default callback for assertions ({.assert_cb})
  DEFAULT_ASSERT_CB = @assert_cb = lambda { |file, line, msg|
    raise AssertError, "#{file}:#{line}:#{msg}"
  }

  # Buffer size for {.sprintf1}
  # @todo make it dynamic
  SPRINTF1_BUFFER_SIZE = 10_000

  def self.panic(msg)
    file, line = caller(1..1).first.split(':')[0..1]
    assert_do file, Integer(line), msg
  end

  if singleton_class.method_defined? :snprintf1
    def self.sprintf(*args)
      args.map do |arg|
        if arg.is_a? Array
          sprintf1(*arg)
        else
          arg
        end
      end.join.freeze
    end

    def self.sprintf1(...) = snprintf1(SPRINTF1_BUFFER_SIZE, ...).first
  end

  ##
  # Our base class for runtime errors.
  #
  class Error < RuntimeError; end

  ##
  # Raised when assertion has failed or panic has been called.
  #
  # @see .panic
  #
  class AssertError < Error; end

  ##
  # Raised when command line parsing goes wrong.
  #
  # @see .cmdline
  #
  class CmdlineError < Error; end

  ##
  # Raised when integer base is invalid.
  #
  # @see .utoa
  # @see .itoa
  #
  class InvalidNtoaBaseError < Error; end
end
