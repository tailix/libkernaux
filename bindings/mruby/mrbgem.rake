MRuby::Gem::Specification.new 'mruby-kernaux' do |spec|
  spec.version = '0.7.0'
  spec.license = 'MIT'
  spec.homepage =
    'https://github.com/tailix/libkernaux/tree/master/bindings/ruby'
  spec.author = 'Alex Kotov'

  spec.summary =
    'Binding to libkernaux - auxiliary library for kernel development'

  spec.description = <<~DESCRIPTION.split("\n").map(&:strip).join ' '
    Binding to libkernaux - auxiliary library for kernel development.
  DESCRIPTION

  spec.add_test_dependency 'mruby-eval'
  spec.add_test_dependency 'mruby-io'
  spec.add_test_dependency 'mruby-random'
  spec.add_test_dependency 'mruby-yaml'

  spec.linker.libraries << 'kernaux'
end
