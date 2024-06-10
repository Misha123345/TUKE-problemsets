/**
 * List of available states.
 */
enum state {
    ALARM,
    CLOCK,
    FACTORY_RESET,
    SHOW_ENV,
    SETTINGS
};

enum date_component {
    YEAR,
    MONTH,
    DAY
};

enum time_component {
    HOURS,
    MINUTES
};

#define NUMBER_OF_OPTIONS 5

enum settings_options {
    SET_DATE,
    SET_TIME,
    SET_ALARM,
    SET_MELODY,
    DELETE_ALARM
};

enum melodies {
    DEFAULT_MELODY,
    STAR_WARS,
    CALM_MELODY
};

/**
 * Individual implementation of states.
 */

enum state state_clock(bool is_alarm);
enum state state_factory_reset();
enum state state_alarm();
enum state state_show_env();
enum state state_settings();