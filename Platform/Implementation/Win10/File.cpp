#include <Platform/File.hpp>

#include <Platform/StringHandling.hpp>
#include <Platform/WindowsInterface.hpp>

void File::ShowOpenFileDialog() {
    std::string fileName;
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr)) {
        IFileOpenDialog *pFileOpen;

        // Create the FileOpenDialog object.
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

        if (SUCCEEDED(hr)) {
            // Show the Open dialog box.
            ShowCursor(TRUE);
            hr = pFileOpen->Show(NULL);

            // Get the file name from the dialog box.
            if (SUCCEEDED(hr)) {
                IShellItem *pItem;
                hr = pFileOpen->GetResult(&pItem);
                if (SUCCEEDED(hr)) {
                    PWSTR pszFilePath;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                    std::wstring returnedFileName(pszFilePath);
                    fileName = StringUtil::WideStringToString(returnedFileName);

                    // Display the file name to the user.
                    if (SUCCEEDED(hr)) {
                        MessageBoxA(NULL, fileName.c_str(), "File Path", MB_OK);
                        CoTaskMemFree(pszFilePath);
                    }
                    pItem->Release();
                }
            }
            pFileOpen->Release();
            ShowCursor(FALSE);
        }
        CoUninitialize();
    }
}


Result File::Init(const std::string& fileName) {
    Result initResult{};

    std::ifstream file(fileName);
    if (file.is_open() == false) {
        initResult.AppendError("File::Init() : Couldn't open file.");
        initResult.AppendError(fileName.c_str());
        return initResult;
    }

    std::string line;
    while (getline(file, line)) {
        lines_.push_back(line);
    }

    if (file.bad()) {
        initResult.AppendError("File::Init() : Couldn't read file.");
        return initResult;
    }
    file.close();
    fileName_ = fileName;
    return initResult;
}

const std::string& File::GetLine(const size_t& index) const {
    return lines_.at(index);
}

void File::PutLine(const size_t& index, const std::string& newLine) {
    if (index < lines_.size()) {
        lines_[index] = newLine;
    } else {
        lines_.push_back(newLine);
    }
}

Result File::WriteToDisk() {
    Result writeResult{};

    std::ofstream file(fileName_);
    if (file.is_open() == false) {
        writeResult.AppendError("File::WriteToDisk() : Couldn't open file.");
        writeResult.AppendError(fileName_.c_str());
        return writeResult;
    }

    std::vector<std::string>::const_iterator lineFinder = lines_.begin();
    std::vector<std::string>::const_iterator lineEnd = lines_.end();
    while (lineFinder != lineEnd) {
        file.write(lineFinder->c_str(), static_cast<std::streamsize>(lineFinder->size()));
        file.put('\n');

        // Loop incrementer.
        ++lineFinder;
    }

    if (file.bad()) {
        writeResult.AppendError("File::WriteToDisk() : Couldn't write file.");
        return writeResult;
    }
    file.close();
    return writeResult;
}