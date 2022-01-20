# frozen_string_literal: true

require 'mkmf'

raise 'libkernaux not found' unless have_library 'kernaux'

have_func 'kernaux_utoa10'
have_func 'kernaux_itoa10'

raise 'can\'t create Makefile' unless create_makefile 'kernaux/default'
