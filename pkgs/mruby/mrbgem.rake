MRuby::Gem::Specification.new 'mruby-kernaux' do |spec|
  spec.version = '0.0.0'
  spec.license = 'MIT'
  spec.homepage = 'https://github.com/tailix/libkernaux/tree/master/pkgs/ruby'
  spec.author = 'Alex Kotov'

  spec.summary =
    'Binding to libkernaux - auxiliary library for kernel development'

  spec.description = <<~DESCRIPTION.split("\n").map(&:strip).join ' '
    Binding to libkernaux - auxiliary library for kernel development.
  DESCRIPTION

  spec.linker.libraries << 'kernaux'
end
