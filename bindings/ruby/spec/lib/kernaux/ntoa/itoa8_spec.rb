# frozen_string_literal: true

require 'spec_helper'

KernAux::Version.with_ntoa? and RSpec.describe KernAux, '.itoa8' do
  subject(:itoa8) { described_class.itoa8 number }

  let(:number) { rand((-2**63)..(2**63 - 1)) }

  def sign = number < 0 ? '-' : ''

  it { is_expected.to be_instance_of String }
  it { is_expected.to be_frozen }
  it { is_expected.to eq "#{sign}0o#{number.abs.to_s(8)}" }

  context 'when number is 0' do
    let(:number) { 0 }

    it { is_expected.to eq '0o0' }
  end

  context 'when number is 1' do
    let(:number) { 1 }

    it { is_expected.to eq '0o1' }
  end

  context 'when number is -1' do
    let(:number) { -1 }

    it { is_expected.to eq '-0o1' }
  end

  context 'when number is min int64_t' do
    let(:number) { -2**63 }

    it { is_expected.to eq "-0o#{number.abs.to_s(8)}" }
  end

  context 'when number is max int64_t' do
    let(:number) { 2**63 - 1 }

    it { is_expected.to eq "0o#{number.to_s(8)}" }
  end

  context 'when number is lesser than min uint64_t' do
    let(:number) { -2**63 - 1 }

    specify do
      expect { itoa8 }.to raise_error \
        RangeError, 'bignum too big to convert into `long long\''
    end
  end

  context 'when number is greater than max uint64_t' do
    let(:number) { 2**63 }

    specify do
      expect { itoa8 }.to raise_error \
        RangeError, 'bignum too big to convert into `long long\''
    end
  end

  context 'when number is not numeric' do
    let(:number) { rand((-2**63)..(2**63 - 1)).to_s }

    specify do
      expect { itoa8 }.to raise_error \
        TypeError, 'no implicit conversion from string'
    end
  end
end
