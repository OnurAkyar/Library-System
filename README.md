# Comprehensive Library Management System in C

[cite_start]This project is a comprehensive Library Management System developed in C, adhering to structural programming principles[cite: 4]. It enables efficient tracking of students, books, authors, and borrowing processes using dynamic memory management, linked lists, and modular file read/write (CSV) operations.

## 🚀 Features

The application basically consists of 4 main modules:

### 👥 Student Operations
* [cite_start]**Registration & Tracking:** Keeps track of students using an 8-digit student number, along with their name, surname, and point information (starting points are 100)[cite: 38, 54].
* **Doubly Linked List:** Student data is kept in memory on a doubly linked list to ensure fast navigation.
* [cite_start]**Penalized Student Control:** The system automatically detects students whose points drop below 0 and prevents them from borrowing new books[cite: 94].
* [cite_start]**Book Movement History:** All books a student has borrowed in the past, returned, or currently holds can be listed[cite: 76].

### 📚 Book and Copy Operations
* [cite_start]**Dynamic Sub-copies:** When a new book is added to the system with a 13-digit ISBN, sub-copies belonging to that book (e.g., `1313131313131_1`, `1313131313131_2`) are dynamically created based on the entered "quantity"[cite: 161, 176].
* [cite_start]**Shelf Status Tracking:** The status of each book copy—whether it is on the shelf or with a student—is tracked individually[cite: 251, 259].
* [cite_start]**Auto Quantity & Copy Update:** During book updates, if the quantity is increased, new copies are generated; if decreased, excess copies are safely removed from memory and the system[cite: 221].

### 🔄 Borrowing and Penalty System
* [cite_start]**Date and Day Calculation:** Book borrowing and returning dates (`dd.mm.yyyy`) are taken and converted into mathematical day equivalents by the system[cite: 108, 141].
* [cite_start]**15-Day Rule:** If a book remains with a student for more than 15 days, the system automatically deducts **10 points** from the student's score[cite: 142].
* [cite_start]**Reporting Overdue Books:** All books that are not returned on time and their exact delay in days can be listed collectively[cite: 277].

### ✍️ Author and Mapping (Relational Data) Operations
* [cite_start]**Auto Author ID:** An automatic ID is assigned sequentially (1, 2, 3...) to each author added to the system[cite: 331].
* [cite_start]**Many-to-Many Mapping:** Using a special `Kitap_Yazar` array (struct), the system manages many-to-many relationships, allowing a single book to have multiple authors or a single author to write multiple books[cite: 288].

## 🛠️ Technology Stack and Advanced Structures

* **Language:** C
* **Data Persistence (CSV Integration):** Upon startup, all data is read from `Ogrenciler.csv`, `Kitaplar.csv`, `Ornek_Kitaplar.csv`, `OduncIslemleri.csv`, `Yazarlar.csv`, and `KitapYazar.csv` files and loaded into memory. [cite_start]After every add/delete operation, lists are instantly written back to these files to prevent data loss[cite: 53, 123, 175, 344].
* **Function Pointers:** To avoid code repetition, operations like saving to a file (`dosyayaKaydetGenel`), listing (`listeleCiftYonlu`), and clearing memory (`ciftYonluListeTemizle`, `tekYonluListeTemizle`) are executed through a single generic function using pointers.
* **Dynamic Memory Management:** Standard arrays are replaced with dynamic memory allocation (`malloc`, `realloc`) for all string structures (name, surname, ISBN) and structs. Memory is freed during deletion operations (`free`) to prevent "Memory Leaks".
