# FileManager (AES-CTR Resource Encryptor)

이 프로젝트는 아래의 라이브러리를 사용하여 기능을 제공합니다.
1. lz4 를 사용하여 압축 기능을 제공합니다.
2. OpenSSL 을 사용하여 암호화/복호화하는 기능을 제공합니다.

## 빌드 방법

### Windows (Visual Studio 2022)
1. OpenSSL Full 버전 설치  
   - https://slproweb.com/products/Win32OpenSSL.html (Win64 OpenSSL v3.x Full)  
   - 기본 경로: `C:\Program Files\OpenSSL-Win64\`
2. visual studio 를 통해 .sin 파일 빌드
  
### Third-party libraries
- [OpenSSL](https://www.openssl.org/) (Apache License 2.0)
- [LZ4](https://github.com/lz4/lz4) (BSD 2-Clause License)
