/*
 * reservation_edit.h
 * C structures mirroring the reservation database tree so the
 * console program (access navigation control.cpp) can edit the same
 * hierarchy that the MySQL schema and API expose.
 *
 *   reservation (tree root)
 *     -> reservation_node        (sub-node / subtree)
 *        -> reservation_branch   (branch)
 *           -> reservation_sub_branch (sub-branch)
 *              -> reservation_module (modular leaf)
 */
#ifndef RESERVATION_EDIT_H
#define RESERVATION_EDIT_H

#include <stdlib.h>
#include <string.h>

/* Modular leaf unit */
struct reservation_module
{
    char *module_name;
    char *module_value;
    struct reservation_module *next;
};

/* Sub-branch */
struct reservation_sub_branch
{
    char *sub_branch_name;
    struct reservation_module *modules;
    struct reservation_sub_branch *next;
};

/* Branch */
struct reservation_branch
{
    char *branch_name;
    struct reservation_sub_branch *sub_branches;
    struct reservation_branch *next;
};

/* Sub-node / subtree */
struct reservation_node
{
    char *node_name;
    char *seat_assignment;
    int available;
    struct reservation_branch *branches;
    struct reservation_node *next;     /* sibling */
    struct reservation_node *children; /* subtree */
};

/* Reservation tree root */
struct reservation_tree
{
    char *reservation_id; /* unique key */
    char *passenger_id;
    char *flight_number;
    double cost;
    struct reservation_node *nodes;
    struct reservation_tree *next;
};

/* Helper: allocate a modifiable copy of a string */
static inline char *res_strdup(const char *src)
{
    size_t n = (src ? strlen(src) : 0) + 1;
    char *dst = (char *)malloc(n);
    if (dst && src)
        memcpy(dst, src, n);
    else if (dst)
        dst[0] = 0;
    return dst;
}

#endif /* RESERVATION_EDIT_H */
