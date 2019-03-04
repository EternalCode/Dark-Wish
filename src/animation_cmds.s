@ -----------------------------------------------
@ General Defines
.equ true, 1
.equ false, 0
.equ attacker, 0x9000
.equ target, 0x9001
.equ attackerx, 0x9002
.equ targetx, 0x9003
.equ attackery, 0x9004
.equ targety, 0x9005
.equ varmax, 0x9013
.equ gLASTRESULT, 0x800D
.equ LASTRESULT, 0x900D
@.equ <, 0
@.equ ==, 1
@.equ >, 2
@.equ <=, 3

@ -----------------------------------------------

@Loads the sprite Id into var_800D
.macro loadspritefull graphics palette oam
.byte 0
.byte 0
.byte 0
.byte 0
.word \graphics
.word \palette
.word \oam
.endm

@pass var which holds your sprite Id
.macro deletesprite var
.byte 1
.byte 0
.hword \var
.endm

.macro rendersprite var varx vary anim
.byte 2
.byte 0
.hword \var
.hword \varx
.hword \vary
.word \anim
.endm

.macro copyvar dst src
.byte 3
.byte 0
.byte 0
.byte 0
.hword \dst
.hword \src
.endm

.macro setvar var value
.byte 4
.byte 0
.byte 0
.byte 0
.hword \var
.hword \value
.endm

.macro addvar var value
.byte 5
.byte 0
.byte 0
.byte 0
.hword \var
.hword \value
.endm

.macro subvar var value
.byte 6
.byte 0
.byte 0
.byte 0
.hword \var
.hword \value
.endm

.macro mulvar var value
.byte 7
.byte 0
.byte 0
.byte 0
.hword \var
.hword \value
.endm

.macro divvar var value
.byte 8
.byte 0
.byte 0
.byte 0
.hword \var
.hword \value
.endm

.macro goto addr
.byte 9
.byte 0
.byte 0
.byte 0
.word \addr
.endm

.macro movesprite var xoff yoff frames boolwait
.byte 10
.byte 0
.hword \var
.hword \xoff
.hword \yoff
.hword \frames
.byte \boolwait
.byte 0
.endm

.macro wait
.byte 11
.byte 0
.byte 0
.byte 0
.endm

.macro startscript script boolcopyvars
.byte 12
.byte 0
.byte 0
.byte \boolcopyvars
.word \script
.endm

.macro pauseframes frames
.byte 13
.byte 0
.hword \frames
.endm

.macro animatesprite var rotscaletable index
.byte 14
.byte \index
.hword \var
.word \rotscaletable
.endm

.macro showsprite var
.byte 15
.byte 0
.hword \var
.endm

.macro hidesprite var
.byte 16
.byte 0
.hword \var
.endm

.macro setspritepal var palette
.byte 17
.byte 0
.hword \var
.word \palette
.endm

.macro spritetobg var tilesw tilesh
.byte 18
.byte 0
.hword \var
.hword \tilesw
.hword \tilesh
.endm

.macro spritebgclear var
.byte 19
.byte 0
.hword \var
.endm

@Coefficient A and Coefficient B.
.macro spriteblend coa cob
.byte 20
.byte 0
.byte \coa
.byte \cob
.endm

.macro excludeblend var
.byte 21
.byte 0
.hword \var
.endm

.macro includeblend var
.byte 31
.byte 0
.hword \var
.endm

@ -----------------------------------------------
@ Defines so Darken and Lighten BG inclusion
.equ INBG0, (1 << 0)
.equ INBG1, (1 << 1)
.equ INBG2, (1 << 2)
.equ INBG3, (1 << 3)
@ -----------------------------------------------

.macro darken factor incbgs
.byte 22
.byte \factor
.byte \incbgs
.byte 0
.endm

.macro lighten factor incbgs
.byte 23
.byte \factor
.byte \incbgs
.byte 0
.endm

.macro clearpalbuffer
.byte 24
.byte 0
.byte 0
.byte 0
.endm

.macro addpalbuffer var boolincbgs
.byte 25
.byte \boolincbgs
.hword \var
.endm

@ -----------------------------------------------
@ Defines for pal fading
.equ FADETO, 0
.equ FADEFROM, 1
@ -----------------------------------------------

.macro beginfade transitionspeed blendcolor fadedirection boolwaitfade amount
.byte 26
.byte \transitionspeed
.hword \blendcolor
.byte \fadedirection
.byte \boolwaitfade
.byte \amount
.byte 0
.endm

.macro fadespritebg transitionspeed blendcolor fadedirection boolwaitfade amount
.byte 53
.byte \transitionspeed
.hword \blendcolor
.byte \fadedirection
.byte \boolwaitfade
.byte \amount
.byte 0
.endm


@ -----------------------------------------------
@ Defines for the sin wave effect
.equ BOUNCE, 0xF
.equ SINWAVE, 0xFF
@ -----------------------------------------------
.macro movewave spritea spriteb amplitude frequency wavetype
.byte 27
.byte 0
.hword \spritea
.hword \spriteb
.byte \amplitude
.byte \frequency
.byte \wavetype
.byte 0
.byte 0
.byte 0
.endm

.macro loadbg2 palsize tileset tilemap palette
.byte 28
.byte 0
.hword \palsize
.word \tileset
.word \tilemap
.word \palette
.endm

.macro showbg bgid
.byte 29
.byte \bgid
.byte 0
.byte 0
.endm

.macro hidebg bgid
.byte 30
.byte \bgid
.byte 0
.byte 0
.endm

.macro flashsprite var flashdur timestoflash boolwait color
.byte 32
.byte 0
.byte \flashdur
.byte \timestoflash
.hword \var
.byte \boolwait
.hword \color
.byte 0
.byte 0
.byte 0
.endm

.macro getattacker
.byte 33
.byte 0
.byte 0
.byte 0
.endm

.macro getdefender
.byte 34
.byte 0
.byte 0
.byte 0
.endm

.macro getattackercoords
.byte 35
.byte 0
.byte 0
.byte 0
.endm

.macro getdefendercoords
.byte 36
.byte 0
.byte 0
.byte 0
.endm

.macro quakebg bgid xquake yquake times delay boolwait
.byte 37
.byte \bgid
.byte \xquake
.byte \yquake
.byte \times
.byte \delay
.byte \boolwait
.byte 0
.endm

.macro call script
.byte 38
.byte 0
.byte 0
.byte 0
.word \script
.endm

.macro return
.byte 39
.endm

.macro if2 condition btype script
.byte 40
.byte \condition
.byte 0
.byte 0
.byte 38
.byte 0
.byte 0
.byte 0
.word script
.endm

.macro if1 condition btype script
.byte 40
.byte \condition
.byte 0
.byte 0
.byte 9
.byte 0
.byte 0
.byte 0
.word \script
.endm

.macro compare var value
.byte 41
.byte 0
.hword \var
.hword \value
.byte 0
.byte 0
.endm

.macro comparevars varA varB
.byte 42
.byte 0
.hword \varA
.hword \varB
.byte 0
.byte 0
.endm

.macro sideof var
.byte 43
.byte 0
.hword \var
.endm

.macro fastsetbattlers
.byte 44
.byte 0
.byte 0
.byte 0
.endm

.macro shakehpbox var
.byte 45
.byte 0
.hword \var
.endm

.macro random min max
.byte 46
.byte 0
.hword \min
.hword \max
.byte 0
.byte 0
.endm

.macro addvars vara varb
.byte 47
.byte 0
.byte 0
.byte 0
.hword \vara
.hword \varb
.endm

.macro subvars vara varb
.byte 48
.byte 0
.byte 0
.byte 0
.hword \vara
.hword \varb
.endm

@vararg priv[1]
@arg priv[2]
@arg2 priv[3]
@arg3 priv[4]
.macro runtask task vararg arg arg2 arg3
.byte 49
.byte \arg
.hword \arg2
.hword \arg3
.hword \vararg
.word \task
.endm

.macro quakesprite var xquake yquake times delay boolwait
.byte 50
.byte 0
.hword \var
.byte \xquake
.byte \yquake
.byte \times
.byte \delay
.byte \boolwait
.byte 0
.byte 0
.byte 0
.endm

.macro setframessprite framenum var frames
.byte 51
.byte \framenum
.hword \var
.word \frames
.endm

.macro loadsprite graphics palette oam
.byte 52
.byte 0
.byte 0
.byte 0
.word \graphics
.word \palette
.word \oam
.endm

.macro waittask task
.byte 54
.byte 0
.byte 0
.byte 0
.word \task
.endm

@speed is the amount of frames to travel the distance
.macro horizontalArcTranslate startAngle endAngle varSrc varDst speed
.byte 55
.byte \speed
.hword \startAngle
.hword \endAngle
.hword \varSrc
.hword \varDst
.byte 0
.byte 0
.endm

.macro waitanimation var
.byte 56
.byte 0
.hword \var
.endm

.macro waitaffineanimation var
.byte 57
.byte 0
.hword \var
.endm

.macro spritecallback var callback
.byte 58
.byte 0
.hword \var
.word \callback
.endm

.macro hidehpbars
.byte 59
.byte 0
.byte 0
.byte 0
.endm

.macro showhpbars
.byte 60
.byte 0
.byte 0
.byte 0
.endm

.macro orbit spriteA spriteB duration width height dir speed boolwait booldelete waveoffset
.byte 61
.byte \boolwait
.hword \spriteA
.hword \spriteB
.hword \duration
.byte \width
.byte \height
.byte \dir
.byte \speed
.byte \booldelete
.byte \waveoffset
.byte 0
.byte 0
.endm

@ -----------------------------------------------
@ Defines for pal fading
.equ LEFT, 1
.equ RIGHT, 2
@ -----------------------------------------------
.macro movebg id xOffset yOffset duration direction boolwait
.byte 62
.byte \id
.hword \xOffset
.hword \yOffset
.byte \duration
.byte \boolwait
.byte \direction
.byte 0
.byte 0
.byte 0
.endm

.macro copyactionpriv var id
.byte 63
.byte \id
.hword \var
.endm

.macro spriteblend2 var coefficient color
.byte 64
.byte \coefficient
.hword \var
.hword \color
.byte 0
.byte 0
.endm

.macro spritebufferposition var bufferx buffery
.byte 65
.byte 0
.hword \var
.hword \bufferx
.hword \buffery
.endm

.macro playmessage bank move id effect
.byte 66
.byte 0
.byte 0
.byte 0
.hword \bank
.hword \move
.hword \id
.hword \effect
.endm

.macro spriteafterimage var tilesw tilesh bgid
.byte 67
.byte \bgid
.hword \var
.hword \tilesw
.hword \tilesh
.endm

.macro BLOCKCMD
.byte 0xFE
.endm

.macro OPENCMD
.byte 0xFD
.endm

.macro end
.byte 0xFF
.endm
