project(HandsOnNetworkProgrammingWithCpp)

log_info("Configuring Hands-On Network Programming with C++ examples")

set(THIS_DIR ${CMAKE_CURRENT_LIST_DIR})
file(
  GLOB folders
  RELATIVE ${THIS_DIR}
  ${THIS_DIR}/*
)
foreach(folder ${folders})
  if(IS_DIRECTORY ${THIS_DIR}/${folder})
    add_subdirectory(${folder})
  endif()
endforeach(folder ${folders})

log_info("Configuring Hands-On Network Programming with C++ examples -- DONE")
