# frozen_string_literal: true

module KernAux
  # Gem version.
  VERSION = '0.3.0'

  ##
  # This module includes functions to determine if specific features are
  # supported by the library.
  #
  module Version
    def self.supports_cmdline?
      KernAux.singleton_class.method_defined? :cmdline
    end

    def self.supports_file?
      defined? KernAux::File
    end

    def self.supports_itoa?
      KernAux.singleton_class.method_defined? :itoa
    end

    def self.supports_itoa2?
      KernAux.singleton_class.method_defined? :itoa2
    end

    def self.supports_itoa8?
      KernAux.singleton_class.method_defined? :itoa8
    end

    def self.supports_itoa10?
      KernAux.singleton_class.method_defined? :itoa10
    end

    def self.supports_itoa16?
      KernAux.singleton_class.method_defined? :itoa16
    end

    def self.supports_printf?
      KernAux.singleton_class.method_defined? :snprintf1
    end

    def self.supports_utoa?
      KernAux.singleton_class.method_defined? :utoa
    end

    def self.supports_utoa2?
      KernAux.singleton_class.method_defined? :utoa2
    end

    def self.supports_utoa8?
      KernAux.singleton_class.method_defined? :utoa8
    end

    def self.supports_utoa10?
      KernAux.singleton_class.method_defined? :utoa10
    end

    def self.supports_utoa16?
      KernAux.singleton_class.method_defined? :utoa16
    end
  end
end
