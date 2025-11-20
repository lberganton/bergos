#ifndef KERNEL_H
#define KERNEL_H

void kernel_initialize(void);
void kernel_panic(int error);
void kernel_halt(void);

#endif
