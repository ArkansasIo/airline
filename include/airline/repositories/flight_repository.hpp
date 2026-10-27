#pragma once

#include "airline/domain.hpp"

#include <optional>

namespace airline::repository {

class FlightRepository {
public:
    virtual ~FlightRepository() = default;

    virtual std::optional<domain::Flight> find_by_number(
        const domain::FlightId& flight_number) = 0;

    virtual void save(const domain::Flight& flight) = 0;
};

} // namespace airline::repository
