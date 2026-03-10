include(FetchContent)
include(GNUInstallDirs)

# lz4 라이브러리
FetchContent_Declare(
  lz4_static
  GIT_REPOSITORY https://github.com/lz4/lz4.git
  GIT_TAG        v1.10.0
  SOURCE_SUBDIR  build/cmake
)
FetchContent_MakeAvailable(lz4_static)

# openssl 라이브러리 설치 필요
find_package(OpenSSL REQUIRED)

# 소스 파일 및 출력 경로 설정
set(
    TSOURCE_FILES
    FileStorage.h FileStorage.cpp
    SecureCodec.h SecureCodec.cpp
    stringUtil.h stringUtil.cpp
)

add_library(FMS STATIC ${TSOURCE_FILES})

target_include_directories(
    FMS 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/FMS>
)

# 라이브러리 연결
target_link_libraries(
    FMS 
    PRIVATE 
        lz4_static
        OpenSSL::Crypto 
)

# Visual Studio 소스 그룹화
source_group("Encrypter" FILES SecureCodec.h SecureCodec.cpp)
source_group("FileManageSystem" FILES FileStorage.h FileStorage.cpp)
source_group("String" FILES stringUtil.h stringUtil.cpp)

install(FILES "FileStorage.h" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/FMS)

install(
    TARGETS 
        FMS 
        lz4_static
    EXPORT 
        FMSTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    EXPORT 
        FMSTargets
    FILE 
        FMSTargets.cmake
    NAMESPACE 
        FMS::
    DESTINATION 
        ${CMAKE_INSTALL_LIBDIR}/cmake/FMS
)

# FMS 설치 시 속성 정의
include(CMakePackageConfigHelpers)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/FMSConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/FMSConfig.cmake"
    INSTALL_DESTINATION 
        ${CMAKE_INSTALL_LIBDIR}/cmake/FMS
)

# 버전 파일 생성 (선택 사항이지만 패키징의 표준입니다)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/FMSConfigVersion.cmake"
    VERSION 
        1.0.0
    COMPATIBILITY
        SameMajorVersion
)

# 생성된 Config 파일들 설치
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/FMSConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/FMSConfigVersion.cmake"
    DESTINATION 
        ${CMAKE_INSTALL_LIBDIR}/cmake/FMS
)