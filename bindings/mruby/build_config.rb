MRuby::Build.new do |conf|
  conf.toolchain
  conf.enable_test
  conf.gem '.'
  conf.gem core: 'mruby-bin-mirb'
end
