project('dwlang',
  'cpp',
  default_options: 'cpp_std=c++23'
)

incdir = include_directories('src')

executable('dcc',
  'src' / 'driver' / 'main.cpp',
  'src' / 'driver' / 'compile_context.cpp',
  'src' / 'driver' / 'compile_context.h',
  'src' / 'frontend' / 'parser' / 'tokenizer.cpp',
  'src' / 'frontend' / 'parser' / 'tokenizer.h',
  'src' / 'frontend' / 'parser' / 'token.cpp',
  'src' / 'frontend' / 'parser' / 'token.h',
  'src' / 'common' / 'utilities.h',
  include_directories: incdir
)
