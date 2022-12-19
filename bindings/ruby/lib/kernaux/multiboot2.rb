# frozen_string_literal: true

module KernAux
  ##
  # Multiboot 2 utils.
  #
  # @see https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html
  #
  module Multiboot2
    ##
    # Raised when a Multiboot 2 structure data which is shorter
    # than even it's base requested to be enough sized.
    #
    # @see Struct#enough!
    #
    class BaseSizeError < Error; end

    ##
    # Raised when an invalid Multiboot 2 structure requested to be valid.
    #
    # @see Struct#valid!
    #
    class InvalidError < Error; end

    ##
    # The base class for Multiboot 2 {Header} and {Info}.
    #
    # @abstract It requires an implementation in C to use **libkernaux**.
    #
    class Struct
      ##
      # @return [String]
      #
      attr_reader :data

      def initialize(data = '')
        @data = String data
        freeze if @data.frozen?
      end

      alias to_s data

      ##
      # @return [String]
      #
      def inspect
        '#<' \
        "#{self.class}" \
        ':' \
        "#{@data[...16].force_encoding(Encoding::ASCII).inspect}" \
        "#{'...' if @data.size > 16}" \
        '>'.freeze
      end

      ##
      # Freeze the structure and it's underlying data.
      #
      def freeze
        @data.freeze
        super
      end

      # :nocov:

      ##
      # Test whether a Multiboot 2 structure data is not shorter than it's base.
      #
      # @abstract
      # @return [Boolean]
      #
      def enough?
        raise NotImplementedError, "#{self.class}#enough?"
      end

      ##
      # Test whether a Multiboot 2 structure is valid.
      #
      # @abstract
      # @return [Boolean]
      #
      def valid?
        raise NotImplementedError, "#{self.class}#valid?"
      end

      # :nocov:

      ##
      # @return [Struct] self
      #
      # @raise [BaseSizeError] the structure size is too small
      #
      def enough!
        raise BaseSizeError, 'The structure size is too small' unless enough?

        self
      end

      ##
      # @return [Struct] self
      #
      # @raise [BaseSizeError] the structure size is too small
      # @raise [InvalidError] the structure is invalid
      #
      def valid!
        enough!
        raise InvalidError, 'The structure is invalid' unless valid?

        self
      end
    end

    ##
    # Multiboot 2 header.
    #
    # @see https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#Header-layout
    #
    class Header < Struct
      ##
      # Header magic number.
      #
      # @see https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#Header-magic-fields
      #
      MAGIC = 0xe85250d6

      ##
      # Header architecture field values.
      #
      # @see https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#Header-magic-fields
      # @see #arch_name
      #
      ARCH = { 0 => :i386, 4 => :mips32 }.freeze

      ##
      # Return the architecture field of the Multiboot 2 header.
      #
      # @return [nil, Symbol]
      #
      # @see https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#Header-magic-fields
      # @see ARCH
      #
      def arch_name = ARCH[arch]
    end

    ##
    # Multiboot 2 information.
    #
    # @see https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#Basic-tags-structure
    #
    class Info < Struct
    end
  end
end
