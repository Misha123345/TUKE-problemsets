#include <superkarel.h>
#define KAREL_USM 50
#define KAREL_ISM 0

void step_until_meet_the_wall() {
    while(front_is_clear()) {
        step();
    }
}

void go_until_meet_the_wall() {
    while(front_is_clear()){
        step();
    }
}

void step_and_put_beepers() {
    while(front_is_clear()) {
        if (!beepers_present()) {
            put_beeper();
        }
        step();
    }
    if (!beepers_present()) {
        put_beeper();
    }
}

void go_to_corner() {
    while(front_is_clear() && right_is_blocked()) {
        step();
    }
}

void turn_opposite () {
    turn_left();
    turn_left();
}

void turn_3_times() {
    turn_left();
    turn_left();
    turn_left();
}


void find_center() {
    step();
    step();
    if (front_is_clear()) {
        find_center();
    } else {
        turn_opposite();
    }
    step();
}

void turn_until_north() {
    while(not_facing_north()) {
        turn_left();
    }
}
void turn_right_way() {
    if (left_is_blocked()) {
        turn_3_times();
    } else {
        turn_left();
    }
}

void go_to_center() {
    find_center();
    turn_right_way();
    find_center();
    turn_right_way();
}

int main() {
    turn_on("task_5.kw");
    set_step_delay(KAREL_USM);

    go_until_meet_the_wall();
    turn_left();
    while(!beepers_present()) {
        step_and_put_beepers();
        turn_left();
        step();
    }

    go_to_corner();
    turn_left();
    go_to_center();
    turn_until_north();


    turn_off();
}
