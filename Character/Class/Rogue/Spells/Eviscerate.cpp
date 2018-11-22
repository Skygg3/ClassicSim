#include "CharacterStats.h"
#include "Equipment.h"
#include "Eviscerate.h"
#include "Random.h"
#include "Rogue.h"
#include "Weapon.h"

Eviscerate::Eviscerate(Character* pchar) :
    Spell("Eviscerate", "Assets/ability/Ability_rogue_eviscerate.png", pchar, RestrictedByGcd::Yes, 0.0, ResourceType::Energy, 35),
    rogue(dynamic_cast<Rogue*>(pchar)),
    evisc_range(new Random(904, 1012))
{
    this->damage_ranges_per_combo_point = {
        QPair<unsigned, unsigned>(224, 332),
        QPair<unsigned, unsigned>(394, 502),
        QPair<unsigned, unsigned>(564, 672),
        QPair<unsigned, unsigned>(734, 842),
        QPair<unsigned, unsigned>(904, 1012),
    };
}

Eviscerate::~Eviscerate() {
    delete evisc_range;
}

bool Eviscerate::is_ready_spell_specific() const {
    return rogue->get_combo_points() > 0;
}

void Eviscerate::spell_effect() {
    rogue->exit_stealth();

    const int result = roll->get_melee_ability_result(rogue->get_mh_wpn_skill(), pchar->get_stats()->get_mh_crit_chance());

    add_gcd_event();

    if (result == AttackResult::MISS) {
        increment_miss();
        rogue->lose_energy(static_cast<unsigned>(resource_cost));
        return;
    }
    if (result == AttackResult::DODGE) {
        increment_dodge();
        rogue->lose_energy(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }
    if (result == AttackResult::PARRY) {
        increment_parry();
        rogue->lose_energy(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }

    set_evisc_range();
    double ap_modifier = rogue->get_stats()->get_melee_ap() * (rogue->get_combo_points() * 0.03);
    double damage_dealt = damage_after_modifiers(evisc_range->get_roll() + ap_modifier);

    if (result == AttackResult::CRITICAL) {
        damage_dealt = round(damage_dealt * rogue->get_ability_crit_dmg_mod());
        rogue->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());
    }
    else if (result == AttackResult::HIT) {
        rogue->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());
    }

    rogue->lose_energy(static_cast<unsigned>(resource_cost));
    rogue->spend_combo_points();
}

void Eviscerate::set_evisc_range() {
    int index = static_cast<int>(rogue->get_combo_points()) - 1;
    assert(index >= 0 && index <= damage_ranges_per_combo_point.size() -1);

    unsigned min = damage_ranges_per_combo_point[index].first;
    unsigned max = damage_ranges_per_combo_point[index].second;

    evisc_range->set_new_range(min, max);
}
