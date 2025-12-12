A **C-based vehicle monitoring system** that stores vehicle logs using a **circular doubly linked list** and maintains a **circular queue** for speeding vehicles.  
The program records vehicle ID, speed, arrival time, and date — with automatic timestamp generation and optional insertion of missed data.

---

## 📌 Features

### ✅ Vehicle Data Management
- Add new vehicle records with **auto-captured date & time**
- Insert previously missed vehicle data manually
- Search for a vehicle by ID
- Remove a vehicle from the dataset
- Display all vehicles in the circular linked list

### 🚨 Speeding Vehicle Detection
- Automatically detects vehicles exceeding **80 km/h**
- Stores them in a fixed-size circular queue
- Displays complete speeding-vehicle history

### ⏱ Automatic Date & Time Handling
- Uses system time converted to **IST (UTC +5:30)**
- Date format → `DD-MM-YYYY`
- Time format → `HH:MM:SS`

### 🔄 Data Structures Used
- **Circular Doubly Linked List** → Stores all vehicle entries  
- **Circular Queue** → Stores speeding vehicles  
- Both structures allow efficient insertion and traversal

---

## 📂 Project Structure
- traffic_system.c # Main source file
- README.md # Project documentation

---

## 🛠 Requirements

- GCC or any standard C compiler  
- Standard header files:  
  `stdio.h`, `stdlib.h`, `string.h`, `time.h`

---

## ▶️ How to Compile & Run

### Compile:
```bash
gcc vehicle_monitor.c -o vehicle_monitor
./vehicle_monitor
