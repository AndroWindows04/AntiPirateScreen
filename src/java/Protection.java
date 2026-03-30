/*
 * AntiPirateScreen - Java Protection Module
 * Version: 2.0.0
 * Author: TIBI624
 * Branch: tibi624
 * 
 * This file contains the Java implementation of the AntiPirateScreen
 * protection library.
 * 
 * WARNING: This file is intended for AntiPirateScreen utility only.
 * Do not modify without proper authorization.
 */

package com.antipiratescreen;

import java.security.MessageDigest;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.net.InetAddress;

public class Protection {
    public static final String VERSION = "2.0.0";
    public static final String AUTHOR = "TIBI624";
    public static final String BRANCH = "tibi624";

    private final String serverURL = "https://api.antipiratescreen.com/verify";
    private final String licenseFile = "license.dat";
    private final String configPath = ".aps/CONFIG.xtml";
    private final String hardwareID;

    public Protection() {
        this.hardwareID = getHardwareID();
    }

    private String getHardwareID() {
        try {
            return InetAddress.getLocalHost().getHostName() + System.getProperty("os.arch");
        } catch (Exception e) {
            return "unknown";
        }
    }

    private String generateHash(String input) throws Exception {
        MessageDigest digest = MessageDigest.getInstance("SHA-256");
        byte[] hash = digest.digest(input.getBytes("UTF-8"));
        StringBuilder hexString = new StringBuilder();
        for (byte b : hash) {
            String hex = Integer.toHexString(0xff & b);
            if (hex.length() == 1) hexString.append('0');
            hexString.append(hex);        }
        return hexString.toString();
    }

    public boolean verifyLicense(String licenseKey) {
        if (!validateFormat(licenseKey)) {
            showProtectionScreen();
            return false;
        }

        try {
            String licenseHash = generateHash(licenseKey + hardwareID);
            // TODO: Send to server for verification
            return true;
        } catch (Exception e) {
            return false;
        }
    }

    private boolean validateFormat(String licenseKey) {
        if (licenseKey.length() != 19) {
            return false;
        }
        if (licenseKey.charAt(4) != '-' || licenseKey.charAt(9) != '-' || licenseKey.charAt(14) != '-') {
            return false;
        }
        return true;
    }

    public boolean verifyIntegrity(String filePath) {
        try {
            String content = new String(Files.readAllBytes(Paths.get(filePath)));
            String fileHash = generateHash(content);
            return !fileHash.isEmpty();
        } catch (Exception e) {
            return false;
        }
    }

    public boolean isDebuggerAttached() {
        return java.lang.management.ManagementFactory.getRuntimeMXBean().getInputArguments()
            .toString().contains("-agentlib:jdwp");
    }

    public void showProtectionScreen() {
        System.out.println("==================================================");
        System.out.println("     AntiPirateScreen Protection");
        System.out.println("     Author: " + AUTHOR);
        System.out.println("     Branch: " + BRANCH);
        System.out.println("==================================================");        System.out.println("  This software requires a valid license.");
        System.out.println("  Please purchase a legitimate copy.");
        System.out.println("==================================================");
    }

    public boolean loadConfig(String configFile) {
        try {
            String content = new String(Files.readAllBytes(Paths.get(configFile)));
            // Parse XTML content
            return true;
        } catch (Exception e) {
            return false;
        }
    }

    public boolean loadAPSFile(String apsFile) {
        if (!apsFile.endsWith(".aps")) {
            return false;
        }
        try {
            String content = new String(Files.readAllBytes(Paths.get(apsFile)));
            // Parse APS content
            return true;
        } catch (Exception e) {
            return false;
        }
    }

    public String getHardwareID() {
        return hardwareID;
    }

    public static String getVersion() {
        return VERSION;
    }

    public static String getAuthor() {
        return AUTHOR;
    }

    public static String getBranch() {
        return BRANCH;
    }
}