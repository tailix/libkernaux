# frozen_string_literal: true

require 'spec_helper'

RSpec.describe KernAux, '.sprintf' do
  if described_class.singleton_class.method_defined? :sprintf
    subject(:sprintf) { described_class.sprintf 'Hello, ', ['%s', 'World'], '!' }

    it { is_expected.to be_instance_of String }
    it { is_expected.to be_frozen }
    it { is_expected.to eq 'Hello, World!' }

    context 'using original tests' do
      printf_yml =
        File.expand_path('../../../../../tests/printf_orig.yml', __dir__)

      YAML.safe_load_file(printf_yml).each do |test|
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

        it "transforms #{args.inspect} to #{expected.inspect}" do
          expect(described_class.sprintf(*args)).to eq expected
        end
      end
    end
  end
end
