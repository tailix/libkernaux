# frozen_string_literal: true

require 'mkmf'

raise 'libkernaux not found' unless have_library 'kernaux'

raise 'kernaux_assert_do not found' unless have_func 'kernaux_assert_do'
unless have_var 'kernaux_assert_cb', 'kernaux.h'
  raise 'kernaux_assert_cb not found'
end

have_func 'kernaux_utoa10'
have_func 'kernaux_itoa10'

raise 'can\'t create Makefile' unless create_makefile 'kernaux/default'
