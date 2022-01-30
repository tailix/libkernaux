# frozen_string_literal: true

require_relative 'kernaux/version'

# Native extensions
require_relative 'kernaux/default'

##
# Binding to libkernaux - auxiliary library for kernel development.
#
module KernAux
  # Default callback for assertions.
  # @see .assert_cb
  DEFAULT_ASSERT_CB = @assert_cb = lambda { |file, line, msg|
    raise AssertError, "#{file}:#{line}:#{msg}"
  }

  # Buffer size for {.sprintf1}.
  # @todo Make it dynamic.
  SPRINTF1_BUFFER_SIZE = 10_000

  # @!scope class

  ##
  # @!attribute [rw] assert_cb
  # Panic callback.
  #
  # @see .panic
  # @see .assert_do
  ##

  ##
  # Raise assertion with implicit file and line, retrieved from `caller`, and
  # explicit message.
  #
  # @param msg [String] any message
  # @return [nil]
  #
  # @raise [AssertError] if {.assert_cb} have not been changed
  #
  # @see .assert_do Explicit file and line.
  #
  def self.panic(msg)
    file, line = caller(1..1).first.split(':')[0..1]
    assert_do file, Integer(line), msg
  end

  ##
  # @!method assert_do(file, line, msg)
  # Raise assertion with explicit file, line and message.
  #
  # @param file [String] file name, usually from `__FILE__`
  # @param line [Integer] line number, usually from `__LINE__`
  # @param msg [String] any message
  # @return [nil]
  #
  # @raise [AssertError] if {.assert_cb} have not been changed
  #
  # @see .panic Implicit file and line

  # @!parse [ruby] def assert_do(file, line, msg); end

  if singleton_class.method_defined? :snprintf1
    ##
    # Typical `printf`.
    #
    # @param args [Array<String, Array<(String, Object)>>]
    # @return [String] formatted output
    #
    # @example
    #   KernAux.sprintf 'foo', ['%*s', 5, 'bar'], 'car', ['%d', 123]
    #   #=> "foo  barcar123"
    #
    def self.sprintf(*args)
      args.map do |arg|
        if arg.is_a? Array
          sprintf1(*arg)
        else
          arg
        end
      end.join.freeze
    end

    ##
    # `printf` for single formatting parameter.
    #
    # @param format [String] formatting string
    # @return [String] formatted output
    #
    # @see .sprintf Multiple formatting parameters
    #
    # @example
    #   KernAux.sprintf1 '%%'            #=> "%"
    #   KernAux.sprintf1 '%s', 'foo'     #=> "foo"
    #   KernAux.sprintf1 '%5s', 'foo'    #=> "  foo"
    #   KernAux.sprintf1 '%*s', 5, 'foo' #=> "  foo"
    #
    def self.sprintf1(format, *args)
      snprintf1(SPRINTF1_BUFFER_SIZE, format, *args).first
    end

    ##
    # @!method snprintf1(buffer_size, format, ...)
    # `printf` for single formatting parameter with manual buffer size.
    #
    # @param buffer_size [Integer] buffer size (including terminating null
    #   character)
    # @param format [String] formatting string
    # @return [String] formatted output
    #
    # @see .sprintf1 Automatic buffer size
    ##
  end

  ##
  # Our base class for runtime errors.
  #
  class Error < RuntimeError; end

  ##
  # Raised when assertion has failed or panic has been called.
  #
  # @see .panic
  # @see .assert_do
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
