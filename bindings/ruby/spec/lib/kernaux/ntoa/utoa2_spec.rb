# frozen_string_literal: true

require 'spec_helper'

KernAux::Version.with_ntoa? and RSpec.describe KernAux, '.utoa2' do
  subject(:utoa2) { described_class.utoa2 number }

  let(:number) { rand 0..(2**64 - 1) }

  it { is_expected.to be_instance_of String }
  it { is_expected.to be_frozen }
  it { is_expected.to eq "0b#{number.to_s(2)}" }

  context 'when number is 0' do
    let(:number) { 0 }

    it { is_expected.to eq '0b0' }
  end

  context 'when number is max uint64_t' do
    let(:number) { 2**64 - 1 }

    it { is_expected.to eq "0b#{number.to_s(2)}" }
  end

  context 'when number is -1' do
    let(:number) { -1 }

    specify do
      expect { utoa2 }.to \
        raise_error RangeError, 'can\'t convert negative number to uint64_t'
    end
  end

  context 'when number is greater than max uint64_t' do
    let(:number) { 2**64 }

    specify do
      expect { utoa2 }.to raise_error \
        RangeError, 'bignum too big to convert into `unsigned long long\''
    end
  end
end
