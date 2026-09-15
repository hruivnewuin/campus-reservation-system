#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include "Reservation.h"
#include "Resource.h"

// Singled linked list node holding one active reservation
struct ReservationNode {
    Reservation data;
    ReservationNode* next;
    ReservationNode(const Reservation& res) : data(res), next(nullptr) {}
};

// Manages all active reservations using a custom single linked list
// A linked list used because reservations are inserted and removed frequently and the collection size is not known in advance

class ReservationManager {
private:
    ReservationNode* head;
    int count;
    int nextReservationID; // used to auto generate/validate unique IDs
public:
    ReservationManager();
    ~ReservationManager(); //must free all nodes
    

    // Loads pre existing reservations from a pipe delimited file
    // Each loaded reservation isinserted into the linked list, and nextreservationID is advanced past the highest ID
    // found so newly created reservations never collide with loaded ones.
    // Returns true on success, false if the file could not be opened
    bool loadFromFile(const std::string& filename);
    // core linked list operations
    // inserts a new reservation at the head (0(1)) or tail (O(n)) 
    bool insertReservation(const Reservation& reservation);
    //removes a reservation by ID and returns the removed reservation via 'outRes'
    // so it can be pushed onto the cancellation stack
    // Returns strue if found and removed, false otherwise
    bool removeReservation(int reservationID, Reservation& outRes);

    //traverse the list and prints every reservation
    void displayActiveReservations() const;

    //traverses the lsit looking for a reservation by ID
    //returns a point to the node's data or nullptr if not found
    Reservation* findReservationByID(int reservationID);

    //validates a reservation request against business rules
    // resource must exist and be available
    // reservation ID must not already be in use
    // resource must not already an active reservation on the same date
    // returns true if request is valid
    bool validateReservationRequest(const Reservation& reservation, ResourceManager& resourceManager) const;

    int getActiveReservationCount() const;
    int generateNextReservationID();
};
#endif //RESERVATION_MANAGER_H


