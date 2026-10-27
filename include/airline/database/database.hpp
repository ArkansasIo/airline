#pragma once

#include "airline/database/database_config.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace airline::database {

struct QueryResult {
    std::vector<std::string> column_names;
    std::vector<std::vector<std::string>> rows;
};

class Database {
public:
    virtual ~Database() = default;

    virtual void open(const DatabaseConfig& config) = 0;
    virtual void close() noexcept = 0;
    virtual bool is_open() const noexcept = 0;

    virtual void begin_transaction() = 0;
    virtual void commit() = 0;
    virtual void rollback() noexcept = 0;

    virtual std::uint64_t execute(const std::string& sql) = 0;
    virtual QueryResult query(const std::string& sql) = 0;
};

class TransactionGuard {
public:
    explicit TransactionGuard(Database& database) : database_(database) {
        database_.begin_transaction();
    }

    TransactionGuard(const TransactionGuard&) = delete;
    TransactionGuard& operator=(const TransactionGuard&) = delete;

    void commit() {
        database_.commit();
        committed_ = true;
    }

    ~TransactionGuard() {
        if (!committed_) {
            database_.rollback();
        }
    }

private:
    Database& database_;
    bool committed_{false};
};

} // namespace airline::database
