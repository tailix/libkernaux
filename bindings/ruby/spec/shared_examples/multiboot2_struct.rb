# frozen_string_literal: true

RSpec.shared_examples 'Multiboot 2 struct' do |struct_name, min_size|
  struct_name = String(struct_name).to_sym
  min_size = Integer min_size

  subject(:multiboot2_struct) { described_class.new data }

  let(:data) { File.read fixture_path }
  let(:fixture) { 0 }

  let :fixture_path do
    File.expand_path(
      "../../../../fixtures/multiboot2_#{struct_name}_example#{fixture}.bin",
      __dir__,
    )
  end

  describe '#data' do
    subject { multiboot2_struct.data }

    it { is_expected.to equal data }
  end

  describe '#to_s' do
    subject { multiboot2_struct.to_s }

    it { is_expected.to equal data }
  end

  describe '#inspect' do
    subject(:inspect) { multiboot2_struct.inspect }

    context 'when data is empty' do
      let(:data) { '' }

      it { is_expected.to be_instance_of String }
      it { is_expected.to be_frozen }
      it { is_expected.to eq "#<#{described_class}:\"\">" }
    end

    context 'when data is not too long' do
      let(:data) { "\x00" * 16 }

      it { is_expected.to be_instance_of String }
      it { is_expected.to be_frozen }

      specify do
        expect(inspect).to eq \
          "#<#{described_class}:" \
          "#{data.force_encoding(Encoding::ASCII).inspect}>"
      end
    end

    context 'when data is too long' do
      let(:data) { "\x00" * 17 }

      it { is_expected.to be_instance_of String }
      it { is_expected.to be_frozen }

      specify do
        expect(inspect).to eq \
          "#<#{described_class}:" \
          "#{data[...16].force_encoding(Encoding::ASCII).inspect}...>"
      end
    end
  end

  describe '#freeze' do
    subject(:freeze) { multiboot2_struct.freeze }

    it { is_expected.to equal multiboot2_struct }

    specify do
      expect { freeze }.to \
        change(multiboot2_struct, :frozen?)
        .from(false)
        .to(true)
    end

    specify do
      expect { freeze }.to change(data, :frozen?).from(false).to(true)
    end
  end

  describe '#enough?' do
    subject { multiboot2_struct.enough? }

    context 'for the fixture 0' do
      let(:fixture) { 0 }

      it { is_expected.to equal true }
    end

    context 'for the fixture 1' do
      let(:fixture) { 1 }

      it { is_expected.to equal true }
    end

    context 'for the fixture 2' do
      let(:fixture) { 2 }

      it { is_expected.to equal true }
    end

    context 'for empty data' do
      let(:data) { '' }

      it { is_expected.to equal false }
    end

    context 'for too small data' do
      let(:data) { "\x00" * (min_size - 1) }

      it { is_expected.to equal false }
    end
  end

  describe '#valid?' do
    subject { multiboot2_struct.valid? }

    context 'for the fixture 0' do
      let(:fixture) { 0 }

      it { is_expected.to equal true }
    end

    context 'for the fixture 1' do
      let(:fixture) { 1 }

      it { is_expected.to equal true }
    end

    context 'for the fixture 2' do
      let(:fixture) { 2 }

      it { is_expected.to equal true }
    end

    context 'for empty data' do
      let(:data) { '' }

      it { is_expected.to equal false }
    end

    context 'for too small data' do
      let(:data) { "\x00" * (min_size - 1) }

      it { is_expected.to equal false }
    end
  end

  describe '#enough!' do
    subject(:enough!) { multiboot2_struct.enough! }

    context 'for the fixture 0' do
      let(:fixture) { 0 }

      it { is_expected.to equal multiboot2_struct }
    end

    context 'for the fixture 1' do
      let(:fixture) { 1 }

      it { is_expected.to equal multiboot2_struct }
    end

    context 'for the fixture 2' do
      let(:fixture) { 2 }

      it { is_expected.to equal multiboot2_struct }
    end

    context 'for empty data' do
      let(:data) { '' }

      specify do
        expect { enough! }.to raise_error(
          KernAux::Multiboot2::BaseSizeError,
          'The structure size is too small',
        )
      end
    end

    context 'for too small data' do
      let(:data) { "\x00" * (min_size - 1) }

      specify do
        expect { enough! }.to raise_error(
          KernAux::Multiboot2::BaseSizeError,
          'The structure size is too small',
        )
      end
    end
  end

  describe '#valid!' do
    subject(:valid!) { multiboot2_struct.valid! }

    context 'for the fixture 0' do
      let(:fixture) { 0 }

      it { is_expected.to equal multiboot2_struct }
    end

    context 'for the fixture 1' do
      let(:fixture) { 1 }

      it { is_expected.to equal multiboot2_struct }
    end

    context 'for the fixture 2' do
      let(:fixture) { 2 }

      it { is_expected.to equal multiboot2_struct }
    end

    context 'for empty data' do
      let(:data) { '' }

      specify do
        expect { valid! }.to raise_error(
          KernAux::Multiboot2::BaseSizeError,
          'The structure size is too small',
        )
      end
    end

    context 'for too small data' do
      let(:data) { "\x00" * (min_size - 1) }

      specify do
        expect { valid! }.to raise_error(
          KernAux::Multiboot2::BaseSizeError,
          'The structure size is too small',
        )
      end
    end
  end
end