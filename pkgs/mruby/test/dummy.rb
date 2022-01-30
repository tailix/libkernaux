assert 'Dummy' do
  assert_equal nil, KernAux.assert_cb
  KernAux.assert_cb = 123
  assert_equal 123, KernAux.assert_cb
  assert_equal nil, KernAux.assert_do(__FILE__, __LINE__, 'hello')
end
