.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impactParticle, 0x9006

.global SurfAnimation
SurfAnimation:
    fastsetbattlers
    // load the surf wave...probably using 2 parts
    semitransparent LASTRESULT
    // load surf bg
    spritetobg target 8 8
    blendsemitransparent 8 8
    
    end

.pool
