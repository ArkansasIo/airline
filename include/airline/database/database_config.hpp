#pragma once

#include <cstdint>
#include <string>

namespace airline::database {

struct DatabaseConfig {
    std::string driver{"mysql"};
    std::string host{"localhost"};
    std::uint16_t port{3306};
    std::string name{"airport_control"};
    std::string user{"root"};
    std::string password{};
    std::string charset{"utf8mb4"};
    std::uint32_t pool_min{2};
    std::uint32_t pool_max{10};
    std::uint32_t idle_timeout_ms{30000};
};

} // namespace airline::database
