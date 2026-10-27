# Airline Reservation System Architecture

## Current transition

The repository now contains two layers:

1. **Legacy console application** - the original linked-list implementation remains available as `airport_legacy` so existing behavior is not discarded during migration.
2. **Modern core services** - new C++20 domain types and booking services live under `include/airline/` and `src/`.

## Domain model

```text
Airline
  └── Flight
       ├── Seat*
       └── Reservation*
             └── Passenger
```

Identifiers are explicit string types at the domain boundary:

- `FlightId`
- `PassengerId`
- `ReservationId`
- `SeatId`

Money is represented as integer cents (`MoneyCents`) rather than floating-point currency values.

## Booking invariants

`BookingService` enforces the following in-memory rules:

- passenger must exist;
- flight must exist;
- reservation ID must be unique;
- requested seat must exist on the requested flight;
- requested seat must be available;
- a flight cannot exceed its configured seat capacity;
- successful booking marks the seat unavailable and associates it with the passenger;
- cancellation releases the assigned seat and removes the reservation.

The same invariants should later be enforced by the MySQL repository layer inside a database transaction.

## Build

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

To build only the modern core and tests without the legacy application:

```bash
cmake -S . -B build -DBUILD_LEGACY_CONSOLE=OFF
cmake --build build
ctest --test-dir build --output-on-failure
```

## Next migration stages

1. Add repository interfaces for airlines, flights, passengers, reservations, and seats.
2. Add a MySQL implementation using prepared statements and transactions.
3. Replace the binary `airline.txt` persistence path with repository-backed persistence.
4. Implement the documented REST API against the service layer.
5. Add authentication, authorization, validation, structured logging, and rate limiting before network deployment.
6. Add CI for Windows and Linux builds plus unit tests and sanitizers.
