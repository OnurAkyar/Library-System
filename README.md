# Comprehensive Library Management System in C

This project is a comprehensive Library Management System developed in C in accordance with structural programming principles. It ensures the efficient tracking of students, books, authors, and borrowing processes by utilizing dynamic memory management, linked lists, and modular file read/write (CSV) operations.

## 🚀 Features

The application basically consists of 4 main modules:

### 👥 Student Operations
* **Registration and Tracking:** Name, surname, and point information are kept along with an 8-digit student number (Starting score is 100). 
* **Doubly Linked List:** Student data is kept on a doubly linked list in memory to provide fast navigation.
* **Penalized Student Control:** The system detects the status of students whose score drops below 0, and new book borrowings are automatically blocked.
* **Book Movement History:** All books a student has borrowed in the past, returned, and currently holds can be listed.

### 📚 Book and Copy Operations
* **Dynamic Sub-copies:** When a new book is added to the system with a 13-digit ISBN number, sub-copies belonging to that book (e.g., `1313131313131_1`, `1313131313131_2`) are dynamically created up to the entered "quantity" information.
* **Shelf Status Tracking:** The status of whether each book copy is on the shelf or with a student is tracked individually.
* **Automatic Quantity and Copy Update:** In book updates, if the quantity is increased, new copies are created; if it is decreased, excess copies are safely deleted from the memory and the system.

### 🔄 Borrowing and Penalty System
* **Date and Day Calculation:** Book borrow and return dates (`dd.mm.yyyy`) are taken and converted into mathematical day equivalents by the system.
* **15-Day Rule:** If a book remains with a student for more than 15 days, the system automatically deducts **10 points** from the student's score.
* **Reporting Overdue Books:** All books that are not returned on time and the number of delay days can be listed collectively.

### ✍️ Author and Mapping (Relational Data) Operations
* **Automatic Author ID:** An automatic ID is sequentially assigned to every author added to the system.
* **Many-to-Many (N:N) Mapping:** The scenario where a book can have multiple authors or an author can have multiple books is mapped and managed with a special `Kitap_Yazar` array (struct).

## 🛠️ Technology Stack and Advanced Structures

* **Language:** C
* **Data Persistence (CSV Integration):** When the program starts, all data is read from the `Ogrenciler.csv`, `Kitaplar.csv`, `Ornek_Kitaplar.csv`, `OduncIslemleri.csv`, `Yazarlar.csv`, and `KitapYazar.csv` files and loaded into memory. After every add/delete operation, the lists are instantly written back to these files to prevent data loss.
* **Function Pointers:** To avoid repeating code, operations such as saving to a file (`dosyayaKaydetGenel`), listing (`listeleCiftYonlu`), and clearing memory (`ciftYonluListeTemizle`, `tekYonluListeTemizle`) are performed using pointers through a single generic function.
* **Dynamic Memory Management:** Instead of standard arrays for all string structures (name, surname, ISBN) and structs, space is allocated using `malloc` and `realloc`, and during deletion operations, they are freed (`free`) to prevent "Memory Leaks".
