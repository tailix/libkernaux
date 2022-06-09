# frozen_string_literal: true

require_relative 'lib/kernaux/version'

Gem::Specification.new do |spec|
  repo = 'https://github.com/tailix/libkernaux'
  home = "#{repo}/tree/master/bindings/ruby"
  bugs = "#{repo}/issues"
  docs = "https://www.rubydoc.info/gems/kernaux/#{KernAux::VERSION}"

  spec.name     = 'kernaux'
  spec.version  = KernAux::VERSION
  spec.license  = 'MIT'
  spec.homepage = home
  spec.platform = Gem::Platform::RUBY

  spec.required_ruby_version = '~> 3.0'

  spec.authors = ['Alex Kotov']
  spec.email   = %w[kotovalexarian@gmail.com]

  spec.summary =
    'Binding to libkernaux - auxiliary library for kernel development'

  spec.description = <<~DESCRIPTION.split("\n").map(&:strip).join ' '
    Binding to libkernaux - auxiliary library for kernel development.
  DESCRIPTION

  spec.metadata['rubygems_mfa_required'] = 'true'
  spec.metadata['homepage_uri']          = home
  spec.metadata['source_code_uri']       = home
  spec.metadata['bug_tracker_uri']       = bugs
  spec.metadata['documentation_uri']     = docs

  spec.bindir        = 'exe'
  spec.require_paths = ['lib']

  spec.files = Dir.chdir File.expand_path __dir__ do
    `git ls-files -z`.split("\x0").reject do |f|
      f.match %r{\A(?:test|spec|features)/}
    end
  end

  spec.executables = spec.files.grep(%r{\Aexe/}) { |f| File.basename f }

  spec.extensions << 'ext/default/extconf.rb'

  spec.add_development_dependency 'bundler',             '~> 2.2'
  spec.add_development_dependency 'pry',                 '~> 0.14'
  spec.add_development_dependency 'rake',                '~> 13.0'
  spec.add_development_dependency 'rake-compiler',       '~> 1.1'
  spec.add_development_dependency 'rspec',               '~> 3.10'
  spec.add_development_dependency 'rubocop',             '~> 1.25'
  spec.add_development_dependency 'rubocop-performance', '~> 1.13'
  spec.add_development_dependency 'rubocop-rake',        '~> 0.6'
  spec.add_development_dependency 'rubocop-rspec',       '~> 2.7'
  spec.add_development_dependency 'simplecov',           '~> 0.21'
  spec.add_development_dependency 'yard',                '~> 0.9'
end
