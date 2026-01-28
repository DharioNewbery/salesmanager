# SalesManager CLI
A high-performance, minimalist C++ sales register built from the ground up.

## 🚀 Overview
SalesManager is a lightweight command-line application designed for rapid sales logging. Unlike typical implementations, this project features a **custom-built dynamic array (Vector)** to handle data management and **custom-build module SDK** for easy expansion.

## 🛠️ Technical Highlights
* **Custom Templates:** Built a generic `Vector<T>` class, featuring manual memory allocation and bounds checking.
* **CLI Architecture:** Designed a clean command-loop interface for real-time data entry.
* **Modular Implementation:** Created a Module SDK for simple and robust functionality scalling and customization.

## 📋 Features
### Core Management
* **Smart Entry:** Add individual or bulk items with automated ID generation.
* **CRUD Operations:** Edit, delete (single/bulk), and list sales records.
* **Data Persistence:** Robust Save/Load functionality using `.txt` parsing.

### Planned Enhancements
- [ ] **Action History:** Undo/Redo stack for error correction.
- [ ] **Analytics:** Generate simple reports (daily totals, top items).
- [ ] **Sorting:** Sort records by date, price, or category.
- [ ] **Activity Log:** A dedicated log file for auditing all changes.

## 🚀 How to Compile
### Prerequisites
* **Compiler:** `g++` (Standard: C++17)
* **Build Tool:** `make`
  * *Note for Windows:* If using MinGW, ensure `mingw32-make` is accessible in your PATH.
### 1. Standard Build (Using Makefile) (Recommended)
To compile the entire project along with all available mods, run:
```powershell
make
```
or
```powershell
mingw32-make
```
### 2. Manual Build (Using g++)
To compile the code using the g++ command, run:
```powershell
g++ -std=c++17 main.cpp -include modules/Core.h -o salesmanager
```
If your project has multiple modules, you will need to specify the include for each extra module, otherwise those modules will not be registered by the application.
```powershell
g++ -std=c++17 main.cpp -include modules/Core.h -include modules/<name>.h ...other includes... -o salesmanager
```
Depending on the terminal you are using, this is also possible and will include all modules automatically:
```powershell
g++ -std=c++17 main.cpp -include modules/*.h -o salesmanager
```



