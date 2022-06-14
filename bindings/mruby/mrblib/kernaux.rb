##
# Binding to [libkernaux](https://github.com/tailix/libkernaux) - auxiliary
# library for kernel development.
#
module KernAux
  DEFAULT_ASSERT_CB = @assert_cb = lambda { |file, line, msg|
    raise AssertError, "#{file}:#{line}:#{msg}"
  }

  SPRINTF1_BUFFER_SIZE = 10_000

  if Version.with_printf?
    def self.sprintf(*args)
      args.map do |arg|
        if arg.is_a? Array
          sprintf1(*arg)
        else
          arg
        end
      end.join.freeze
    end

    def self.sprintf1(format, *args)
      snprintf1(SPRINTF1_BUFFER_SIZE, format, *args).first
    end
  end

  class Error < RuntimeError; end
  class AssertError < Error; end
  class CmdlineError < Error; end
  class InvalidNtoaBaseError < Error; end
  class TooLongNtoaPrefixError < Error; end
end
