#include "SimSettings.h"

#include <QThread>

#include "RulesetControl.h"
#include "Utils/Check.h"

SimSettings::SimSettings() :
    current_phase(Content::Phase::Naxxramas),
    combat_length(300),
    combat_iterations_quick_sim(1000),
    combat_iterations_full_sim(10000),
    num_threads(QThread::idealThreadCount()),
    execute_threshold(0.2),
    ruleset_control(new RulesetControl()) {}

SimSettings::~SimSettings() {
    delete ruleset_control;
}

Content::Phase SimSettings::get_phase() const {
    return this->current_phase;
}

void SimSettings::set_phase(const Content::Phase phase) {
    current_phase = phase;
}

int SimSettings::get_combat_iterations_quick_sim() const {
    return this->combat_iterations_quick_sim;
}

int SimSettings::get_combat_length() const {
    return this->combat_length;
}

int SimSettings::get_combat_iterations_full_sim() const {
    return this->combat_iterations_full_sim;
}

void SimSettings::set_combat_length(const int combat_length) {
    this->combat_length = combat_length;
}

void SimSettings::set_combat_iterations_full_sim(const int combat_iterations) {
    this->combat_iterations_full_sim = combat_iterations;
}

void SimSettings::set_combat_iterations_quick_sim(const int combat_iterations) {
    this->combat_iterations_quick_sim = combat_iterations;
}

int SimSettings::get_num_threads_current() const {
    return num_threads;
}

int SimSettings::get_num_threads_max() const {
    return QThread::idealThreadCount();
}

void SimSettings::set_num_threads(const int num_threads) {
    if (num_threads < 1 || num_threads > get_num_threads_max())
        return;

    this->num_threads = num_threads;
}

void SimSettings::add_sim_option(SimOption::Name option) {
    check((option != SimOption::Name::NoScale), "Cannot add NoScale as sim option");
    sim_options.insert(option);
}

void SimSettings::set_sim_options(const QSet<SimOption::Name>& options) {
    check(!options.contains(SimOption::Name::NoScale), "Cannot add NoScale as sim option");
    sim_options = options;
}

void SimSettings::remove_sim_option(SimOption::Name option) {
    if (sim_options.contains(option))
        sim_options.remove(option);
}

bool SimSettings::option_active(SimOption::Name option) const {
    return sim_options.contains(option);
}

QSet<SimOption::Name> SimSettings::get_active_options() const {
    return sim_options;
}

void SimSettings::use_ruleset(const Ruleset ruleset, Character* pchar) {
    ruleset_control->use_ruleset(ruleset, pchar, this);
}

Ruleset SimSettings::get_ruleset() const {
    return ruleset_control->get_active_ruleset();
}

double SimSettings::get_execute_threshold() const {
    return this->execute_threshold;
}

void SimSettings::set_execute_threshold(const double threshold) {
    this->execute_threshold = threshold;
}
