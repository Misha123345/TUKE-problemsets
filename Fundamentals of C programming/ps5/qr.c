#include <math.h>
#include <stdbool.h>
#include <string.h>

void encode_char(const char character, bool bits[8]);
char decode_byte(const bool bits[8]);
void encode_string(const char string[], bool bytes[strlen(string)+1][8]);
void decode_bytes(const int rows, bool bytes[rows][8], char string[rows]);
void bytes_to_blocks(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]);
void blocks_to_bytes(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]);

int main() {
   /* bool blocks[2*8][4] = {
	{0, 0, 0, 0},
	{1, 1, 1, 1},
	{1, 1, 1, 1},
	{1, 0, 1, 0},
	{0, 0, 0, 0},
	{0, 1, 1, 0},
	{1, 0, 0, 0},
	{0, 1, 0, 1},
	{0, 0, 0, 0},
	{1, 1, 1, 0},
	{1, 1, 1, 0},
	{1, 0, 0, 0},
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{1, 0, 1, 0},
	{0, 1, 1, 0}
};
bool bytes[8][8];

blocks_to_bytes(4, 2, blocks, 8, bytes);
for(int j = 0; j < 8; j++){
    for(int i = 0; i < 8; i++){
        printf("%d", bytes[j][i]);
    }
    printf("\n");
}
*/
  return 0;
}

void encode_char(const char character, bool bits[8]) {
  int temp = character;
  for (int i = 0; i < 8; i++) {
    bits[7 - i] = (bool)(temp % 2);
    temp /= 2;
  }
}

char decode_byte(const bool bits[8]) {
  int char_code = 0;
  for (int i = 0; i < 8; i++) {
    char_code += pow(2, i) * bits[7 - i];
  }
  return char_code;
}

void encode_string(const char string[], bool bytes[strlen(string)+1][8]){
  for (int i = 0; i < strlen(string) + 1; i++) {
    encode_char(string[i], bytes[i]);
  }
}

void decode_bytes(const int rows, bool bytes[rows][8], char string[rows]) {
  for (int i = 0; i < rows; i++) {
    string[i] = decode_byte(bytes[i]);
  }
}

void bytes_to_blocks(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]) {
  int writed_bytes = 0;
  for (int i = 0; i < offset * 8; i++) {
    for (int j = 0; j < cols; j++) {
      blocks[i][j] = ((writed_bytes + j) < rows) ? bytes[writed_bytes + j][i % 8] : 0;
    }
    if (i % 8 == 7) writed_bytes += cols;
  }
}

void blocks_to_bytes(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]) {
  int checked_offsets = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < 8; j++) {
      bytes[i][j] = blocks[j + checked_offsets][i % cols];
    }
    if (i % cols == cols - 1) checked_offsets += 8;
  }
}
