#include "CancellationHistory.h"

void CancellationHistory::storeCancelled(const ReservationRecord& reservation) {
    cancelled.push(reservation);
}

bool CancellationHistory::undoCancellation(
    const std::function<bool(const ReservationRecord&)>& restore) {
    if (cancelled.empty() || !restore) return false;
    if (!restore(cancelled.top())) return false;
    cancelled.pop();
    return true;
}

void CancellationHistory::display(std::ostream& out) const {
    out << "Cancellation history (newest first):\n";
    if (cancelled.empty()) {
        out << "No cancelled reservations.\n";
        return;
    }
    // Printing a copy preserves the original undo order.
    auto copy = cancelled;
    while (!copy.empty()) {
        const auto& r = copy.top();
        out << r.reservationId << " | " << r.studentId << " | "
            << r.studentName << " | " << r.resourceId << " | "
            << r.reservationDate << '\n';
        copy.pop();
    }
}

bool CancellationHistory::empty() const { return cancelled.empty(); }
std::size_t CancellationHistory::size() const { return cancelled.size(); }
