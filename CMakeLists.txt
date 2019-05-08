
cmake_minimum_required(VERSION 3.7)

project(structs)

set(CMAKE_CXX_STANDARD 11)

include(utils-fs.cmake)


macro(ADD_EXE_BY_DIR curdir pre)
    message('---ADD_EXE_BY_DIR begin:')
    scandir_r(SUBDIRS ${curdir})
    list(APPEND SUBDIRS "/")
    foreach(subdir ${SUBDIRS})
        message('subdir : ' ${subdir})
        set(hfiles "")
        set(cppfiles "")
        file(GLOB hfiles ${curdir}/*.h)
        file(GLOB cfiles ${curdir}/*.c)
        file(GLOB cppfiles ${curdir}/*.cpp)
        string(LENGTH "${cfiles}" cfiles_len)
        string(LENGTH "${cppfiles}" cppfiles_len)
        message('cfiles : ' ${cfiles})
        message('cppfiles : ' ${cppfiles})
        if ((cfiles_len GREATER 2) OR (cppfiles_len GREATER 2))
            string(REGEX MATCH ".*/(.*)" temp1 ${subdir})
            if (CMAKE_MATCH_1)
                set(dirname1 ${CMAKE_MATCH_1})
                #                message("dirname1 : " ${dirname1})
                set(programe_name ${pre}_${dirname1})
                add_executable(${programe_name}
                        ${hfiles}
                        ${cfiles}
                        ${cppfiles}
                        )
                message('---ADD_EXE_BY_DIR :' ${programe_name})
            endif ()
            string(REGEX MATCH "^.*\\.[^.]*$" temp1 ${subdir}) # 第几个括号（序号）是 ${CMAKE_MATCH_n} 中的n
        endif ()
        #    ADD_SUBDIRECTORY(${subdir})
    endforeach()
    message('---ADD_EXE_BY_DIR end.')
endmacro()

macro(ADD_EXE_BY_DIR2 curdir pre)
    message('---ADD_EXE_BY_DIR begin:')
    set(hfiles "")
    set(cppfiles "")
    file(GLOB hfiles ${curdir}/*.h)
    file(GLOB cfiles ${curdir}/*.c)
    file(GLOB cppfiles ${curdir}/*.cpp)
    string(LENGTH "${cfiles}" cfiles_len)
    string(LENGTH "${cppfiles}" cppfiles_len)
#    message('cfiles : ' ${cfiles})
#    message('cppfiles : ' ${cppfiles})
    if ((cfiles_len GREATER 2) OR (cppfiles_len GREATER 2))
        string(REGEX MATCH ".*/(.*)" temp1 ${curdir})
        if (CMAKE_MATCH_1)
            set(dirname1 ${CMAKE_MATCH_1})
            #                message("dirname1 : " ${dirname1})
            set(programe_name ${pre}_${dirname1})
            add_executable(${programe_name}
                    ${hfiles}
                    ${cfiles}
                    ${cppfiles}
                    )
            message('---ADD_EXE_BY_DIR :' ${programe_name})
        endif ()
    endif ()
    #    ADD_SUBDIRECTORY(${subdir})
    message('---ADD_EXE_BY_DIR end.')
endmacro()

ADD_EXE_BY_DIR2(${CMAKE_CURRENT_SOURCE_DIR}/c structs)
ADD_EXE_BY_DIR2(${CMAKE_CURRENT_SOURCE_DIR}/cpp structs)


# c
#https://users.cs.fiu.edu/~weiss/dsaa_c2e/files.html
# c++
#https://users.cs.fiu.edu/~weiss/dsaa_c++4/code/
# java
#http://users.cis.fiu.edu/~weiss/dsaajava3/code/
