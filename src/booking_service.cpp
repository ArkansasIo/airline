#include "airline/booking_service.hpp"

#include <algorithm>

namespace airline::service {

BookingResult BookingService::create_reservation(
    const BookingRequest& request,
    std::unordered_map<domain::PassengerId, domain::Passenger>& passengers,
    std::unordered_map<domain::FlightId, domain::Flight>& flights,
    std::unordered_map<domain::FlightId, std::vector<domain::Seat>>& seats,
    std::unordered_map<domain::ReservationId, domain::Reservation>& reservations) {

    BookingResult result;

    if (request.reservation_id.empty() || request.passenger_id.empty() ||
        request.flight_number.empty() || request.seat_id.empty()) {
        result.error = "reservation, passenger, flight, and seat identifiers are required";
        return result;
    }

    if (!passengers.contains(request.passenger_id)) {
        result.error = "passenger does not exist";
        return result;
    }

    if (!flights.contains(request.flight_number)) {
        result.error = "flight does not exist";
        return result;
    }

    if (reservations.contains(request.reservation_id)) {
        result.error = "reservation ID already exists";
        return result;
    }

    auto seat_it = seats.find(request.flight_number);
    if (seat_it == seats.end()) {
        result.error = "no seat map exists for flight";
        return result;
    }

    auto& flight_seats = seat_it->second;
    auto seat = std::find_if(flight_seats.begin(), flight_seats.end(),
        [&](const domain::Seat& value) {
            return value.id == request.seat_id;
        });

    if (seat == flight_seats.end()) {
        result.error = "requested seat does not exist";
        return result;
    }

    if (!seat->available) {
        result.error = "requested seat is already occupied";
        return result;
    }

    auto& flight = flights.at(request.flight_number);
    if (flight.total_seats != 0) {
        const auto booked = static_cast<std::uint32_t>(
            std::count_if(flight_seats.begin(), flight_seats.end(),
                [](const domain::Seat& value) { return !value.available; }));
        if (booked >= flight.total_seats) {
            result.error = "flight is full";
            return result;
        }
    }

    seat->available = false;
    seat->passenger_id = request.passenger_id;

    domain::Reservation reservation;
    reservation.id = request.reservation_id;
    reservation.passenger_id = request.passenger_id;
    reservation.flight_number = request.flight_number;
    reservation.cost_cents = request.cost_cents;
    reservation.seat_assignments.push_back(request.seat_id);

    auto [inserted, ok] = reservations.emplace(reservation.id, reservation);
    if (!ok) {
        // Roll back the in-memory seat mutation if insertion unexpectedly fails.
        seat->available = true;
        seat->passenger_id.reset();
        result.error = "reservation could not be stored";
        return result;
    }

    result.success = true;
    result.reservation = inserted->second;
    return result;
}

bool BookingService::cancel_reservation(
    const domain::ReservationId& reservation_id,
    std::unordered_map<domain::FlightId, std::vector<domain::Seat>>& seats,
    std::unordered_map<domain::ReservationId, domain::Reservation>& reservations,
    std::string& error) {

    auto reservation_it = reservations.find(reservation_id);
    if (reservation_it == reservations.end()) {
        error = "reservation does not exist";
        return false;
    }

    const auto reservation = reservation_it->second;
    auto seat_it = seats.find(reservation.flight_number);
    if (seat_it != seats.end()) {
        for (const auto& seat_id : reservation.seat_assignments) {
            auto seat = std::find_if(seat_it->second.begin(), seat_it->second.end(),
                [&](const domain::Seat& value) { return value.id == seat_id; });
            if (seat != seat_it->second.end() &&
                seat->passenger_id == reservation.passenger_id) {
                seat->available = true;
                seat->passenger_id.reset();
            }
        }
    }

    reservations.erase(reservation_it);
    return true;
}

} // namespace airline::service
