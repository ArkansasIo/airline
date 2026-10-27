#pragma once

#include "airline/domain.hpp"

#include <string>
#include <unordered_map>
#include <vector>

namespace airline::service {

struct BookingRequest {
    domain::ReservationId reservation_id;
    domain::PassengerId passenger_id;
    domain::FlightId flight_number;
    domain::SeatId seat_id;
    domain::MoneyCents cost_cents{};
};

struct BookingResult {
    bool success{false};
    std::string error;
    domain::Reservation reservation;
};

class BookingService {
public:
    BookingResult create_reservation(
        const BookingRequest& request,
        std::unordered_map<domain::PassengerId, domain::Passenger>& passengers,
        std::unordered_map<domain::FlightId, domain::Flight>& flights,
        std::unordered_map<domain::FlightId, std::vector<domain::Seat>>& seats,
        std::unordered_map<domain::ReservationId, domain::Reservation>& reservations);

    bool cancel_reservation(
        const domain::ReservationId& reservation_id,
        std::unordered_map<domain::FlightId, std::vector<domain::Seat>>& seats,
        std::unordered_map<domain::ReservationId, domain::Reservation>& reservations,
        std::string& error);
};

} // namespace airline::service
