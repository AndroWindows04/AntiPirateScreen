/*
 * AntiPirateScreen - C++ Protection Header
 * Version: 2.0.0
 * Author: TIBI624
 * Branch: tibi624
 * 
 * This header file contains the C++ API for the AntiPirateScreen
 * protection library. It provides object-oriented interface for
 * license verification and anti-piracy protection.
 * 
 * WARNING: This file is intended for AntiPirateScreen utility only.
 * Do not modify without proper authorization.
 */

#ifndef ANTIPIRATE_SCREEN_PROTECTION_H
#define ANTIPIRATE_SCREEN_PROTECTION_H

#include <string>
#include <vector>
#include <memory>
#include <functional>

namespace AntiPirateScreen {

/* Protection configuration structure */
struct ProtectionConfig {
    std::string license_key;
    std::string hardware_id;
    std::string config_path;
    bool enable_debug_check;
    bool enable_integrity_check;
    int timeout_seconds;
};

/* License verification result */
struct VerificationResult {
    bool is_valid;
    int error_code;
    std::string error_message;
    std::string hardware_id;
    long long timestamp;
};

/* Main protection class */
class Protection {
public:
    Protection();
    explicit Protection(const ProtectionConfig& config);
    ~Protection();
    /* License verification */
    VerificationResult verifyLicense(const std::string& license_key);
    bool validateLicenseFormat(const std::string& license_key);

    /* File integrity */
    bool verifyIntegrity(const std::string& file_path);
    bool verifyDirectory(const std::string& dir_path);

    /* Anti-debugging */
    bool isDebuggerAttached();
    bool checkAntiTampering();

    /* Configuration */
    bool loadConfig(const std::string& config_file);
    bool loadAPSFile(const std::string& aps_file);
    ProtectionConfig getConfig() const;

    /* Hardware identification */
    std::string getHardwareID();
    std::string getSystemInfo();

    /* Protection screen */
    void showProtectionScreen();
    void setCustomMessage(const std::string& message);

    /* Callbacks */
    void setOnVerificationFailed(std::function<void()> callback);
    void setOnVerificationSuccess(std::function<void()> callback);

    /* Static utilities */
    static std::string getVersion();
    static std::string getAuthor();
    static std::string getBranch();
    static bool validateAPSFile(const std::string& file_path);

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

/* Exception class for protection errors */
class ProtectionException : public std::exception {
public:
    explicit ProtectionException(const std::string& message, int code = 0);
    const char* what() const noexcept override;
    int errorCode() const noexcept;

private:
    std::string message_;
    int error_code_;};

} // namespace AntiPirateScreen

#endif /* ANTIPIRATE_SCREEN_PROTECTION_H */