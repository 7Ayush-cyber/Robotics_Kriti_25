# Smart Disposable Dustbin — Robotics Kriti '25 🏆

**Gold Medal Winner, Kriti (Robotics Competition), 2025**

An automated waste management system that combines sensor-based waste segregation, vacuum-powered plastic bag deployment, and CNC-controlled mechanisms to make waste disposal more efficient, hygienic, and hands-free.

## Overview

The Smart Disposable Dustbin automates the full waste-handling cycle — detecting waste, opening the lid, segregating it, compacting it, and deploying a fresh plastic liner — with minimal manual intervention. The system integrates ultrasonic distance/level sensing, gas sensing, a BLDC fan for vacuum-based bag handling, and a stepper-motor-driven CNC mechanism, all coordinated through an Arduino Mega.

## Key Features

- **Automatic lid operation** — opens/closes based on proximity detection, reducing manual contact and improving hygiene
- **Sensor-based level detection** — ultrasonic sensors monitor fill level to know when the bin needs attention
- **Gas sensing** — detects buildup of harmful/foul gases inside the bin
- **Vacuum-powered bag deployment** — a BLDC fan is used to unfurl and seat a new plastic bag automatically after disposal
- **CNC-controlled compaction mechanism** — a stepper-motor-driven system compacts waste and manages the mechanical sequencing of the bin
- **Reduced manual effort** — minimizes the need for a person to touch the bin, its lid, or the liner

## Repository Contents

| Category | Files |
|---|---|
| **Firmware (Arduino)** | `MainMega.ino` (main controller), `sensors.ino`, `lid_opening.ino`, `New_bag_deployment.ino`, `Level_Detection_CNC.ino` |
| **CAD Assemblies** | `Assem1.SLDASM`, `dustbin.SLDASM`, `dustbin_2.SLDASM`, `Plastic_wrapper_assembly.SLDASM` |
| **CAD Parts** | Individual `.SLDPRT` files for structural components — walls, base, lid, motor mounts, compactor walls, plastic holder/wrapper parts, etc. |
| **Engineering Drawings** | `.SLDDRW` drawing files with corresponding `.DXF` exports for manufacturing/laser-cutting |
| **Sheet Metal Data** | `.yld` files (SolidWorks sheet metal flat-pattern data) |
| **Reports** | `Report_Smart_disposable_dustbin.pdf`, `robotics_kriti_final_report.pdf` |

## Hardware Used

- Arduino Mega (main controller)
- Ultrasonic sensors (level/proximity detection)
- Gas sensor
- BLDC fan (vacuum-powered bag deployment)
- Stepper motor (CNC-controlled compaction/actuation)

## Getting Started

### Mechanical
1. Open the assembly files (`Assem1.SLDASM`, `dustbin.SLDASM`, etc.) in SolidWorks to review the full CAD model.
2. Use the corresponding `.DXF` files to laser-cut or CNC-machine the sheet metal/plastic parts.
3. Assemble per the drawings in the `.SLDDRW` files.

### Electronics / Firmware
1. Wire the ultrasonic sensors, gas sensor, BLDC fan, and stepper motor to the Arduino Mega as referenced in the `.ino` files.
2. Upload `MainMega.ino` as the primary control program (it coordinates the subsystem logic found in `sensors.ino`, `lid_opening.ino`, `New_bag_deployment.ino`, and `Level_Detection_CNC.ino`).
3. Power on and test each subsystem (lid actuation, level detection, bag deployment) individually before full integration.

## Documentation

For the complete design rationale, methodology, and results, see:
- `Report_Smart_disposable_dustbin.pdf`
- `robotics_kriti_final_report.pdf`

## Acknowledgment

This project was built for **Kriti**, where it won the **Gold Medal**. This repository is forked from [7Ayush-cyber/Robotics_Kriti_25](https://github.com/7Ayush-cyber/Robotics_Kriti_25).

## License

No license file is currently included. Add one (e.g., MIT) if you intend for others to reuse this work.
