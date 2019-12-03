.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impactParticle, 0x9006
.equ surf_left_particle, 0x9007
.equ surf_right_particle, 0x9008
.equ counter, 0x9009
.equ counter2, 0x900A


.global SurfAnimation
SurfAnimation:
    fastsetbattlers
    setbgpos 2 0 0
    // load side dependant assets
    sideof attacker
    if2 0x0 goto playersurfload
    if2 0x1 goto opponentsurfload

    // load side independant assets
    loadspritefull bimpact1Sprite bimpact1Palette bimpact1Oam
    copyvar impactParticle LASTRESULT
    spriteblend2 impactParticle 10 0x7FB5

    // prepare surf wave to blend with attacker
    spritetobg attacker 8 8
    blendsemitransparent 6 10
    hidehpbars

    // apply wave growth animation for surf sprites
    BLOCKCMD
    animatesprite surf_left_particle surf_player_leftAffine 0
    animatesprite surf_right_particle surf_player_leftAffine 0
    subvar attackerx 32
    addvar attackery 29
    addpalbuffer surf_left_particle false
    addpalbuffer surf_right_particle false
    OPENCMD
    BLOCKCMD
    startscript fadespritein_surf true
    rendersprite surf_left_particle attackerx attackery surf_player_leftAffine
    addvar attackerx 64
    rendersprite surf_right_particle attackerx attackery surf_player_leftAffine
    movesprite surf_right_particle 0 0xFFFE 10 false
    movesprite surf_right_particle 0xFFFF 0 7 false
    movesprite surf_left_particle 0 0xFFFE 10 false
    movesprite surf_left_particle 1 0 7 false
    OPENCMD
    beginfade 1 0xFFFF FADETO true 10
    BLOCKCMD
    movesprite surf_right_particle 0 2 10 false
    movesprite surf_left_particle 0 2 10 false
    OPENCMD
    beginfade 1 0xFFFF FADEFROM true 10
    waitthread 1
    deletesprite surf_left_particle
    deletesprite surf_right_particle
    showsprite attacker
    spritebgclear attacker
    runtask task_surfbgfade 0 0 0 0
    showbg 2
    sideof attacker
    if2 0x0 goto playersurfbgmove
    if2 0x1 goto opponentsurfbgmove
    setvar gLASTRESULT 0x7FB5
    startscript FireworkAnimationNoBlend true
    semitransparent target
    spritepriority attacker 2
    setprioritybg 2 2
    BLOCKCMD
    rendersprite impactParticle targetx targety nullrsf
    spritetobg impactParticle 4 4
    showbg 1
    startscript hidebgafter10frames true
    OPENCMD
    pauseframes 7
    quakesprite target 2 0 5 1 false
    waitthread 1
    BLOCKCMD
    hidebg 2
    OPENCMD
    clearblending
    BLOCKCMD
    spritepriority attacker 3
    nontransparent attacker
    nontransparent target
    deletesprite surf_left_particle
    deletesprite surf_right_particle
    setbgpos 2 0 0
    OPENCMD
    showhpbars
    end

playersurfload:
    loadspritefull surf_player_leftSprite surf_player_leftPalette surf_player_leftOam
    copyvar surf_left_particle LASTRESULT
    semitransparent LASTRESULT
    loadspritefull surf_player_rightSprite surf_player_rightPalette surf_player_leftOam
    copyvar surf_right_particle LASTRESULT
    semitransparent LASTRESULT
    loadbg2 32 surfbgTiles surfbgMap surfbgPal
    return

opponentsurfload:
    subvar attackery 13
    loadspritefull surf_opp_leftSprite surf_opp_leftPalette surf_player_leftOam
    copyvar surf_left_particle LASTRESULT
    semitransparent LASTRESULT
    loadspritefull surf_opp_rightSprite surf_opp_rightPalette surf_player_leftOam
    copyvar surf_right_particle LASTRESULT
    semitransparent LASTRESULT
    loadbg2 32 surfbg_oppTiles surfbg_oppMap surfbg_oppPal
    return

playersurfbgmove:
    movebg 2 0xFFFC 4 36 UP false
    return

opponentsurfbgmove:
    movebg 2 0xFFFC 4 36 DOWN false
    return


fadespritein_surf:
    BLOCKCMD
    setvar counter 6
    setvar counter2 10

surf_loop:
    OPENCMD
    BLOCKCMD
    addvar counter 2
    subvar counter2 2
    compare counter 16
    OPENCMD
    if1 0x1 goto reverse_surf_blend_start
    BLOCKCMD
    blendsemitransparent counter counter2
    goto surf_loop

reverse_surf_blend_start:
    BLOCKCMD
    pauseframes 5

reverse_surf_blend:
    OPENCMD
    BLOCKCMD
    addvar counter2 2
    subvar counter 2
    compare counter 0
    OPENCMD
    if1 0x1 goto endscr_surf
    BLOCKCMD
    blendsemitransparent counter counter2
    goto reverse_surf_blend

endscr_surf:
    end

hidebgafter10frames:
    pauseframes 7
    hidebg 1
    deletesprite impactParticle
    end

.pool
