# frozen_string_literal: true

require 'spec_helper'

KernAux::Version.with_printf? and RSpec.describe KernAux, '.sprintf' do
  subject :sprintf do
    described_class.sprintf 'Hello, %s!', 'World'
  end

  it { is_expected.to be_instance_of String }
  it { is_expected.to be_frozen }
  it { is_expected.to eq 'Hello, World!' }

  context 'when there are unnecessary arguments at all' do
    subject(:sprintf) { described_class.sprintf 'Hello!', 'World' }

    specify do
      expect { sprintf }.to raise_error ArgumentError, 'too many arguments'
    end
  end

  context 'when there are too many arguments' do
    subject(:sprintf) { described_class.sprintf 'Hello, %s!', 'World', 'Alex' }

    specify do
      expect { sprintf }.to raise_error ArgumentError, 'too many arguments'
    end
  end

  context 'when there are no arguments' do
    subject(:sprintf) { described_class.sprintf }

    specify do
      expect { sprintf }.to raise_error ArgumentError, 'too few arguments'
    end
  end

  context 'when the argument is absent' do
    subject(:sprintf) { described_class.sprintf 'Hello, %s!' }

    specify do
      expect { sprintf }.to raise_error ArgumentError, 'too few arguments'
    end
  end

  context 'when the arguments after the width are absent' do
    subject(:sprintf) { described_class.sprintf 'Hello, %*s!', 20 }

    specify do
      expect { sprintf }.to raise_error ArgumentError, 'too few arguments'
    end
  end

  context 'when the arguments after the precision are absent' do
    subject(:sprintf) { described_class.sprintf 'Hello, %.*s!', 20 }

    specify do
      expect { sprintf }.to raise_error ArgumentError, 'too few arguments'
    end
  end

  context 'when the arguments after the width and the precision are absent' do
    subject(:sprintf) { described_class.sprintf 'Hello, %*.*s!', 20, 20 }

    specify do
      expect { sprintf }.to raise_error ArgumentError, 'too few arguments'
    end
  end

  [
    ['',      'using regular tests'],
    ['_orig', 'using original tests'],
  ].each do |(suffix, description)|
    context description do
      printf_yml = File.expand_path(
        "../../../../../common/printf#{suffix}.yml",
        __dir__,
      )

      YAML.safe_load_file(printf_yml).each do |test|
        expected = test['result']

        format = ''
        args = []

        test['args'].each do |arg|
          if arg.is_a? String
            format += arg
          else
            format += arg[0]
            arg[1..].each do |item|
              if item.is_a? Array
                if item.length == 1
                  args << item[0]
                elsif item[0] == 'long long'
                  args << item[1]
                else
                  raise "Unknown format: #{args.inspect}"
                end
              else
                args << item
              end
            end
          end
        end

        it "transforms (#{format.inspect}, #{args.inspect[1...-1]}) " \
           "to #{expected.inspect}" do
          expect(described_class.sprintf(format, *args)).to eq expected
        end
      end
    end
  end
end
