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
    end

    describe '#enough!' do
      subject(:enough!) { multiboot2_header.enough! }

      specify { expect { enough! }.not_to raise_error }
      it { is_expected.to equal multiboot2_header }
    end

    describe '#magic' do
      subject(:magic) { multiboot2_header.magic }

      it { is_expected.to be_instance_of Integer }
      it { is_expected.to equal described_class::MAGIC }
    end

    describe '#arch' do
      subject(:arch) { multiboot2_header.arch }

      it { is_expected.to be_instance_of Integer }
      it { is_expected.to equal 0 }
    end

    describe '#arch_name' do
      subject(:arch_name) { multiboot2_header.arch_name }

      it { is_expected.to be_instance_of Symbol }
      it { is_expected.to equal :i386 }
    end

    describe '#total_size' do
      subject(:total_size) { multiboot2_header.total_size }

      it { is_expected.to be_instance_of Integer }
      it { is_expected.to equal 24 }
    end
  end
end
