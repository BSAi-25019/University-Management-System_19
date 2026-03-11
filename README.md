# 🎓 University Management System (CMS Portal)

A complete, console-based Campus Management System (CMS) built in standard C++. This project demonstrates strong foundational programming skills, including raw dynamic memory management, Object-Oriented structures, File I/O for persistent storage, and custom Windows console rendering.

## 🌟 Key Features

* **Custom Graphical Console UI:** Built a dedicated frontend interface directly in the terminal using the Windows API (`gotoRowCol`, colored output, and shape rendering) for a professional user experience.
* **Admin Security:** Password-protected portal entry to simulate secure access.
* **Complete CRUD Operations:** Fully manage (Create, Read, Update, Delete) data across three core modules:
  * **Course Management:** Track course IDs, instructors, credit hours, and seat capacities.
  * **Student Management:** Track student records, departments, and active semesters.
  * **Enrollment Management:** Register students for courses, automatically check seat availability, and process course drops.
* **Advanced Sorting & Searching:** Implemented custom sorting algorithms using **function pointers** to dynamically sort students and courses by Name, ID, Semester, or Enrollment counts.
* **Persistent Storage:** Utilizes C++ `fstream` to automatically save and load all records via text files (`courses.txt`, `students.txt`, `enrollments.txt`), ensuring zero data loss between sessions.

## 📸 Interface Preview
*(Screenshot of the main CMS portal coming soon!)*

## 💻 Tech Stack & Concepts
* **Language:** C++
* **Environment:** Visual Studio / Windows
* **Core Concepts Used:** Raw Dynamic Memory Allocation (Pointers/Arrays), Function Pointers, Structs, File Handling (`fstream`), and Windows Console API.

## 🚀 How to Run Locally

1. Clone this repository to your local machine.
2. Open the `.sln` file in **Visual Studio**.
3. Ensure the project is set to compile for Windows (uses `<windows.h>`).
4. Build and run the project.
5. **Login Credentials:** When prompted for the Admin Password, enter: `itu123456`