#ifndef POKEMON_TYPES_H_
#define POKEMON_TYPES_H_

enum PokemonType {
    TYPE_NORMAL = 0,
    TYPE_FIGHTING = 1,
    TYPE_FLYING = 2,
    TYPE_POISON = 3,
    TYPE_GROUND = 4,
    TYPE_ROCK = 5,
    TYPE_BUG = 6,
    TYPE_GHOST = 7,
    TYPE_STEEL = 8,
    TYPE_NONE = 9, /**< ??? Type */
    TYPE_FIRE = 10,
    TYPE_WATER = 11,
    TYPE_GRASS = 12,
    TYPE_ELECTRIC = 13,
    TYPE_PSYCHIC = 14,
    TYPE_ICE = 15,
    TYPE_DRAGON = 16,
    TYPE_DARK = 17,
    TYPE_FAIRY = 18,
    TYPE_MAX = 19,
};

extern const u8 TypeEffectivenessChart[361];
extern const pchar PkmnTypeNames[TYPE_MAX][13];

#endif /* POKEMON_TYPES_H_ */
