MRuby::Build.new do |conf|
  conf.toolchain
  conf.enable_test
  conf.gem '.'
end
