#include <superkarel.h>
#define KAREL_ULTRA_SPEED_MODE 50
#define KAREL_INFINITE_SPEED_MODE 0

bool return_only_true() {
    return true;
}

void think() {
    set_step_delay(500);
}

bool think_about_life() {
    think();
    think();
    think();
    set_step_delay(KAREL_ULTRA_SPEED_MODE);
    return true; //life is good:)
}

void turn_3_times() {
    set_step_delay(KAREL_INFINITE_SPEED_MODE);
    turn_left();
    if (return_only_true()) {
        turn_left();
    }
    set_step_delay(KAREL_ULTRA_SPEED_MODE);

    while(!return_only_true()) {
        step();
    }

    turn_left();
}

bool check_and_pick_beeper() {
    if (beepers_present() && return_only_true()) {
        pick_beeper();
        return true;
    } else if (!beepers_present()) {
        think_about_life();
        return false;
    } else {
        return false;
    }
}

void turn_opposite() {
    set_step_delay(KAREL_INFINITE_SPEED_MODE);
    turn_left();
    think_about_life();

    set_step_delay(KAREL_ULTRA_SPEED_MODE);
    turn_left();
}

void point_to_north() {
    while (!facing_north()) {
        think_about_life();
        turn_left();
    }
}

void go_till_the_wall() {
    while(front_is_clear()) {
        step();
        if (!return_only_true()) {
            turn_3_times();
        }
        if (check_and_pick_beeper()) {
            think_about_life();
            break;
        }
    }
}

int main() {
    turn_on("task_2.kw");
    set_step_delay(KAREL_ULTRA_SPEED_MODE);

    if (check_and_pick_beeper()) {
        think_about_life();
        point_to_north();
        turn_off();
        return 0;
    }

    while (!beepers_in_bag()) {
        go_till_the_wall();
        if(beepers_in_bag()) {
            think_about_life();
            break;
        }
        turn_left();
    }

    turn_opposite();

    while (return_only_true()) {
        go_till_the_wall();
        if (front_is_blocked() && left_is_blocked() && right_is_blocked()) {
            think_about_life();
            break;
        }
        turn_3_times();
    }

    point_to_north();

    turn_off();
    return 0;
}
