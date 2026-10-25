-- =====================================================================
-- Airport Control / Airline Reservation Database Schema
-- Reservation hierarchy:
--   reservation (root / tree)
--     -> reservation_node        (sub-node / subtree)
--        -> reservation_branch   (branch)
--           -> reservation_sub_branch (sub-branch)
--              -> reservation_module    (modular leaf units)
-- =====================================================================

CREATE DATABASE IF NOT EXISTS airport_control
  CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
USE airport_control;

-- ---------------------------------------------------------------------
-- Core entity tables (unique keys, no duplicated data)
-- ---------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS airline (
  airline_id     INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
  airlinename    VARCHAR(80)  NOT NULL UNIQUE
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS flight (
  flight_id          INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
  flightnumber       VARCHAR(80)  NOT NULL UNIQUE,
  date_of_flight     DATE         NOT NULL,
  departure_location VARCHAR(80)  NOT NULL,
  arrival_location   VARCHAR(80)  NOT NULL,
  take_off_time      TIME         NOT NULL,
  arrival_time       TIME         NOT NULL,
  total_seats        INT UNSIGNED NOT NULL DEFAULT 0,
  seats_booked       INT UNSIGNED NOT NULL DEFAULT 0,
  airline_id         INT UNSIGNED NOT NULL,
  CONSTRAINT fk_flight_airline
    FOREIGN KEY (airline_id) REFERENCES airline(airline_id)
    ON DELETE CASCADE,
  INDEX idx_flight_departure (date_of_flight, take_off_time)
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS passenger (
  passenger_id  VARCHAR(20)  PRIMARY KEY,          -- unique key
  name_suffix   VARCHAR(6),
  name          VARCHAR(120) NOT NULL,
  address       VARCHAR(200),
  city          VARCHAR(60),
  gender        ENUM('M','F','O'),
  date_of_birth DATE,
  weight_kg     DECIMAL(5,2)
) ENGINE=InnoDB;

-- ---------------------------------------------------------------------
-- Reservation root (tree)
-- ---------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS reservation (
  reservation_id VARCHAR(20) PRIMARY KEY,           -- unique key
  passenger_id   VARCHAR(20) NOT NULL,
  flightnumber   VARCHAR(80) NOT NULL,
  cost           DECIMAL(10,2) NOT NULL DEFAULT 0.00,
  created_at     TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  CONSTRAINT fk_res_passenger
    FOREIGN KEY (passenger_id) REFERENCES passenger(passenger_id),
  CONSTRAINT fk_res_flight
    FOREIGN KEY (flightnumber) REFERENCES flight(flightnumber)
) ENGINE=InnoDB;

-- ---------------------------------------------------------------------
-- Reservation tree -> sub-node (subtree)
-- ---------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS reservation_node (
  node_id        INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
  reservation_id VARCHAR(20)  NOT NULL,
  parent_node_id INT UNSIGNED NULL,                 -- allows nested subtrees
  node_name      VARCHAR(80)  NOT NULL,
  node_type      ENUM('ROOT','SUBTREE','BRANCH','SUB_BRANCH','MODULE')
                 NOT NULL DEFAULT 'SUBTREE',
  seat_assignment VARCHAR(80),
  available      TINYINT(1) NOT NULL DEFAULT 1,
  CONSTRAINT fk_node_reservation
    FOREIGN KEY (reservation_id) REFERENCES reservation(reservation_id)
    ON DELETE CASCADE,
  CONSTRAINT fk_node_parent
    FOREIGN KEY (parent_node_id) REFERENCES reservation_node(node_id)
    ON DELETE CASCADE
) ENGINE=InnoDB;

-- ---------------------------------------------------------------------
-- Reservation branch (stored under a sub-node)
-- ---------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS reservation_branch (
  branch_id   INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
  node_id     INT UNSIGNED NOT NULL,
  branch_name VARCHAR(80) NOT NULL,
  status      ENUM('OPEN','CLOSED','CANCELLED') NOT NULL DEFAULT 'OPEN',
  CONSTRAINT fk_branch_node
    FOREIGN KEY (node_id) REFERENCES reservation_node(node_id)
    ON DELETE CASCADE
) ENGINE=InnoDB;

-- ---------------------------------------------------------------------
-- Reservation sub-branch (stored under a branch)
-- ---------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS reservation_sub_branch (
  sub_branch_id   INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
  branch_id       INT UNSIGNED NOT NULL,
  sub_branch_name VARCHAR(80) NOT NULL,
  status          ENUM('OPEN','CLOSED','CANCELLED') NOT NULL DEFAULT 'OPEN',
  CONSTRAINT fk_subbranch_branch
    FOREIGN KEY (branch_id) REFERENCES reservation_branch(branch_id)
    ON DELETE CASCADE
) ENGINE=InnoDB;

-- ---------------------------------------------------------------------
-- Modular unit (leaf) attached to a sub-branch
-- ---------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS reservation_module (
  module_id      INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
  sub_branch_id  INT UNSIGNED NOT NULL,
  module_name    VARCHAR(80) NOT NULL,
  module_value   VARCHAR(255),
  created_at     TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  CONSTRAINT fk_module_subbranch
    FOREIGN KEY (sub_branch_id) REFERENCES reservation_sub_branch(sub_branch_id)
    ON DELETE CASCADE
) ENGINE=InnoDB;

-- ---------------------------------------------------------------------
-- Configuration / settings / options (used by config.json + API)
-- ---------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS app_setting (
  setting_key   VARCHAR(80) PRIMARY KEY,
  setting_value VARCHAR(255) NOT NULL,
  updated_at    TIMESTAMP DEFAULT CURRENT_TIMESTAMP
                 ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB;

-- ---------------------------------------------------------------------
-- Seed default settings
-- ---------------------------------------------------------------------
INSERT INTO app_setting (setting_key, setting_value) VALUES
  ('database.host',    'localhost'),
  ('database.port',    '3306'),
  ('database.name',    'airport_control'),
  ('api.base_url',     'http://localhost:8080/api/v1'),
  ('api.max_retries',  '3'),
  ('seats.default',    '150'),
  ('currency',         'USD')
ON DUPLICATE KEY UPDATE setting_value = VALUES(setting_value);

-- ---------------------------------------------------------------------
-- Handy view: full reservation tree flattened
-- ---------------------------------------------------------------------
CREATE OR REPLACE VIEW v_reservation_tree AS
SELECT r.reservation_id,
       r.passenger_id,
       r.flightnumber,
       r.cost,
       n.node_id,
       n.parent_node_id,
       n.node_name,
       n.node_type,
       b.branch_id,
       b.branch_name,
       sb.sub_branch_id,
       sb.sub_branch_name,
       m.module_id,
       m.module_name,
       m.module_value
FROM reservation r
LEFT JOIN reservation_node n        ON n.reservation_id = r.reservation_id
LEFT JOIN reservation_branch b      ON b.node_id = n.node_id
LEFT JOIN reservation_sub_branch sb ON sb.branch_id = b.branch_id
LEFT JOIN reservation_module m      ON m.sub_branch_id = sb.sub_branch_id;
