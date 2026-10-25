-- =====================================================================
-- Airport Control - Sample Dataset
-- Loads demo data into the reservation tree:
--   reservation -> reservation_node (subtree)
--               -> reservation_branch
--               -> reservation_sub_branch
--               -> reservation_module
-- =====================================================================
USE airport_control;

START TRANSACTION;

-- Airlines ------------------------------------------------------------
INSERT INTO airline (airlinename) VALUES ('SkyWings Air'), ('Delta Horizon');

-- Flights -------------------------------------------------------------
INSERT INTO flight (flightnumber, date_of_flight, departure_location,
                    arrival_location, take_off_time, arrival_time,
                    total_seats, seats_booked, airline_id) VALUES
  ('SW101', '2026-11-01', 'Little Rock', 'Dallas',    '08:30', '10:15', 150, 2, 1),
  ('SW205', '2026-11-02', 'Dallas',      'Denver',    '13:00', '15:45', 150, 1, 1),
  ('DH330', '2026-11-03', 'Denver',      'Seattle',   '09:10', '12:40', 180, 0, 2);

-- Passengers ----------------------------------------------------------
INSERT INTO passenger (passenger_id, name_suffix, name, address, city, gender, date_of_birth, weight_kg) VALUES
  ('P001', 'Mr',   'John Smith',   '12 Oak St',  'Little Rock', 'M', '1990-04-12', 78.50),
  ('P002', 'Mrs',  'Emma Jones',   '44 Pine Ave','Dallas',      'F', '1985-09-30', 65.20),
  ('P003', 'Dr',   'Alan Brown',   '7 Elm Rd',   'Denver',      'M', '1978-01-22', 82.10);

-- Reservations (tree roots) -------------------------------------------
INSERT INTO reservation (reservation_id, passenger_id, flightnumber, cost) VALUES
  ('R0001', 'P001', 'SW101', 245.00),
  ('R0002', 'P002', 'SW101', 245.00),
  ('R0003', 'P003', 'SW205', 310.50);

-- Sub-nodes / subtrees -------------------------------------------------
INSERT INTO reservation_node (reservation_id, parent_node_id, node_name, node_type, seat_assignment, available) VALUES
  ('R0001', NULL, 'Main Itinerary',  'ROOT',      '12A', 1),
  ('R0001', 1,    'Baggage Group',   'SUBTREE',   NULL,  1),
  ('R0002', NULL, 'Main Itinerary',  'ROOT',      '14C', 1),
  ('R0003', NULL, 'Main Itinerary',  'ROOT',      '02B', 1);

-- Branches -------------------------------------------------------------
INSERT INTO reservation_branch (node_id, branch_name, status) VALUES
  (2, 'Checked Baggage', 'OPEN'),
  (2, 'Carry-On',        'OPEN');

-- Sub-branches ----------------------------------------------------------
INSERT INTO reservation_sub_branch (branch_id, sub_branch_name, status) VALUES
  (1, 'Standard Bag',  'OPEN'),
  (1, 'Oversize Bag',  'OPEN'),
  (2, 'Personal Item', 'OPEN');

-- Modules (modular leaf units) ------------------------------------------
INSERT INTO reservation_module (sub_branch_id, module_name, module_value) VALUES
  (1, 'bag_weight_limit', '23kg'),
  (1, 'bag_fee',          '0.00'),
  (2, 'bag_weight_limit', '32kg'),
  (2, 'bag_fee',          '75.00'),
  (3, 'item_size',        '40x30x10cm');

COMMIT;
