# frozen_string_literal: true

require 'spec_helper'

if KernAux::Version.with_multiboot2?
  RSpec.describe KernAux::Multiboot2::Header do
    subject(:multiboot2_header) { described_class.new data }

    let :data do
      "\xd6\x50\x52\xe8" + "\x00" * 12
    end

    describe '#magic' do
      subject(:magic) { multiboot2_header.magic }

      it { is_expected.to be_instance_of Integer }
      it { is_expected.to equal described_class::MAGIC }
    end
  end
end
