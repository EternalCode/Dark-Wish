.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ sandParticle, 0x9006
.equ TempSprite, 0x9007
.equ counter, 0x9008

.global SandAttackAnimation
SandAttackAnimation:
    fastsetbattlers
    loadspritefull sandattackSprite sandattackPalette sandattackOam
    copyvar sandParticle LASTRESULT
    spritetobg target 8 8
    spritepriority attacker 0
    blendsemitransparent 10 6
    setvar counter 0
    addvar attackery 16

loopSand:
    compare counter 6
    if1 0x1 goto finish
    BLOCKCMD
    compare counter 2
    if2 0x1 call quakemon
    loadsprite sandattackSprite sandattackPalette sandattackOam
    copyvar TempSprite LASTRESULT
    semitransparent TempSprite
    rendersprite TempSprite attackerx attackery nullrsf
    setframessprite 0 TempSprite sandattackFrames
    OPENCMD
    spritemovedst 20 TempSprite target
    addvar counter 1
    goto loopSand

quakemon:
    quakebg 1 2 0 6 2 false
    return

finish:
    pauseframes 10
    clearblending
    showsprite target
    hidebg 1
    spritebgclear target
    spritepriority attacker 3
    deletesprite sandParticle
    end

.pool
