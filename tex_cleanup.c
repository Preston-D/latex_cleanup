#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>

// Recursive function to traverse directories and delete .aux and .log files
void cleanup_directory(char *basePath, int verbose, int run_before, int run_after, int *aux_count, int *log_count)
{
  char path[1000];
  struct dirent *dp;
  DIR *dir = opendir(basePath);

  // Unable to open directory stream
  if (!dir)
    return;

  while ((dp = readdir(dir)) != NULL)
  {
    if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
    {
      // Construct new path from our base path
      strcpy(path, basePath);
      strcat(path, "/");
      strcat(path, dp->d_name);

      // Check if path is a directory
      struct stat sb;
      if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
      {
        // Recurse into sub-directory
        cleanup_directory(path, verbose, run_before, run_after, aux_count, log_count);
      }
      else
      {
        // Delete .aux and .log files
        char *ext = strrchr(path, '.');
        if (ext != NULL && (strcmp(ext, ".aux") == 0 || strcmp(ext, ".log") == 0))
        {
          if (run_before && strcmp(ext, ".log") == 0)
          {
            // Skip deleting .log files if run_before is set
            continue;
          }

          if (access(path, W_OK) == 0)
          {
            remove(path);
            if (strcmp(ext, ".aux") == 0)
            {
              (*aux_count)++;
            }
            else
            {
              (*log_count)++;
            }
            if (verbose)
            {
              printf("DELETED %s\n", path);
            }
          }
        }
        else if (run_before && ext != NULL && strcmp(ext, ".tex") == 0)
        {
          // Run pdflatex before deleting files
          char command[1024];
          snprintf(command, sizeof(command), "pdflatex %s", path);
          system(command);
        }
      }
    }
  }

  closedir(dir);

  if (run_after)
  {
    // Run pdflatex after deleting files
    dir = opendir(basePath);
    while ((dp = readdir(dir)) != NULL)
    {
      if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
      {
        strcpy(path, basePath);
        strcat(path, "/");
        strcat(path, dp->d_name);

        char *ext = strrchr(path, '.');
        if (ext != NULL && strcmp(ext, ".tex") == 0)
        {
          char command[1024];
          snprintf(command, sizeof(command), "pdflatex %s", path);
          system(command);
        }
      }
    }
    closedir(dir);
  }
}

int main(int argc, char *argv[])
{
  char directory[256] = ".";
  int verbose = 0, run_before = 0, run_after = 0;
  int aux_count = 0, log_count = 0;

  static struct option long_options[] = {
      {"directory", required_argument, NULL, 'd'},
      {"verbose", no_argument, NULL, 'v'},
      {"run_before", no_argument, NULL, 'b'},
      {"run_after", no_argument, NULL, 'a'},
      {"help", no_argument, NULL, 'h'},
      {NULL, 0, NULL, 0}};

  int opt;
  while ((opt = getopt_long(argc, argv, "d:vba:h", long_options, NULL)) != -1)
  {
    switch (opt)
    {
    case 'd':
      strncpy(directory, optarg, sizeof(directory));
      break;
    case 'v':
      verbose = 1;
      break;
    case 'b':
      run_before = 1;
      break;
    case 'a':
      run_after = 1;
      break;
    case 'h':
    default:
      printf("Usage: %s [-d|--directory directory] [-v|--verbose] [-b|--run_before] [-a|--run_after] [-h|--help]\n", argv[0]);
      return 0;
    }
  }

  cleanup_directory(directory, verbose, run_before, run_after, &aux_count, &log_count);
  printf("Deleted %d .aux files and %d .log files\n", aux_count, log_count);

  return 0;
}
