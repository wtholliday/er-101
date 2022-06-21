#include <stdio.h>
#include <stdint.h>

#define NUM_VOLTAGES_PER_TABLE 100
#define MAX_STEPS 2000
#define MAX_PATTERNS 400
#define NUM_TRACKS 4
#define INVALID_PATTERN 0xFFFF
#define INVALID_STEP 0xFFFF

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

typedef int (*read_func_t)(size_t bytes, void* dest);
typedef int (*write_func_t)(size_t bytes, void* src);

typedef struct
{
  uint8_t cvA;
  uint8_t cvB;
  uint8_t duration;
  uint8_t gate;
} snapshot_step_t;

typedef struct
{
  uint8_t ns; // num of steps
  uint8_t options;
} snapshot_pattern_t;

typedef struct
{
  uint32_t magic;
  track_t tracks[NUM_TRACKS];
} snapshot_data_t;


void seq_save_data(sequencer_data_t* data, write_func_t write_func) {
  
  snapshot_data_t snap_data;
  snap_data.magic = data->magic;
  for(int i=0;i<NUM_TRACKS;++i) {
    snap_data.tracks[i] = data->tracks[i];
  }
  write_func(sizeof(snapshot_data_t), &snap_data);

  // Write out patterns.
  for(int i=0;i<NUM_TRACKS;++i) {
    for(pattern_id_t pat_id = data->tracks[i].first; pat_id != INVALID_PATTERN; pat_id = data->patterns.pool[pat_id].next) {
      pattern_t pat = data->patterns.pool[pat_id];
      snapshot_pattern_t snap_pat;
      snap_pat.ns = pat.ns;
      snap_pat.options = pat.options;
      write_func(sizeof(snapshot_pattern_t), &snap_pat);

      // Write out steps.
      for(step_id_t step_id = pat.first; step_id != INVALID_STEP; step_id = data->steps.pool[step_id].next) {
        step_t step = data->steps.pool[step_id];
        snapshot_step_t snap_step;
        snap_step.cvA = step.cvA;
        snap_step.cvB = step.cvB;
        snap_step.duration = step.duration;
        snap_step.gate = step.gate;
        write_func(sizeof(snapshot_step_t), &snap_step);
      }
    }
  }

  // Indicate that we're done writing so data is flushed.
  write_func(0, NULL);

}

int main() {
    printf("running tests\n");
}