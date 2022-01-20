# frozen_string_literal: true

require 'spec_helper'

RSpec.describe KernAux, '.panic' do
  subject(:panic) { described_class.panic msg }

  let(:msg) { 'Hello, World!' }

  specify do
    expect { panic }.to \
      raise_error described_class::AssertError, /\A#{__FILE__}:\d+:#{msg}\z/
  end

  context 'when custom assertion callback has beed set' do
    around do |example|
      described_class.assert_cb = lambda { |file, line, msg|
        raise "file: #{file.inspect}, line: #{line}, msg: #{msg.inspect}"
      }
      example.run
    ensure
      described_class.assert_cb = described_class::DEFAULT_ASSERT_CB
    end

    specify do
      expect { panic }.to raise_error(
        RuntimeError,
        /\Afile: #{__FILE__.inspect}, line: \d+, msg: #{msg.inspect}\z/,
      )
    end
  end
end
