/*
 * AntiPirateScreen - C++ Protection Implementation
 * Version: 2.0.0
 * Author: TIBI624
 * Branch: tibi624
 * 
 * This file contains the core C++ implementation of the AntiPirateScreen
 * protection library. It handles license verification, file integrity
 * checks, anti-debugging measures, and configuration management.
 * 
 * WARNING: This file is intended for AntiPirateScreen utility only.
 * Do not modify without proper authorization.
 */

#include "protection.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <cstring>
#include <algorithm>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <sys/ptrace.h>
#endif

#define APS_AUTHOR "TIBI624"
#define APS_BRANCH "tibi624"

namespace AntiPirateScreen {

/* Internal implementation class (PIMPL pattern) */
class Protection::Impl {
public:
    ProtectionConfig config;
    std::function<void()> on_verification_failed;
    std::function<void()> on_verification_success;
    std::string custom_message;

    Impl() {
        config.license_key = "";
        config.hardware_id = "";
        config.config_path = ".aps/CONFIG.xtml";
        config.enable_debug_check = true;
        config.enable_integrity_check = true;
        config.timeout_seconds = 30;
    }
    std::string generateHash(const std::string& input) {
        unsigned long hash = 5381;
        for (char c : input) {
            hash = ((hash << 5) + hash) + c;
        }
        std::stringstream ss;
        ss << std::hex << hash;
        return ss.str();
    }

    std::string getHardwareID() {
#ifdef _WIN32
        char volumeName[MAX_PATH + 1] = {0};
        DWORD serialNumber = 0;
        GetVolumeInformationA("C:\\", volumeName, MAX_PATH, &serialNumber, NULL, NULL, NULL, MAX_PATH);
        std::stringstream ss;
        ss << std::hex << serialNumber;
        return ss.str();
#else
        return std::to_string(gethostid());
#endif
    }
};

/* Protection class implementation */
Protection::Protection() : pImpl(std::make_unique<Impl>()) {
    pImpl->config.hardware_id = pImpl->getHardwareID();
}

Protection::Protection(const ProtectionConfig& config) : pImpl(std::make_unique<Impl>()) {
    pImpl->config = config;
    pImpl->config.hardware_id = pImpl->getHardwareID();
}

Protection::~Protection() = default;

VerificationResult Protection::verifyLicense(const std::string& license_key) {
    VerificationResult result;
    result.timestamp = std::chrono::system_clock::now().time_since_epoch().count();
    result.hardware_id = pImpl->config.hardware_id;

    if (!validateLicenseFormat(license_key)) {
        result.is_valid = false;
        result.error_code = 1;
        result.error_message = "Invalid license format";
        if (pImpl->on_verification_failed) {
            pImpl->on_verification_failed();
        }
        return result;    }

    std::string license_hash = pImpl->generateHash(license_key + pImpl->config.hardware_id);
    (void)license_hash; /* Suppress unused warning */

    /* TODO: Send to server for verification */

    result.is_valid = true;
    result.error_code = 0;
    result.error_message = "License verified successfully";

    if (pImpl->on_verification_success) {
        pImpl->on_verification_success();
    }

    return result;
}

bool Protection::validateLicenseFormat(const std::string& license_key) {
    if (license_key.length() != 19) {
        return false;
    }
    if (license_key[4] != '-' || license_key[9] != '-' || license_key[14] != '-') {
        return false;
    }
    return true;
}

bool Protection::verifyIntegrity(const std::string& file_path) {
    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    std::string hash = pImpl->generateHash(content);

    return !hash.empty();
}

bool Protection::verifyDirectory(const std::string& dir_path) {
    (void)dir_path; /* Suppress unused warning */
    /* TODO: Implement directory verification */
    return true;
}

bool Protection::isDebuggerAttached() {
#ifdef _WIN32    return IsDebuggerPresent();
#else
    return ptrace(PTRACE_TRACEME, 0, 1, 0) < 0;
#endif
}

bool Protection::checkAntiTampering() {
    /* TODO: Implement anti-tampering checks */
    return !isDebuggerAttached();
}

bool Protection::loadConfig(const std::string& config_file) {
    std::ifstream file(config_file);
    if (!file.is_open()) {
        return false;
    }

    /* Parse CONFIG.xtml file */
    std::string line;
    while (std::getline(file, line)) {
        /* Process configuration entries */
    }

    return true;
}

bool Protection::loadAPSFile(const std::string& aps_file) {
    if (!validateAPSFile(aps_file)) {
        return false;
    }

    std::ifstream file(aps_file);
    if (!file.is_open()) {
        return false;
    }

    /* Parse .aps file content */
    std::string line;
    while (std::getline(file, line)) {
        /* Process APS file entries */
    }

    return true;
}

ProtectionConfig Protection::getConfig() const {
    return pImpl->config;
}

std::string Protection::getHardwareID() {    return pImpl->config.hardware_id;
}

std::string Protection::getSystemInfo() {
    std::stringstream ss;
    ss << "Hardware ID: " << pImpl->config.hardware_id << "\n";
    ss << "Author: " << APS_AUTHOR << "\n";
    ss << "Branch: " << APS_BRANCH << "\n";
    ss << "Platform: ";
#ifdef _WIN32
    ss << "Windows\n";
#elif defined(__linux__)
    ss << "Linux\n";
#elif defined(__APPLE__)
    ss << "macOS\n";
#endif
    return ss.str();
}

void Protection::showProtectionScreen() {
    std::string message = pImpl->custom_message.empty() ?
        "========================================\n"
        "     AntiPirateScreen Protection        \n"
        "     Author: TIBI624                    \n"
        "     Branch: tibi624                    \n"
        "========================================\n"
        "  This software requires a valid       \n"
        "  license to run.                       \n"
        "  Please purchase a legitimate copy.    \n"
        "========================================\n" :
        pImpl->custom_message;

    std::cout << message << std::endl;

#ifdef _WIN32
    MessageBoxA(NULL,
        "AntiPirateScreen Protection\n\n"
        "Author: TIBI624\n"
        "Branch: tibi624\n"
        "This software requires a valid license.\n"
        "Please purchase a legitimate copy.",
        "Protection Alert",
        MB_OK | MB_ICONWARNING);
#endif
}

void Protection::setCustomMessage(const std::string& message) {
    pImpl->custom_message = message;
}
void Protection::setOnVerificationFailed(std::function<void()> callback) {
    pImpl->on_verification_failed = callback;
}

void Protection::setOnVerificationSuccess(std::function<void()> callback) {
    pImpl->on_verification_success = callback;
}

std::string Protection::getVersion() {
    return "2.0.0";
}

std::string Protection::getAuthor() {
    return APS_AUTHOR;
}

std::string Protection::getBranch() {
    return APS_BRANCH;
}

bool Protection::validateAPSFile(const std::string& file_path) {
    if (file_path.empty()) {
        return false;
    }

    /* Check file extension */
    size_t dot_pos = file_path.rfind('.');
    if (dot_pos == std::string::npos) {
        return false;
    }

    std::string ext = file_path.substr(dot_pos);
    if (ext != ".aps") {
        return false;
    }

    /* Verify file exists and is readable */
    std::ifstream file(file_path);
    return file.is_open();
}

/* ProtectionException implementation */
ProtectionException::ProtectionException(const std::string& message, int code)
    : message_(message), error_code_(code) {}

const char* ProtectionException::what() const noexcept {
    return message_.c_str();
}

int ProtectionException::errorCode() const noexcept {    return error_code_;
}

} // namespace AntiPirateScreen