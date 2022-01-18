# frozen_string_literal: true

require_relative 'lib/kernaux/version'

Gem::Specification.new do |spec|
  repo = 'https://github.com/tailix/libkernaux'

  spec.name     = 'kernaux'
  spec.version  = KernAux::VERSION
  spec.license  = 'MIT'
  spec.homepage = "#{repo}/tree/master/pkgs/ruby"
  spec.platform = Gem::Platform::RUBY
  spec.summary  = 'Auxiliary library for kernel development'

  spec.required_ruby_version = '~> 3.0'

  spec.authors = ['Alex Kotov']
  spec.email   = %w[kotovalexarian@gmail.com]

  spec.description = <<~DESCRIPTION.split("\n").map(&:strip).join ' '
    Auxiliary library for kernel development.
  DESCRIPTION

  spec.metadata['homepage_uri']          = spec.homepage
  spec.metadata['source_code_uri']       = spec.homepage
  spec.metadata['bug_tracker_uri']       = "#{repo}/issues"
  spec.metadata['rubygems_mfa_required'] = 'true'

  spec.bindir        = 'exe'
  spec.require_paths = ['lib']

  spec.files = Dir.chdir File.expand_path __dir__ do
    `git ls-files -z`.split("\x0").reject do |f|
      f.match %r{\A(?:test|spec|features)/}
    end
  end

  spec.executables = spec.files.grep(%r{\Aexe/}) { |f| File.basename f }

  spec.extensions << 'ext/libkernaux/extconf.rb'

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
