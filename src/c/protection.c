/*
 * AntiPirateScreen - C Protection Implementation
 * Version: 2.0.0
 * Author: TIBI624
 * Branch: tibi624
 * 
 * This file contains the core implementation of the AntiPirateScreen
 * protection library. It handles license verification, file integrity
 * checks, and anti-debugging measures.
 * 
 * WARNING: This file is intended for AntiPirateScreen utility only.
 * Do not modify without proper authorization.
 */

#include "protection.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <sys/ptrace.h>
#endif

#define APS_VERSION "2.0.0"
#define APS_AUTHOR "TIBI624"
#define APS_BRANCH "tibi624"
#define APS_BUFFER_SIZE 256

/* Internal hash function (simplified - use SHA-256 in production) */
static unsigned long aps_hash(const char* input) {
    unsigned long hash = 5381;
    int c;
    while ((c = *input++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

/* Generate hardware ID */
static const char* aps_generate_hardware_id(void) {
    static char hwid[APS_BUFFER_SIZE];
    
#ifdef _WIN32
    DWORD serialNumber = 0;
    GetVolumeInformationA("C:\\", NULL, 0, &serialNumber, NULL, NULL, NULL, 0);
    sprintf(hwid, "%08X", serialNumber);#else
    sprintf(hwid, "%ld", gethostid());
#endif
    
    return hwid;
}

APS_Context* aps_init(void) {
    APS_Context* ctx = (APS_Context*)malloc(sizeof(APS_Context));
    if (ctx == NULL) {
        return NULL;
    }
    
    ctx->license_key = NULL;
    ctx->hardware_id = aps_generate_hardware_id();
    ctx->config_path = ".aps/CONFIG.xtml";
    ctx->is_verified = false;
    ctx->error_code = 0;
    
    return ctx;
}

bool aps_verify_license(APS_Context* ctx, const char* license_key) {
    if (ctx == NULL || license_key == NULL) {
        return false;
    }
    
    /* Validate license format: XXXX-XXXX-XXXX-XXXX */
    if (strlen(license_key) != 19) {
        ctx->error_code = 1;
        return false;
    }
    
    if (license_key[4] != '-' || license_key[9] != '-' || license_key[14] != '-') {
        ctx->error_code = 2;
        return false;
    }
    
    /* Generate license hash */
    unsigned long license_hash = aps_hash(license_key);
    (void)license_hash; /* Suppress unused warning */
    
    /* TODO: Send to server for verification */
    
    ctx->is_verified = true;
    return true;
}

bool aps_verify_integrity(APS_Context* ctx, const char* file_path) {
    if (ctx == NULL || file_path == NULL) {        return false;
    }
    
    FILE* file = fopen(file_path, "rb");
    if (file == NULL) {
        ctx->error_code = 3;
        return false;
    }
    
    /* Read file and compute hash */
    char buffer[APS_BUFFER_SIZE];
    unsigned long file_hash = 0;
    
    while (fgets(buffer, APS_BUFFER_SIZE, file) != NULL) {
        file_hash += aps_hash(buffer);
    }
    
    fclose(file);
    
    return (file_hash != 0);
}

bool aps_is_debugger_attached(APS_Context* ctx) {
    (void)ctx; /* Suppress unused warning */
    
#ifdef _WIN32
    return IsDebuggerPresent();
#else
    return ptrace(PTRACE_TRACEME, 0, 1, 0) < 0;
#endif
}

void aps_show_protection_screen(APS_Context* ctx) {
    (void)ctx; /* Suppress unused warning */
    
    printf("========================================\n");
    printf("     AntiPirateScreen Protection        \n");
    printf("     Author: TIBI624                    \n");
    printf("     Branch: tibi624                    \n");
    printf("========================================\n");
    printf("  This software requires a valid       \n");
    printf("  license to run.                       \n");
    printf("  Please purchase a legitimate copy.    \n");
    printf("========================================\n");
    
#ifdef _WIN32
    MessageBoxA(NULL,
        "AntiPirateScreen Protection\n\n"
        "Author: TIBI624\n"
        "This software requires a valid license.\n"        "Please purchase a legitimate copy.",
        "Protection Alert",
        MB_OK | MB_ICONWARNING);
#endif
}

const char* aps_get_hardware_id(APS_Context* ctx) {
    if (ctx == NULL) {
        return NULL;
    }
    return ctx->hardware_id;
}

bool aps_load_config(APS_Context* ctx, const char* config_file) {
    if (ctx == NULL || config_file == NULL) {
        return false;
    }
    
    FILE* file = fopen(config_file, "r");
    if (file == NULL) {
        ctx->error_code = 4;
        return false;
    }
    
    /* Parse CONFIG.xtml file */
    char buffer[APS_BUFFER_SIZE];
    while (fgets(buffer, APS_BUFFER_SIZE, file) != NULL) {
        /* Process configuration entries */
    }
    
    fclose(file);
    return true;
}

bool aps_validate_aps_file(const char* file_path) {
    if (file_path == NULL) {
        return false;
    }
    
    /* Check file extension */
    const char* ext = strrchr(file_path, '.');
    if (ext == NULL || strcmp(ext, ".aps") != 0) {
        return false;
    }
    
    /* Verify file exists and is readable */
    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        return false;
    }    
    fclose(file);
    return true;
}

void aps_free(APS_Context* ctx) {
    if (ctx != NULL) {
        free(ctx);
    }
}

const char* aps_get_version(void) {
    return APS_VERSION;
}

const char* aps_get_author(void) {
    return APS_AUTHOR;
}