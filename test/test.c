#include <stdio.h>
#include <stdint.h>

#define NUM_VOLTAGES_PER_TABLE 100
#define MAX_STEPS 2000
#define MAX_PATTERNS 400
#define NUM_TRACKS 4

typedef struct
{
  uint8_t cvA_mode;
  uint8_t cvB_mode;
  uint8_t duration_mode;
  uint8_t gate_mode;
  int cvA;
  int cvB;
  int duration;
  int gate;
} transform_t;

typedef uint16_t step_id_t;
typedef uint16_t pattern_id_t;

typedef struct
{
  step_id_t prev;
  step_id_t next;
  uint8_t cvA;
  uint8_t cvB;
  uint8_t duration;
  uint8_t gate;
} step_t;

typedef struct
{
  step_id_t first;
  step_id_t last;
  pattern_id_t prev;
  pattern_id_t next;
  uint8_t ns; // num of steps
  uint8_t options;
} pattern_t;

typedef struct
{
  transform_t transform;
  uint8_t id;
  uint8_t nm; // num of patterns
  pattern_id_t first;
  pattern_id_t last;
  // loop start
  step_id_t lstart;
  // loop end
  step_id_t lend;
  uint16_t voltages[2][NUM_VOLTAGES_PER_TABLE];
  uint8_t options;
  uint8_t ppqn;
  uint8_t divide;
  uint8_t reserved1;
  uint8_t reserved2;
  uint8_t reserved3;
} track_t;

typedef struct
{
  step_t pool[MAX_STEPS];
  step_id_t available[MAX_STEPS];
  step_id_t head;
} step_pool_t;

typedef struct
{
  pattern_t pool[MAX_PATTERNS];
  pattern_id_t available[MAX_PATTERNS];
  pattern_id_t head;
  // uint8_t reserved;
} pattern_pool_t;

typedef struct
{
  uint32_t magic;
  transform_t transform; // not used
  track_t tracks[NUM_TRACKS];
  pattern_pool_t patterns;
  step_pool_t steps;
  // uint16_t reserved;
} sequencer_data_t;

int main() {
    printf("running tests\n");
}