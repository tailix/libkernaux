# frozen_string_literal: true

# Copyright (c) 2014-2019 Marco Paland <info@paland.com>
# Author: Marco Paland (info@paland.com) PALANDesign Hannover, Germany

require 'spec_helper'

RSpec.describe KernAux, '.sprintf' do
  subject(:sprintf) { described_class.sprintf 'Hello, ', ['%s', 'World'], '!' }

  it { is_expected.to be_instance_of String }
  it { is_expected.to be_frozen }
  it { is_expected.to eq 'Hello, World!' }

  context 'using original tests' do
    [
      [' 4232',                  ['% d', 4232]],
      ['This is a test of 12EF', ['This is a test of %X', 0x12EF]],
      ['-1000',                  ['%d', -1000]],
      ['-1',                     ['%d', -1]],
      ['2345',                   ['%d', 2345]],
      ['3 -1000 test',           ['%d ', 3], ['%d ', -1000], ['%s', 'test']],
      ['3 -1000 test',           ['%d', 3], [' %d', -1000], [' %s', 'test']],
      ['3 -1000 test',           ['%d', 3], ' ', ['%d', -1000], ' ', ['%s', 'test']],
      # space flag
      [' 42',                    ['% d', 42]],
      ['-42',                    ['% d', -42]],
      ['   42',                  ['% 5d', 42]],
      ['  -42',                  ['% 5d', -42]],
      ['             42',        ['% 15d', 42]],
      ['            -42',        ['% 15d', -42]],
      ['        -42.987',        ['% 15.3f', -42.987]],
      ['         42.987',        ['% 15.3f', 42.987]],
      ['Hello testing',          ['% s', 'Hello testing']],
      [' 1024',                  ['% d', 1024]],
      ['-1024',                  ['% d', -1024]],
      [' 1024',                  ['% i', 1024]],
      ['-1024',                  ['% i', -1024]],
      ['1024',                   ['% u', 1024]],
      ['4294966272',             ['% u', 4_294_966_272]],
      ['777',                    ['% o', 511]],
      ['37777777001',            ['% o', 4_294_966_785]],
      ['1234abcd',               ['% x', 305_441_741]],
      ['edcb5433',               ['% x', 3_989_525_555]],
      ['1234ABCD',               ['% X', 305_441_741]],
      ['EDCB5433',               ['% X', 3_989_525_555]],
      ['x',                      ['% c', 'x']],
    ].each do |expected, *args|
      specify do
        expect(described_class.sprintf(*args)).to eq expected
      end
    end
  end
end
