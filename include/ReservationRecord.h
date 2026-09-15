#ifndef RESERVATION_RECORD_H
#define RESERVATION_RECORD_H
#include <string>

// Shared data only; adapt to your team's Reservation class during integration.
// Fields match reservations.txt. Waiting requests also retain a reservation ID.
struct ReservationRecord {
    int reservationId;
    int studentId;
    std::string studentName;
    std::string resourceId;
    std::string reservationDate;
};
#endif
