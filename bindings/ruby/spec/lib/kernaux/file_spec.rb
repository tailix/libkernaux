# frozen_string_literal: true

require 'spec_helper'

defined? KernAux::File and RSpec.describe KernAux::File do
  subject(:our_file) { described_class.new method :out }

  def out(str)
    (@buffer ||= +'') << String(str)
  end

  specify do
    expect(our_file.instance_variable_get(:@out)).to eq method :out
  end
end
