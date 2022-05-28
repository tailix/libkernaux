# TODO: implement this
# rubocop:disable Style/BlockComments
=begin
assert 'KernAux.sprintf' do
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
                item[0]
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
=end
# rubocop:enable Style/BlockComments
