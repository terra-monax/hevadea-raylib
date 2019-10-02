#pragma once

#include <hevadea/position.h>
#include <hevadea/utils.h>
#include <hevadea/vector.h>
#include <hevadea/rectangle.h>

typedef enum
{
    COMPONENT_PLAYER = 1 << 0,
    COMPONENT_MOTION = 1 << 1,
    COMPONENT_COLIDER = 1 << 2,

    __COMPONENT_COUNT,
} entity_component_t;

struct entity_blueprint_t;

typedef struct
{
    bool allocated;

    int components;
    position_t position;
    vector_t motion;
    rectangle_t colider;

    const struct entity_blueprint_t *blueprint;
} entity_instance_t;

typedef void (*entity_blueprint_construct_callback_t)(entity_instance_t *instance);

typedef struct entity_blueprint_t
{
    const char *name;
    entity_blueprint_construct_callback_t construct;
} entity_blueprint_t;

typedef unsigned int entity_t;

/* --- Entity logistic ------------------------------------------------------ */

entity_t entity_create(const entity_blueprint_t *blueprint, position_t position);

void entity_destroy(entity_t entity);

#define E(__entity) entity_instance(__entity)

entity_instance_t *entity_instance(entity_t entity);

const entity_blueprint_t *entity_blueprint(const char *name);

/* --- Entity iterators ----------------------------------------------------- */

typedef iterate_state_t (*entity_iterate_callback_t)(entity_t entity, void *arg);

void entity_iterate_all(entity_iterate_callback_t callback, void *arg);

/* --- Entity state --------------------------------------------------------- */

bool entity_has_component(entity_t entity, entity_component_t mask);

rectangle_t entity_get_bound(entity_t entity);