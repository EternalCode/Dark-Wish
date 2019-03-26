.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ guillotineLeft, 0x9006
.equ guillotineRight, 0x9007
.equ coeffA, 0x9008
.equ coeffB, 0x9009

.global GuillotineAnimation
GuillotineAnimation:
    fastsetbattlers
    loadspritefull guillotineSprite guillotinePalette guillotineOam
    copyvar guillotineRight LASTRESULT
    loadspritefull guillotineLeftSprite guillotineLeftPalette guillotineOam
    copyvar guillotineLeft LASTRESULT
    spritepriority target 2
    spritepriority guillotineRight 1
    spritepriority guillotineLeft 3
    hidehpbars
    BLOCKCMD
    animatesprite guillotineLeft guillotineGrowAffine 0
    animatesprite guillotineRight guillotineGrowAffine 0
    OPENCMD
    BLOCKCMD
    addvar targety 10
    subvar targetx 24
    rendersprite guillotineLeft targetx targety guillotineGrowAffine
    addvar targetx 48
    addvar targety 3
    rendersprite guillotineRight targetx targety guillotineGrowAffine
    movesprite guillotineLeft 0 0xFFFF 18 false
    movesprite guillotineRight 0 0xFFFF 18 true
    OPENCMD
    wait
    BLOCKCMD
    spritepriority target 0
    spritepriority guillotineLeft 3
    spritepriority guillotineRight 3
    spritepriority attacker 0
    OPENCMD
    setvar coeffA 0
    setvar coeffB 16
    spritesblendall coeffA coeffB
    setprioritybg 3 2

fadeLoop:
    compare coeffA 16
    BLOCKCMD
    if1 0x1 goto showGuillotinesAtIdea
    addvar coeffA 1
    subvar coeffB 1
    spritesblendall coeffA coeffB
    OPENCMD
    goto fadeLoop


showGuillotinesAtIdea:
    OPENCMD
    BLOCKCMD
    fastsetbattlers
    subvar targety 6
    subvar targetx 48
    spritesetposition guillotineLeft targetx targety
    addvar targety 3
    addvar targetx 96
    spritesetposition guillotineRight targetx targety
    animatesprite guillotineLeft guillotineTiltRightAffine 0
    animatesprite guillotineRight guillotineTiltLeftAffine 0
    OPENCMD
    clearblending
    setprioritybg 3 3
    spritepriority guillotineLeft 3
    spritepriority target 2
    spritepriority guillotineRight 1
    movesprite guillotineLeft 4 0 10 false
    movesprite guillotineRight 0xFFFC 0 10 false
    pauseframes 5
    BLOCKCMD
    setvar gLASTRESULT 0x00FA
    startscript FireworkAnimationNoBlend true
    quakesprite target 2 0 4 2 true
    spritecallback guillotineLeft SCB_SpriteBlink
    spritecallback guillotineRight SCB_SpriteBlink
    OPENCMD
    wait
    waittask TaskCreateSmallFireworkImpact
    deletesprite guillotineLeft
    deletesprite guillotineRight
    spritepriority target 3
    spritepriority attacker 3
    showhpbars
    end

.pool
