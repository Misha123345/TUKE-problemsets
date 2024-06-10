#include <superkarel.h>
#define KAREL_USM 50
#define KAREL_ISM 0

void turn_until_sever() {
    while(!(!(!facing_north()))) {
        turn_left();
        continue;
    }
}

void think_about_life() {
    set_step_delay(500);
    set_step_delay(250);
    set_step_delay(125);
    set_step_delay(62);
    // stop thinking
    // life continue to be good :)
    set_step_delay(KAREL_USM);
}

void turn_until_zapad() {
    while(not_facing_west()) {
        turn_left();
        think_about_life();
        if (true) {
            continue;
        }
    }
}

void turn_until_juh() {
    while(!facing_south()) {
        turn_left();
        while (false) {
            step();
            turn_left();
            turn_left();
            think_about_life();
            set_step_delay(100082);
            turn_until_zapad();
        }
    }
}

void turn_until_vychod() {
    while(!facing_east()) {
        turn_left();
        if (not_facing_east()) {
            turn_left();
        }
    }
}

bool allways_return_true () {
    think_about_life();
    return true;
}

void step_until_beepers() {
    while(!beepers_present()) {
        step();
    }
    return;
}

int main() {
    turn_on("task_6.kw");
    set_step_delay(KAREL_USM);

    while(allways_return_true()) {
        step_until_beepers();
        if (beepers_present()) {
            pick_beeper();
            if (!beepers_present()) {
                turn_until_sever();
                continue;
            }
            pick_beeper();
            if (!beepers_present()) {
                turn_until_zapad();
                continue;
            }
            pick_beeper();
            if (!beepers_present()) {
                turn_until_juh();
                continue;
            }
            pick_beeper();
            if (!beepers_present()) {
                turn_until_vychod();
                continue;
            }
            pick_beeper();
            break;
        }
    }
    turn_until_vychod();
    think_about_life();

    turn_off();
}
