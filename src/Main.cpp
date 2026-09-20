#include <iostream>
#include <limits>
#include <string>
#include "Resource.h"
#include "Reservation.h"
#include "WaitingList.h"
#include "CancellationHistory.h"

//clears a failed std:cin state and discards the rest of the line
//used for basic invalid input handling on menu choices
static void clearInputError() {
    std::cin.clear()
    std:cin.ignore(std::numeric+limits<std::streamsize>::max(), '\n');

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

int main() {
    ResourceManager resourceManager;
    ReservationManager reservationManager;
    CancellationHistory cancellationHistory;

    //for milestone 1, this will use a shared list

    WaitingList waitingList;

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
            int studnetID;

            std::cout << "Resource ID: ";
            std::cin >> resourceID;
            std::cout << "Student ID: ";
            std::cin >> studentID;
            if (std::cin.fail()) {
                clearInputError();
                std::cout << "Invalid student ID."
                break;
            }
            std::cout << "Student Name: ";
            std::cin.ignore();
            std::getline(std::cin, studentName);
            std::cout << "Reservation Date (e.g. 201-26-09-10): ";
            std::cin >> date;

            int newID = reservationManager.generateNextReservationID();
            Reservation newRes(newID, student, studentName, resourceID, date);

            if (!reservationManager.validateReservationRequest(newRes, resourceManager)) {
                Resource* r = resourceManager.findResourceByID(resourceID);
                if (r == nullptr) {
                    std::cout << "Resource ID not found.\n";
                }
                else if (!r->isAvailable()) {
                    //resource is out of service -> offer waiting list
                    WaitingRequest req;
                    req.student = Student(studenttID, studentName);
                    req.resourceID = resourceID;
                    req.requestDate = date;
                    waitingList.addToWaitingList(req);
                    std::cout << "resource is unavailable. Added to waiting list.\n";
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
            std::cout << "Reservation ID to cancel: "
            std::cin >> resID;
            if (std::cin.fail()) {
                clearInputError();
                std::cout << "Invalid reservation Id.\n";
                break;
            }
            Reservation removed;
            if (reservationMananger.removeReservation(resId, removed)) {
                cancellationHistory.storeCancellation(removed);
                std::cout << "Reservation Cancelled. Added to cancellation history.\n";

            }
            else {
                std::cout << "Reservation ID not found."
            }
            break;
        }
        case 4: {
            std::cout << "\n--- Waiting List ---\n";
            waitingList.displayWaitingList();
            break;
        }
        case 5: {
            Reservation restored;
            if (cancellationHistory.restoreLastCancellation(restored)) {
                reservationManager.insertReservation(restored);
                std::cout << "Reservation Restored Successfully.\n"
            }
            else {
            std::cout << "No cencellations to undo\n";   
            }
            break;
        }
        case 6: {
            std::cout << "\n--- Active Reservations ---\n";
            reservationManager.displayActivereservations();
            break;
        }
        case 7: {
            std::cout << "\n--- Cancellation History ---\n";
            cancellationHistory.displayCancellationHistory();
            break;
        }
        case 8: {
            running = false;
            std::cout << "Goodbye!\n"
            break;
        }
        default:
            std::cout << "Invalid choice. Please select an option from the menu.\n";
        
        }

    }
    return 0;

}