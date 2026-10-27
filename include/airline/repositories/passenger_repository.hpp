#pragma once

#include "airline/domain.hpp"

#include <optional>

namespace airline::repository {

class PassengerRepository {
public:
    virtual ~PassengerRepository() = default;

    virtual std::optional<domain::Passenger> find_by_id(
        const domain::PassengerId& id) = 0;

    virtual void save(const domain::Passenger& passenger) = 0;
};

} // namespace airline::repository
