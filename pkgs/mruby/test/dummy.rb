assert do
  assert_equal KernAux::DEFAULT_ASSERT_CB, KernAux.assert_cb

  KernAux.assert_cb = 123
  assert_equal 123, KernAux.assert_cb

  KernAux.assert_cb = KernAux::DEFAULT_ASSERT_CB
  assert_equal KernAux::DEFAULT_ASSERT_CB, KernAux.assert_cb

  assert_raise KernAux::AssertError, 'foo.rb:123:hello' do
    KernAux.assert_do 'foo.rb', 123, 'hello'
  end
end
