# frozen_string_literal: true

# rubocop:disable Style/Documentation
begin; end

module KernAux
  # Buffer size for {.sprintf1}.
  # @todo Make it dynamic.
  SPRINTF1_BUFFER_SIZE = 10_000

  # @!scope class

  # @!parse [ruby]

  if Version.with_printf?
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
end

# rubocop:enable Style/Documentation
