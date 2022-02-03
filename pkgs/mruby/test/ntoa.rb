assert 'KernAux.utoa' do
  number = Random.rand(2**32 - 1)
  base = 2 + Random.rand(36 - 2)
  assert_equal number.to_s(base), KernAux.utoa(number, base)

  number = 0
  base = 2 + Random.rand(36 - 2)
  assert_equal '0', KernAux.utoa(number, base)

  number = 2**32 - 1
  base = 2 + Random.rand(36 - 2)
  assert_equal number.to_s(base), KernAux.utoa(number, base)

  number = -1
  base = 2 + Random.rand(36 - 2)
  assert_raise RangeError, 'can\'t convert negative number to uint64_t' do
    KernAux.utoa number, base
  end

  number = Random.rand(2**32 - 1)
  base = -(2 + Random.rand(36 - 2))
  assert_equal number.to_s(-base).upcase, KernAux.utoa(number, base)

  number = Random.rand(2**32 - 1)
  base = :b
  assert_equal number.to_s(2), KernAux.utoa(number, base)

  number = Random.rand(2**32 - 1)
  base = :B
  assert_equal number.to_s(2), KernAux.utoa(number, base)

  number = Random.rand(2**32 - 1)
  base = :o
  assert_equal number.to_s(8), KernAux.utoa(number, base)

  number = Random.rand(2**32 - 1)
  base = :O
  assert_equal number.to_s(8), KernAux.utoa(number, base)

  number = Random.rand(2**32 - 1)
  base = :d
  assert_equal number.to_s(10), KernAux.utoa(number, base)

  number = Random.rand(2**32 - 1)
  base = :D
  assert_equal number.to_s(10), KernAux.utoa(number, base)

  number = Random.rand(2**32 - 1)
  base = :h
  assert_equal number.to_s(16), KernAux.utoa(number, base)

  number = Random.rand(2**32 - 1)
  base = :x
  assert_equal number.to_s(16), KernAux.utoa(number, base)

  number = Random.rand(2**32 - 1)
  base = :H
  assert_equal number.to_s(16).upcase, KernAux.utoa(number, base)

  number = Random.rand(2**32 - 1)
  base = :X
  assert_equal number.to_s(16).upcase, KernAux.utoa(number, base)
end

assert 'KernAux.itoa' do
  number = Random.rand(2**31 - 1) * [1, -1].sample
  base = 2 + Random.rand(36 - 2)
  assert_equal number.to_s(base), KernAux.itoa(number, base)

  number = 0
  base = 2 + Random.rand(36 - 2)
  assert_equal '0', KernAux.itoa(number, base)

  number = 1
  base = 2 + Random.rand(36 - 2)
  assert_equal '1', KernAux.itoa(number, base)

  number = -1
  base = 2 + Random.rand(36 - 2)
  assert_equal '-1', KernAux.itoa(number, base)

  number = 2**31 - 1
  base = 2 + Random.rand(36 - 2)
  assert_equal number.to_s(base), KernAux.itoa(number, base)

  number = -(2**31 - 1)
  base = 2 + Random.rand(36 - 2)
  assert_equal number.to_s(base), KernAux.itoa(number, base)

  number = Random.rand(2**31 - 1) * [1, -1].sample
  base = :b
  assert_equal number.to_s(2), KernAux.itoa(number, base)

  number = Random.rand(2**31 - 1) * [1, -1].sample
  base = :B
  assert_equal number.to_s(2), KernAux.itoa(number, base)

  number = Random.rand(2**31 - 1) * [1, -1].sample
  base = :o
  assert_equal number.to_s(8), KernAux.itoa(number, base)

  number = Random.rand(2**31 - 1) * [1, -1].sample
  base = :O
  assert_equal number.to_s(8), KernAux.itoa(number, base)

  number = Random.rand(2**31 - 1) * [1, -1].sample
  base = :d
  assert_equal number.to_s(10), KernAux.itoa(number, base)

  number = Random.rand(2**31 - 1) * [1, -1].sample
  base = :D
  assert_equal number.to_s(10), KernAux.itoa(number, base)

  number = Random.rand(2**31 - 1) * [1, -1].sample
  base = :h
  assert_equal number.to_s(16), KernAux.itoa(number, base)

  number = Random.rand(2**31 - 1) * [1, -1].sample
  base = :x
  assert_equal number.to_s(16), KernAux.itoa(number, base)

  number = Random.rand(2**31 - 1) * [1, -1].sample
  base = :H
  assert_equal number.to_s(16).upcase, KernAux.itoa(number, base)

  number = Random.rand(2**31 - 1) * [1, -1].sample
  base = :X
  assert_equal number.to_s(16).upcase, KernAux.itoa(number, base)
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
