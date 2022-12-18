# frozen_string_literal: true

require 'spec_helper'

if KernAux::Version.with_multiboot2?
  RSpec.describe KernAux::Multiboot2::Header do
    subject(:multiboot2_header) { described_class.new data }

    let(:data) { File.read fixture_path }
    let(:fixture) { 0 }

    let :fixture_path do
      File.expand_path(
        "../../../../../../fixtures/multiboot2_header_example#{fixture}.bin",
        __dir__,
      )
    end

    it_behaves_like 'Multiboot 2 struct', :header, 16

    describe '#valid?' do
      subject(:valid?) { multiboot2_header.valid? }

      context 'when given size is greater than the expected size' do
        let(:data) { "#{[header(0, 24), tag_none].join}\x00" }

        it { is_expected.to equal true }
      end

      context 'when given size is equal to the expected size' do
        let(:data) { [header(0, 24), tag_none].join }

        it { is_expected.to equal true }
      end

      context 'when given size is lesser than the expected size' do
        let(:data) { [header(0, 24), tag_none].join[0...-1] }

        it { is_expected.to equal false }
      end
    end

    describe '#valid!' do
      subject(:valid!) { multiboot2_header.valid! }

      context 'when given size is greater than the expected size' do
        let(:data) { "#{[header(0, 24), tag_none].join}\x00" }

        it { is_expected.to equal multiboot2_header }
      end

      context 'when given size is equal to the expected size' do
        let(:data) { [header(0, 24), tag_none].join }

        it { is_expected.to equal multiboot2_header }
      end

      context 'when given size is lesser than the expected size' do
        let(:data) { [header(0, 24), tag_none].join[0...-1] }

        specify do
          expect { valid! }.to raise_error(
            KernAux::Multiboot2::InvalidError,
            'The structure is invalid',
          )
        end
      end
    end

    describe '#magic' do
      subject(:magic) { multiboot2_header.magic }

      it { is_expected.to equal described_class::MAGIC }

      context 'for the fixture 1' do
        let(:fixture) { 1 }

        it { is_expected.to equal described_class::MAGIC }
      end

      context 'for the fixture 2' do
        let(:fixture) { 2 }

        it { is_expected.to equal described_class::MAGIC }
      end

      context 'for empty data' do
        let(:data) { '' }

        it { is_expected.to equal nil }
      end

      context 'for too small data' do
        let(:data) { "\x00" * 15 }

        it { is_expected.to equal nil }
      end
    end

    describe '#arch' do
      subject(:arch) { multiboot2_header.arch }

      it { is_expected.to equal 0 }

      context 'for the fixture 1' do
        let(:fixture) { 1 }

        it { is_expected.to equal 4 }
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
        let(:data) { "\x00" * 15 }

        it { is_expected.to equal nil }
      end
    end

    describe '#arch_name' do
      subject(:arch_name) { multiboot2_header.arch_name }

      it { is_expected.to equal :i386 }

      context 'for the fixture 1' do
        let(:fixture) { 1 }

        it { is_expected.to equal :mips32 }
      end

      context 'for the fixture 2' do
        let(:fixture) { 2 }

        it { is_expected.to equal :i386 }
      end

      context 'for empty data' do
        let(:data) { '' }

        it { is_expected.to equal nil }
      end

      context 'for too small data' do
        let(:data) { "\x00" * 15 }

        it { is_expected.to equal nil }
      end
    end

    describe '#total_size' do
      subject(:total_size) { multiboot2_header.total_size }

      it { is_expected.to equal 24 }

      context 'for the fixture 1' do
        let(:fixture) { 1 }

        it { is_expected.to equal 104 }
      end

      context 'for the fixture 2' do
        let(:fixture) { 2 }

        it { is_expected.to equal 272 }
      end

      context 'for empty data' do
        let(:data) { '' }

        it { is_expected.to equal nil }
      end

      context 'for too small data' do
        let(:data) { "\x00" * 15 }

        it { is_expected.to equal nil }
      end
    end

    describe '#checksum' do
      subject(:checksum) { multiboot2_header.checksum }

      it { is_expected.to equal 0x17adaf12 }

      context 'for the fixture 1' do
        let(:fixture) { 1 }

        it { is_expected.to equal 0x17adaebe }
      end

      context 'for the fixture 2' do
        let(:fixture) { 2 }

        it { is_expected.to equal 0x17adae1a }
      end

      context 'for empty data' do
        let(:data) { '' }

        it { is_expected.to equal nil }
      end

      context 'for too small data' do
        let(:data) { "\x00" * 15 }

        it { is_expected.to equal nil }
      end
    end

    def header(arch, total_size)
      arch = Integer arch
      total_size = Integer total_size

      [
        # uint32_t magic
        [described_class::MAGIC].pack('I'),
        # uint32_t arch: i386
        [arch].pack('I'),
        # uint32_t total_size
        [total_size].pack('I'),
        # uint32_t checksum
        [-(described_class::MAGIC + arch + total_size)].pack('I'),
      ].join
    end

    def tag_none
      [
        # uint16_t tags[0].type: none
        [0].pack('S'),
        # uint16_t tags[0].flags
        [0].pack('S'),
        # uint32_t tags[0].size
        [8].pack('I'),
      ].join
    end
  end
end
