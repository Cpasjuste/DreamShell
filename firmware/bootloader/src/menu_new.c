//
// Created by cpasjuste on 28/01/2020.
//

#include <kos.h>
#include "drawing.h"

static uint32 last_buttons = 0;

static int menu_input() {

    maple_device_t *cont = NULL;
    cont_state_t *state = NULL;

    cont = maple_enum_type(0, MAPLE_FUNC_CONTROLLER);

    if (cont) {
        state = (cont_state_t *) maple_dev_status(cont);

        if (!state) {
            return 1;
        }

        if (last_buttons != state->buttons) {
            if (state->buttons & CONT_DPAD_UP) {
            }
            if (state->buttons & CONT_DPAD_DOWN) {
            }
            if ((state->buttons & CONT_DPAD_LEFT) || (state->buttons & CONT_DPAD_RIGHT)) {
            }
            if (state->buttons & CONT_A) {
            }
            if (state->buttons & CONT_B) {
            }
            if (state->buttons & CONT_Y) {
            }
            if (state->buttons & CONT_X) {
            }

            last_buttons = state->buttons;
        }
    }

    return 1;
}

void menu_run() {

    draw_init();

    while (menu_input()) {

        draw_start();

        draw_box_outline(32, 32, (float) vid_mode->width - 64, (float) vid_mode->height - 64, 100,
                         COL_BLUE, COL_YELLOW, 4);

        draw_string(36, 36, 101, COL_BLUE_LIGHT, "Hello World");

        draw_end();

    }
}
