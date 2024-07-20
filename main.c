#include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// FILE *fileptr;

int flags(int argi, char** argv) {
  int fchar = 1;

  if (argv[argi][fchar] == '-')
  {
    fchar++;
  }

  char arg = argv[argi][fchar];

  if (arg > 90)
  {
    arg -= 32;
  }

  switch (arg) {
    
    case 'H':
      printf("input what you want to do\n'w' to write to list\n'r' to read list\n'd' to delete list elements\n");
      return 0;
    default:
      printf("flag not recognized\nTack -h or --help to see options\n");
      return 0;
  }
}


int main(int argc, char** argv)
{
  if (argc == 1)
  {
    printf("No command supplied.\nPlease provide a command or --help to see options.\n");
    return 1;
  }

  for (int i = 1; i < argc; i++)
  {
    char arg = argv[i][0];

    if (arg > 90)
    {
      arg -= 32;
    }

    switch (arg) {
      case 'D':
        printf("Delete\n");
        break;
      
      case 'R':
        printf("Read\n");
        break;

      case 'W':
        printf("Write\n");
        break;

      case '-':
        return flags(i, argv);

      default:
        printf("Invalid command passed\n");
        return 5;
    }
  }

}
