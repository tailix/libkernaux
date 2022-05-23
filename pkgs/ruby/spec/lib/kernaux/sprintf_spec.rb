# frozen_string_literal: true

# Copyright (c) 2014-2019 Marco Paland <info@paland.com>
# Author: Marco Paland (info@paland.com) PALANDesign Hannover, Germany

require 'spec_helper'

RSpec.describe KernAux, '.sprintf' do
  if described_class.singleton_class.method_defined? :sprintf
    subject(:sprintf) { described_class.sprintf 'Hello, ', ['%s', 'World'], '!' }

    it { is_expected.to be_instance_of String }
    it { is_expected.to be_frozen }
    it { is_expected.to eq 'Hello, World!' }

    context 'using original tests' do
      YAML.safe_load_file(File.expand_path('printf.yml', __dir__)).each do |test|
        expected = test['result']
        args     = test['args']

        it "transforms #{args.inspect} to #{expected.inspect}" do
          expect(described_class.sprintf(*args)).to eq expected
        end
      end
    end
  end
end
