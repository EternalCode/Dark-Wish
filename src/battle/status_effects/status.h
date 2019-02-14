#ifndef STATUS_DATA_H_
#define STATUS_DATA_H_

#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"

typedef void (*StatusOnStart)(u8 bank);
typedef void (*StatusOnBeforeMove)(u8 bank);
typedef u16 (*StatusOnModSpeed)(u8 bank, u16 speed_stat);
typedef void (*StatusOnHit)(u8 bank);
typedef void (*StatusOnInflict)(u8 bank);
typedef void (*StatusOnResidual)(u8 bank);

struct status_ailments {
	StatusOnInflict on_inflict;
};


extern struct status_ailments statuses[];


#endif /* STATUS_DATA_H_ */
