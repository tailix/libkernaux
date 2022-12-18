# frozen_string_literal: true

require 'spec_helper'

if KernAux::Version.with_multiboot2?
  RSpec.describe KernAux::Multiboot2::Header do
    subject(:multiboot2_header) { described_class.new fixture_data }

    let(:fixture) { 0 }

    let(:fixture_data) { File.read fixture_path }

    let :fixture_path do
      File.expand_path(
        "../../../../../../fixtures/multiboot2_header_example#{fixture}.bin",
        __dir__,
      )
    end

    describe '#freeze' do
      subject(:freeze) { multiboot2_header.freeze }

      it { is_expected.to equal multiboot2_header }

      specify do
        expect { freeze }.to \
          change(multiboot2_header, :frozen?)
          .from(false)
          .to(true)
      end

      specify do
        expect { freeze }.to change(fixture_data, :frozen?).from(false).to(true)
      end
    end

    describe '#enough?' do
      subject(:enough?) { multiboot2_header.enough? }

      it { is_expected.to equal true }

      context 'for the fixture 1' do
        let(:fixture) { 1 }

        it { is_expected.to equal true }
      end

      context 'for the fixture 2' do
        let(:fixture) { 2 }

        it { is_expected.to equal true }
      end
    end

    describe '#valid?' do
      subject(:valid?) { multiboot2_header.valid? }

      it { is_expected.to equal true }

      context 'for the fixture 1' do
        let(:fixture) { 1 }

        it { is_expected.to equal true }
      end

      context 'for the fixture 2' do
        let(:fixture) { 2 }

        it { is_expected.to equal true }
      end
    end

    describe '#enough!' do
      subject(:enough!) { multiboot2_header.enough! }

      specify { expect { enough! }.not_to raise_error }
      it { is_expected.to equal multiboot2_header }

      context 'for the fixture 1' do
        let(:fixture) { 1 }

        specify { expect { enough! }.not_to raise_error }
        it { is_expected.to equal multiboot2_header }
      end

      context 'for the fixture 2' do
        let(:fixture) { 2 }

        specify { expect { enough! }.not_to raise_error }
        it { is_expected.to equal multiboot2_header }
      end
    end

    describe '#valid!' do
      subject(:valid!) { multiboot2_header.valid! }

      specify { expect { valid! }.not_to raise_error }
      it { is_expected.to equal multiboot2_header }

      context 'for the fixture 1' do
        let(:fixture) { 1 }

        specify { expect { valid! }.not_to raise_error }
        it { is_expected.to equal multiboot2_header }
      end

      context 'for the fixture 2' do
        let(:fixture) { 2 }

        specify { expect { valid! }.not_to raise_error }
        it { is_expected.to equal multiboot2_header }
      end
    end

    describe '#magic' do
      subject(:magic) { multiboot2_header.magic }

      it { is_expected.to be_instance_of Integer }
      it { is_expected.to equal described_class::MAGIC }

      context 'for the fixture 1' do
        let(:fixture) { 1 }

        it { is_expected.to be_instance_of Integer }
        it { is_expected.to equal described_class::MAGIC }
      end

      context 'for the fixture 2' do
        let(:fixture) { 2 }

        it { is_expected.to be_instance_of Integer }
        it { is_expected.to equal described_class::MAGIC }
      end
    end

    describe '#arch' do
      subject(:arch) { multiboot2_header.arch }

      it { is_expected.to be_instance_of Integer }
      it { is_expected.to equal 0 }

      context 'for the fixture 1' do
        let(:fixture) { 1 }

        it { is_expected.to be_instance_of Integer }
        it { is_expected.to equal 4 }
      end

      context 'for the fixture 2' do
        let(:fixture) { 2 }

        it { is_expected.to be_instance_of Integer }
        it { is_expected.to equal 0 }
      end
    end

    describe '#arch_name' do
      subject(:arch_name) { multiboot2_header.arch_name }

      it { is_expected.to be_instance_of Symbol }
      it { is_expected.to equal :i386 }

      context 'for the fixture 1' do
        let(:fixture) { 1 }

        it { is_expected.to be_instance_of Symbol }
        it { is_expected.to equal :mips32 }
      end

      context 'for the fixture 2' do
        let(:fixture) { 2 }

        it { is_expected.to be_instance_of Symbol }
        it { is_expected.to equal :i386 }
      end
    end

    describe '#total_size' do
      subject(:total_size) { multiboot2_header.total_size }

      it { is_expected.to be_instance_of Integer }
      it { is_expected.to equal 24 }

      context 'for the fixture 1' do
        let(:fixture) { 1 }

        it { is_expected.to be_instance_of Integer }
        it { is_expected.to equal 104 }
      end

      context 'for the fixture 2' do
        let(:fixture) { 2 }

        it { is_expected.to be_instance_of Integer }
        it { is_expected.to equal 272 }
      end
    end

    describe '#checksum' do
      subject(:checksum) { multiboot2_header.checksum }

      it { is_expected.to be_instance_of Integer }
      it { is_expected.to equal 0x17adaf12 }

      context 'for the fixture 1' do
        let(:fixture) { 1 }

        it { is_expected.to be_instance_of Integer }
        it { is_expected.to equal 0x17adaebe }
      end

      context 'for the fixture 2' do
        let(:fixture) { 2 }

        it { is_expected.to be_instance_of Integer }
        it { is_expected.to equal 0x17adae1a }
      end
    end
  end
end
