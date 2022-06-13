# frozen_string_literal: true

require 'mkmf'

$CFLAGS += ' -pedantic -Wall -Wextra'

raise 'libkernaux not found' unless have_library 'kernaux'

raise 'kernaux_assert_do not found' unless have_func 'kernaux_assert_do'
unless have_var 'kernaux_assert_cb', 'kernaux.h'
  raise 'kernaux_assert_cb not found'
end

raise 'can\'t create Makefile' unless create_makefile 'kernaux/default'
