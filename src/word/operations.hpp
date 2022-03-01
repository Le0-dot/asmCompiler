#pragma once

enum class operations {
    add, and_op, ld, ldi, ldr, lea,
    not_op, st, sti, str, jmp, jsr,
    br, trap, tgetc, toutc, tputs, tin,
    thalt, tinu16, toutu16
};
