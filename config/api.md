# Airport Control - Reservation Tree API (v1)

Base URL: `http://localhost:8080/api/v1` (see `config/config.json`)

## Tree structure

```
reservation (tree root)
└── reservation_node        (sub-node / subtree)
    └── reservation_branch  (branch)
        └── reservation_sub_branch (sub-branch)
            └── reservation_module (modular leaf)
```

## Endpoints

### Reservations (tree)
| Method | Path | Description |
|--------|------|-------------|
| GET    | `/reservations` | List all reservations |
| GET    | `/reservations/{id}` | Get one reservation |
| POST   | `/reservations` | Create reservation. Body: `{ "passenger_id", "flightnumber", "cost" }` |
| DELETE | `/reservations/{id}` | Delete reservation and its whole tree |

### Sub-nodes / subtrees
| Method | Path | Description |
|--------|------|-------------|
| GET    | `/reservations/{id}/nodes` | List sub-nodes of a reservation |
| POST   | `/reservations/{id}/nodes` | Add sub-node. Body: `{ "node_name", "node_type", "parent_node_id", "seat_assignment" }` |
| PATCH  | `/nodes/{node_id}` | Update sub-node (e.g. toggle `available`) |
| DELETE | `/nodes/{node_id}` | Delete sub-node and everything under it |

### Branches
| Method | Path | Description |
|--------|------|-------------|
| GET    | `/nodes/{node_id}/branches` | List branches under a sub-node |
| POST   | `/nodes/{node_id}/branches` | Add branch. Body: `{ "branch_name", "status" }` |
| DELETE | `/branches/{branch_id}` | Delete branch |

### Sub-branches
| Method | Path | Description |
|--------|------|-------------|
| GET    | `/branches/{branch_id}/sub-branches` | List sub-branches |
| POST   | `/branches/{branch_id}/sub-branches` | Add sub-branch. Body: `{ "sub_branch_name" }` |
| DELETE | `/sub-branches/{id}` | Delete sub-branch |

### Modules (modular leaves)
| Method | Path | Description |
|--------|------|-------------|
| GET    | `/sub-branches/{id}/modules` | List modules |
| POST   | `/sub-branches/{id}/modules` | Add module. Body: `{ "module_name", "module_value" }` |
| DELETE | `/modules/{module_id}` | Delete module |

### Full tree
| Method | Path | Description |
|--------|------|-------------|
| GET    | `/reservations/{id}/tree` | Returns the entire reservation tree in one nested JSON document |

### Flights, passengers & settings
| Method | Path | Description |
|--------|------|-------------|
| GET    | `/flights` | All flights, sorted by departure time/date |
| GET    | `/flights/{number}/passengers` | Passengers on a flight, sorted by last name |
| GET    | `/settings` | Current settings (from `app_setting` table) |
| PUT    | `/settings` | Update settings. Body: `{ "key": "value", ... }` |

## Business rules
- A reservation requires an **existing** passenger ID and flight number.
- Passenger and flight unique IDs are never duplicated.
- Deleting a parent node cascades to its branches/sub-branches/modules.

## Example: full tree response

```json
GET /api/v1/reservations/R0001/tree
{
  "reservation_id": "R0001",
  "passenger_id": "P001",
  "flightnumber": "SW101",
  "cost": 245.00,
  "nodes": [
    {
      "node_id": 1,
      "node_name": "Main Itinerary",
      "node_type": "ROOT",
      "seat_assignment": "12A",
      "branches": [
        {
          "branch_id": 1,
          "branch_name": "Checked Baggage",
          "sub_branches": [
            {
              "sub_branch_id": 1,
              "sub_branch_name": "Standard Bag",
              "modules": [
                { "module_id": 1, "module_name": "bag_weight_limit", "module_value": "23kg" },
                { "module_id": 2, "module_name": "bag_fee", "module_value": "0.00" }
              ]
            }
          ]
        }
      ]
    }
  ]
}
```
