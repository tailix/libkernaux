# frozen_string_literal: true

require 'spec_helper'

KernAux::Version.supports_printf? and RSpec.describe KernAux, '.sprintf' do
  subject :sprintf do
    described_class.sprintf 'Hello, ', ['%s', 'World'], '!'
  end

  it { is_expected.to be_instance_of String }
  it { is_expected.to be_frozen }
  it { is_expected.to eq 'Hello, World!' }

  context 'for empty string value' do
    subject(:sprintf) { described_class.sprintf ['Hello testing%s'] }

    it { is_expected.to eq 'Hello testing' }
  end

  [
    ['',      'using regular tests'],
    ['_orig', 'using original tests'],
  ].each do |(suffix, description)|
    context description do
      printf_yml = File.expand_path(
        "../../../../../../common/printf#{suffix}.yml",
        __dir__,
      )

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
