#include <iostream>
#include <limits>
#include <string>
#include <map>
#include "Resource.h"
#include "Reservation.h"
#include "ReservationManager.h"
#include "WaitingList.h"
#include "CancellationHistory.h"
#include "Reservationrecord.h"

//clears a failed std:cin state and discards the rest of the line
//used for basic invalid input handling on menu choices
static void clearInputError() {
    std::cin.clear()
    std:cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

}

static void printMenu() {
    std::cout << "\n===== Campus Resource Reservation System =====\n";
    std::cout << "1. View Resources\n";
    std::cout << "2. Create Reservation\n";
    std::cout << "3. Cancel Reservation\n";
    std::cout << "4. View Waiting List\n";
    std::cout << "5. Undo Cancellation\n";
    std::cout << "6. Display Active Reservations\n";
    std::cout << "7. Display Cancellation History\n";
    std::cout << "8. Exit\n";
    std::cout << "Enter Choice: ";  
}
//reservation class and reservationrecord are two different shared types.
//these two convert between them at the boundary.
static ReservationRecord toRecord(const Reservation& r) {
    ReservationRecord rec;
    rec.reservationId = r.getReservationID();
    rec.studentId = r.getStudentID();
    rec.studentName = r.getStudentName();
    rec.reservationDate = r.getReservationDate();
    return rec;
}
static Reservation fromRecord(const ReservationRecord& rec) {
    return Reservation(rec.reservationId, rec.studentId, rec.studentName, rec.resourceId, rec.reservationDate);
}

int main() {
    ResourceManager resourceManager;
    ReservationManager reservationManager;
    CancellationHistory cancellationHistory;

    //for milestone 1, this will use a shared list

    //one waiting list per resource, created on first use
    std::map<std::string, WaitingList> waitingLists;

    if (!resourceManager.loadFromFile("data/resources.txt")) {
        std::cout << "Warning: continuing with an empty resource list.\n";
    }
    if (!reservationManager.loadFromFile("data/reservations.txt")) {
        std::cout << "Warning: continuing with no pre-loaded reservations.\n";
    }
    else {
        std::cout << "Loaded " << reservationManager.getActiveReservationCount() << " existing reservations from file.\n";
    }

    bool running = true;
    while (running) {
        printMenu();

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            clearInputError();
            std:: cout << "Invalid input. Please enter a number from the menu.\n";
            continue;
        }

        switch (choice) {
        case 1: {
            std::cout << "\n--- All Resources ---\n";
            resourceManager.displayAllResources();
            std::cout << "\n--- Available Resources ---\n";
            break;
        }
        case 2: {
            std::string resourceID, studentName, date;
            int studentID;

            std::cout << "Resource ID: ";
            std::cin >> resourceID;
            std::cout << "Student ID: ";
            std::cin >> studentID;
            if (std::cin.fail()) {
                clearInputError();
                std::cout << "Invalid student ID.\n";
                break;
            }
            std::cout << "Student Name: ";
            std::cin.ignore();
            std::getline(std::cin, studentName);
            std::cout << "Reservation Date (e.g. 201-26-09-10): ";
            std::cin >> date;

            int newID = reservationManager.generateNextReservationID();
            Reservation newRes(newID, studentID, studentName, resourceID, date);

            if (!reservationManager.validateReservationRequest(newRes, resourceManager)) {
                Resource* r = resourceManager.findResourceByID(resourceID);
                if (r == nullptr) {
                    std::cout << "Resource ID not found.\n";
                }
                else if (!r->isAvailable()) {
                    //resource is out of service -> offer waiting list
                    auto it = waitingLists.find(resourceID);
                    if ( it == waitingLists.end()) {
                        it = waitingLists.emplace(resourceID, WaitingList(resourceID)).first;
                    }
                    ReservationRecord req = toRecord(newRes);
                    if (it->second.addStudent(req)) {
                        std::cout << "resource is unavailable. Added to waiting list.\n";
                    }
                    else {
                        std::cout << "Could not add to waiting list (duplicate or invalid request).\n";
                    }
                }
                
                else {
                    //resource is in service but already booked on that date
                    std::cout << "That resource is already booked on " << date << ". Try a different date or resource.\n";
                }
                break;
            }
            reservationManager.insertReservation(newRes);
            std::cout << "Reservation Created Successfully. ID: " << newID << "\n";
            break;
        }
        case 3: {
            int resID;
            std::cout << "Reservation ID to cancel: ";
            std::cin >> resID;
            if (std::cin.fail()) {
                clearInputError();
                std::cout << "Invalid reservation ID.\n";
                break;
            }
            Reservation removed;
            if (reservationMananger.removeReservation(resID, removed)) {
                cancellationHistory.storeCancelled(removed);
                std::cout << "Reservation Cancelled. Added to cancellation history.\n";

            //automatically offer the freed resource to the next waiting student if any
                auto it = waitingLists.find(removed.getResourceID());
                if (it != waitingLists.end() && !it->second.empty()) {
                    bool assigned = it->second.processNext([&](const ReservationRecord& rec) {
                        Reservation promoted = fromRecord(rec);
                        promoted.setReservationID(reservationManager.generateNextReservationID());
                        return reservationManager.insertReservation(promoted);
    
                    });
                    if (assigned) {
                        std::cout << "Resource " << removed.getResourceID() << " automatically assigned to the next waiting student.\n";
                    }
                }
            }
                
                
            else {
                std::cout << "Reservation ID not found.";
            }
            break;
        }
        case 4: {
            std::cout << "\n--- Waiting List ---\n";
            if (waitingLists.empty()) {
                std::cout << "No waiting lists yet.\n";
            else {
                for (const auto& entry : waitingLists) {
                    entry.second.display(std::cout);
                }
            }
            break;
        }
        case 5: {
            bool restoredAny = cancellationHistory.undoCancellation([&](const ReservationRecord& rec) {
                return reservationManager.insertReservation(fromRecord(rec));
            });
            if (restoredAny) {
                std::cout << "Reservation Restored Successfully.\n";
            }
            else {
            std::cout << "No cancellations to undo\n";   
            }
            break;
        }
        case 6: {
            std::cout << "\n--- Active Reservations ---\n";
            reservationManager.displayActiveReservations();
            break;
        }
        case 7: {
            std::cout << "\n--- Cancellation History ---\n";
            cancellationHistory.display(std::cout);
            break;
        }
        case 8: {
            running = false;
            std::cout << "Goodbye!\n";
            break;
        }
        default:
            std::cout << "Invalid choice. Please select an option from the menu.\n";
        
        }

    }
    return 0;

}
