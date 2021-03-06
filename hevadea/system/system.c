#include <raylib.h>
#include <stddef.h>

#include "hevadea/camera.h"
#include "hevadea/logger.h"

#include "hevadea/system/system.h"
#include <hevadea/system/debug_entity_colider.h>
#include <hevadea/system/debug_entity_motion.h>
#include <hevadea/system/entity_motion.h>
#include <hevadea/system/entity_pathfinding.h>
#include <hevadea/system/entity_sprite.h>
#include <hevadea/system/entity_sprite_animated.h>
#include <hevadea/system/entity_wandering.h>
#include <hevadea/system/player_input.h>

static system_t *systems[] = {
    &system_player_input,
    &system_entity_motion,
    &system_entity_sprite,
    &system_entity_sprite_animated,
    &system_pathfinding,
    &system_wandering,

    &system_debug_entity_motion,
    &system_debug_entity_colider,
    NULL,
};

typedef struct
{
    system_t *sys;
    gametime_t gametime;
} system_process_callback_args_t;

IterationDecision system_process_callback(system_process_callback_args_t *args, entity_instance_t *entity)
{
    bool is_entity_processable = entity_has_component(entity, args->sys->mask);

    if (is_entity_processable)
    {
        args->sys->process(entity, args->gametime);
    }

    return ITERATION_CONTINUE;
}

void system_process(system_type_t type, gametime_t gametime)
{
    for (int i = 0; systems[i]; i++)
    {
        if (systems[i]->type == type)
        {
            system_process_callback_args_t args;

            args.sys = systems[i];
            args.gametime = gametime;

            entity_iterate_all(&args, (EntityIterateCallback)system_process_callback);
        }
    }
}