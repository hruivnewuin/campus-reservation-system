Campus Resource Reservation System
-----------------------------------
Milestone 1: Core System Development

TEAM MEMBERS
------------
- Faith Paredes: Resource Management
- Isiah Ndanzia: Waiting List
- Caleb Djan: Reservation Management

PROJECT STRUCTURE
-----------------
Project1/
  include/    -- Header Files (class declarations) --
  src/         -- Implementation Files --
  data/        -- Resource inventory & existing reservation to be loaded at startup--
    resources.txt
    reservations.txt.
  README.txt
  ComplexityAnalysis.md
  GroupContributionReport.docx
  .gitignore

HOW TO BUILD
-------------
From the Project1/ directory, on CELL or any g++ environment:
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
Linked List -> ReservationManager: stores active reservations (insert, remove, traverse, display)
Queue -> WaitingList: FIFO waiting list (enqueue, dequeue, display)
Stack -> CancellationHistory: LIFO cancellation history (push on cancel, pop to undo, display)
Vector -> ResourceManager: resource inventory

VALIDATION RULES
----------------
A reservation request is rejected if:
- the reservation ID is already in use
- or the same resource already has an active reservation on the same date
- or if the resource is marked unavailable , in which case the request is routed to the waiting list instead

TESTING PERFORMED
------------------
File loading:  verified all 20 resources and 20 reservations load correctly from the provided data files.
Reservations: created and cancelled reservations. Confirmed the correct behavior for data conflicts, unavailable resources, and duplicate IDs.
Undo: confirmed the most recently cancelled reservation is restores correctly, and that undoing with an empty history is handled gracefully.
Waiting List: confirmed FIFO add/remove order.
Invalid input: confirmed non-numeric menu input and invalid reservations IDs are handled without crashing.

GITHUB REPOSITORY
------------------
https://github.com/hruivnewuin/campus-reservation-system


    


