# FileManager (LZ4 Compress, AES-CTR Encrypt)

**FMS**는 LZ4 알고리즘을 통한 고속 압축과 OpenSSL(AES-CTR)을 이용한 강력한 암호화를 결합한 C++ 데이터 관리 라이브러리입니다.   
파일의 내용을 노출하지 않고 파일을 배포하기 위한 목적으로 설계되었습니다.

## 🚀 주요 특징
- **고속 압축**: lz4 라이브러리를 내장하여 실시간 데이터 처리에 적합한 빠른 압축 및 해제 기능을 제공합니다.
- **강력한 보안**: OpenSSL의 AES-CTR 모드를 사용하여 데이터 기밀성을 보장하며, 안전한 코덱 인터페이스를 제공합니다.

## 🛠 사전 요구 사항
빌드를 위해 다음 도구 및 라이브러리가 설치되어 있어야 합니다:

- C++ 컴파일러: C++17 이상 지원 (Visual Studio 2022 권장)
- CMake: 버전 3.16 이상
- OpenSSL v3.x: 시스템에 설치되어 있어야 합니다. (Win64 OpenSSL v3.x Full 버전 권장)
	- Win64 OpenSSL 다운로드
	- 기본 설치 경로: C:\Program Files\OpenSSL-Win64\

## 📦 프로젝트 구조
```
FMS/
├── FMS/               # FMS 라이브러리 핵심 소스 코드 (.h, .cpp)
├── External/          # 외부 의존성 라이브러리 (lz4 등 FetchContent 관리)
├── dist/              # 배포용 SDK (빌드 및 설치 후 생성됨)
├── LICENSE            # MIT License
├── THIRD-PARTY-NOTICES.md  # 오픈소스 고지 문구 (lz4, OpenSSL)
└── CMakeLists.txt     # 프로젝트 루트 CMake 설정 파일
```
## 🔨 빌드 및 설치 방법

### 1. 저장소 클론
```bash
git clone https://github.com/your-username/FMS.git
cd FMS
```

### 2. 프로젝트 구성 및 빌드 (CLI)
```bash
# 빌드용 폴더 생성
mkdir Build
cd Build

# 프로젝트 구성 (OpenSSL이 설치된 상태여야 합니다)
cmake ..

# 빌드 실행 (Debug 또는 Release)
cmake --build . --config Release
```
  
### 📄 라이선스
- FMS: MIT License
- Third-party: 상세 내용은 THIRD-PARTY-NOTICES.md를 참조하세요.
	- OpenSSL: Apache License 2.0
	- LZ4: BSD 2-Clause License
