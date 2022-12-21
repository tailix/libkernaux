def test_cmdline(str, expected)
  result = KernAux.cmdline str

  assert_true result.instance_of? Array
  assert_true result.frozen?
  result.each do |item|
    assert_true item.instance_of? String
    assert_true item.frozen?
  end

  assert_equal result, expected
end

if KernAux::Version.with_cmdline?
  assert 'default' do
    test_cmdline 'foo bar\\ baz "car cdr"', ['foo', 'bar baz', 'car cdr']
  end

  assert 'when str is empty' do
    test_cmdline '', []
  end

  assert 'when str has invalid type' do
    assert_raise TypeError, 'Integer cannot be converted to String' do
      KernAux.cmdline 123
    end
  end

  assert 'when str has EOL after backslash' do
    assert_raise KernAux::CmdlineError, 'EOL after backslash' do
      KernAux.cmdline '\\'
    end
  end

  assert 'when str has EOL after backslash inside quote' do
    assert_raise KernAux::CmdlineError, 'EOL after backslash inside quote' do
      KernAux.cmdline '"\\'
    end
  end

  assert 'when str has unescaped quotation mark' do
    assert_raise KernAux::CmdlineError, 'unescaped quotation mark' do
      KernAux.cmdline 'foo"'
    end
  end

  assert 'when str has EOL inside quote' do
    assert_raise KernAux::CmdlineError, 'EOL inside quote' do
      KernAux.cmdline '"'
    end
  end

  assert 'when there are not too many args' do
    test_cmdline 'a ' * 256, ['a'] * 256
  end

  assert 'when there are too many args' do
    assert_raise KernAux::CmdlineError, 'too many args' do
      KernAux.cmdline 'a ' * 257
    end
  end

  assert 'when args don\'t cause buffer overflow' do
    test_cmdline 'a' * 4095, ['a' * 4095]
  end

  assert 'when args cause buffer overflow' do
    assert_raise KernAux::CmdlineError, 'EOF or buffer overflow' do
      KernAux.cmdline 'a' * 4096
    end
  end

  assert 'usign fixtures' do
    cmdline_yml = File.expand_path('../../../../fixtures/cmdline.yml', __FILE__)

    YAML.load(File.read(cmdline_yml)).each do |test|
      escape_str = lambda do |str|
        eval "\"#{str}\"", nil, __FILE__, __LINE__ # "str"
      end

      cmdline = escape_str.call test['cmdline']
      arg_count_max = test['arg_count_max']
      buffer_size = test['buffer_size']
      result = test['result']&.map(&escape_str)

      next unless arg_count_max.nil? && buffer_size.nil? && !result.nil?

      assert "transforms #{cmdline.inspect} to #{result.inspect}" do
        assert_equal KernAux.cmdline(cmdline), result
      end
    end
  end
end
