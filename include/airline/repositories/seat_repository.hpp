#pragma once

#include "airline/domain.hpp"

#include <optional>
#include <vector>

namespace airline::repository {

class SeatRepository {
public:
    virtual ~SeatRepository() = default;

    virtual std::vector<domain::Seat> find_by_flight(
        const domain::FlightId& flight_number) = 0;

    virtual std::optional<domain::Seat> find_by_id(
        const domain::FlightId& flight_number,
        const domain::SeatId& seat_id) = 0;

    virtual void save(const domain::Seat& seat) = 0;
};

} // namespace airline::repository
