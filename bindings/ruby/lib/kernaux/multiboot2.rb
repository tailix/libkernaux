# frozen_string_literal: true

module KernAux
  ##
  # Multiboot 2 utils.
  #
  # @see https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html
  #
  module Multiboot2
    ##
    # Raised when trying to create a Multiboot 2 structure
    # which is shorter than even it's base.
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
    # The base class for any Multiboot 2 structure.
    #
    class Struct
      def initialize(data)
        @data = String data
      end

      ##
      # Freeze the structure and it's underlying data.
      #
      def freeze
        @data.freeze
        super
        nil
      end

      def enough?
        raise NotImplementedError, "#{self.class}#enough?"
      end

      def valid?
        raise NotImplementedError, "#{self.class}#valid?"
      end

      ##
      # @raise [BaseSizeError] the structure size is too small
      #
      def enough!
        raise BaseSizeError, 'The structure size is too small' unless enough?
      end

      ##
      # @raise [BaseSizeError] the structure size is too small
      # @raise [InvalidError] the structure is invalid
      #
      def valid!
        enough!
        raise InvalidError, 'The structure is invalid' unless valid?
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
      # @return [Symbol]
      #
      # @see https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#Header-magic-fields
      # @see ARCH
      #
      def arch_name = ARCH[arch]
    end
  end
end
