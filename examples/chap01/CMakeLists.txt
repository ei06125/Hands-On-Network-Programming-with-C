if(OS_NAME_RESULT STREQUAL "Windows")
  add_executable(win_init win_init.c)
  add_executable(win_list win_list.c)
else()
  add_executable(unix_list unix_list.c)
endif()
