# ESP32 Light Switch Controller

**Status:** Work in Progress

A WiFi-controlled servo-operated light switch using ESP32 and PlatformIO. Control your lights remotely through a web interface!

## Project Overview

This project allows you to control a physical light switch using:
- **ESP32** microcontroller
- **Servo motor** for physical switch actuation
- **WiFi connectivity** for remote control
- **Web interface** for easy control from any device

## Hardware Requirements

- ESP32 development board
- Servo motor (SG90 or similar)
- 3D printed mount (`LightSwitch_v1.stl`)
- Jumper wires
- Breadboard (optional)

## Pin Configuration

| Component | ESP32 Pin | Notes |
|-----------|-----------|-------|
| Servo Signal | GPIO 18 | PWM signal to servo |
| Servo VCC | 3.3V or 5V | Power supply |
| Servo GND | GND | Ground connection |
| Status LED | GPIO 2 | Built-in LED |

## Getting Started

### Prerequisites

1. **Install PlatformIO**
   - [VS Code](https://code.visualstudio.com/) + [PlatformIO extension](https://platformio.org/install/ide?install=vscode)
   - Or [PlatformIO CLI](https://docs.platformio.org/en/latest/core/installation.html)

2. **Install ESP32 USB Drivers**
   - [CP2102 drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) (most common)
   - Or check your ESP32 board documentation

### Configuration

1. **WiFi Setup**
   ```cpp
   const char* ssid = "YOUR_WIFI_SSID";
   const char* password = "YOUR_WIFI_PASSWORD";
   ```

2. **COM Port Setup**
   - Check Device Manager for your ESP32 port
   - Update `platformio.ini`:
   ```ini
   upload_port = COM3    ; Your ESP32 port
   monitor_port = COM3   ; Your ESP32 port
   ```

### Flashing to ESP32

#### Method 1: Using VS Code + PlatformIO

1. **Open Project**
   ```bash
   cd c:\Users\alper\Git\esp32_lightSwitch
   code .
   ```

2. **Build Project**
   - Open Command Palette (`Ctrl+Shift+P`)
   - Run: `PlatformIO: Build`
   - Or click the ✓ button in bottom toolbar

3. **Upload to ESP32**
   - Connect ESP32 via USB
   - Hold BOOT button (if required by your board)
   - Run: `PlatformIO: Upload`
   - Or click the → button in bottom toolbar

4. **Monitor Serial Output**
   - Run: `PlatformIO: Serial Monitor`
   - Or click the 🔌 button in bottom toolbar

#### Method 2: Using PlatformIO CLI

```powershell
# Navigate to project directory
cd c:\Users\alper\Git\esp32_lightSwitch

# Build the project
pio run

# Upload to ESP32 (replace COM3 with your port)
pio run --target upload --upload-port COM3

# Monitor serial output
pio device monitor --port COM3 --baud 115200
```

#### Method 3: One-Command Flash & Monitor

```powershell
# Build, upload, and start monitoring in one command
pio run --target upload --target monitor --upload-port COM3 --monitor-port COM3
```

### Troubleshooting Flash Issues

#### ESP32 Not Detected
```powershell
# Check available ports
pio device list

# Try different upload speeds in platformio.ini
upload_speed = 460800  # or 115200 for slower but more reliable
```

#### Failed to Connect
1. **Hold BOOT button** while connecting/uploading
2. **Press EN (reset) button** after upload
3. **Check USB cable** (data cable, not just power)
4. **Try different COM port** in Device Manager

#### Permission Errors
```powershell
# Close any open serial monitors/Arduino IDE
# Run PowerShell as Administrator
```

## Usage

1. **Power on ESP32** and wait for WiFi connection
2. **Check Serial Monitor** for IP address
3. **Open web browser** and navigate to ESP32's IP
4. **Control your light** using the ON/OFF buttons

### Expected Serial Output
```
=== ESP32 Light Switch Starting ===
Servo initialized on pin 18
Connecting to WiFi: YourWiFiName
.....
WiFi connected successfully!
IP address: 192.168.1.100
Access the web interface at: http://192.168.1.100
Web server started!
=== Setup Complete ===
```

## Project Structure

```
esp32_lightSwitch/
├── platformio.ini          # PlatformIO configuration
├── src/
│   └── main.cpp            # Main application code
├── LightSwitch_v1.stl      # 3D printable mount
├── README.md               # This file
└── espLightSwitchLogic.ino # Original Arduino IDE file (deprecated)
```


## 3D Printing

Use the included `LightSwitch_v1.stl` file to print a mount for your servo motor. This will help securely attach the servo to your light switch.

## Known Issues & TODO

- [ ] Add WiFi credentials configuration via web interface
- [ ] Add OTA (Over-The-Air) updates
- [ ] Add servo position feedback
- [ ] Add authentication to web interface (?)

## License

This project is open source. Feel free to modify and distribute.

## Contributing

This is an ongoing project. Contributions, suggestions, and improvements are welcome!

---

**Note:** This project is still under development. Some features may be incomplete or require additional testing.
