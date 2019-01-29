#include <pokeagb/pokeagb.h>

extern void dprintf(const char * str, ...);

void DrawMetatile(s32 metatileLayerType, u16 *metatiles, u16 offset)
{

    switch (metatileLayerType) {
    case 3:
        // triple layer
        gBGTilemapBuffers3[offset] = metatiles[0];
        gBGTilemapBuffers3[offset + 1] = metatiles[1];
        gBGTilemapBuffers3[offset + 0x20] = metatiles[2];
        gBGTilemapBuffers3[offset + 0x21] = metatiles[3];

        gBGTilemapBuffers2[offset] = metatiles[4];
        gBGTilemapBuffers2[offset + 1] = metatiles[5];
        gBGTilemapBuffers2[offset + 0x20] = metatiles[6];
        gBGTilemapBuffers2[offset + 0x21] = metatiles[7];

        gBGTilemapBuffers1[offset] = metatiles[8];
        gBGTilemapBuffers1[offset + 1] = metatiles[9];
        gBGTilemapBuffers1[offset + 0x20] = metatiles[10];
        gBGTilemapBuffers1[offset + 0x21] = metatiles[11];
        break;
    case 1: // LAYER_TYPE_
        // Draw metatile's bottom layer to the bottom background layer.
        gBGTilemapBuffers3[offset] = metatiles[0];
        gBGTilemapBuffers3[offset + 1] = metatiles[1];
        gBGTilemapBuffers3[offset + 0x20] = metatiles[2];
        gBGTilemapBuffers3[offset + 0x21] = metatiles[3];

        // Draw transparent tiles to the middle background layer.
        gBGTilemapBuffers2[offset] = 0;
        gBGTilemapBuffers2[offset + 1] = 0;
        gBGTilemapBuffers2[offset + 0x20] = 0;
        gBGTilemapBuffers2[offset + 0x21] = 0;

        // Draw metatile's top layer to the top background layer.
        gBGTilemapBuffers1[offset] = metatiles[4];
        gBGTilemapBuffers1[offset + 1] = metatiles[5];
        gBGTilemapBuffers1[offset + 0x20] = metatiles[6];
        gBGTilemapBuffers1[offset + 0x21] = metatiles[7];
        break;
    case 2:  // LAYER_TYPE_COVERED_BY_OBJECTS
        // Draw metatile's bottom layer to the bottom background layer.
        gBGTilemapBuffers3[offset] = metatiles[0];
        gBGTilemapBuffers3[offset + 1] = metatiles[1];
        gBGTilemapBuffers3[offset + 0x20] = metatiles[2];
        gBGTilemapBuffers3[offset + 0x21] = metatiles[3];

        // Draw metatile's top layer to the middle background layer.
        gBGTilemapBuffers2[offset] = metatiles[4];
        gBGTilemapBuffers2[offset + 1] = metatiles[5];
        gBGTilemapBuffers2[offset + 0x20] = metatiles[6];
        gBGTilemapBuffers2[offset + 0x21] = metatiles[7];

        // Draw transparent tiles to the top background layer.
        gBGTilemapBuffers1[offset] = 0;
        gBGTilemapBuffers1[offset + 1] = 0;
        gBGTilemapBuffers1[offset + 0x20] = 0;
        gBGTilemapBuffers1[offset + 0x21] = 0;
        break;
    case 0: // LAYER_TYPE_NORMAL
        // Draw garbage to the bottom background layer.
        gBGTilemapBuffers3[offset] = 0x3014;
        gBGTilemapBuffers3[offset + 1] = 0x3014;
        gBGTilemapBuffers3[offset + 0x20] = 0x3014;
        gBGTilemapBuffers3[offset + 0x21] = 0x3014;

        // Draw metatile's top layer to the top background layer, which covers event object sprites.
        gBGTilemapBuffers2[offset] = metatiles[0];
        gBGTilemapBuffers2[offset + 1] = metatiles[1];
        gBGTilemapBuffers2[offset + 0x20] = metatiles[2];
        gBGTilemapBuffers2[offset + 0x21] = metatiles[3];

        // Draw metatile's bottom layer to the middle background layer.
        gBGTilemapBuffers1[offset] = metatiles[4];
        gBGTilemapBuffers1[offset + 1] = metatiles[5];
        gBGTilemapBuffers1[offset + 0x20] = metatiles[6];
        gBGTilemapBuffers1[offset + 0x21] = metatiles[7];
        break;
    }
    bgid_mark_for_sync(1);
    bgid_mark_for_sync(2);
    bgid_mark_for_sync(3);
}
