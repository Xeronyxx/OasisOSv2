#include "print.h"
#include "standard.h"
#include "process.h"
#include "system.h"
#include "keyboard.h"

void kernel_main();
void test();

unsigned short memorySizeKB;
int keyPressed = false;

<<<<<<< HEAD
=======
struct BDA {
    unsigned short memorySize;
};

void getMemorySize() {
    struct BDA *bda = (struct BDA *)0x400;
    memorySizeKB = bda->memorySize;
}

>>>>>>> 72bcdeed6fd4bd41b23adb123a636438a7592ac4
int main() {
    print_clear();
    print_set_colour(PRINT_COLOUR_WHITE, PRINT_COLOUR_BLACK);

    START("kernel", kernel_main);
    return 0;
}

void test() {
    while (1) {}
}

void kernel_main() {
    print_clear();
    print_str("OASIS OS. MADE BY XAVIER AND ALBI.\n");

    START("memget", getMemorySize);

    print_str("Running on ");
    print_int(memorySizeKB);
    print_str(" KB of memory.\n");

<<<<<<< HEAD
    // while (1) {
    //     if (crashed == false) {
    //         for (int i = 0; i < processCount; i++) {
    //             if (processes[i].finished) {
    //                 KILL(processes[i].id);
    //                 print_int(processes[i].id);
    //                 print_str("\n");
    //             }
    //         }
    //     }
    // }
=======
    while (1) {
        if (crashed == false) {
            for (int i = 0; i < processCount; i++) {
                if (processes[i].finished) {
                    KILL(processes[i].id);
                }
            }
        }

        if (scanKey() == KEY_R && keyPressed == false) {
            keyPressed = true;
            print_str("NAME                       PID\n");
            for (int i = 0; i < processCount; i++) {
                print_str(processes[i].name);

                int zerosNeeded = 25 - strlen(processes[i].name);
                for (int j = 0; j < zerosNeeded; j++) {
                    print_char(' ');
                }

                print_int(processes[i].id);
                print_char('\n');
            }
        }

        if (scanKey() == 0 && keyPressed == true) {
            keyPressed = false;
        }
    }
>>>>>>> 72bcdeed6fd4bd41b23adb123a636438a7592ac4
}