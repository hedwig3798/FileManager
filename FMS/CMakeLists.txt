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

add_library(FMS STATIC ${TSOURCE_FILES})
list(APPEND STATIC_LIBS FMS)

target_include_directories(
    FMS 

    PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/FMS>
)

# 라이브러리 연결
target_link_libraries(
    FMS 

    PRIVATE 
    lz4
    OpenSSL::Crypto 
)

# Visual Studio 소스 그룹화
source_group("Encrypter" FILES SecureCodec.h SecureCodec.cpp)
source_group("FileManageSystem" FILES FileStorage.h FileStorage.cpp)
source_group("String" FILES stringUtil.h stringUtil.cpp)

# 인클루드 경로 설정
target_include_directories(FMS PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

install(FILES "FileStorage.h" DESTINATION include/FMS)

# lib 병합
set(LIB_FILE_PATHS "")
foreach(lib IN LISTS STATIC_LIBS)
    list(APPEND LIB_FILE_PATHS "$<TARGET_FILE:${lib}>")
endforeach()

add_custom_target(merged_static_lib ALL DEPENDS ${STATIC_LIBS})

add_custom_command(
    TARGET 
        merged_static_lib 
    POST_BUILD
    COMMAND 
        link.exe /lib /OUT:"${BIN_OUTPUT_DIR}/$<CONFIG>/FMS.lib"
        ${LIB_FILE_PATHS}
)