# frozen_string_literal: true

module KernAux
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
