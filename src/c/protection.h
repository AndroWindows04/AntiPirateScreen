/*
 * AntiPirateScreen - C Protection Header
 * Version: 2.0.0
 * Author: TIBI624
 * Branch: tibi624
 * 
 * This header file contains the public API for the AntiPirateScreen
 * protection library. It is designed to be integrated into your
 * application for license verification and anti-piracy protection.
 * 
 * WARNING: This file is intended for AntiPirateScreen utility only.
 * Do not modify without proper authorization.
 */

#ifndef ANTIPIRATE_SCREEN_PROTECTION_H
#define ANTIPIRATE_SCREEN_PROTECTION_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Protection context structure */
typedef struct {
    const char* license_key;
    const char* hardware_id;
    const char* config_path;
    bool is_verified;
    int error_code;
} APS_Context;

/* Initialize protection context */
APS_Context* aps_init(void);

/* Verify license key */
bool aps_verify_license(APS_Context* ctx, const char* license_key);

/* Verify file integrity */
bool aps_verify_integrity(APS_Context* ctx, const char* file_path);

/* Check for debugger attachment */
bool aps_is_debugger_attached(APS_Context* ctx);

/* Show protection screen */
void aps_show_protection_screen(APS_Context* ctx);

/* Get hardware ID */
const char* aps_get_hardware_id(APS_Context* ctx);

/* Load configuration from .aps files */
bool aps_load_config(APS_Context* ctx, const char* config_file);

/* Validate .aps file format */
bool aps_validate_aps_file(const char* file_path);

/* Free protection context */
void aps_free(APS_Context* ctx);

/* Get library version */
const char* aps_get_version(void);

/* Get author information */
const char* aps_get_author(void);

#ifdef __cplusplus
}
#endif

#endif /* ANTIPIRATE_SCREEN_PROTECTION_H */