# frozen_string_literal: true

# rubocop:disable Style/Documentation
begin; end

module KernAux
  # Default callback for assertions.
  # @see .assert_cb
  DEFAULT_ASSERT_CB = @assert_cb = lambda { |file, line, msg|
    raise AssertError, "#{file}:#{line}:#{msg}"
  }

  # @!scope class

  ##
  # @!attribute [rw] assert_cb
  # Panic callback.
  #
  # @return [Proc]
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
  ##
end

# rubocop:enable Style/Documentation
