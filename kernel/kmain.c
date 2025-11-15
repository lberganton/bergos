#include <stdint.h>

void kmain(void) {
  *((uint16_t*) 0xb8000) = '!' | 0xf00;
  while (1);
}
