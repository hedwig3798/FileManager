include(FetchContent)

set(STATIC_LIBS "")

# lz4 라이브러리
FetchContent_Declare(
  lz4
  GIT_REPOSITORY https://github.com/lz4/lz4.git
  GIT_TAG        v1.10.0
  SOURCE_SUBDIR  build/cmake
)
FetchContent_MakeAvailable(lz4)
list(APPEND STATIC_LIBS lz4_static)

# openssl 라이브러리 설치 필요
find_package(OpenSSL REQUIRED)

# 소스 파일 및 출력 경로 설정
set(
    TSOURCE_FILES
    FileStorage.h FileStorage.cpp
    SecureCodec.h SecureCodec.cpp
    stringUtil.h
)

add_library(FMSInternal STATIC ${TSOURCE_FILES})
list(APPEND STATIC_LIBS FMSInternal)

target_include_directories(
    FMSInternal 

    PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/FMSInternal>
)

# 라이브러리 연결
target_link_libraries(
    FMSInternal 

    PRIVATE 
    lz4
    OpenSSL::Crypto 
)

# Visual Studio 소스 그룹화
source_group("Encrypter" FILES SecureCodec.h SecureCodec.cpp)
source_group("FileManageSystem" FILES FileStorage.h FileStorage.cpp)
source_group("String" FILES stringUtil.h stringUtil.cpp)

# 인클루드 경로 설정
target_include_directories(FMSInternal PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# lib 병합
set(LIB_FILE_PATHS "")
foreach(lib IN LISTS STATIC_LIBS)
    list(APPEND LIB_FILE_PATHS "$<TARGET_FILE:${lib}>")
endforeach()

add_custom_target(merged_static_lib ALL DEPENDS ${STATIC_LIBS})
set(MERGED_DIR "${CMAKE_BINARY_DIR}/merged/$<CONFIG>")
set(FINAL_FMS_LIB "${MERGED_DIR}/FMS"<$<CONFIG:Debug>:${CMAKE_DEBUG_POSTFIX}".lib")

add_custom_command(
    TARGET 
        merged_static_lib 
    POST_BUILD
    COMMAND 
        ${CMAKE_COMMAND} -E make_directory "${MERGED_DIR}"
    COMMAND 
        link.exe /lib /OUT:"${FINAL_FMS_LIB}"
        ${LIB_FILE_PATHS}
)

install(
    FILES 
        "${FINAL_FMS_LIB}" 
    DESTINATION 
        "${CMAKE_INSTALL_LIBDIR}"
    RENAME
        "${FINAL_LIB_NAME}"

)
install(FILES "FileStorage.h" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/FMS)