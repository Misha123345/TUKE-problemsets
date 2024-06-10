#include <superkarel.h>
#define KAREL_ULTRA_SPEED_MODE 50
#define KAREL_INFINITE_SPEED_MODE 0

void turn_3_times() {
    set_step_delay(KAREL_INFINITE_SPEED_MODE);
    turn_left();
    turn_left();
    set_step_delay(KAREL_ULTRA_SPEED_MODE);
    turn_left();
}

bool allways_return_true() {
    return true;
}

void turn_until_east() {
    while(not_facing_east()) {
        turn_left();
    }
}

void turn_until_west() {
    while(not_facing_west()) {
        turn_left();
    }
}

void turn_opposite() {
    set_step_delay(KAREL_INFINITE_SPEED_MODE);
    turn_left();
    set_step_delay(KAREL_ULTRA_SPEED_MODE);
    turn_left();
}

void step_until_the_wall() {
    while (front_is_clear()) {
        step();
    }
}

void step_and_pick_all_beepers() {
    while(front_is_clear()) {
        step();
        if (beepers_present()) {
            pick_beeper();
        }
    }
}

void return_and_place_beepers() {
    while(front_is_clear()) {
        turn_3_times();
        if (front_is_blocked() && beepers_in_bag()) {
            put_beeper();
        } else if (front_is_clear() && beepers_in_bag()) {
            step();
            if (beepers_present()) {
                turn_opposite();
                step();
                put_beeper();
            } else {
                turn_opposite();
                step();
            }
        }
        turn_until_west();
        step();
    }
}

void step_until_meet_the_beeper() {
    while(!beepers_present()) {
        step();
    }
}

int main() {
    turn_on("task_3.kw");
    set_step_delay(KAREL_ULTRA_SPEED_MODE);

    turn_until_east();
    while (allways_return_true()) {
        step_and_pick_all_beepers();
        if (!beepers_in_bag()) {
            turn_left();
            step();
            if(!beepers_present()) {
                turn_left();
                while(!beepers_present()) {
                    step();
                }
                turn_3_times();
            }
            step_until_the_wall();
            turn_left();
            step_until_the_wall();
            turn_until_east();
            break;
        }
        turn_opposite();
        return_and_place_beepers();
        turn_left();
        if (front_is_clear()) {
            step();
        } else {
            turn_until_east();
            step_until_meet_the_beeper();
            turn_left();
            step_until_the_wall();
            turn_left();
            step_until_the_wall();
            turn_until_east();
            break;
        }
        turn_until_east();
    }

    turn_off();
    return 0;
}
