// Win32_TextImage - Simple image OCR using Windows.Media.Ocr (C++/WinRT)
// Build as x64 Console application

#include <winrt/base.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Graphics.Imaging.h>
#include <winrt/Windows.Media.Ocr.h>
#include <winrt/Windows.Globalization.h>

#include <iostream>
#include <string>
#include <vector>

#pragma comment(lib, "WindowsApp.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "ole32.lib")

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace Windows::Graphics::Imaging;
using namespace Windows::Media::Ocr;
using namespace Windows::Globalization;

// Load image file into SoftwareBitmap
SoftwareBitmap LoadImage(const std::wstring& imagePath)
{
    StorageFile file = StorageFile::GetFileFromPathAsync(hstring{ imagePath }).get();
    IRandomAccessStream stream = file.OpenAsync(FileAccessMode::Read).get();
    BitmapDecoder decoder = BitmapDecoder::CreateAsync(stream).get();
    SoftwareBitmap bitmap = decoder.GetSoftwareBitmapAsync().get();
    return bitmap;
}

// Perform OCR and return full text + list of words
struct OcrOutput
{
    std::wstring fullText;
    std::vector<std::wstring> words;
};

OcrOutput PerformOcr(const SoftwareBitmap& bitmap)
{
    OcrOutput result;

    // Prefer user profile languages (best default)
    OcrEngine engine = OcrEngine::TryCreateFromUserProfileLanguages();

    // Alternative: force a specific language
    // Language lang{ L"en-US" };
    // OcrEngine engine = OcrEngine::TryCreateFromLanguage(lang);

    if (!engine)
    {
        std::wcerr << L"Error: Could not create OCR engine. Check language packs." << std::endl;
        return result;
    }

    OcrResult ocrResult = engine.RecognizeAsync(bitmap).get();

    result.fullText = ocrResult.Text().c_str();

    // Extract individual words from lines
    for (auto const& line : ocrResult.Lines())
    {
        for (auto const& word : line.Words())
        {
            result.words.push_back(word.Text().c_str());
        }
    }

    return result;
}

int wmain(int argc, wchar_t* argv[])
{
    // Initialize WinRT apartment
    init_apartment();

    if (argc < 2)
    {
        std::wcout << L"Usage: Win32_TextImage.exe <image_path>" << std::endl;
        std::wcout << L"Example: Win32_TextImage.exe C:\\temp\\sample.png" << std::endl;
        return 1;
    }

    std::wstring imagePath = argv[1];

    try
    {
        std::wcout << L"Loading image: " << imagePath << std::endl;
        SoftwareBitmap bitmap = LoadImage(imagePath);

        std::wcout << L"Recognizing text..." << std::endl;
        OcrOutput output = PerformOcr(bitmap);

        std::wcout << L"\n=== Full OCR Text ===" << std::endl;
        std::wcout << output.fullText << std::endl;

        std::wcout << L"\n=== Words Found (" << output.words.size() << L") ===" << std::endl;
        for (const auto& word : output.words)
        {
            std::wcout << word << std::endl;
        }
    }
    catch (hresult_error const& ex)
    {
        std::wcerr << L"WinRT Error: " << ex.message().c_str() << std::endl;
        return 1;
    }
    catch (std::exception const& ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
