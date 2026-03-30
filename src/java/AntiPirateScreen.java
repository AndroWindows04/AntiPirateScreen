/*
 * AntiPirateScreen - Java Entry Point
 * Version: 2.0.0
 * Author: TIBI624
 * Branch: tibi624
 * 
 * WARNING: This file is intended for AntiPirateScreen utility only.
 * Do not modify without proper authorization.
 */

package com.antipiratescreen;

public class AntiPirateScreen {
    public static void main(String[] args) {
        Protection protector = new Protection();

        if (protector.isDebuggerAttached()) {
            System.out.println("Debugger detected! Exiting...");
            System.exit(1);
        }

        String licenseKey = System.getenv("ANTIPIRATE_LICENSE");

        if (licenseKey != null && !licenseKey.isEmpty()) {
            if (!protector.verifyLicense(licenseKey)) {
                System.exit(1);
            }
        } else {
            System.out.println("No license key provided. Running in trial mode.");
        }

        System.out.println("AntiPirateScreen: Protection verified!");
        System.out.println("Author: " + Protection.getAuthor());
        System.out.println("Branch: " + Protection.getBranch());
        System.out.println("Hardware ID: " + protector.getHardwareID());
    }
}