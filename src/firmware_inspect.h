#pragma once

#include <WString.h>
#include <cstdint>

enum class LauncherFirmwareKind : uint8_t {
    Invalid,
    StandaloneApp,
    FullFlash,
    F1EmbeddedApp,
};

struct LauncherFirmwareValidation {
    LauncherFirmwareKind kind = LauncherFirmwareKind::Invalid;
    bool f1Eligible = false;
    bool esp32S3 = false;
    uint32_t fileBytes = 0;
    uint32_t sourceOffset = 0;
    uint32_t imageBytes = 0;
};

// Reuses the D2-A bounded parser for install-time validation.
bool launcherValidateFirmwareFile(const String &path, LauncherFirmwareValidation &validation);

// Narrow F1-v1 validation for a single-factory-app FullFlash wrapper. This
// deliberately remains separate from the generic StandaloneApp validator.
bool launcherValidateF1FirmwareFile(const String &path, LauncherFirmwareValidation &validation);

// Opens a compact, read-only report for the selected firmware file. The
// implementation uses only launcherStorageFileSize()/launcherStorageReadAt().
void launcherInspectFirmwareFile(const String &path);
