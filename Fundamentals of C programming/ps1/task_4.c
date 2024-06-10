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

void turn_opposite () {
    set_step_delay(KAREL_INFINITE_SPEED_MODE);
    turn_left();
    set_step_delay(KAREL_ULTRA_SPEED_MODE);
    turn_left();
}

void turn_until_east() {
    while(not_facing_east()) {
        turn_3_times();
    }
}

void go_until_meet_the_wall() {
    while(front_is_clear()) {
        step();
    }
}

bool step_and_check_beepers() {
    while (front_is_clear()) {
        if (beepers_present()) {
            return true;
        }
        step();
    }
    if (beepers_present()) {
        return true;
    }
    return false;
}

void return_and_put_beepers() {
    do  {
        if (!beepers_present()) {
            put_beeper();
        }
        step();
    } while(front_is_clear());
    if (!beepers_present()) {
        put_beeper();
    }
}

int main() {
    turn_on("task_4.kw");
    set_step_delay(KAREL_ULTRA_SPEED_MODE);

    while (allways_return_true()) {
        turn_left();
        if (step_and_check_beepers()) {
            go_until_meet_the_wall();
            turn_opposite();
            return_and_put_beepers();
        } else {
            turn_opposite();
            go_until_meet_the_wall();
        }
        if (left_is_blocked()) {
            break;
        }
        turn_left();
        step();
    }

    turn_until_east();

    turn_off();
    return 0;
}
