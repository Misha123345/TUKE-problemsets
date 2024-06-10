#define NUMBER_OF_MELODIES 3
#define DEFAULT_NOTES_NUMBER 5
#define STAR_WARS_NOTES_NUMBER 39
#define CALM_NOTES_NUMBER 34

void play_default(int* current_note, unsigned long* last_time);
void play_star_wars(int* current_note, unsigned long* last_time);
void play_calm_song(int* current_note, unsigned long* last_time);