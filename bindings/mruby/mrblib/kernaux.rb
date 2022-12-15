##
# Binding to [libkernaux](https://github.com/tailix/libkernaux) - auxiliary
# library for kernel development.
#
module KernAux
  DEFAULT_ASSERT_CB = @assert_cb = lambda { |file, line, msg|
    raise AssertError, "#{file}:#{line}:#{msg}"
  }

  class Error < RuntimeError; end
  class AssertError < Error; end
  class CmdlineError < Error; end
  class InvalidNtoaBaseError < Error; end
  class TooLongNtoaPrefixError < Error; end
end
