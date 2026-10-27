#pragma once

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace airline::domain {

using FlightId = std::string;
using PassengerId = std::string;
using ReservationId = std::string;
using SeatId = std::string;
using MoneyCents = std::int64_t;

struct Airline {
    std::uint64_t id{};
    std::string name;
};

struct Passenger {
    PassengerId id;
    std::string name;
    std::string address;
    std::string city;
    std::optional<std::string> gender;
    std::optional<std::chrono::year_month_day> date_of_birth;
    std::optional<double> weight_kg;
};

struct Flight {
    FlightId number;
    std::uint64_t airline_id{};
    std::chrono::year_month_day date;
    std::string departure_location;
    std::string arrival_location;
    std::chrono::minutes departure_time{};
    std::chrono::minutes arrival_time{};
    std::uint32_t total_seats{};
    std::vector<SeatId> seats;
};

struct Reservation {
    ReservationId id;
    PassengerId passenger_id;
    FlightId flight_number;
    MoneyCents cost_cents{};
    std::vector<SeatId> seat_assignments;
};

struct Seat {
    SeatId id;
    bool available{true};
    std::optional<PassengerId> passenger_id;
    MoneyCents cost_cents{};
};

inline bool has_available_seat(const std::vector<Seat>& seats) {
    return std::any_of(seats.begin(), seats.end(), [](const Seat& seat) {
        return seat.available;
    });
}

} // namespace airline::domain
