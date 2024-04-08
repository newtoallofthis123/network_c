#include <stdio.h>

int main(int argc, char *argv[]) {
  char *filename = "wow.txt";
  if (argc > 1) {
    filename = argv[1];
  }

  FILE *file;
  char buff[10];

  file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error opening input file");
    return 1;
  }

  while (fgets(buff, sizeof(buff), file) != NULL) {
    printf("%s", buff);
  }
}
