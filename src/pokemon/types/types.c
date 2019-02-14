#include <pokeagb/pokeagb.h>

const pchar PkmnTypeNames[19][13] = {
    _("Normal"),
    _("Fighting"),
    _("Flying"),
    _("Poison"),
    _("Ground"),
    _("Rock"),
    _("Bug"),
    _("Ghost"),
    _("Steel"),
    _("Typeless"),
    _("Fire"),
    _("Water"),
    _("Grass"),
    _("Electric"),
    _("Psychic"),
    _("Ice"),
    _("Dragon"),
    _("Dark"),
    _("Fairy"),
};

// percentages to mod
// 100 - Normal damage
// 200 - Super effective damage
// 50 - Not very effective damage
// 0 - Immune

const u8 TypeEffectivenessChart[361] = {

/* Normal */
	100, // Normal
	200, // Fighting
	100, // Flying
	100, // Poison
	100, // Ground
	100, // Rock
	100, // Bug
	0, // Ghost
	100, // Steel
	100, // ???
	100, // Fire
	100, // Water
	100, // Grass
	100, // Electric
	100, // Psychic
	100, // Ice
	100, // Dragon
	100, // Dark
	100, // Fairy

/* Fighting */
	100, // Normal
	100, // Fighting
	200, // Flying
	100, // Poison
	100, // Ground
	50, // Rock
	50, // Bug
	100, // Ghost
	100, // Steel
	100, // ???
	100, // Fire
	100, // Water
	100, // Grass
	100, // Electric
	200, // Psychic
	100, // Ice
	100, // Dragon
	50, // Dark
	200, // Fairy

/* Flying */
	100, // Normal
	50, // Fighting
	100, // Flying
	100, // Poison
	0, // Ground
	200, // Rock
	50, // Bug
	100, // Ghost
	100, // Steel
	100, // ???
	100, // Fire
	100, // Water
	50, // Grass
	200, // Electric
	100, // Psychic
	200, // Ice
	100, // Dragon
	100, // Dark
	100, // Fairy

/* Poison */
	100, // Normal
	50, // Fighting
	100, // Flying
	50, // Poison
	200, // Ground
	100, // Rock
	50, // Bug
	100, // Ghost
	100, // Steel
	100, // ???
	100, // Fire
	100, // Water
	50, // Grass
	100, // Electric
	200, // Psychic
	100, // Ice
	100, // Dragon
	100, // Dark
	50, // Fairy

/* Ground */
	100, // Normal
	100, // Fighting
	100, // Flying
	50, // Poison
	100, // Ground
	50, // Rock
	100, // Bug
	100, // Ghost
	100, // Steel
	100, // ???
	100, // Fire
	200, // Water
	200, // Grass
	0, // Electric
	100, // Psychic
	200, // Ice
	100, // Dragon
	100, // Dark
	100, // Fairy

/* Rock */
	50, // Normal
	200, // Fighting
	50, // Flying
	50, // Poison
	200, // Ground
	100, // Rock
	100, // Bug
	100, // Ghost
	200, // Steel
	100, // ???
	50, // Fire
	200, // Water
	200, // Grass
	100, // Electric
	100, // Psychic
	100, // Ice
	100, // Dragon
	100, // Dark
	100, // Fairy

/* Bug */
	100, // Normal
	50, // Fighting
	200, // Flying
	100, // Poison
	50, // Ground
	200, // Rock
	100, // Bug
	100, // Ghost
	100, // Steel
	100, // ???
	200, // Fire
	100, // Water
	50, // Grass
	100, // Electric
	100, // Psychic
	100, // Ice
	100, // Dragon
	100, // Dark
	100, // Fairy

/* Ghost */
	0, // Normal
	0, // Fighting
	100, // Flying
	50, // Poison
	100, // Ground
	100, // Rock
	50, // Bug
	200, // Ghost
	100, // Steel
	100, // ???
	100, // Fire
	100, // Water
	100, // Grass
	100, // Electric
	100, // Psychic
	100, // Ice
	100, // Dragon
	200, // Dark
	100, // Fairy

/* Steel */
	50, // Normal
	200, // Fighting
	50, // Flying
	0, // Poison
	200, // Ground
	50, // Rock
	50, // Bug
	100, // Ghost
	50, // Steel
	100, // ???
	200, // Fire
	100, // Water
	50, // Grass
	100, // Electric
	50, // Psychic
	50, // Ice
	50, // Dragon
	100, // Dark
	50, // Fairy

/* ??? */
	100, // Normal
	100, // Fighting
	100, // Flying
	100, // Poison
	100, // Ground
	100, // Rock
	100, // Bug
	100, // Ghost
	100, // Steel
	100, // ???
	100, // Fire
	100, // Water
	100, // Grass
	100, // Electric
	100, // Psychic
	100, // Ice
	100, // Dragon
	100, // Dark
	100, // Fairy

/* Fire */
	100, // Normal
	100, // Fighting
	100, // Flying
	100, // Poison
	200, // Ground
	200, // Rock
	50, // Bug
	100, // Ghost
	50, // Steel
	100, // ???
	50, // Fire
	200, // Water
	50, // Grass
	100, // Electric
	100, // Psychic
	50, // Ice
	100, // Dragon
	100, // Dark
	50, // Fairy

/* Water */
	100, // Normal
	100, // Fighting
	100, // Flying
	100, // Poison
	100, // Ground
	100, // Rock
	100, // Bug
	100, // Ghost
	50, // Steel
	100, // ???
	50, // Fire
	50, // Water
	200, // Grass
	200, // Electric
	100, // Psychic
	50, // Ice
	100, // Dragon
	100, // Dark
	100, // Fairy

/* Grass */
	100, // Normal
	100, // Fighting
	200, // Flying
	200, // Poison
	50, // Ground
	100, // Rock
	200, // Bug
	100, // Ghost
	100, // Steel
	100, // ???
	200, // Fire
	50, // Water
	50, // Grass
	50, // Electric
	100, // Psychic
	200, // Ice
	100, // Dragon
	100, // Dark
	100, // Fairy

/* Electric */
	100, // Normal
	100, // Fighting
	50, // Flying
	100, // Poison
	200, // Ground
	100, // Rock
	100, // Bug
	100, // Ghost
	50, // Steel
	100, // ???
	100, // Fire
	100, // Water
	100, // Grass
	50, // Electric
	100, // Psychic
	100, // Ice
	100, // Dragon
	100, // Dark
	100, // Fairy

/* Psychic */
	100, // Normal
	50, // Fighting
	100, // Flying
	100, // Poison
	100, // Ground
	100, // Rock
	200, // Bug
	200, // Ghost
	100, // Steel
	100, // ???
	100, // Fire
	100, // Water
	100, // Grass
	100, // Electric
	50, // Psychic
	100, // Ice
	100, // Dragon
	200, // Dark
	100, // Fairy

/* Ice */
	100, // Normal
	200, // Fighting
	100, // Flying
	100, // Poison
	100, // Ground
	200, // Rock
	100, // Bug
	100, // Ghost
	200, // Steel
	100, // ???
	200, // Fire
	100, // Water
	100, // Grass
	100, // Electric
	100, // Psychic
	50, // Ice
	100, // Dragon
	100, // Dark
	100, // Fairy

/* Dragon */
	100, // Normal
	100, // Fighting
	100, // Flying
	100, // Poison
	100, // Ground
	100, // Rock
	100, // Bug
	100, // Ghost
	100, // Steel
	100, // ???
	50, // Fire
	50, // Water
	50, // Grass
	50, // Electric
	100, // Psychic
	200, // Ice
	200, // Dragon
	100, // Dark
	200, // Fairy

/* Dark */
	100, // Normal
	200, // Fighting
	100, // Flying
	100, // Poison
	100, // Ground
	100, // Rock
	200, // Bug
	50, // Ghost
	100, // Steel
	100, // ???
	100, // Fire
	100, // Water
	100, // Grass
	100, // Electric
	0, // Psychic
	100, // Ice
	100, // Dragon
	50, // Dark
	200, // Fairy

/* Fairy */
	100, // Normal
	50, // Fighting
 	100, // Flying
	200, // Poison
	100, // Ground
	100, // Rock
	50, // Bug
	100, // Ghost
	200, // Steel
	100, // ???
	100, // Fire
	100, // Water
	100, // Grass
	100, // Electric
	100, // Psychic
	100, // Ice
	0, // Dragon
	50, // Dark
	100, // Fairy
};


extern const pchar PkmnTypeNames[19][13];
