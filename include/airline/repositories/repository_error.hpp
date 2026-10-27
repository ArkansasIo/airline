#pragma once

#include <stdexcept>
#include <string>

namespace airline::repository {

class RepositoryError : public std::runtime_error {
public:
    explicit RepositoryError(const std::string& message)
        : std::runtime_error(message) {}
};

} // namespace airline::repository
