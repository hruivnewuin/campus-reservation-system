Campus Resource Reservation System
-----------------------------------
Milestone 1: Core System Development

TEAM MEMBERS
------------
- Faith Paredes: (Job here)
- NAME HERE: (Job here)
- NAME HERE: (Job here)

PROJECT STRUCTURE
-----------------
Project1/
  include/    -- Header Files (class declarations) --
    Student.h
    Resource.h
    Reservation.h
    ReservationManager.h
    WaitingList.h
    CancellationHistory.h
src/         -- Implementation Files --
    main.cpp
    Student.cpp
    Resource.cpp
    Reservation.cpp
    ReservationManager.cpp
    WaitingList.cpp
    CancellationHistory.cpp
data/        
  resources.txt
  reservations.txt.
README.txt
ComplexityAnalysis.md
.gitignore

HOW TO BUILD
-------------
From the Project1/ directory, on CELL or any g++ envoirnment:
  g++ -std=c++17 -Wall - Iinclude src/*.cpp -o reservation_system

HOW TO RUN
----------
  ./reservation_system

The program loads data/resources.txt and data/reservations.txt on startup, then presents a menu driven interface:

  ==== Campus Resource Reservation System =====
  1. View Resources
  2. Create Reservation
  3. Cancel Reservation
  4. View Waiting List
  5. Undo Cancellation
  6. Display Active Reservations
  7. Display Cancellation History
  8. Exit

DATA FILE FORMATS
-----------------
Both files use pipe (|) delimited fields.

resources.txt:
  ResourceID|ResourceName|ResourceType|Available/Unavailble
  Example: R101|Study Room 101|Study Room|Available

reservations.txt:
  ReservationID|StudentID|StudnetName|ResourceID|Date
  Example: 301|1001|Alice Smith|R101|09/15/2026

DATA STRUCTURES USED
---------------------
- Linked List -> ReservationManager: stores active reservations (insert, remove, traverse, display)
- Queue -> WaitingList: FIFO waiting list (enqueue, dequeue, display)
- Stack -> CancellationHistory: LIFO cancellation history (push on cancel, pop to undo, display)
- Vector -> ResourceManager: resource inventory

VALIDATION RULES
----------------
A reservation request is rejected if:
- the reservation ID is already in use
- or the same resource already has an active reservation on the same date
- or if the resource is marked unavailable , in which case the request is routed to the waiting list instead

GITHUB REPOSITORY
------------------



    


