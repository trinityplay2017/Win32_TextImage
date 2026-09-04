# Win32_TextImage

Simple C++ console project that loads image files (JPG, PNG, BMP, etc.) and performs OCR to extract and scan for text words using the built-in Windows.Media.Ocr API (Windows 10+).

## Features
- Load image from file path (command-line argument)
- Perform OCR using system OCR engine
- Output recognized full text and individual words
- Uses C++/WinRT for modern Windows APIs

## Requirements
- Windows 10 or later
- Visual Studio 2019/2022 with "Desktop development with C++" workload
- Windows 10/11 SDK
- C++/WinRT (built-in or via NuGet `Microsoft.Windows.CppWinRT`)

## Build Instructions

### Visual Studio (recommended)
1. Open Visual Studio → Create a new project → **Console App** (C++)
2. Project Properties → Configuration Properties → General → **C++ Language Standard** = ISO C++17 or later
3. Project Properties → C/C++ → General → **Additional Include Directories**: add path if needed
4. Enable Windows Runtime:  
   - C/C++ → General → **Consume Windows Runtime Extension** = Yes (`/ZW`)  
   **OR** (preferred modern way) install NuGet package `Microsoft.Windows.CppWinRT` and use pure C++/WinRT headers.
5. Replace the default source with the content from `src/main.cpp`
6. Build for **x64** (Debug or Release)

### Quick note on linking
You may need to link `WindowsApp.lib` in some configurations (Linker → Input → Additional Dependencies).

## Usage
```bash
Win32_TextImage.exe "C:\path\to\your\image.png"
```

Example:
```
Loading image: sample.png
Recognizing text...

=== Full OCR Text ===
Hello World
This is a sample text from an image.

=== Words Found ===
Hello
World
This
is
a
sample
text
from
an
image.
```

## Language Support
The code uses `OcrEngine::TryCreateFromUserProfileLanguages()` by default (best for most users).  
You can change it to a specific language, e.g.:
```cpp
Windows::Globalization::Language lang{ L"en-US" };
auto engine = OcrEngine::TryCreateFromLanguage(lang);
```

Supported languages depend on what is installed on the system (Settings → Time & Language → Language → add language packs that support OCR).

## Notes
- Works with common image formats supported by `BitmapDecoder` (JPEG, PNG, BMP, TIFF, GIF…).
- OCR accuracy depends on image quality, contrast, font size, and installed language packs.
- This is a minimal example focused on loading an image and extracting text/words.

## Project Structure
```
Win32_TextImage/
├── README.md
├── src/
│   └── main.cpp
└── (optional) CMakeLists.txt
```

## License
MIT
