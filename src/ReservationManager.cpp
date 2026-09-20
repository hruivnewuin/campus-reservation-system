#include "ReservationManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
/* Default constructor initializing an empty linked list
Time complexity: 0(1)
*/

ReservationManager::ReservationManager() : head(nullptr), count(0), nextReservationID(1) {}

/*The expected file format is pipe delimited
- Handles invalid inputs
*/
bool ReservationManager::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return false;
    }
    std::string line;
    while (std::getline(inFile, line)) {

        if(line.empty())continue;

        std::stringstream ss(line);
        std::string resIDStr, studIDStr, studName, resourceID, date;

        if (!std::getline(ss, resIDStr, '|'))continue;
        if (!std::getline(ss, studIDStr, '|'))continue;
        if (!std::getline(ss, studName, '|'))continue;
        if (!std::getline(ss, resourceID, '|'))continue;
        if (!std::getline(ss, date, '|'))continue;

        int resID, studID;
        try {
            resID = std::stoi(resIDStr);
            studID = std::stoi(studIDStr);
        }
        catch (const std::exception&) {
            std::cerr << "Skipping malformed reservation line: " << line << std::endl;
            continue;
        }
        // Validate that IDs are positive (invalid input management)
        if (resID <= 0 || studID <= 0) {
            std::cerr << "Skipping line with invalid negative/ zero ID: " << line << std::endl;
            continue:
        }

        Reservation res(resID, studID, studName, resourceID, date);
        insertReservation(res);

        if (resID >= nextReservationID) {
            nextReservationID = resID + 1;
        }
    }
    inFile.close();
    return true;

}
/* Destructor to erase allocated memory in linked list.
  - Prevents memory leaks.
*/
ReservationManager::~ReservationManager() {
    ReservationNode* current = head;
    while (current != nullptr) {
        ReservationNode* toDelete = current;
        current = current->next;
        delete toDelete;
    }
    head = nullptr;

}

/* inserts at the head of the list -> 0(n) because of duplicate chech, else O(1).
validates against duplicate rservation IDs
*/
bool ReservationManager::insertReservation(const Reservation& reservation) {
    if (findReservationByID(reservation.getReservationID()) != nullptr{
        std::cerr << "Error: Reservation ID " << rerservation.getReservationID() << " already exists. Insertion failed." << std::endl;
    return false;
    }
        
ReservationNode* newNode = new ReservationNode(reservation);
    newNode->next = head;
    head = newNode;
    count++;
    return true;
}

//traverses the list to find the target node-> O(n)
bool ReservationManager::removeReservation(int reservationID, Reservation& outRes) {
    ReservationNode* current = head;
    ReservationNode* prev = nullptr;

    while (current != nullptr) {
        if (current->data.getReservationID() == reservationID) {
            outRes = current->data;

            if (prev == nullptr) {
                head = current->next; //removing head
            }
            else {
                prev->next = current->next; // bypassing the node
            }
            delete current;
            count--;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false; // not found

}
/* Traverses linked list and displays all active reservations
Time Complexity: 0(n)
*/
void ReservationManager::displayActiveReservations() const {
    if (head == nullptr) {
        std::cout << "No active reservations." << std::endl;
        return;
    }
    ReservationNode* current = head;
    while (current!= nullptr) {
        current->data.display();
        current = current->next;
    }
}
/* Searches linked list by ID for a specific reservation
 Time complexity: 0(n), Worst-case
    */
Reservation* ReservationManager::findReservationByID(int reservationID) {
    ReservationNode* current = head;
    while (current!= nullptr) {
        if (current->data.getReservationID() == reservationID) {
            return &(current->data);
        }
        current = current->next;
    }
    return nullptr;

}
/* Validates if a new reservation requests conflicts with an existing reservation, also checks if requested resource is unavailable.
Time Complexity: 0(n)
*/
bool ReservationManager::validateReservationRequest(const Reservation& reservation, ResourceManager& resourceManager) const {
    //reservation ID must not already be in use, and the resource/date
    //pair must not already be booked by another active reservation
    ReservationNode* current = head;
    while (current != nullptr) {
        if (current->data.getResourceID() == reservation.getResourceID() && current->data.getReservationDate() == reservation.getReservationDate()) {
            std::cerr << "Validation failed: resource " << reservation.getResourceID() << " is already booked on " << reservation.getReservationDate() << "." <<std::endl;
            return false;
        }
        current = current->next;
    }

    //resource must exist and be available
    Resource* res = resourceManager.findResourceByID(reservation.getResourceID());
    if (res == nullptr) {
        std::cerr << "Validation failed: resource ID does not exist." << std::endl;
        return false;
    }
    if (!res->isAvailable()) {
        std::cerr << "Validation failed: resource is not available." << std::endl;
        return false;
    }

    return true;
}
// Returns total number of active reservations in linked list. Time Complexity: 0(1)
int ReservationManager::getActiveReservationCount() const {
    return count;
}
// Generations next available unique reservation ID
int ReservationManager::generateNextReservationID() {
    return nextReservationID++;
}
