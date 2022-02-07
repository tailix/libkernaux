def test_utoa(number, base, expected)
  result = KernAux.utoa(number, base)

  assert_true result.instance_of? String
  assert_true result.frozen?
  assert_equal expected, result
end

def test_itoa(number, base, expected)
  result = KernAux.itoa(number, base)

  assert_true result.instance_of? String
  assert_true result.frozen?
  assert_equal expected, result
end

def test_utoa10(number, expected)
  result = KernAux.utoa10(number)

  assert_true result.instance_of? String
  assert_true result.frozen?
  assert_equal expected, result
end

def test_itoa10(number, expected)
  result = KernAux.itoa10(number)

  assert_true result.instance_of? String
  assert_true result.frozen?
  assert_equal expected, result
end

def test_utoa16(number, expected)
  result = KernAux.utoa16(number)

  assert_true result.instance_of? String
  assert_true result.frozen?
  assert_equal expected, result
end

def test_itoa16(number, expected)
  result = KernAux.itoa16(number)

  assert_true result.instance_of? String
  assert_true result.frozen?
  assert_equal expected, result
end

assert 'KernAux.utoa' do
  number = Random.rand(2**32 - 1)
  base = 2 + Random.rand(36 - 2)
  test_utoa number, base, number.to_s(base)

  base = 2 + Random.rand(36 - 2)
  test_utoa 0, base, '0'

  number = 2**32 - 1
  base = 2 + Random.rand(36 - 2)
  test_utoa number, base, number.to_s(base)

  base = 2 + Random.rand(36 - 2)
  assert_raise RangeError, 'can\'t convert negative number to uint64_t' do
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
end

assert 'KernAux.utoa10' do
  test_utoa10 0, '0'
  test_utoa10 1, '1'
  test_utoa10 123, '123'
  test_utoa10 2**32 - 1, (2**32 - 1).to_s

  assert_raise RangeError, 'can\'t convert negative number to uint64_t' do
    KernAux.utoa10(-1)
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
end

assert 'KernAux.utoa16' do
  test_utoa16 0, '0'
  test_utoa16 1, '1'
  test_utoa16 0x123, '123'
  test_utoa16 2**32 - 1, (2**32 - 1).to_s(16)

  assert_raise RangeError, 'can\'t convert negative number to uint64_t' do
    KernAux.utoa16(-1)
  end
end

assert 'KernAux.itoa16' do
  test_itoa16 0, '0'
  test_itoa16 1, '1'
  test_itoa16(-1, '-1')
  test_itoa16 0x123, '123'
  test_itoa16(-0x123, '-123')
  test_itoa16 2**31 - 1, (2**31 - 1).to_s(16)
  test_itoa16(-2**31, (-2**31).to_s(16))
end
