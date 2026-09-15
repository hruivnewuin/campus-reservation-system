#ifndef CANCELLATION_HISTORY_H
#define CANCELLATION_HISTORY_H
#include "ReservationRecord.h"
#include <functional>
#include <ostream>
#include <stack>

// One history for the system: only the newest cancellation can be undone.
class CancellationHistory {
private:
    std::stack<ReservationRecord> cancelled;
public:
    // Call once for each successfully cancelled active reservation.
    void storeCancelled(const ReservationRecord& reservation);
    // The manager callback validates and inserts into its active linked list.
    // False (including unavailable resources) preserves the entire history.
    bool undoCancellation(
        const std::function<bool(const ReservationRecord&)>& restore);
    void display(std::ostream& out) const;
    bool empty() const;
    std::size_t size() const;
};
#endif
