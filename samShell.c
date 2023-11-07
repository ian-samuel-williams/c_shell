#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>


// ---------------------------- Getting user input -----------------------------
char *getUserIn() {
  char *buffer;
  size_t bufSize;

  printf(">>");
  int s = getline(&buffer, &bufSize, stdin);
  // printf("You typed %s \n", buffer);
  return buffer;
}

// -------------------------- Splitting the string by delimiters ---------------
void tokenize(char *userString, char *userArr[]) {
  char *token;
  const char *dlim = " \t\r\n\a";
  token = strtok(userString, dlim);
  int i = 0;
  userArr[i] = token;
  while (token != NULL) {
    i += 1;
    //printf("%s\n", token);
    token = strtok(NULL, dlim);
    userArr[i] = token;
    //printf("%s\n", userArr[i]);

  }
  if (i != 0) {
      userArr[i + 1] = NULL;
  }

}


// -------------------------- Forking ------------------------------------------
void executeCom(char *userArr[]) {
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "Failed to fork");
  }
  else if (rc == 0) {
    if (execvp(userArr[0], userArr) == -1) {
      printf("bad command \n");
      exit(1);
    }

  }
  else {
    int wc = wait(NULL);
    assert(wc >= 0);
  }
}


// -------------------------- Main Function ------------------------------------
int main(int argc, char *argv[]) {
  char **inArr = malloc(16*sizeof(char*));
  while (1) {
    *inArr = realloc(inArr, 16*sizeof(char*));
    tokenize(getUserIn(), inArr);

    if (strcmp(inArr[0], "exit") == 0) {
      printf("Exiting...\n See you later \n");
      free(inArr);
      exit(0);
    }

    executeCom(inArr);
}
free(inArr);
return 0;
}
