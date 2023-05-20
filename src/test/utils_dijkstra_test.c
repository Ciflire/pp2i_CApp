#include "../include/utils_dijkstra.h"

int main(void) {
  borne *b1 = create_borne(1, 1, 1, 1, 1);
  borne *b2 = create_borne(2, 2, 2, 2, 2);
  int distance = get_distance_x_y(b1, b2);
  printf("%d\n", distance);
  destroy_borne(b1);
  destroy_borne(b2);
  return 0;
}
