# frozen_string_literal: true

require_relative 'kernaux/version'

# Native extensions
require_relative 'kernaux/default'

require_relative 'kernaux/file'

##
# Binding to [libkernaux](https://github.com/tailix/libkernaux) - auxiliary
# library for kernel development.
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
  # @api unsafe
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

  # @!parse [ruby]

  if singleton_class.method_defined? :snprintf1
    ##
    # Typical `printf`.
    #
    # @param args [Array<String,
    #              Array<(String, Object)>,
    #              Array<(String, Integer, Object)>>]
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
    # @return [Array<(String, Integer)>] formatted output and it's size
    #
    # @see .sprintf1 Automatic buffer size
    ##
  end

  ##
  # @!method cmdline(str)
  # Parse command line.
  #
  # @param str [String] command line string
  # @return [Array<String>] command line arguments
  #
  # @raise [CmdlineError] syntax is invalid

  # @!parse [ruby]

  ##
  # @!method utoa(number, base, prefix)
  # Convert `uint64_t` to a string in multiple numeral systems.
  #
  # Base can be a positive or negative integer between 2 and 36, or a symbol
  # which is an alias to a valid integer value. Positive integers and lowercase
  # symbols mean lowercase output when base is greater than 10. Negative
  # integers and uppercase symbols mean uppercase output when base is greater
  # than 10. Aliases are: `:b`, `:B` - 2; `:o`, `:O` - 8; `:d`, `:D` - 10; `:h`,
  # `:x` - 16 (lowercase); `:H`, `:X` - -10 (uppercase).
  #
  # @param number [Integer] a number between 0 and `UINT64_MAX`
  # @param base [Integer, Symbol] base of a numeral system
  # @param prefix [nil, String] string to put before a number
  # @return [String]
  #
  # @raise [RangeError] number is out of range
  # @raise [InvalidNtoaBaseError] base is invalid
  # @raise [TooLongNtoaPrefixError] prefix is too long
  #
  # @see .itoa Convert signed integers
  ##

  ##
  # @!method itoa(number, base, prefix)
  # Convert `int64_t` to a string in multiple numeral systems.
  #
  # Base can be a positive or negative integer between 2 and 36, or a symbol
  # which is an alias to a valid integer value. Positive integers and lowercase
  # symbols mean lowercase output when base is greater than 10. Negative
  # integers and uppercase symbols mean uppercase output when base is greater
  # than 10. Aliases are: `:b`, `:B` - 2; `:o`, `:O` - 8; `:d`, `:D` - 10; `:h`,
  # `:x` - 16 (lowercase); `:H`, `:X` - -10 (uppercase).
  #
  # @param number [Integer] a number between `INT64_MIN` and `INT64_MAX`
  # @param base [Integer, Symbol] base of a numeral system
  # @param prefix [nil, String] string to put between a sign and a number
  # @return [String]
  #
  # @raise [RangeError] number is out of range
  # @raise [InvalidNtoaBaseError] base is invalid
  # @raise [TooLongNtoaPrefixError] prefix is too long
  #
  # @see .utoa Convert unsigned integers
  ##

  ##
  # @!method utoa2(number)
  # Convert `uint64_t` to a binary string.
  #
  # @param number [Integer] a number between 0 and `UINT64_MAX`
  # @return [String]
  #
  # @raise [RangeError] number is out of range
  ##

  ##
  # @!method itoa2(number)
  # Convert `int64_t` to a binary string.
  #
  # @param number [Integer] a number between `INT64_MIN` and `INT64_MAX`
  # @return [String]
  #
  # @raise [RangeError] number is out of range
  ##

  ##
  # @!method utoa8(number)
  # Convert `uint64_t` to a octal string.
  #
  # @param number [Integer] a number between 0 and `UINT64_MAX`
  # @return [String]
  #
  # @raise [RangeError] number is out of range
  ##

  ##
  # @!method itoa8(number)
  # Convert `int64_t` to a octal string.
  #
  # @param number [Integer] a number between `INT64_MIN` and `INT64_MAX`
  # @return [String]
  #
  # @raise [RangeError] number is out of range
  ##

  ##
  # @!method utoa10(number)
  # Convert `uint64_t` to a decimal string.
  #
  # @param number [Integer] a number between 0 and `UINT64_MAX`
  # @return [String]
  #
  # @raise [RangeError] number is out of range
  ##

  ##
  # @!method itoa10(number)
  # Convert `int64_t` to a decimal string.
  #
  # @param number [Integer] a number between `INT64_MIN` and `INT64_MAX`
  # @return [String]
  #
  # @raise [RangeError] number is out of range
  ##

  ##
  # @!method utoa16(number)
  # Convert `uint64_t` to a hexadecimal string.
  #
  # @param number [Integer] a number between 0 and `UINT64_MAX`
  # @return [String]
  #
  # @raise [RangeError] number is out of range
  ##

  ##
  # @!method itoa16(number)
  # Convert `int64_t` to a hexadecimal string.
  #
  # @param number [Integer] a number between `INT64_MIN` and `INT64_MAX`
  # @return [String]
  #
  # @raise [RangeError] number is out of range
  ##

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

  ##
  # Raised when prefix is too long.
  #
  # @see .utoa
  # @see .itoa
  #
  class TooLongNtoaPrefixError < Error; end
end
