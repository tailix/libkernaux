module KernAux
  DEFAULT_ASSERT_CB = @assert_cb = lambda { |file, line, msg|
    raise AssertError, "#{file}:#{line}:#{msg}"
  }

  class Error < RuntimeError; end
  class AssertError < Error; end
end
