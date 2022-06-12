# frozen_string_literal: true

require 'spec_helper'

RSpec.describe KernAux do
  describe '::VERSION' do
    specify do
      expect(described_class::VERSION).to match(/\A\d+\.\d+\.\d+\z/)
    end
  end
end
