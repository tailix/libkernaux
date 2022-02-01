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
