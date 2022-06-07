# frozen_string_literal: true

# rubocop:disable Style/Documentation
begin; end

module KernAux
  # @!scope class

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
end

# rubocop:enable Style/Documentation
