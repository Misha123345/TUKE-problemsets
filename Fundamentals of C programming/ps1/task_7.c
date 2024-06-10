#include <superkarel.h>
#define KAREL_USM 100
#define KAREL_ISM 0

void turn_opposite() {
    set_step_delay(KAREL_ISM);
    turn_left();
    set_step_delay(KAREL_USM);
    turn_left();
}

void turn_3_times() {
    set_step_delay(KAREL_ISM);
    turn_left();
    turn_left();
    set_step_delay(KAREL_USM);
    turn_left();
}

void place_2_beepers() {
    put_beeper();
    put_beeper();
}

void check_and_place_beeper() {
    if (left_is_clear()) {
        turn_left();
        step();
        place_2_beepers();
        turn_opposite();
        step();
        turn_left();
    }
}

void place_beepers_in_start() {
    do {
        check_and_place_beeper();
        step();
    } while(front_is_clear());
    check_and_place_beeper();
}

void go_belong_left_side() {
    while(true) {
        if(!left_is_clear()) {
            if (front_is_clear()) {
                step();
                if (beepers_present()) {
                    break;
                }
            } else {
                turn_3_times();
            }
        } else if (left_is_clear()) {
            turn_left();
            step();
            if (beepers_present()) {
                break;
            }
        }
    }
}

// teraz nepouzivam, ale nech bude
void go_belong_right_side() {
    while(true) {
        if (right_is_blocked()) {
            if (front_is_clear()) {
                step();
                if (beepers_present()) {
                    pick_beeper();
                    break;
                }
            } else {
                turn_left();
            }
        } else if (right_is_clear()) {
            turn_3_times();
            step();
            if (beepers_present()) {
                break;
            }
        }
    }
}

bool tunel_is_not_checked() {
    if (beepers_present()) {
        pick_beeper();
        if (beepers_present()) {
            put_beeper();
            return true;
        }
        else {
            put_beeper();
            return false;
        }
    } else {
        return false;
    }
}

void check_one_tunel() {
    if (left_is_clear()) {
        turn_left();
        step();
        if (tunel_is_not_checked()) {
            pick_beeper();
            go_belong_left_side();
            pick_beeper();
        } else {
            turn_opposite();
        }
        step();
        turn_left();
    }
}

void run_until_meet_the_wall() {
    while(front_is_clear()) {
        step();
    }
}

void check_all_tunels() {
    while (front_is_clear()) {
        check_one_tunel();
        if (front_is_clear()) {
            step();
        }
    }
    check_one_tunel();
}

int main() {
    turn_on("task_7.kw");
    set_step_delay(KAREL_USM);

    place_beepers_in_start();
    turn_opposite();
    while(front_is_clear()) {
        step();
    }
    turn_opposite();

    check_all_tunels();

    turn_opposite();
    while(front_is_clear()) {
        step();
    }
    turn_opposite();

    check_all_tunels();

    turn_off();
}
