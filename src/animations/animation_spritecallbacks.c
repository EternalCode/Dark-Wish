#include <pokeagb/pokeagb.h>
#include "animation_core.h"
#include "../global.h"
#include "../battle/battle_actions/actions.h"
#include "../battle/battle_data/battle_state.h"
#include "../battle/battle_data/pkmn_bank_stats.h"


void SCB_SpriteBlink(struct Sprite* sprite)
{
    sprite->invisible = !sprite->invisible;
}
