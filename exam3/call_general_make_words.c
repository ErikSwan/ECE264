int general_make_words(char **, int, int (*)(char *, char));
int filter(char *, char);
int main(int argc, char *argv[])
{
  general_make_words(argv+1, argc-1, filter);
  return 0;
}
