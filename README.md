# SalesManager CLI
A high-performance, minimalist C++ sales register built from the ground up.

## 🚀 Overview
SalesManager is a lightweight command-line application designed for rapid sales logging. Unlike typical implementations, this project features a **custom-built dynamic array (Vector)** to handle data management, demonstrating low-level memory control and template programming.

## 🛠️ Technical Highlights
* **Custom Templates:** Built a generic `Vector<T>` class, featuring manual memory allocation and bounds checking.
* **CLI Architecture:** Designed a clean command-loop interface for real-time data entry.

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

## 🏗️ Installation & Usage
1. Clone the repo: `git clone https://github.com/yourusername/salesmanager.git`
2. Compile: `g++ main.cpp -o salesmanager`
3. Run: `./salesmanager`
