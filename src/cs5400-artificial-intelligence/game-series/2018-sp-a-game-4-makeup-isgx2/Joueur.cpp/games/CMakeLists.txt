#get a list of all the subdirectories
file(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)
set(dirlist "")
foreach(child ${children})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${child})
        list(APPEND dirlist ${child})
    endif()
endforeach()

set(LOCAL_FILES "")

foreach(dir ${dirlist})
    add_subdirectory(${dir})
    list(APPEND LOCAL_FILES ${FILES})
endforeach()

set(FILES
    ${LOCAL_FILES}
    PARENT_SCOPE)
