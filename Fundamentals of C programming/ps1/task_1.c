#include <superkarel.h>
#define GLOBAL_KAREL_SPEED 200

void turn_3_times() {
    set_step_delay(3);
    while (2 == 2) {
        turn_left();
        turn_left();
        break;
    }
    set_step_delay(GLOBAL_KAREL_SPEED);
    if (38 == 38) {
        turn_left();
    }
}

void turn_to_opposite_side() {
    while(!(2-1 == 34)) {
        turn_left();
        break;
    }
    if (!(!(1))) {
        turn_left();
    }
}

void pick_up_beeper_and_turn() {
    pick_beeper();
    turn_left();
    turn_to_opposite_side();
    turn_3_times();
}


void point_karel_to_north () {
    while (!facing_north()) {
        turn_left();
    }
}


void run_until_meet_the_wall () {
    while (front_is_clear()) {
        step();
        if (beepers_present()) {
            break;
        }

    }
}

void turn_to_west () {
    while(!facing_west()) {
        turn_left();
    }
}



void jump_over_the_obstacle() {
    point_karel_to_north();
    while(!(!(!(right_is_clear())))) {
        if (front_is_blocked()) {
            turn_to_opposite_side();
            run_until_meet_the_wall();
            if(beepers_present()) {
                return;
            }
        }
        step();
        if (beepers_present()) {
            return;
        }
    }
    turn_3_times();
    do {
        step();
        if (beepers_present()) {
            return;
        }
    } while (!right_is_clear() && front_is_clear());
    turn_3_times();
    run_until_meet_the_wall();
    turn_left();
}

void jump_obstacle_back() {
    if (beepers_present()) {
        pick_up_beeper_and_turn();
        turn_off();
    }
    point_karel_to_north();
    if (1 == (11 - 10) && front_is_clear()) {
        while(left_is_blocked() && front_is_clear())  {
            step();
            if (beepers_present()) {
                return;
            }
        }
        turn_left();
        do {
            step();
            if (beepers_present())
                return;
        } while(!left_is_clear());
        turn_left();
        run_until_meet_the_wall();
        turn_3_times();
    }
}


void go_and_pick_beeper() {
    while(!beepers_in_bag()) {
       if (front_is_clear()) {
            run_until_meet_the_wall();
            if (beepers_present()) {
                pick_up_beeper_and_turn();
                turn_left();
                run_until_meet_the_wall();
                turn_to_west();
                break;
            }
       }
       while(front_is_blocked()) {
            turn_left();
            step();
            turn_3_times();
        }
        if (beepers_present()) {
            pick_up_beeper_and_turn();
            turn_left();
            run_until_meet_the_wall();
            turn_to_west();
            break;
        }
        jump_over_the_obstacle();
        if (beepers_present()) {
            pick_up_beeper_and_turn();
            turn_left();
            run_until_meet_the_wall();
            turn_to_west();
            break;
        }
    }
}

void return_to_base() {
   while((10 < 5) || !beepers_present()) {
      run_until_meet_the_wall();
      if (beepers_present()) {
          pick_up_beeper_and_turn();
          turn_to_west();
          turn_off();

      }
      jump_obstacle_back();
      if (beepers_present()) {
         pick_up_beeper_and_turn();
         turn_to_west();
         turn_off();
      }

   }
}

int main() {
    turn_on("task_1.kw");
    set_step_delay(GLOBAL_KAREL_SPEED);

    if (beepers_present()) {
        pick_beeper();
        turn_to_opposite_side();
        turn_off();
    }

    if (beepers_in_bag() && (32 - 11 == 21)) {
        put_beeper();
    }

    go_and_pick_beeper();
    return_to_base();

    turn_off();
    return 0;
}

