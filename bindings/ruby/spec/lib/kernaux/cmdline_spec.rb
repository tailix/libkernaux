# frozen_string_literal: true

require 'spec_helper'

KernAux::Version.with_cmdline? and RSpec.describe KernAux, '.cmdline' do
  subject(:cmdline) { described_class.cmdline str }

  let(:str) { 'foo bar\\ baz "car cdr"' }

  it { is_expected.to be_instance_of Array }
  it { is_expected.to be_frozen }
  it { is_expected.to all be_instance_of String }
  it { is_expected.to all be_frozen }
  it { is_expected.to eq ['foo', 'bar baz', 'car cdr'] }

  context 'when str is empty' do
    let(:str) { '' }

    it { is_expected.to eq [] }
  end

  context 'when str has invalid type' do
    let(:str) { 123 }

    specify { expect { cmdline }.to raise_error TypeError }
  end

  context 'when str has EOL after backslash' do
    let(:str) { '\\' }

    specify do
      expect { cmdline }.to \
        raise_error described_class::CmdlineError, 'EOL after backslash'
    end
  end

  context 'when str has EOL after backslash inside quote' do
    let(:str) { '"\\' }

    specify do
      expect { cmdline }.to raise_error \
        described_class::CmdlineError, 'EOL after backslash inside quote'
    end
  end

  context 'when str has unescaped quotation mark' do
    let(:str) { 'foo"' }

    specify do
      expect { cmdline }.to \
        raise_error described_class::CmdlineError, 'unescaped quotation mark'
    end
  end

  context 'when str has EOL inside quote' do
    let(:str) { '"' }

    specify do
      expect { cmdline }.to \
        raise_error described_class::CmdlineError, 'EOL inside quote'
    end
  end

  context 'when there are not too many args' do
    let(:str) { 'a ' * 256 }

    it { is_expected.to eq ['a'] * 256 }
  end

  context 'when there are too many args' do
    let(:str) { 'a ' * 257 }

    specify do
      expect { cmdline }.to \
        raise_error described_class::CmdlineError, 'too many args'
    end
  end

  context 'when args don\'t cause buffer overflow' do
    let(:str) { 'a' * 4095 }

    it { is_expected.to eq ['a' * 4095] }
  end

  context 'when args cause buffer overflow' do
    let(:str) { 'a' * 4096 }

    specify do
      expect { cmdline }.to \
        raise_error described_class::CmdlineError, 'EOF or buffer overflow'
    end
  end

  context 'using fixtures' do
    cmdline_yml =
      File.expand_path('../../../../../fixtures/cmdline.yml', __dir__)

    YAML.safe_load_file(cmdline_yml).each do |test|
      escape_str = lambda do |str|
        eval "\"#{str}\"", binding, __FILE__, __LINE__ # "str"
      end

      cmdline = escape_str.call test['cmdline']
      arg_count_max = test['arg_count_max']
      buffer_size = test['buffer_size']
      result = test['result']&.map(&escape_str)

      next unless arg_count_max.nil? && buffer_size.nil? && !result.nil?

      it "transforms #{cmdline.inspect} to #{result.inspect}" do
        expect(described_class.cmdline(cmdline)).to eq result
      end
    end
  end
end
