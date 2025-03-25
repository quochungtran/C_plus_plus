#include <iostream>
#include <fstream>
#include <filesystem>
#include <memory>
#include <archive.h>
#include <archive_entry.h>
#include <sys/stat.h>
#include <ctime>

class UP_Time {
public:
    static UP_Time Now() {
        return UP_Time();
    }

    std::string asString(const std::string& format, int timezone) const {
        char buffer[80];
        time_t now = time(0);
        struct tm tstruct;
        tstruct = *gmtime(&now);
        strftime(buffer, sizeof(buffer), format.c_str(), &tstruct);
        return buffer;
    }
};

class DistriboxHelper {
public:
    DistriboxHelper(const std::filesystem::path& inputDir) : _inputDir(inputDir) {}

    std::filesystem::path writeTarball(const std::string& iPackageName) {
        auto aOutputFilePath = buildNewFile(iPackageName);
        auto ar_tar = createArchive(aOutputFilePath);
        writeFilesToArchive(ar_tar);
        return aOutputFilePath;
    }

private:
    std::filesystem::path buildNewFile(const std::string& iPackageName) {
        UP_Time aNowTime = UP_Time::Now();
        std::string aFileName = iPackageName + "_" + aNowTime.asString("%Y%m%d_%H%M%S", 0);
        return (_inputDir / aFileName).replace_extension("tar");
    }

    using archive_wrapper = std::unique_ptr<archive, decltype([](archive* ar) { archive_write_free(ar); })>;

    struct archive_open_wrapper {
        using raii_wrapper = std::unique_ptr<archive, decltype([](archive* ar) { archive_write_close(ar); })>;
        archive_open_wrapper(archive* ar, const std::filesystem::path& filePath) : _ar(ar) {
            archive_write_set_format_pax_restricted(ar);
            archive_write_open_filename(ar, filePath.c_str());
        }

    private:
        raii_wrapper _ar;  // this ensures the class is not copyable, and has correct semantics on move
    };

    archive_wrapper createArchive(const std::filesystem::path& aOutputFilePath) {
        archive_wrapper ar_tar = archive_wrapper(archive_write_new());
        archive_open_wrapper ar_open(ar_tar.get(), aOutputFilePath);
        return ar_tar;
    }

    void writeFilesToArchive(archive_wrapper& ar_tar) {
        for (const auto& dir_entry : std::filesystem::recursive_directory_iterator(_inputDir)) {
            const auto& path = dir_entry.path();
            if (std::filesystem::is_regular_file(path) && path.extension() == ".fb") {
                using ar_entry_wrapper = std::unique_ptr<archive_entry, decltype([](archive_entry* entry) { archive_entry_free(entry); })>;
                ar_entry_wrapper ar_entry = ar_entry_wrapper(archive_entry_new());
                archive_entry_set_pathname(ar_entry.get(), path.filename().c_str());
                struct stat st;
                stat(path.c_str(), &st);
                archive_entry_set_size(ar_entry.get(), st.st_size);
                archive_entry_set_filetype(ar_entry.get(), AE_IFREG);
                archive_entry_set_perm(ar_entry.get(), 0644);
                archive_write_header(ar_tar.get(), ar_entry.get());

                std::ifstream aFileToRead(path.c_str(), std::ios::binary);
                if (aFileToRead.is_open()) {
                    char buff[8192];
                    while (aFileToRead.read(buff, sizeof(buff))) {
                        archive_write_data(ar_tar.get(), buff, sizeof(buff));
                    }
                    // Write any remaining bytes
                    archive_write_data(ar_tar.get(), buff, aFileToRead.gcount());
                } else {
                    std::cerr << "[Issue] Unable to open " << path.c_str() << " file for reading!" << std::endl;
                }
            }
        }
    }

    std::filesystem::path _inputDir;
};

int main() {
    DistriboxHelper helper("/path/to/input/dir");
    std::filesystem::path tarballPath = helper.writeTarball("package_name");
    std::cout << "Tarball created at: " << tarballPath << std::endl;
    return 0;
}
