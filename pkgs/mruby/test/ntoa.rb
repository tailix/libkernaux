def test_utoa(number, base, expected)
  result = KernAux.utoa(number, base)

  assert_true result.instance_of? String
  #assert_true result.frozen?
  assert_equal expected, result
end

def test_itoa(number, base, expected)
  result = KernAux.itoa(number, base)

  assert_true result.instance_of? String
  #assert_true result.frozen?
  assert_equal expected, result
end

assert 'KernAux.utoa' do
  number = Random.rand(2**32 - 1)
  base = 2 + Random.rand(36 - 2)
  test_utoa number, base, number.to_s(base)

  number = 0
  base = 2 + Random.rand(36 - 2)
  test_utoa number, base, '0'

  number = 2**32 - 1
  base = 2 + Random.rand(36 - 2)
  test_utoa number, base, number.to_s(base)

  number = -1
  base = 2 + Random.rand(36 - 2)
  assert_raise RangeError, 'can\'t convert negative number to uint64_t' do
    KernAux.utoa number, base
  end

  number = Random.rand(2**32 - 1)
  base = -(2 + Random.rand(36 - 2))
  test_utoa number, base, number.to_s(-base).upcase

  number = Random.rand(2**32 - 1)
  base = :b
  test_utoa number, base, number.to_s(2)

  number = Random.rand(2**32 - 1)
  base = :B
  test_utoa number, base, number.to_s(2)

  number = Random.rand(2**32 - 1)
  base = :o
  test_utoa number, base, number.to_s(8)

  number = Random.rand(2**32 - 1)
  base = :O
  test_utoa number, base, number.to_s(8)

  number = Random.rand(2**32 - 1)
  base = :d
  test_utoa number, base, number.to_s(10)

  number = Random.rand(2**32 - 1)
  base = :D
  test_utoa number, base, number.to_s(10)

  number = Random.rand(2**32 - 1)
  base = :h
  test_utoa number, base, number.to_s(16)

  number = Random.rand(2**32 - 1)
  base = :x
  test_utoa number, base, number.to_s(16)

  number = Random.rand(2**32 - 1)
  base = :H
  test_utoa number, base, number.to_s(16).upcase

  number = Random.rand(2**32 - 1)
  base = :X
  test_utoa number, base, number.to_s(16).upcase
end

assert 'KernAux.itoa' do
  number = Random.rand(2**31 - 1) * [1, -1].sample
  base = 2 + Random.rand(36 - 2)
  test_itoa number, base, number.to_s(base)

  number = 0
  base = 2 + Random.rand(36 - 2)
  test_itoa number, base, '0'

  number = 1
  base = 2 + Random.rand(36 - 2)
  test_itoa number, base, '1'

  number = -1
  base = 2 + Random.rand(36 - 2)
  test_itoa number, base, '-1'

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
  base = :b
  test_itoa number, base, number.to_s(2)

  number = Random.rand(2**31 - 1) * [1, -1].sample
  base = :B
  test_itoa number, base, number.to_s(2)

  number = Random.rand(2**31 - 1) * [1, -1].sample
  base = :o
  test_itoa number, base, number.to_s(8)

  number = Random.rand(2**31 - 1) * [1, -1].sample
  base = :O
  test_itoa number, base, number.to_s(8)

  number = Random.rand(2**31 - 1) * [1, -1].sample
  base = :d
  test_itoa number, base, number.to_s(10)

  number = Random.rand(2**31 - 1) * [1, -1].sample
  base = :D
  test_itoa number, base, number.to_s(10)

  number = Random.rand(2**31 - 1) * [1, -1].sample
  base = :h
  test_itoa number, base, number.to_s(16)

  number = Random.rand(2**31 - 1) * [1, -1].sample
  base = :x
  test_itoa number, base, number.to_s(16)

  number = Random.rand(2**31 - 1) * [1, -1].sample
  base = :H
  test_itoa number, base, number.to_s(16).upcase

  number = Random.rand(2**31 - 1) * [1, -1].sample
  base = :X
  test_itoa number, base, number.to_s(16).upcase
end

assert 'KernAux.utoa10' do
  assert_equal '0', KernAux.utoa10(0)
  assert_equal '1', KernAux.utoa10(1)
  assert_equal '123', KernAux.utoa10(123)
  assert_equal (2**32 - 1).to_s, KernAux.utoa10(2**32 - 1)
end

assert 'KernAux.itoa10' do
  assert_equal '0', KernAux.itoa10(0)
  assert_equal '1', KernAux.itoa10(1)
  assert_equal '-1', KernAux.itoa10(-1)
  assert_equal '123', KernAux.itoa10(123)
  assert_equal '-123', KernAux.itoa10(-123)
  assert_equal (2**31 - 1).to_s, KernAux.itoa10(2**31 - 1)
  assert_equal (-2**31).to_s, KernAux.itoa10(-2**31)
end

assert 'KernAux.utoa16' do
  assert_equal '0', KernAux.utoa16(0)
  assert_equal '1', KernAux.utoa16(1)
  assert_equal '123', KernAux.utoa16(0x123)
  assert_equal (2**32 - 1).to_s(16), KernAux.utoa16(2**32 - 1)
end

assert 'KernAux.itoa16' do
  assert_equal '0', KernAux.itoa16(0)
  assert_equal '1', KernAux.itoa16(1)
  assert_equal '-1', KernAux.itoa16(-1)
  assert_equal '123', KernAux.itoa16(0x123)
  assert_equal '-123', KernAux.itoa16(-0x123)
  assert_equal (2**31 - 1).to_s(16), KernAux.itoa16(2**31 - 1)
  assert_equal (-2**31).to_s(16), KernAux.itoa16(-2**31)
end
