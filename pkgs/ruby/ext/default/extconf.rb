# frozen_string_literal: true

require 'mkmf'

have_library 'kernaux'

have_func 'kernaux_utoa10'
have_func 'kernaux_itoa10'

create_makefile 'kernaux/default'
