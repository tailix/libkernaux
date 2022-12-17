# frozen_string_literal: true

require 'spec_helper'

if KernAux::Version.with_multiboot2?
  RSpec.describe KernAux::Multiboot2::Header do
    subject(:multiboot2_header) { described_class.new data }

    let :data do
      [
        [Integer(magic_data)].pack('I'),
        [Integer(arch_data)].pack('I'),
        [Integer(total_size_data)].pack('I'),
        "\x00" * 4,
      ].join.freeze
    end

    let(:magic_data) { described_class::MAGIC }
    let(:arch_data) { 0 }
    let(:total_size_data) { 20 }

    describe '#magic' do
      subject(:magic) { multiboot2_header.magic }

      it { is_expected.to be_instance_of Integer }
      it { is_expected.to equal described_class::MAGIC }

      context 'when magic data is zero' do
        let(:magic_data) { 0 }

        it { is_expected.to be_instance_of Integer }
        it { is_expected.to equal magic_data }
      end

      context 'when magic data is some other value' do
        let(:magic_data) { 0x1234abcd }

        it { is_expected.to be_instance_of Integer }
        it { is_expected.to equal magic_data }
      end
    end

    describe '#arch' do
      subject(:arch) { multiboot2_header.arch }

      it { is_expected.to be_instance_of Integer }
      it { is_expected.to equal arch_data }

      context 'when arch data is zero' do
        let(:arch_data) { 0 }

        it { is_expected.to be_instance_of Integer }
        it { is_expected.to equal arch_data }
      end

      context 'when arch data is some other value' do
        let(:arch_data) { 0x1234abcd }

        it { is_expected.to be_instance_of Integer }
        it { is_expected.to equal arch_data }
      end
    end

    describe '#arch_name' do
      subject(:arch_name) { multiboot2_header.arch_name }

      it { is_expected.to be_instance_of Symbol }
      it { is_expected.to equal described_class::ARCH.fetch arch_data }

      context 'when arch is i386' do
        let(:arch_data) { 0 }

        it { is_expected.to be_instance_of Symbol }
        it { is_expected.to equal :i386 }
      end

      context 'when arch is MIPS32' do
        let(:arch_data) { 4 }

        it { is_expected.to be_instance_of Symbol }
        it { is_expected.to equal :mips32 }
      end

      context 'when arch data is some other value' do
        let(:arch_data) { 0x1234abcd }

        it { is_expected.to equal nil }
      end
    end

    describe '#total_size' do
      subject(:total_size) { multiboot2_header.total_size }

      it { is_expected.to be_instance_of Integer }
      it { is_expected.to equal total_size_data }

      context 'when total size data is zero' do
        let(:total_size_data) { 0 }

        it { is_expected.to be_instance_of Integer }
        it { is_expected.to equal total_size_data }
      end

      context 'when total size data is some other value' do
        let(:total_size_data) { 0x1234abcd }

        it { is_expected.to be_instance_of Integer }
        it { is_expected.to equal total_size_data }
      end
    end
  end
end
