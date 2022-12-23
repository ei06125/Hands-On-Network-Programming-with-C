file(GLOB_RECURSE files_RESULT "*.c")

foreach(file ${files_RESULT})
  get_filename_component(filename ${file} NAME_WE [CACHE])
  add_executable(${filename} ${filename}.c)
endforeach()
