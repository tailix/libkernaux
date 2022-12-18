# frozen_string_literal: true

require 'spec_helper'

if KernAux::Version.with_multiboot2?
  RSpec.describe KernAux::Multiboot2::Info do
    subject(:multiboot2_info) { described_class.new data }

    let(:data) { File.read fixture_path }
    let(:fixture) { 0 }

    let :fixture_path do
      File.expand_path(
        "../../../../../../fixtures/multiboot2_info_example#{fixture}.bin",
        __dir__,
      )
    end

    describe '#freeze' do
      subject(:freeze) { multiboot2_info.freeze }

      it { is_expected.to equal multiboot2_info }

      specify do
        expect { freeze }.to \
          change(multiboot2_info, :frozen?)
          .from(false)
          .to(true)
      end

      specify do
        expect { freeze }.to change(data, :frozen?).from(false).to(true)
      end
    end

    describe '#enough?' do
      subject(:enough?) { multiboot2_info.enough? }

      it { is_expected.to equal true }

      context 'for the fixture 1' do
        let(:fixture) { 1 }

        it { is_expected.to equal true }
      end

      context 'for the fixture 2' do
        let(:fixture) { 2 }

        it { is_expected.to equal true }
      end

      context 'for empty data' do
        let(:data) { '' }

        it { is_expected.to equal false }
      end

      context 'for too small data' do
        let(:data) { "\x00" * 7 }

        it { is_expected.to equal false }
      end
    end

    describe '#valid?' do
      subject(:valid?) { multiboot2_info.valid? }

      it { is_expected.to equal true }

      context 'for the fixture 1' do
        let(:fixture) { 1 }

        it { is_expected.to equal true }
      end

      context 'for the fixture 2' do
        let(:fixture) { 2 }

        it { is_expected.to equal true }
      end

      context 'for empty data' do
        let(:data) { '' }

        it { is_expected.to equal false }
      end

      context 'for too small data' do
        let(:data) { "\x00" * 15 }

        it { is_expected.to equal false }
      end

      context 'when given size is greater than the expected size' do
        let(:data) { "#{[info(16), tag_none].join}\x00" }

        it { is_expected.to equal true }
      end

      context 'when given size is equal to the expected size' do
        let(:data) { [info(16), tag_none].join }

        it { is_expected.to equal true }
      end

      context 'when given size is lesser than the expected size' do
        let(:data) { [info(16), tag_none].join[0...-1] }

        it { is_expected.to equal false }
      end
    end

    describe '#enough!' do
      subject(:enough!) { multiboot2_info.enough! }

      it { is_expected.to equal multiboot2_info }

      context 'for the fixture 1' do
        let(:fixture) { 1 }

        it { is_expected.to equal multiboot2_info }
      end

      context 'for the fixture 2' do
        let(:fixture) { 2 }

        it { is_expected.to equal multiboot2_info }
      end

      context 'for empty data' do
        let(:data) { '' }

        specify do
          expect { enough! }.to raise_error(
            KernAux::Multiboot2::BaseSizeError,
            'The structure size is too small',
          )
        end
      end

      context 'for too small data' do
        let(:data) { "\x00" * 7 }

        specify do
          expect { enough! }.to raise_error(
            KernAux::Multiboot2::BaseSizeError,
            'The structure size is too small',
          )
        end
      end
    end

    describe '#valid!' do
      subject(:valid!) { multiboot2_info.valid! }

      it { is_expected.to equal multiboot2_info }

      context 'for the fixture 1' do
        let(:fixture) { 1 }

        it { is_expected.to equal multiboot2_info }
      end

      context 'for the fixture 2' do
        let(:fixture) { 2 }

        it { is_expected.to equal multiboot2_info }
      end

      context 'for empty data' do
        let(:data) { '' }

        specify do
          expect { valid! }.to raise_error(
            KernAux::Multiboot2::BaseSizeError,
            'The structure size is too small',
          )
        end
      end

      context 'for too small data' do
        let(:data) { "\x00" * 7 }

        specify do
          expect { valid! }.to raise_error(
            KernAux::Multiboot2::BaseSizeError,
            'The structure size is too small',
          )
        end
      end

      context 'when given size is greater than the expected size' do
        let(:data) { "#{[info(16), tag_none].join}\x00" }

        it { is_expected.to equal multiboot2_info }
      end

      context 'when given size is equal to the expected size' do
        let(:data) { [info(16), tag_none].join }

        it { is_expected.to equal multiboot2_info }
      end

      context 'when given size is lesser than the expected size' do
        let(:data) { [info(16), tag_none].join[0...-1] }

        specify do
          expect { valid! }.to raise_error(
            KernAux::Multiboot2::InvalidError,
            'The structure is invalid',
          )
        end
      end
    end

    describe '#total_size' do
      subject(:total_size) { multiboot2_info.total_size }

      it { is_expected.to equal 16 }

      context 'for the fixture 1' do
        let(:fixture) { 1 }

        it { is_expected.to equal 864 }
      end

      context 'for the fixture 2' do
        let(:fixture) { 2 }

        it { is_expected.to equal 1816 }
      end

      context 'for empty data' do
        let(:data) { '' }

        it { is_expected.to equal nil }
      end

      context 'for too small data' do
        let(:data) { "\x00" * 7 }

        it { is_expected.to equal nil }
      end
    end

    describe '#reserved' do
      subject(:reserved) { multiboot2_info.reserved }

      it { is_expected.to equal 0 }

      context 'for the fixture 1' do
        let(:fixture) { 1 }

        it { is_expected.to equal 0 }
      end

      context 'for the fixture 2' do
        let(:fixture) { 2 }

        it { is_expected.to equal 0 }
      end

      context 'for empty data' do
        let(:data) { '' }

        it { is_expected.to equal nil }
      end

      context 'for too small data' do
        let(:data) { "\x00" * 7 }

        it { is_expected.to equal nil }
      end
    end

    def info(total_size)
      total_size = Integer total_size

      [
        # uint32_t total_size
        [total_size].pack('I'),
        # uint32_t reserved
        [0].pack('I'),
      ].join
    end

    def tag_none
      [
        # uint32_t tags[0].type: none
        [0].pack('I'),
        # uint32_t tags[0].size
        [8].pack('I'),
      ].join
    end
  end
end
