# frozen_string_literal: true

require 'spec_helper'

KernAux::Version.supports_printf? and RSpec.describe KernAux, '.sprintf1' do
  context 'with 1 argument' do
    subject(:sprintf1) { described_class.sprintf1 format }

    let(:format) { '%%' }

    it { is_expected.to be_instance_of String }
    it { is_expected.to be_frozen }
    it { is_expected.to eq described_class.snprintf1(1000, format).first }
  end

  context 'with 2 argument' do
    subject(:sprintf1) { described_class.sprintf1 format, arg }

    let(:format) { '%s' }
    let(:arg) { 'Hello, World!' }

    it { is_expected.to be_instance_of String }
    it { is_expected.to be_frozen }
    it { is_expected.to eq described_class.snprintf1(100, format, arg).first }
  end
end
