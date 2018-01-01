
#include "Execute.h"

#include <iostream>

int Execute::spell_effect(const int resource_level) const {
    // TODO: Find weapon skill for mainhand.
    AttackResult* result = roll->get_melee_ability_result(300);

    if (result->is_miss()) {
        add_fail_stats("Miss");
    }
    // TODO: Apply Overpower
    if (result->is_dodge()) {
        add_fail_stats("Dodge");
    }
    if (result->is_parry()) {
        add_fail_stats("Parry");
    }

    int damage_dealt = 600 + 15 * resource_level;

    // TODO: Apply Flurry
    if (result->is_critical()) {
        // TODO: Remove hardcoding of 2/2 Impale.
        damage_dealt *= 2.2;
        add_success_stats("Critical", damage_dealt);
    }
    else if (result->is_hit())
        add_success_stats("Hit", damage_dealt);

    add_gcd_event();

    return resource_level;
}