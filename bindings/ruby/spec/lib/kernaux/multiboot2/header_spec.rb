# frozen_string_literal: true

require 'spec_helper'

if KernAux::Version.with_multiboot2?
  RSpec.describe KernAux::Multiboot2::Header do
    subject(:multiboot2_header) { described_class.new data }

    let :data do
      [magic_data, arch_data, "\x00" * 8].join.freeze
    end

    let(:magic_data) { "\xd6\x50\x52\xe8" }
    let(:arch_data)  { "\x04\x00\x00\x00" }

    describe '#magic' do
      subject(:magic) { multiboot2_header.magic }

      it { is_expected.to be_instance_of Integer }
      it { is_expected.to equal described_class::MAGIC }
    end

    describe '#arch' do
      subject(:arch) { multiboot2_header.arch }

      it { is_expected.to be_instance_of Integer }
      it { is_expected.to equal 4 }
    end

    describe '#arch_name' do
      subject(:arch_name) { multiboot2_header.arch_name }

      it { is_expected.to be_instance_of Symbol }
      it { is_expected.to equal :mips32 }
    end
  end
end
