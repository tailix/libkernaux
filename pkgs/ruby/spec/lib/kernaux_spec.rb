# frozen_string_literal: true

require 'spec_helper'

RSpec.describe KernAux do
  describe '::VERSION' do
    specify do
      expect(described_class::VERSION).to match(/\A\d+\.\d+\.\d+\z/)
    end
  end

  describe '.panic' do
    subject(:panic) { described_class.panic msg }

    let(:msg) { 'Hello, World!' }

    specify do
      expect { panic }.to \
        raise_error described_class::AssertError, /\A#{__FILE__}:\d+:#{msg}\z/
    end

    context 'when custom assertion callback has beed set' do
      around do |example|
        described_class.assert_cb = lambda { |file, line, msg|
          raise "file: #{file.inspect}, line: #{line}, msg: #{msg.inspect}"
        }
        example.run
      ensure
        described_class.assert_cb = described_class::DEFAULT_ASSERT_CB
      end

      specify do
        expect { panic }.to raise_error(
          RuntimeError,
          /\Afile: #{__FILE__.inspect}, line: \d+, msg: #{msg.inspect}\z/,
        )
      end
    end
  end

  if described_class.singleton_class.method_defined? :utoa10
    describe '.utoa10' do
      subject(:utoa10) { described_class.utoa10 number }

      let(:number) { rand 0..(2**64 - 1) }

      it { is_expected.to be_instance_of String }
      it { is_expected.to be_frozen }
      it { is_expected.to eq number.to_s }

      context 'when number is 0' do
        let(:number) { 0 }

        it { is_expected.to eq '0' }
      end

      context 'when number is max uint64_t' do
        let(:number) { 2**64 - 1 }

        it { is_expected.to eq number.to_s }
      end

      context 'when number is -1' do
        let(:number) { -1 }

        specify do
          expect { utoa10 }.to \
            raise_error RangeError, 'can\'t convert negative number to uint64_t'
        end
      end

      context 'when number is greater than max uint64_t' do
        let(:number) { 2**64 }

        specify do
          expect { utoa10 }.to raise_error \
            RangeError, 'bignum too big to convert into `unsigned long long\''
        end
      end
    end
  end

  if described_class.singleton_class.method_defined? :itoa10
    describe '.itoa10' do
      subject(:itoa10) { described_class.itoa10 number }

      let(:number) { rand((-2**63)..(2**63 - 1)) }

      it { is_expected.to be_instance_of String }
      it { is_expected.to be_frozen }
      it { is_expected.to eq number.to_s }

      context 'when number is 0' do
        let(:number) { 0 }

        it { is_expected.to eq '0' }
      end

      context 'when number is 1' do
        let(:number) { 1 }

        it { is_expected.to eq '1' }
      end

      context 'when number is -1' do
        let(:number) { -1 }

        it { is_expected.to eq '-1' }
      end

      context 'when number is min int64_t' do
        let(:number) { -2**63 }

        it { is_expected.to eq number.to_s }
      end

      context 'when number is max int64_t' do
        let(:number) { 2**63 - 1 }

        it { is_expected.to eq number.to_s }
      end

      context 'when number is lesser than min uint64_t' do
        let(:number) { -2**63 - 1 }

        specify do
          expect { itoa10 }.to raise_error \
            RangeError, 'bignum too big to convert into `long long\''
        end
      end

      context 'when number is greater than max uint64_t' do
        let(:number) { 2**63 }

        specify do
          expect { itoa10 }.to raise_error \
            RangeError, 'bignum too big to convert into `long long\''
        end
      end
    end
  end
end
