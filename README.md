# Win32_TextImage

Simple C++ console project that loads image files (JPG, PNG, BMP, etc.) and performs OCR to extract and scan for text words using the built-in Windows.Media.Ocr API (Windows 10+).

## Features
- Load image from file path (command-line argument)
- Perform OCR using system OCR engine
- Output recognized full text and individual words
- Uses C++/WinRT for modern Windows APIs

## Requirements
- Windows 10 or later
- Visual Studio 2019/2022 with **"Desktop development with C++"** workload
- Windows 10/11 SDK
- **Must build as x64** (x86 has more linking issues)

## Important Build Notes (fixes the linker errors you saw)

Your previous command used `/SUBSYSTEM:WINDOWS` → that expects `WinMain`, but this project uses `wmain` (console entry point).

**Correct way:**

### Option 1 – Visual Studio (easiest)
1. Create new project → **Console App** (C++)
2. Set platform to **x64**
3. Project Properties → C/C++ → Language → C++ Language Standard = **ISO C++17**
4. Project Properties → Linker → System → **SubSystem = Console** (`/SUBSYSTEM:CONSOLE`)
5. Replace source with `src/main.cpp`
6. Build

The source already contains:
```cpp
#pragma comment(lib, "WindowsApp.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "ole32.lib")
```

### Option 2 – Command line (cl.exe)
```bat
cl /EHsc /std:c++17 /DUNICODE /D_UNICODE ^
   src\main.cpp ^
   /link /SUBSYSTEM:CONSOLE /MACHINE:X64 ^
   WindowsApp.lib oleaut32.lib ole32.lib user32.lib
```

Do **NOT** use `/SUBSYSTEM:WINDOWS`.

### If you still get WINRT_IMPL_* unresolved symbols
1. Make sure you are using the **x64** toolset.
2. Install NuGet package **Microsoft.Windows.CppWinRT** (recommended modern way).
3. Or enable `/ZW` (Consume Windows Runtime Extension) in project properties (older method).

## Usage
```bash
Win32_TextImage.exe "C:\path\to\your\image.png"
```

## Language Support
Default uses the languages installed on your Windows profile.
You can force a language in code:
```cpp
Language lang{ L"en-US" };   // or L"zh-CN", L"ja", etc.
OcrEngine engine = OcrEngine::TryCreateFromLanguage(lang);
```

## Project Structure
```
Win32_TextImage/
├── README.md
├── src/
│   └── main.cpp
└── CMakeLists.txt
```

## License
MIT
