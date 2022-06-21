if KernAux::Version.with_printf?
  assert 'KernAux.sprintf' do
    assert 'integers' do
      assert_equal 'i:0',           KernAux.sprintf('i:',  ['%i', 0])
      assert_equal 'u:0',           KernAux.sprintf('u:',  ['%u', 0])
      assert_equal 'i:1',           KernAux.sprintf('i:',  ['%i', 1])
      assert_equal 'u:1',           KernAux.sprintf('u:',  ['%u', 1])
      assert_equal 'i:10',          KernAux.sprintf('i:',  ['%i', 10])
      assert_equal 'u:10',          KernAux.sprintf('u:',  ['%u', 10])
      assert_equal 'i:100',         KernAux.sprintf('i:',  ['%i', 100])
      assert_equal 'u:100',         KernAux.sprintf('u:',  ['%u', 100])
      assert_equal 'i:1000',        KernAux.sprintf('i:',  ['%i', 1000])
      assert_equal 'u:1000',        KernAux.sprintf('u:',  ['%u', 1000])
      assert_equal 'i:10000',       KernAux.sprintf('i:',  ['%i', 10_000])
      assert_equal 'u:10000',       KernAux.sprintf('u:',  ['%u', 10_000])
      assert_equal 'i:100000',      KernAux.sprintf('i:',  ['%i', 100_000])
      assert_equal 'u:100000',      KernAux.sprintf('u:',  ['%u', 100_000])
      assert_equal 'i:1000000',     KernAux.sprintf('i:',  ['%i', 1_000_000])
      assert_equal 'u:1000000',     KernAux.sprintf('u:',  ['%u', 1_000_000])
      assert_equal 'i:10000000',    KernAux.sprintf('i:',  ['%i', 10_000_000])
      assert_equal 'u:10000000',    KernAux.sprintf('u:',  ['%u', 10_000_000])
      assert_equal 'i:100000000',   KernAux.sprintf('i:',  ['%i', 10**8])
      assert_equal 'u:100000000',   KernAux.sprintf('u:',  ['%u', 10**8])
      assert_equal 'i:1000000000',  KernAux.sprintf('i:',  ['%i', 10**9])
      assert_equal 'u:1000000000',  KernAux.sprintf('u:',  ['%u', 10**9])
      assert_equal 'i:2147483647',  KernAux.sprintf('i:',  ['%i', 2**31 - 1])
      assert_equal 'u:2147483647',  KernAux.sprintf('u:',  ['%u', 2**31 - 1])
    end

    # TODO: test with different boxing
    # assert 'integer overflows' do
    #   assert_equal 'i:-2147483648', KernAux.sprintf('i:',  ['%i', 2**31])
    #   assert_equal 'u: 2147483648', KernAux.sprintf('u: ', ['%u', 2**31])
    #   assert_equal 'i:-2147483647', KernAux.sprintf('i:',  ['%i', 2**31 + 1])
    #   assert_equal 'u: 2147483649', KernAux.sprintf('u: ', ['%u', 2**31 + 1])
    #   assert_equal 'i:-1',          KernAux.sprintf('i:',  ['%i', 2**32 - 1])
    #   assert_equal 'u: 4294967295', KernAux.sprintf('u: ', ['%u', 2**32 - 1])
    #   assert_equal 'i: 0',          KernAux.sprintf('i: ', ['%i', 2**32])
    #   assert_equal 'u: 0',          KernAux.sprintf('u: ', ['%u', 2**32])
    # end

    [
      ['',      'using regular tests'],
      ['_orig', 'using original tests'],
    ].each do |(suffix, description)|
      assert description do
        printf_yml =
          File.expand_path("../../../../common/printf#{suffix}.yml", __FILE__)

        YAML.load(File.read(printf_yml)).each do |test|
          expected = test['result']

          args = test['args'].map do |arg|
            if arg.is_a? String
              arg
            else
              arg.map do |item|
                if item.is_a? Array
                  if item.length == 1
                    item[0]
                  elsif item[0] == 'long long'
                    item[1]
                  else
                    raise "Unknown format: #{args.inspect}"
                  end
                else
                  item
                end
              end
            end
          end

          assert "transforms #{args.inspect} to #{expected.inspect}" do
            assert_equal expected, KernAux.sprintf(*args)
          end
        end
      end
    end
  end
end
