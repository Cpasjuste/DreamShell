//
// Created by cpasjuste on 28/01/2020.
//

#include <kos.h>
#include "drawing.h"

static uint32 last_buttons = 0;

extern void dc_load_callback();

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
            } else if (state->buttons & CONT_DPAD_DOWN) {
            } else if ((state->buttons & CONT_DPAD_LEFT) || (state->buttons & CONT_DPAD_RIGHT)) {
            } else if (state->buttons & CONT_A) {
            } else if (state->buttons & CONT_B) {
            } else if (state->buttons & CONT_Y) {
            } else if (state->buttons & CONT_X) {
            } else if (state->buttons & CONT_START) {
                dc_load_callback();
            }

            last_buttons = state->buttons;
        }
    }

    return 1;
}

void menu_run() {

    draw_init();

    Rect menuRect = {32, 32,
                     (float) vid_mode->width - 64, (float) vid_mode->height - 64};

    while (menu_input()) {

        draw_start();

        draw_box_outline(menuRect.left, menuRect.top, menuRect.width, menuRect.height, 100,
                         COL_BLUE, COL_YELLOW, 4);

        draw_string(menuRect.left + 16, menuRect.top + 16, 101, COL_WHITE, "Hello World");

        draw_end();
    }
}
