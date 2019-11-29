.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ fireParticle, 0x9006
.equ fireParticle2, 0x9007


.global EmberAnimation
EmberAnimation:
    fastsetbattlers
    BLOCKCMD
    loadspritefull smallfireSprite smallfirePalette smallfireAffOam
    copyvar fireParticle LASTRESULT
    spritetobg target 8 8
    spriteblend 8 8
    spritesetposition fireParticle attackerx attackery
    addfadebg1
    OPENCMD
    BLOCKCMD
    addvar targety 12
    spritesetposition target targetx targety
    spritemovedstdelay 30 fireParticle target 1
    runtask TaskSpriteFaceSprite fireParticle 0 target 0
    setframessprite 0 fireParticle smallfireFrames
    OPENCMD
    showsprite fireParticle
    pauseframes 26
    deletesprite fireParticle
    beginfade 1 0x1CF8 FADETO true 10
    quakebg 1 2 0 2 2 false
    BLOCKCMD
    loadspritefull smallFireSprite smallfirePalette smallfireOam
    copyvar fireParticle LASTRESULT
    setframessprite 0 fireParticle smallfireFrames
    spritepriority fireParticle 1
    semitransparent fireParticle
    OPENCMD
    rendersprite fireParticle targetx targety nullrsf
    pauseframes 10
    deletesprite fireParticle
    beginfade 1 0x1CF8 FADEFROM true 10
    clearblending
    subvar targety 12
    spritesetposition target targetx targety
    showsprite target
    spritebgclear target
    end



.pool
