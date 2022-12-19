if KernAux::Version.with_printf?
  assert 'KernAux.sprintf' do
    assert 'integers' do
      assert_equal 'i:0',           KernAux.sprintf('i:%i',  0)
      assert_equal 'u:0',           KernAux.sprintf('u:%u',  0)
      assert_equal 'i:1',           KernAux.sprintf('i:%i',  1)
      assert_equal 'u:1',           KernAux.sprintf('u:%u',  1)
      assert_equal 'i:10',          KernAux.sprintf('i:%i',  10)
      assert_equal 'u:10',          KernAux.sprintf('u:%u',  10)
      assert_equal 'i:100',         KernAux.sprintf('i:%i',  100)
      assert_equal 'u:100',         KernAux.sprintf('u:%u',  100)
      assert_equal 'i:1000',        KernAux.sprintf('i:%i',  1000)
      assert_equal 'u:1000',        KernAux.sprintf('u:%u',  1000)
      assert_equal 'i:10000',       KernAux.sprintf('i:%i',  10_000)
      assert_equal 'u:10000',       KernAux.sprintf('u:%u',  10_000)
      assert_equal 'i:100000',      KernAux.sprintf('i:%i',  100_000)
      assert_equal 'u:100000',      KernAux.sprintf('u:%u',  100_000)
      assert_equal 'i:1000000',     KernAux.sprintf('i:%i',  1_000_000)
      assert_equal 'u:1000000',     KernAux.sprintf('u:%u',  1_000_000)
      assert_equal 'i:10000000',    KernAux.sprintf('i:%i',  10_000_000)
      assert_equal 'u:10000000',    KernAux.sprintf('u:%u',  10_000_000)
      assert_equal 'i:100000000',   KernAux.sprintf('i:%i',  10**8)
      assert_equal 'u:100000000',   KernAux.sprintf('u:%u',  10**8)
      assert_equal 'i:1000000000',  KernAux.sprintf('i:%i',  10**9)
      assert_equal 'u:1000000000',  KernAux.sprintf('u:%u',  10**9)
      assert_equal 'i:2147483647',  KernAux.sprintf('i:%i',  2**31 - 1)
      assert_equal 'u:2147483647',  KernAux.sprintf('u:%u',  2**31 - 1)
    end

    # TODO: test with different boxing
    # assert 'integer overflows' do
    #   assert_equal 'i:-2147483648', KernAux.sprintf('i:%i',  2**31)
    #   assert_equal 'u: 2147483648', KernAux.sprintf('u: %u', 2**31)
    #   assert_equal 'i:-2147483647', KernAux.sprintf('i:%i',  2**31 + 1)
    #   assert_equal 'u: 2147483649', KernAux.sprintf('u: %u', 2**31 + 1)
    #   assert_equal 'i:-1',          KernAux.sprintf('i:%i',  2**32 - 1)
    #   assert_equal 'u: 4294967295', KernAux.sprintf('u: %u', 2**32 - 1)
    #   assert_equal 'i: 0',          KernAux.sprintf('i: %i', 2**32)
    #   assert_equal 'u: 0',          KernAux.sprintf('u: %u', 2**32)
    # end

    assert 'when there are too many arguments' do
      [
        ['Hello!', 'World!'],
        ['Hello, %s!', 'World', 'Alex'],
      ].each do |args|
        assert_raise ArgumentError, 'too many arguments' do
          KernAux.sprintf(*args)
        end
      end
    end

    assert 'when there are too few arguments' do
      [
        [],
        ['Hello, %s!'],
        ['Hello, %*s!', 20],
        ['Hello, %.*s!', 20],
        ['Hello, %*.*s!', 20, 20],
      ].each do |args|
        assert_raise ArgumentError, 'too few arguments' do
          KernAux.sprintf(*args)
        end
      end
    end

    [
      ['',      'using regular fixtures'],
      ['_orig', 'using original fixtures'],
    ].each do |(suffix, description)|
      assert description do
        printf_yml =
          File.expand_path("../../../../fixtures/printf#{suffix}.yml", __FILE__)

        YAML.load(File.read(printf_yml)).each do |test|
          expected = test['result']

          format = ''
          args = []

          test['args'].each do |arg|
            if arg.is_a? String
              format += arg
            else
              format += arg[0]
              is_int_format = %w[i d u x X o b].any? { |s| arg[0].include? s }
              arg[1..].each do |item|
                if item.is_a? Array
                  if item.length == 1
                    args << item[0]
                  elsif item[0] == 'long long'
                    args << item[1]
                  else
                    raise "Unknown format: #{args.inspect}"
                  end
                elsif is_int_format && item.is_a?(Float)
                  args << item.round
                else
                  args << item
                end
              end
            end
          end

          assert "transforms (#{format.inspect}, #{args.inspect[1...-1]}) " \
                 "to #{expected.inspect}" do
            assert_equal expected, KernAux.sprintf(format, *args)
          end
        end
      end
    end
  end
end
