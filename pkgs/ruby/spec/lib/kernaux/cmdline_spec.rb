# frozen_string_literal: true

require 'spec_helper'

RSpec.describe KernAux, '.cmdline' do
  subject(:cmdline) { described_class.cmdline str }

  let(:str) { 'foo bar\\ baz "car cdr"' }

  it { is_expected.to be_instance_of Array }
  it { is_expected.to be_frozen }
  it { is_expected.to all be_instance_of String }
  it { is_expected.to all be_frozen }
  it { is_expected.to eq ['foo', 'bar baz', 'car cdr'] }
end
