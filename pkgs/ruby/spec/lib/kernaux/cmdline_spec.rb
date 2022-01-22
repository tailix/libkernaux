# frozen_string_literal: true

require 'spec_helper'

RSpec.describe KernAux, '.cmdline' do
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

  xcontext 'when there are too many args' do
    let(:str) { 'a ' * 257 }

    specify do
      expect { cmdline }.to \
        raise_error described_class::CmdlineError, 'too many args'
    end
  end

  xcontext 'when args cause buffer overflow' do
    let(:str) { 'a' * 4096 }

    specify do
      expect { cmdline }.to \
        raise_error described_class::CmdlineError, 'buffer overflow'
    end
  end
end
