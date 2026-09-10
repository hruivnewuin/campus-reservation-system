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
    
}


