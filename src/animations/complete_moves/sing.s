.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ notesParticle, 0x9006
.equ notes2Particle, 0x900A
.equ notes3Particle, 0x900B
.equ tempSprite, 0x9007
.equ tx, 0x9008
.equ ty, 0x9009

.global SingAnimation
SingAnimation:
    fastsetbattlers
    copyvar tx targetx
    copyvar ty targety
    addfadeplatformbg
    spritetobg target 8 8
    blendsemitransparent 13 3
    sideof attacker
    if2 0 call playerUsingSing
    if2 1 call opponentUsingSing
    loadspritefull notesSprite notesPalette notesOam
    copyvar notesParticle LASTRESULT
    loadspritefull notes2Sprite notes2Palette notesOam
    copyvar notes2Particle LASTRESULT
    loadspritefull notes3Sprite notes3Palette notesOam
    copyvar notes3Particle LASTRESULT
    hidehpbars
    beginfade 3 0xFFFF FADETO true 8
    call singNote1
    call singNote
    call singNote2
    call singNote
    call singNote3
    call singNote
    call singNote4
    call singNote
    call singNote5
    call singNote
    call singNote6
    call singNote
    call singNote1
    call singNote
    call singNote2
    call singNote
    call singNote3
    call singNote
    call singNote4
    call singNote
    call singNote5
    call singNote
    call singNote6
    call singNote
    pauseframes 50
    beginfade 3 0xFFFF FADEFROM true 8
    BLOCKCMD
    spritesetposition target tx ty
    clearblending
    showsprite target
    OPENCMD
    hidebg 1
    spritebgclear target
    showhpbars
    startscript animSleep false
    waitthread 1
    deletesprite notesParticle
    deletesprite notes2Particle
    deletesprite notes3Particle
    end

singNote1:
    loadsprite notesSprite notesPalette notesOam
    copyvar tempSprite LASTRESULT
    setframessprite 0 tempSprite note1Frame
    return

singNote2:
    loadsprite notesSprite notes2Palette notesOam
    copyvar tempSprite LASTRESULT
    setframessprite 0 tempSprite note2Frame
    return

singNote3:
    loadsprite notesSprite notes3Palette notesOam
    copyvar tempSprite LASTRESULT
    setframessprite 0 tempSprite note3Frame
    return

singNote4:
    loadsprite notesSprite notesPalette notesOam
    copyvar tempSprite LASTRESULT
    setframessprite 0 tempSprite note4Frame
    return

singNote5:
    loadsprite notesSprite notes2Palette notesOam
    copyvar tempSprite LASTRESULT
    setframessprite 0 tempSprite note5Frame
    return

singNote6:
    loadsprite notesSprite notes3Palette notesOam
    copyvar tempSprite LASTRESULT
    setframessprite 0 tempSprite note6Frame
    return

singNote:
    BLOCKCMD
    rendersprite tempSprite attackerx attackery nullrsf
    movewave tempSprite target 2 3 60
    runtask TaskSpriteSingColors tempSprite 0 0 0
    OPENCMD
    return

playerUsingSing:
    addvar targetx 48
    subvar targety 48
    spritesetposition target targetx targety
    return

opponentUsingSing:
    subvar targetx 48
    addvar targety 48
    spritesetposition target targetx targety
    return


.pool
