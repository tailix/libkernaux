# frozen_string_literal: true

require_relative 'kernaux/version'

##
# Auxiliary library for kernel development.
#
module KernAux
  # Default callback for assertions ({.assert_cb})
  DEFAULT_ASSERT_CB = @assert_cb = lambda { |file, line, str|
    raise AssertError, "#{file}:#{line}:#{str}"
  }

  # Buffer size for {.sprintf1}
  # @todo make it dynamic
  SPRINTF1_BUFFER_SIZE = 10_000

  def self.panic(msg)
    file, line = caller(1..1).first.split(':')[0..1]
    assert_do file, Integer(line), msg
  end

  def self.sprintf(*args)
    args.map do |arg|
      if arg.is_a? Array
        sprintf1(*arg)
      else
        arg
      end
    end.join.freeze
  end

  def self.sprintf1(format, arg = nil)
    if arg.nil?
      snprintf1(SPRINTF1_BUFFER_SIZE, format).first
    else
      snprintf1(SPRINTF1_BUFFER_SIZE, format, arg).first
    end
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
end

# Native extension
require_relative 'kernaux/default'
