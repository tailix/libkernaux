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
        args     = test['args']

        assert "transforms #{args.inspect} to #{expected.inspect}" do
          assert_equal expected, KernAux.sprintf(*args)
        end
      end
    end
  end
end
=end
# rubocop:enable Style/BlockComments
