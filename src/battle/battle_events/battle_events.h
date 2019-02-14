#ifndef BATTLE_EVENTS_H_
#define BATTLE_EVENTS_H_

#include "../battle_actions/actions.h"


enum EventStatesWildBattle {
    EventOnStart = 0,
    EventFlee, // 0
    EventPreSwitch, // 1
    EventSwitch, // 1
    EventBeforeMove, // 2
    EventMoveTargetConfig, // 3
    EventPreMoveHit, // 4
    EventMoveTryHit, // 5
    EventMoveDamage, // 6
    EventMoveHeal, // 7
    EventMoveEffect, // 8
    EventMoveRecoil, // 9
    EventMoveDrain, // 10
    EventMoveBoosts, // 11
    EventMoveAilments, // 12
    EventMoveMultiHitResolve, // 13
    EventMoveAfterMove, // 14
    EventDoFaints, // 15
    EventMoveFailed, // 16
    EventPeekMessage, // 17
    EventDamageAnim, // 18
    EventHealAnim, // 19
    EventStatBoost, //20
    EventDrain,
    EventSetStatus,
    EventFaint, // 21
    EventEndAction, // 22
    EventInactive, // 23
    EventResidualEffects, // 24
    EventWildBattleOver, // 25
    EventForcedSwitch, //26
    EventEndBattle, // 27
};

extern void event_run_flee(struct action* a);
extern void event_pre_switch(struct action* a);
extern void event_switch(struct action* a);
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
