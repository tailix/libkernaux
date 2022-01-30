assert 'KernAux.assert_cb is set by default' do
  assert_equal KernAux::DEFAULT_ASSERT_CB, KernAux.assert_cb
end

assert 'KernAux::DEFAULT_ASSERT_CB raises' do
  assert_raise KernAux::AssertError, 'foo.rb:123:bar' do
    KernAux::DEFAULT_ASSERT_CB.call 'foo.rb', 123, 'bar'
  end
end

assert 'we can set KernAux.assert_cb' do
  KernAux.assert_cb = KernAux::DEFAULT_ASSERT_CB
  assert_equal KernAux::DEFAULT_ASSERT_CB, KernAux.assert_cb
end

assert 'KernAux.assert_do raises' do
  assert_raise KernAux::AssertError, 'foo.rb:123:hello' do
    KernAux.assert_do 'foo.rb', 123, 'hello'
  end
end
