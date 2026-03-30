/*
 * AntiPirateScreen - C# Protection Module
 * Version: 2.0.0
 * Author: TIBI624
 * Branch: tibi624
 * 
 * This file contains the C# implementation of the AntiPirateScreen
 * protection library.
 * 
 * WARNING: This file is intended for AntiPirateScreen utility only.
 * Do not modify without proper authorization.
 */

using System;
using System.IO;
using System.Security.Cryptography;
using System.Text;

namespace AntiPirateScreen
{
    public class Protection
    {
        public const string Version = "2.0.0";
        public const string Author = "TIBI624";
        public const string Branch = "tibi624";

        private readonly string serverURL = "https://api.antipiratescreen.com/verify";
        private readonly string licenseFile = "license.dat";
        private readonly string configPath = ".aps/CONFIG.xtml";
        private readonly string hardwareID;

        public Protection()
        {
            hardwareID = GetHardwareID();
        }

        private string GetHardwareID()
        {
            return Environment.MachineName + Environment.OSVersion.Platform;
        }

        private string GenerateHash(string input)
        {
            using (var sha256 = SHA256.Create())
            {
                byte[] bytes = sha256.ComputeHash(Encoding.UTF8.GetBytes(input));
                StringBuilder builder = new StringBuilder();
                foreach (byte b in bytes)
                {
                    builder.Append(b.ToString("x2"));                }
                return builder.ToString();
            }
        }

        public bool VerifyLicense(string licenseKey)
        {
            if (!ValidateFormat(licenseKey))
            {
                ShowProtectionScreen();
                return false;
            }

            string licenseHash = GenerateHash(licenseKey + hardwareID);

            // TODO: Send to server for verification

            return true;
        }

        private bool ValidateFormat(string licenseKey)
        {
            if (licenseKey.Length != 19)
            {
                return false;
            }
            if (licenseKey[4] != '-' || licenseKey[9] != '-' || licenseKey[14] != '-')
            {
                return false;
            }
            return true;
        }

        public bool VerifyIntegrity(string filePath)
        {
            try
            {
                string content = File.ReadAllText(filePath);
                string fileHash = GenerateHash(content);
                return !string.IsNullOrEmpty(fileHash);
            }
            catch
            {
                return false;
            }
        }

        public bool IsDebuggerAttached()
        {
            return System.Diagnostics.Debugger.IsAttached;        }

        public void ShowProtectionScreen()
        {
            Console.WriteLine(new string('=', 50));
            Console.WriteLine("     AntiPirateScreen Protection");
            Console.WriteLine($"     Author: {Author}");
            Console.WriteLine($"     Branch: {Branch}");
            Console.WriteLine(new string('=', 50));
            Console.WriteLine("  This software requires a valid license.");
            Console.WriteLine("  Please purchase a legitimate copy.");
            Console.WriteLine(new string('=', 50));
        }

        public bool LoadConfig(string configFile)
        {
            try
            {
                string content = File.ReadAllText(configFile);
                // Parse XTML content
                return true;
            }
            catch
            {
                return false;
            }
        }

        public bool LoadAPSFile(string apsFile)
        {
            if (!apsFile.EndsWith(".aps"))
            {
                return false;
            }
            try
            {
                string content = File.ReadAllText(apsFile);
                // Parse APS content
                return true;
            }
            catch
            {
                return false;
            }
        }

        public string GetHardwareID()
        {
            return hardwareID;
        }
        public static string GetVersion()
        {
            return Version;
        }

        public static string GetAuthor()
        {
            return Author;
        }

        public static string GetBranch()
        {
            return Branch;
        }
    }
}