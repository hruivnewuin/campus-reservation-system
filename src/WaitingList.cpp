#include "WaitingList.h"
#include <stdexcept>

WaitingList::WaitingList(const std::string& id) : resourceId(id) {
    if (id.empty()) throw std::invalid_argument("Resource ID cannot be empty.");
}

bool WaitingList::addStudent(const ReservationRecord& request) {
    if (request.reservationId <= 0 || request.studentId <= 0 ||
        request.studentName.find_first_not_of(" \t\r\n") == std::string::npos ||
        request.reservationDate.empty() || request.resourceId != resourceId) {
        return false;
    }
    // Scan a copy so checking duplicates does not disturb FIFO order.
    auto copy = requests;
    while (!copy.empty()) {
        const auto& existing = copy.front();
        if (existing.reservationId == request.reservationId ||
            (existing.studentId == request.studentId &&
             existing.reservationDate == request.reservationDate)) return false;
        copy.pop();
    }
    requests.push(request);
    return true;
}

bool WaitingList::removeStudent(ReservationRecord& removed) {
    if (requests.empty()) return false;
    removed = requests.front();
    requests.pop();
    return true;
}

bool WaitingList::processNext(
    const std::function<bool(const ReservationRecord&)>& assign) {
    if (requests.empty() || !assign) return false;
    if (!assign(requests.front())) return false;
    requests.pop();
    return true;
}

void WaitingList::display(std::ostream& out) const {
    out << "Waiting list for " << resourceId << ":\n";
    if (requests.empty()) {
        out << "No students waiting.\n";
        return;
    }
    auto copy = requests;
    int position = 1;
    while (!copy.empty()) {
        const auto& r = copy.front();
        out << position++ << ". " << r.studentId << " | " << r.studentName
            << " | " << r.resourceId << " | " << r.reservationDate
            << " | Request ID: " << r.reservationId << '\n';
        copy.pop();
    }
}

bool WaitingList::empty() const { return requests.empty(); }
std::size_t WaitingList::size() const { return requests.size(); }
