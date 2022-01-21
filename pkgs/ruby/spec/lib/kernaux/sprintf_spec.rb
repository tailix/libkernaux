# frozen_string_literal: true

require 'spec_helper'

RSpec.describe KernAux, '.sprintf' do
  subject(:sprintf) { described_class.sprintf 'Hello, ', ['%s', 'World'], '!' }

  it { is_expected.to be_instance_of String }
  it { is_expected.to be_frozen }
  it { is_expected.to eq 'Hello, World!' }
end
