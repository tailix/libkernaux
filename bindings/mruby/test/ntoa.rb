def common_assert(expected, result)
  assert_true result.instance_of? String
  assert_true result.frozen?
  assert_equal expected, result
end

def test_utoa(number, base, expected)
  common_assert expected, KernAux.utoa(number, base)
  common_assert expected, KernAux.utoa(number, base, nil)
  common_assert expected, KernAux.utoa(number, base, '')
end

def test_itoa(number, base, expected)
  common_assert expected, KernAux.itoa(number, base)
  common_assert expected, KernAux.itoa(number, base, nil)
  common_assert expected, KernAux.itoa(number, base, '')
end

def test_utoax(number, base, prefix, expected)
  common_assert expected, KernAux.utoa(number, base, prefix)
end

def test_itoax(number, base, prefix, expected)
  common_assert expected, KernAux.itoa(number, base, prefix)
end

def test_utoa2(number, expected)
  common_assert expected, KernAux.utoa2(number)
end

def test_itoa2(number, expected)
  common_assert expected, KernAux.itoa2(number)
end

def test_utoa8(number, expected)
  common_assert expected, KernAux.utoa8(number)
end

def test_itoa8(number, expected)
  common_assert expected, KernAux.itoa8(number)
end

def test_utoa10(number, expected)
  common_assert expected, KernAux.utoa10(number)
end

def test_itoa10(number, expected)
  common_assert expected, KernAux.itoa10(number)
end

def test_utoa16(number, expected)
  common_assert expected, KernAux.utoa16(number)
end

def test_itoa16(number, expected)
  common_assert expected, KernAux.itoa16(number)
end

if KernAux::Version.with_ntoa?
  assert 'KernAux.utoa' do
    number = Random.rand(2**32 - 1)
    base = 2 + Random.rand(36 - 2)
    test_utoa number, base, number.to_s(base)

    base = 2 + Random.rand(36 - 2)
    test_utoa 0, base, '0'

    number = 2**32 - 1
    base = 2 + Random.rand(36 - 2)
    test_utoa number, base, number.to_s(base)

    assert_raise RangeError, 'can\'t convert negative number to uint64_t' do
      base = 2 + Random.rand(36 - 2)
      KernAux.utoa(-1, base)
    end

    number = Random.rand(2**32 - 1)
    base = -(2 + Random.rand(36 - 2))
    test_utoa number, base, number.to_s(-base).upcase

    number = Random.rand(2**32 - 1)
    test_utoa number, :b, number.to_s(2)

    number = Random.rand(2**32 - 1)
    test_utoa number, :B, number.to_s(2)

    number = Random.rand(2**32 - 1)
    test_utoa number, :o, number.to_s(8)

    number = Random.rand(2**32 - 1)
    test_utoa number, :O, number.to_s(8)

    number = Random.rand(2**32 - 1)
    test_utoa number, :d, number.to_s(10)

    number = Random.rand(2**32 - 1)
    test_utoa number, :D, number.to_s(10)

    number = Random.rand(2**32 - 1)
    test_utoa number, :h, number.to_s(16)

    number = Random.rand(2**32 - 1)
    test_utoa number, :x, number.to_s(16)

    number = Random.rand(2**32 - 1)
    test_utoa number, :H, number.to_s(16).upcase

    number = Random.rand(2**32 - 1)
    test_utoa number, :X, number.to_s(16).upcase

    number = Random.rand(2**32 - 1)
    base = 2 + Random.rand(36 - 2)
    prefix = 'foo'
    test_utoax number, base, prefix, "#{prefix}#{number.abs.to_s(base)}"

    number = Random.rand(2**32 - 1)
    base = 2 + Random.rand(36 - 2)
    prefix = 'a' * 100
    test_utoax number, base, prefix, "#{prefix}#{number.abs.to_s(base)}"

    assert_raise(
      KernAux::TooLongNtoaPrefixError,
      'prefix length 101 is too long',
    ) do
      number = Random.rand(2**32 - 1)
      base = 2 + Random.rand(36 - 2)
      prefix = 'a' * 101
      KernAux.utoa(number, base, prefix)
    end

    assert_raise TypeError, 'no implicit conversion from string' do
      number = Random.rand(2**32 - 1).to_s
      KernAux.utoa(number.to_s)
    end
  end

  assert 'KernAux.itoa' do
    number = Random.rand(2**31 - 1) * [1, -1].sample
    base = 2 + Random.rand(36 - 2)
    test_itoa number, base, number.to_s(base)

    base = 2 + Random.rand(36 - 2)
    test_itoa 0, base, '0'

    base = 2 + Random.rand(36 - 2)
    test_itoa 1, base, '1'

    base = 2 + Random.rand(36 - 2)
    test_itoa(-1, base, '-1')

    number = 2**31 - 1
    base = 2 + Random.rand(36 - 2)
    test_itoa number, base, number.to_s(base)

    number = -(2**31 - 1)
    base = 2 + Random.rand(36 - 2)
    test_itoa number, base, number.to_s(base)

    number = 2**31 - 1
    base = -(2 + Random.rand(36 - 2))
    test_itoa number, base, number.to_s(-base).upcase

    number = -(2**31 - 1)
    base = -(2 + Random.rand(36 - 2))
    test_itoa number, base, number.to_s(-base).upcase

    number = Random.rand(2**31 - 1) * [1, -1].sample
    test_itoa number, :b, number.to_s(2)

    number = Random.rand(2**31 - 1) * [1, -1].sample
    test_itoa number, :B, number.to_s(2)

    number = Random.rand(2**31 - 1) * [1, -1].sample
    test_itoa number, :o, number.to_s(8)

    number = Random.rand(2**31 - 1) * [1, -1].sample
    test_itoa number, :O, number.to_s(8)

    number = Random.rand(2**31 - 1) * [1, -1].sample
    test_itoa number, :d, number.to_s(10)

    number = Random.rand(2**31 - 1) * [1, -1].sample
    test_itoa number, :D, number.to_s(10)

    number = Random.rand(2**31 - 1) * [1, -1].sample
    test_itoa number, :h, number.to_s(16)

    number = Random.rand(2**31 - 1) * [1, -1].sample
    test_itoa number, :x, number.to_s(16)

    number = Random.rand(2**31 - 1) * [1, -1].sample
    test_itoa number, :H, number.to_s(16).upcase

    number = Random.rand(2**31 - 1) * [1, -1].sample
    test_itoa number, :X, number.to_s(16).upcase

    number = Random.rand(2**31 - 1) * [1, -1].sample
    base = 2 + Random.rand(36 - 2)
    prefix = 'foo'
    sign = number < 0 ? '-' : ''
    test_itoax number, base, prefix, "#{sign}#{prefix}#{number.abs.to_s(base)}"

    number = Random.rand(2**31 - 1) * [1, -1].sample
    base = 2 + Random.rand(36 - 2)
    prefix = 'a' * 100
    sign = number < 0 ? '-' : ''
    test_itoax number, base, prefix, "#{sign}#{prefix}#{number.abs.to_s(base)}"

    assert_raise(
      KernAux::TooLongNtoaPrefixError,
      'prefix length 101 is too long',
    ) do
      number = Random.rand(2**31 - 1) * [1, -1].sample
      base = 2 + Random.rand(36 - 2)
      prefix = 'a' * 101
      KernAux.itoa(number, base, prefix)
    end

    assert_raise TypeError, 'no implicit conversion from string' do
      number = Random.rand(2**31 - 1) * [1, -1].sample
      KernAux.itoa(number.to_s)
    end
  end

  assert 'KernAux.utoa2' do
    test_utoa2 0, '0b0'
    test_utoa2 1, '0b1'
    test_utoa2 123, '0b1111011'
    test_utoa2 2**32 - 1, "0b#{(2**32 - 1).to_s(2)}"

    assert_raise RangeError, 'can\'t convert negative number to uint64_t' do
      KernAux.utoa2(-1)
    end

    assert_raise TypeError, 'no implicit conversion from string' do
      number = Random.rand(2**32 - 1).to_s
      KernAux.utoa2(number.to_s)
    end
  end

  assert 'KernAux.itoa2' do
    test_itoa2 0, '0b0'
    test_itoa2 1, '0b1'
    test_itoa2(-1, '-0b1')
    test_itoa2 123, '0b1111011'
    test_itoa2(-123, '-0b1111011')
    test_itoa2 2**31 - 1, "0b#{(2**31 - 1).to_s(2)}"
    test_itoa2(-2**31, "-0b#{(2**31).to_s(2)}")

    assert_raise TypeError, 'no implicit conversion from string' do
      number = Random.rand(2**31 - 1) * [1, -1].sample
      KernAux.itoa2(number.to_s)
    end
  end

  assert 'KernAux.utoa8' do
    test_utoa8 0, '0o0'
    test_utoa8 0o1, '0o1'
    test_utoa8 0o123, '0o123'
    test_utoa8 2**32 - 1, "0o#{(2**32 - 1).to_s(8)}"

    assert_raise RangeError, 'can\'t convert negative number to uint64_t' do
      KernAux.utoa8(-1)
    end

    assert_raise TypeError, 'no implicit conversion from string' do
      number = Random.rand(2**32 - 1).to_s
      KernAux.utoa8(number.to_s)
    end
  end

  assert 'KernAux.itoa8' do
    test_itoa8 0, '0o0'
    test_itoa8 0o1, '0o1'
    test_itoa8(-0o1, '-0o1')
    test_itoa8 0o123, '0o123'
    test_itoa8(-0o123, '-0o123')
    test_itoa8 2**31 - 1, "0o#{(2**31 - 1).to_s(8)}"
    test_itoa8(-2**31, "-0o#{(2**31).to_s(8)}")

    assert_raise TypeError, 'no implicit conversion from string' do
      number = Random.rand(2**31 - 1) * [1, -1].sample
      KernAux.itoa8(number.to_s)
    end
  end

  assert 'KernAux.utoa10' do
    test_utoa10 0, '0'
    test_utoa10 1, '1'
    test_utoa10 123, '123'
    test_utoa10 2**32 - 1, (2**32 - 1).to_s

    assert_raise RangeError, 'can\'t convert negative number to uint64_t' do
      KernAux.utoa10(-1)
    end

    assert_raise TypeError, 'no implicit conversion from string' do
      number = Random.rand(2**32 - 1).to_s
      KernAux.utoa10(number.to_s)
    end
  end

  assert 'KernAux.itoa10' do
    test_itoa10 0, '0'
    test_itoa10 1, '1'
    test_itoa10(-1, '-1')
    test_itoa10 123, '123'
    test_itoa10(-123, '-123')
    test_itoa10 2**31 - 1, (2**31 - 1).to_s
    test_itoa10(-2**31, (-2**31).to_s)

    assert_raise TypeError, 'no implicit conversion from string' do
      number = Random.rand(2**31 - 1) * [1, -1].sample
      KernAux.itoa10(number.to_s)
    end
  end

  assert 'KernAux.utoa16' do
    test_utoa16 0, '0x0'
    test_utoa16 1, '0x1'
    test_utoa16 0x123, '0x123'
    test_utoa16 2**32 - 1, "0x#{(2**32 - 1).to_s(16)}"

    assert_raise RangeError, 'can\'t convert negative number to uint64_t' do
      KernAux.utoa16(-1)
    end

    assert_raise TypeError, 'no implicit conversion from string' do
      number = Random.rand(2**32 - 1).to_s
      KernAux.utoa16(number.to_s)
    end
  end

  assert 'KernAux.itoa16' do
    test_itoa16 0, '0x0'
    test_itoa16 1, '0x1'
    test_itoa16(-1, '-0x1')
    test_itoa16 0x123, '0x123'
    test_itoa16(-0x123, '-0x123')
    test_itoa16 2**31 - 1, "0x#{(2**31 - 1).to_s(16)}"
    test_itoa16(-2**31, "-0x#{(2**31).to_s(16)}")

    assert_raise TypeError, 'no implicit conversion from string' do
      number = Random.rand(2**31 - 1) * [1, -1].sample
      KernAux.itoa16(number.to_s)
    end
  end
end
