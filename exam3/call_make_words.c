void make_words(char **, int);
int main(int argc, char *argv[])
{
  make_words(argv+1, argc-1);
  return 0;
}
