# frozen_string_literal: true

require 'spec_helper'

RSpec.describe KernAux, '.snprintf1' do
  let(:size) { 10_000 }

  context 'with 2 arguments' do
    subject(:snprintf1) { described_class.snprintf1 size, format }

    let(:format) { '%%' }

    it { is_expected.to be_instance_of Array }
    it { is_expected.to be_frozen }
    it { is_expected.to all be_frozen }

    specify { expect(snprintf1.size).to equal 2 }
    specify { expect(snprintf1[0]).to be_instance_of String }
    specify { expect(snprintf1[1]).to be_instance_of Integer }
    specify { expect(snprintf1[0]).to eq '%' }
    specify { expect(snprintf1[1]).to eq 1 }

    context 'with leading and trailing spaces' do
      let(:format) { '  %%  ' }

      specify { expect(snprintf1[0]).to eq '  %  ' }
    end

    context 'with "%s" format' do
      let(:format) { '%s' }

      specify { expect(snprintf1[0]).to eq '' }
    end

    context 'when size has invalid type' do
      let(:size) { '10000' }

      specify { expect { snprintf1 }.to raise_error TypeError }
    end

    context 'when size is negative' do
      let(:size) { -1 }

      specify do
        expect { snprintf1 }.to \
          raise_error RangeError, 'expected non-negative size'
      end
    end

    context 'when format doesn\'t include "%" char' do
      let(:format) { 'foo' }

      specify do
        expect { snprintf1 }.to raise_error ArgumentError, 'invalid format'
      end
    end

    context 'when format includes more than two "%" chars' do
      let(:format) { '%%%' }

      specify do
        expect { snprintf1 }.to raise_error ArgumentError, 'invalid format'
      end
    end
  end

  context 'with 3 arguments' do
    subject(:snprintf1) { described_class.snprintf1 size, format, arg }

    let(:format) { '%s' }
    let(:arg) { 'Hello, World!' }

    it { is_expected.to be_instance_of Array }
    it { is_expected.to be_frozen }
    it { is_expected.to all be_frozen }

    specify { expect(snprintf1.size).to equal 2 }
    specify { expect(snprintf1[0]).to be_instance_of String }
    specify { expect(snprintf1[1]).to be_instance_of Integer }
    specify { expect(snprintf1[0]).to eq arg }
    specify { expect(snprintf1[1]).to eq arg.size }

    context 'with leading and trailing spaces' do
      let(:format) { '  %s  ' }

      specify { expect(snprintf1[0]).to eq "  #{arg}  " }
    end

    context 'with "%%" format' do
      let(:format) { '%%' }

      specify { expect(snprintf1[0]).to eq '%' }
    end

    context 'when size has invalid type' do
      let(:size) { '10000' }

      specify { expect { snprintf1 }.to raise_error TypeError }
    end

    context 'when size is negative' do
      let(:size) { -1 }

      specify do
        expect { snprintf1 }.to \
          raise_error RangeError, 'expected non-negative size'
      end
    end

    context 'when format doesn\'t include "%" char' do
      let(:format) { 'foo' }

      specify do
        expect { snprintf1 }.to raise_error ArgumentError, 'invalid format'
      end
    end

    context 'when format includes more than two "%" chars' do
      let(:format) { '%%%' }

      specify do
        expect { snprintf1 }.to raise_error ArgumentError, 'invalid format'
      end
    end
  end

  context 'with 4 arguments' do
    subject(:snprintf1) { described_class.snprintf1 size, format, width, arg }

    let(:format) { '%*s' }
    let(:width) { 20 }
    let(:arg) { 'Hello, World!' }

    it { is_expected.to be_instance_of Array }
    it { is_expected.to be_frozen }
    it { is_expected.to all be_frozen }

    specify { expect(snprintf1.size).to equal 2 }
    specify { expect(snprintf1[0]).to be_instance_of String }
    specify { expect(snprintf1[1]).to be_instance_of Integer }
    specify { expect(snprintf1[0]).to eq arg.rjust(width, ' ') }
    specify { expect(snprintf1[1]).to eq width }

    context 'with leading and trailing spaces' do
      let(:format) { '  %*s  ' }

      specify { expect(snprintf1[0]).to eq "  #{arg.rjust(width, ' ')}  " }
    end

    context 'with "%*%" format' do
      let(:format) { '%*%' }

      specify { expect(snprintf1[0]).to eq '%' }
    end

    context 'when size has invalid type' do
      let(:size) { '10000' }

      specify { expect { snprintf1 }.to raise_error TypeError }
    end

    context 'when size is negative' do
      let(:size) { -1 }

      specify do
        expect { snprintf1 }.to \
          raise_error RangeError, 'expected non-negative size'
      end
    end

    context 'when format doesn\'t include "%" char' do
      let(:format) { 'foo' }

      specify do
        expect { snprintf1 }.to raise_error ArgumentError, 'invalid format'
      end
    end

    context 'when format includes more than two "%" chars' do
      let(:format) { '%%%' }

      specify do
        expect { snprintf1 }.to raise_error ArgumentError, 'invalid format'
      end
    end
  end

  context 'with 0 arguments' do
    specify do
      expect { described_class.snprintf1 }.to \
        raise_error ArgumentError, 'expected 2, 3 or 4 args'
    end
  end

  context 'with 1 argument' do
    specify do
      expect { described_class.snprintf1 size }.to \
        raise_error ArgumentError, 'expected 2, 3 or 4 args'
    end
  end

  context 'with 5 arguments' do
    specify do
      expect { described_class.snprintf1 size, '%*s', 20, 'foo', 'bar' }.to \
        raise_error ArgumentError, 'expected 2, 3 or 4 args'
    end
  end
end
