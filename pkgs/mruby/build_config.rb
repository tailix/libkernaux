MRuby::Build.new do |conf|
  conf.toolchain
  conf.enable_test
  conf.gem '.'

  # FIXME: temporary hack to fix FreeBSD build
  conf.cc do |cc|
    cc.include_paths += %w[/usr/local/include]
  end
  conf.linker do |linker|
    linker.library_paths += %w[/usr/local/lib]
  end
end
