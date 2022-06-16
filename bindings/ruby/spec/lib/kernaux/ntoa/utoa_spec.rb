# frozen_string_literal: true

require 'spec_helper'

KernAux::Version.with_ntoa? and RSpec.describe KernAux, '.utoa' do
  subject(:utoa) { described_class.utoa number, base, prefix }

  let(:number) { rand 0..(2**64 - 1) }
  let(:base) { rand 2..36 }
  let(:prefix) { [nil, ''].sample }

  it { is_expected.to be_instance_of String }
  it { is_expected.to be_frozen }
  it { is_expected.to eq number.to_s base }

  context 'when number is 0' do
    let(:number) { 0 }

    it { is_expected.to be_instance_of String }
    it { is_expected.to be_frozen }
    it { is_expected.to eq '0' }
  end

  context 'when number is max uint64_t' do
    let(:number) { 2**64 - 1 }

    it { is_expected.to be_instance_of String }
    it { is_expected.to be_frozen }
    it { is_expected.to eq number.to_s base }
  end

  context 'when number is -1' do
    let(:number) { -1 }

    specify do
      expect { utoa }.to \
        raise_error RangeError, 'can\'t convert negative number to uint64_t'
    end
  end

  context 'when number is greater than max uint64_t' do
    let(:number) { 2**64 }

    specify do
      expect { utoa }.to raise_error \
        RangeError, 'bignum too big to convert into `unsigned long long\''
    end
  end

  context 'when number is not numeric' do
    let(:number) { rand(0..(2**64 - 1)).to_s }

    specify do
      expect { utoa }.to raise_error \
        TypeError, 'no implicit conversion from string'
    end
  end

  context 'when base is negative' do
    let(:base) { -rand(2..36) }

    it { is_expected.to be_instance_of String }
    it { is_expected.to be_frozen }
    it { is_expected.to eq number.to_s(-base).upcase }
  end

  context 'when base is :b' do
    let(:base) { :b }

    it { is_expected.to be_instance_of String }
    it { is_expected.to be_frozen }
    it { is_expected.to eq number.to_s 2 }
  end

  context 'when base is :B:' do
    let(:base) { :B }

    it { is_expected.to be_instance_of String }
    it { is_expected.to be_frozen }
    it { is_expected.to eq number.to_s 2 }
  end

  context 'when base is :o' do
    let(:base) { :o }

    it { is_expected.to be_instance_of String }
    it { is_expected.to be_frozen }
    it { is_expected.to eq number.to_s 8 }
  end

  context 'when base is :O' do
    let(:base) { :O }

    it { is_expected.to be_instance_of String }
    it { is_expected.to be_frozen }
    it { is_expected.to eq number.to_s 8 }
  end

  context 'when base is :d' do
    let(:base) { :d }

    it { is_expected.to be_instance_of String }
    it { is_expected.to be_frozen }
    it { is_expected.to eq number.to_s }
  end

  context 'when base is :D' do
    let(:base) { :D }

    it { is_expected.to be_instance_of String }
    it { is_expected.to be_frozen }
    it { is_expected.to eq number.to_s }
  end

  context 'when base is :h' do
    let(:base) { :h }

    it { is_expected.to be_instance_of String }
    it { is_expected.to be_frozen }
    it { is_expected.to eq number.to_s 16 }
  end

  context 'when base is :x' do
    let(:base) { :x }

    it { is_expected.to be_instance_of String }
    it { is_expected.to be_frozen }
    it { is_expected.to eq number.to_s 16 }
  end

  context 'when base is :H' do
    let(:base) { :H }

    it { is_expected.to be_instance_of String }
    it { is_expected.to be_frozen }
    it { is_expected.to eq number.to_s(16).upcase }
  end

  context 'when base is :X' do
    let(:base) { :X }

    it { is_expected.to be_instance_of String }
    it { is_expected.to be_frozen }
    it { is_expected.to eq number.to_s(16).upcase }
  end

  context 'when base is an invalid symbol' do
    let(:base) { :foo }

    specify do
      expect { utoa }.to \
        raise_error described_class::InvalidNtoaBaseError, 'invalid base'
    end
  end

  context 'when no prefix is given' do
    subject(:utoa) { described_class.utoa number, base }

    it { is_expected.to be_instance_of String }
    it { is_expected.to be_frozen }
    it { is_expected.to eq number.to_s base }
  end

  context 'when prefix is nil' do
    let(:prefix) { nil }

    it { is_expected.to be_instance_of String }
    it { is_expected.to be_frozen }
    it { is_expected.to eq number.to_s base }
  end

  context 'when prefix is empty' do
    let(:prefix) { '' }

    it { is_expected.to be_instance_of String }
    it { is_expected.to be_frozen }
    it { is_expected.to eq number.to_s base }
  end

  context 'when prefix is present' do
    let(:prefix) { 'foo' }

    it { is_expected.to be_instance_of String }
    it { is_expected.to be_frozen }
    it { is_expected.to eq "#{prefix}#{number.to_s(base)}" }
  end

  context 'when prefix is not a string' do
    let(:prefix) { 123 }

    specify do
      expect { utoa }.to raise_error(
        TypeError,
        "no implicit conversion of #{prefix.class} into String",
      )
    end
  end

  context 'when prefix has max length' do
    let(:prefix) { 'a' * 100 }

    it { is_expected.to be_instance_of String }
    it { is_expected.to be_frozen }
    it { is_expected.to eq "#{prefix}#{number.to_s(base)}" }
  end

  context 'when prefix is too long' do
    let(:prefix) { 'a' * 101 }

    specify do
      expect { utoa }.to raise_error(
        described_class::TooLongNtoaPrefixError,
        "prefix length #{prefix.length} is too long",
      )
    end
  end
end
