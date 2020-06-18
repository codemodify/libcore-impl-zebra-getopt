
#if defined(LibCoreOS_windows) && defined(LibCoreARCH_amd64) && defined(LibCoreCompier_GNUC)

#include <libcore-spec-getopt/getopt.h>

int optopt;
char* optarg;

error getOptions(int argc, string[] argv, string validOptions, int startIndex) {
  static int sp = 1;
  register int c;
  register char* cp;

  if (sp == 1)
    if (startIndex >= argc || argv[startIndex][0] != '-' || argv[startIndex][1] == '\0')
      return (EOF);
    // else if(strcmp(argv[startIndex], "--") == NULL) {
    else if (strcmp(argv[startIndex], "--") == 0) {
      startIndex++;
      return (EOF);
    }
  optopt = c = argv[startIndex][sp];
  if (c == ':' || (cp = strchr(opts, c)) == NULL) {
    ERR(": illegal option -- ", c);
    if (argv[startIndex][++sp] == '\0') {
      startIndex++;
      sp = 1;
    }
    return ('?');
  }
  if (*++cp == ':') {
    if (argv[startIndex][sp + 1] != '\0')
      optarg = &argv[startIndex++][sp + 1];
    else if (++startIndex >= argc) {
      ERR(": option requires an argument -- ", c);
      sp = 1;
      return ('?');
    } else {
      optarg = argv[startIndex++];
    }
    sp = 1;
  } else {
    if (argv[startIndex][++sp] == '\0') {
      sp = 1;
      startIndex++;
    }
    optarg = NULL;
  }
  return (c);
}

#endif /* __GNUC__ */

#endif
