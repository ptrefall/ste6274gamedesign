
# detect the OS
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(WINDOWS 1)
else()
    message(WARNING "Unsupported operating system")
    return()
endif()

# detect the architecture
# note: this test won't work for cross-compilation
include(CheckTypeSize)
check_type_size(void* SIZEOF_VOID_PTR)
if(${SIZEOF_VOID_PTR} MATCHES "^4$")
    set(ARCH_32BITS 1)
else()
    set(ARCH_64BITS 1)
endif()

# detect the compiler and its version
if(MSVC_VERSION EQUAL 1400)
    set(COMPILER_MSVC 2005)
elseif(MSVC_VERSION EQUAL 1500)
    set(COMPILER_MSVC 2008)
elseif(MSVC_VERSION EQUAL 1600)
    set(COMPILER_MSVC 2010)
else()
    message(WARNING "Unsupported compiler")
    return()
endif()

# define the install directory for miscellaneous files
if(WINDOWS)
    set(INSTALL_MISC_DIR .)
endif()

macro (CMP_QT_LIBRARIES_INSTALL_RULES QTLIBLIST destination)
   # message(STATUS "CMP_COPY_QT4_RUNTIME_LIBRARIES")
    if (MSVC)
        if (DEFINED QT_QMAKE_EXECUTABLE)
            set(TYPE "d")
            FOREACH(qtlib ${QTLIBLIST})
                
                GET_FILENAME_COMPONENT(QT_DLL_PATH_tmp ${QT_QMAKE_EXECUTABLE} PATH)
                message(STATUS "Generating Install Rule for Qt Debug DLL Library ${QT_DLL_PATH_tmp}/${qtlib}d4.dll -> ${destination}/Debug")  
                INSTALL(FILES ${QT_DLL_PATH_tmp}/${qtlib}${type}d4.dll 
                    DESTINATION "${destination}/Debug")
                message(STATUS "Generating Install Rule for Qt Release DLL Library ${QT_DLL_PATH_tmp}/${qtlib}4.dll -> ${destination}/Release")
                INSTALL(FILES ${QT_DLL_PATH_tmp}/${qtlib}4.dll 
                    DESTINATION "${destination}/Release")
				INSTALL(FILES ${QT_DLL_PATH_tmp}/${qtlib}4.dll 
                    DESTINATION "${destination}/MinSizeRel")
				INSTALL(FILES ${QT_DLL_PATH_tmp}/${qtlib}4.dll 
                    DESTINATION "${destination}/RelWithDebInfo")
            ENDFOREACH(qtlib)
        endif(DEFINED QT_QMAKE_EXECUTABLE)
    endif()
endmacro()