# frozen_string_literal: true

require 'mkmf'

$CFLAGS += ' -pedantic -Wall -Wextra'

raise 'libkernaux not found' unless have_library 'kernaux'

raise 'kernaux_assert_do not found' unless have_func 'kernaux_assert_do'
unless have_var 'kernaux_assert_cb', 'kernaux.h'
  raise 'kernaux_assert_cb not found'
end

have_func 'kernaux_utoa'
have_func 'kernaux_itoa'
have_func 'kernaux_utoa8'
have_func 'kernaux_itoa8'
have_func 'kernaux_utoa10'
have_func 'kernaux_itoa10'
have_func 'kernaux_utoa16'
have_func 'kernaux_itoa16'

have_func 'kernaux_snprintf'

# TODO: do something if not found?
have_func 'KernAux_PrintfFmt_Spec_create'
have_func 'KernAux_PrintfFmt_Spec_parse'
have_func 'KernAux_PrintfFmt_Spec_set_width'
have_func 'KernAux_PrintfFmt_Spec_set_precision'

have_func 'kernaux_cmdline'

raise 'can\'t create Makefile' unless create_makefile 'kernaux/default'
