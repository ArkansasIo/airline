#pragma once

#include "airline/domain.hpp"

#include <optional>

namespace airline::repository {

class ReservationRepository {
public:
    virtual ~ReservationRepository() = default;

    virtual bool exists(const domain::ReservationId& id) = 0;
    virtual std::optional<domain::Reservation> find_by_id(
        const domain::ReservationId& id) = 0;
    virtual void save(const domain::Reservation& reservation) = 0;
    virtual void remove(const domain::ReservationId& id) = 0;
};

} // namespace airline::repository
