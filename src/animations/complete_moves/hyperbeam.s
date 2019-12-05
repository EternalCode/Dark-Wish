.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ hbeamParticle, 0x9006
.equ counter, 0x9007
.equ TempSprite, 0x9008
.equ angle, 0x9009
.equ origin, 0x900A

.global HyperBeamAnimation
HyperBeamAnimation:
    fastsetbattlers
    getangle attackerx attackery targetx targety angle
    addfadeplatformbg
    addfadebg2
    spritetobg attacker 8 8
    showbg 1
    hidesprite attacker
    blendsemitransparent 12 4
    loadspritefull hyperbeam_originSprite hyperbeam_originPalette hyperbeam_originOam
    copyvar origin LASTRESULT
    loadbg2 32 hyperbeambgTiles hyperbeambgMap hyperbeambgPal
    hidehpbars
    beginfade 2 0 FADETO true 16
    showbg 2
    sideof attacker
    if1 0x0 goto playerHyperbeam
    if1 0x1 goto oppHyperbeam

playerHyperbeam:
    movebg 2 16 0 150 RIGHT false
    copyvar hbeamParticle LASTRESULT
    loadspritefull hyperbeam_playerSprite hyperbeam_playerPalette hyperbeamOAM
    beginfade 2 0 FADEFROM true 16
    BLOCKCMD
    addvar attackerx 10
    animatesprite origin hyperbeam_originAffine 0
    OPENCMD
    rendersprite origin attackerx attackery hyperbeam_originAffine
    loadsprite hyperbeamSprite hyperbeamPalette hyperbeamOAM
    spritesetposition LASTRESULT attackerx attackery
    spritecallbackargs LASTRESULT 70 angle 240 8 SpriteTravelDir_hyperbeam
    startscript QuakeSpriteHbeam true
    goto playerloopParticles

oppHyperbeam:
    movebg 2 16 0 150 LEFT false
    BLOCKCMD
    loadspritefull hyperbeamSprite hyperbeamPalette hyperbeamOAM
    copyvar hbeamParticle LASTRESULT
    subvar attackerx 10
    animatesprite origin hyperbeam_originAffine 0
    OPENCMD
    beginfade 2 0 FADEFROM true 16
    startscript QuakeSpriteHbeam true
    rendersprite origin attackerx attackery hyperbeam_originAffine

loopParticles:
    BLOCKCMD
    compare counter 30
    if1 0x1 goto finishAnim
    loadsprite hyperbeamSprite hyperbeamPalette hyperbeamOAM
    spritesetposition LASTRESULT attackerx attackery
    spritecallbackargs LASTRESULT 70 angle 240 8 SpriteTravelDir_hyperbeam
    setframessprite 0 LASTRESULT hyperbeamFrames
    addvar counter 1
    OPENCMD
    goto loopParticles

playerloopParticles:
    BLOCKCMD
    compare counter 30
    if1 0x1 goto sharedEnd
    loadsprite hyperbeam_playerSprite hyperbeam_playerPalette hyperbeamOAM
    spritesetposition LASTRESULT attackerx attackery
    spritecallbackargs LASTRESULT 70 angle 240 8 SpriteTravelDir_hyperbeam
    setframessprite 0 LASTRESULT hyperbeamFrames
    addvar counter 1
    OPENCMD
    goto playerloopParticles


finishAnim:
    loadsprite hyperbeamSprite hyperbeamPalette hyperbeamOAM
    spritesetposition LASTRESULT attackerx attackery
    spritecallbackargs LASTRESULT 70 angle 240 8 SpriteTravelDir_hyperbeam

sharedEnd:
    OPENCMD
    pauseframes 5
    deletesprite origin
    pauseframes 5
    beginfade 2 0 FADETO true 16
    hidebg 2
    beginfade 2 0 FADEFROM true 16
    deletesprite hbeamParticle
    showsprite attacker
    spritebgclear attacker
    setbgpos 2 0 0
    clearblending
    showhpbars
    end

QuakeSpriteHbeam:
    pauseframes 10
    quakesprite target 3 0 10 2 true
    end


.pool
