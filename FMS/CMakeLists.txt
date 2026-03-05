include(FetchContent)

# lz4 라이브러리
FetchContent_Declare(
  lz4
  GIT_REPOSITORY https://github.com/lz4/lz4.git
  GIT_TAG        v1.10.0
  SOURCE_SUBDIR  build/cmake
)
FetchContent_MakeAvailable(lz4)

# openssl 라이브러리 설치 필요
find_package(OpenSSL REQUIRED)

# 소스 파일 및 출력 경로 설정
set(TSOURCE_FILES
    FileStorage.h FileStorage.cpp
    SecureCodec.h SecureCodec.cpp
    stringUtil.h
)

add_library(FMS STATIC ${TSOURCE_FILES})

target_include_directories(FMS PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/FMS>
)

# 라이브러리 연결
target_link_libraries(FMS PRIVATE 
    lz4_static 
    OpenSSL::Crypto 
)

# Visual Studio 소스 그룹화
source_group("Encrypter" FILES SecureCodec.h SecureCodec.cpp)
source_group("FileManageSystem" FILES FileStorage.h FileStorage.cpp)
source_group("String" FILES stringUtil.h stringUtil.cpp)

# 인클루드 경로 설정
target_include_directories(FMS PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
