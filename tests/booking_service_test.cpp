#include "airline/booking_service.hpp"

#include <cassert>
#include <unordered_map>

using namespace airline;

int main() {
    std::unordered_map<domain::PassengerId, domain::Passenger> passengers;
    std::unordered_map<domain::FlightId, domain::Flight> flights;
    std::unordered_map<domain::FlightId, std::vector<domain::Seat>> seats;
    std::unordered_map<domain::ReservationId, domain::Reservation> reservations;

    passengers.emplace("P001", domain::Passenger{"P001", "Ada Lovelace", "1 Main St", "Montreal"});
    flights.emplace("AC101", domain::Flight{"AC101", 1, {}, "Montreal", "Toronto", {}, {}, 2});
    seats["AC101"] = {
        {"1A", true, std::nullopt, 2500},
        {"1B", true, std::nullopt, 2500}
    };

    service::BookingService service;
    service::BookingRequest request{"R001", "P001", "AC101", "1A", 2500};

    auto created = service.create_reservation(request, passengers, flights, seats, reservations);
    assert(created.success);
    assert(reservations.contains("R001"));
    assert(!seats["AC101"][0].available);
    assert(seats["AC101"][0].passenger_id == "P001");

    auto duplicate = service.create_reservation(request, passengers, flights, seats, reservations);
    assert(!duplicate.success);

    service::BookingRequest occupied{"R002", "P001", "AC101", "1A", 2500};
    auto occupied_result = service.create_reservation(occupied, passengers, flights, seats, reservations);
    assert(!occupied_result.success);

    std::string error;
    assert(service.cancel_reservation("R001", seats, reservations, error));
    assert(!reservations.contains("R001"));
    assert(seats["AC101"][0].available);

    return 0;
}
