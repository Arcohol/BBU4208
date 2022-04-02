/* Given 10 box ,numbered from 0 to 9, to store mail items. Every item is also signed with a phone
 * number of its receiver. Write a policy to distribute the items into the box. The rule is: try
 * to mach the box number with the last digit of the related phone number, if the box has already
 * ocuppied, use the quadratic probing method to deal with the collision. */

#include <stdio.h>
#include <string.h>

#define BOX_SIZE 10
#define NUMBER_SIZE 11

int IsEmpty(char *tmp) { return tmp == NULL; }
int Hash(char tmp[]) { return tmp[NUMBER_SIZE - 1] - '0'; }

int main() {
    char *box[BOX_SIZE] = {0}, str[150], *tmp;
    int pos, collision;

    scanf("%s", str);

    tmp = strtok(str, ",");
    while (tmp != NULL) {
        collision = 0;
        pos = Hash(tmp);
        while (!IsEmpty(box[pos])) {
            pos += 2 * ++collision - 1;
            if (pos >= 10) {
                pos -= 10;
            }
        }
        box[pos] = tmp;
        tmp = strtok(NULL, ",");
    }

    for (int i = 0; i < BOX_SIZE; i++) {
        if (IsEmpty(box[i])) {
            printf("0");
        } else {
            printf("%s", box[i]);
        }

        if (i < BOX_SIZE - 1) {
            putchar(',');
        }
    }

    return 0;
}