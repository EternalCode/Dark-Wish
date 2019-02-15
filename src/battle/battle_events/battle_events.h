#ifndef BATTLE_EVENTS_H_
#define BATTLE_EVENTS_H_

#include "../battle_actions/actions.h"


enum EventStatesWildBattle {
    EventOnStart = 0,
    EventFlee, // 0
    EventPreSwitch, // 1
    EventSwitch, // 1
    EventPostSwitch, // 2
    EventBeforeMove, // 3
    EventMoveTargetConfig, // 4
    EventPreMoveHit, // 5
    EventMoveTryHit, // 6
    EventMoveDamage, // 7
    EventMoveHeal, // 8
    EventMoveEffect, // 9
    EventMoveRecoil, // 10
    EventMoveDrain, // 11
    EventMoveBoosts, // 12
    EventMoveAilments, // 13
    EventMoveMultiHitResolve, // 14
    EventMoveAfterMove, // 15
    EventDoFaints, // 16
    EventMoveFailed, // 17
    EventPeekMessage, // 18
    EventDamageAnim, // 19
    EventHealAnim, // 20
    EventStatBoost, //21
    EventDrain, // 22
    EventSetStatus, // 23
    EventFaint, // 24
    EventEndAction, // 25
    EventInactive, // 26
    EventResidualEffects, // 27
    EventWildBattleOver, // 28
    EventForcedSwitch, //29
    EventEndBattle, // 30
};

extern void event_run_flee(struct action* a);
extern void event_pre_switch(struct action* a);
extern void event_switch(struct action* a);
extern void event_after_switch(struct action* a);

extern void event_on_start(struct action* a);
extern void event_before_move(struct action* a);
extern void event_pre_move_hit(struct action* a);
extern void event_config_move_hitlist(struct action* a);
extern void event_pre_move_hit(struct action* current_action);
extern void event_move_tryhit_external(struct action* current_action);
extern void event_move_damage(struct action* current_action);
extern void event_move_heal(struct action* current_action);
extern void event_move_effect(struct action* current_action);
extern void event_move_recoil(struct action* current_action);
extern void event_move_drain(struct action* current_action);
extern void event_move_boosts(struct action* current_action);
extern void event_move_ailments(struct action* current_action);
extern void event_multi_hit(struct action* current_action);
extern void event_after_move(struct action* current_action);
extern void event_fainted(struct action* current_action);

extern void event_move_failed(struct action* current_action);
extern void event_peek_message(struct action* current_action);
extern void init_damage(struct action* current_action);
extern void init_heal(struct action* current_action);
extern void event_stat_boost(struct action* current_action);
extern void event_drain(struct action* current_action);
extern void event_set_status(struct action* current_move);
extern void event_faint(struct action* current_action);
extern void event_set_inactive(struct action* current_action);
extern void event_residual_effects(struct action* current_action);
extern void wild_battle_status_update(struct action* current_action);
extern void event_forced_switch(struct action* current_action);
extern void end_battle(struct action* a);

#endif /* BATTLE_EVENTS_H_ */
