#include <ctype.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256
#define BUCKET_SIZE 2048
char testName[3][BUFFER_SIZE] =
    {"browning.txt", "shakespeare.txt", "shelly.txt"};
char buffer[BUFFER_SIZE];

struct user_input {
   size_t numOfFile;
   char** textFile;
   size_t min;
   size_t max;
   char order;
};

struct environment {
   int process;
   int size;
};

struct string_chunk {
   char* str;
   size_t size;
};

struct node {
   char key[BUFFER_SIZE];
   size_t value;
   struct node* next;
};

struct hash_map {
   struct node* bucket[BUCKET_SIZE];
};

struct node* node_init(char* key, size_t val) {
   struct node* n = malloc(sizeof(struct node));
   strcpy(n->key, key);
   n->value = val;
   n->next = NULL;
   return n;
}

void node_add(struct node* n, char* str, size_t val) {
   if (!strcmp(n->key, str)) {
      n->value += val;
      return;
   }
   if (n->next)
      node_add(n->next, str, val);
   else
      n->next = node_init(str, val);
}

// djb2 hash, source: http://www.cse.yorku.ca/~oz/hash.html
size_t hash(char* str) {
   size_t hash = 5381;
   int c;

   while (c = *str++)
      hash = ((hash << 5) + hash) + c;

   return hash;
}

struct node* hashmap_getorcreate(struct hash_map* hashmap, char* str) {
   int idx = hash(str) % BUCKET_SIZE;
   struct node* n = hashmap->bucket[idx];
   if (n == NULL) {
      n = node_init(str, 0);
      hashmap->bucket[idx] = n;
   }

   return n;
}

void hashmap_add(struct hash_map* hashmap, char* str, size_t val) {
   node_add(hashmap_getorcreate(hashmap, str), str, val);
}

size_t hashmap_size(struct hash_map* hashmap) {
   size_t size = 0;
   struct node* n;
   for (int i = 0; i < BUCKET_SIZE; i++) {
      n = hashmap->bucket[i];
      if (n != NULL) {
         do {
            size++;
         } while (n = n->next);
      }
   }
   return size;
}

struct node** hashmap_to_array(struct hash_map* hashmap) {
   size_t size = hashmap_size(hashmap) + 1;
   struct node** aryNode = (struct node**)malloc(size * sizeof(struct node*));
   struct node* n;
   for (int i = 0, j = 0; i < BUCKET_SIZE; i++) {
      n = hashmap->bucket[i];
      if (n != NULL) {
         do {
            aryNode[j++] = n;
         } while (n = n->next);
      }
   }
   return aryNode;
}

int val_comparator(const void* v1, const void* v2) {
   const struct node *p1, *p2;
   p1 = *(const struct node**)v1;
   p2 = *(const struct node**)v2;
   if (p1->value < p2->value)
      return +1;
   else if (p1->value > p2->value)
      return -1;
   else
      return 0;
}

int alpha_comparator(const void* v1, const void* v2) {
   const struct node *p1, *p2;
   p1 = *(const struct node**)v1;
   p2 = *(const struct node**)v2;
   int cmp = strcmp(p1->key, p2->key);
   if (cmp != 0)
      return cmp;
   else
      return 0;
}

void getinputtest(struct user_input* input) {
   input->numOfFile = 3;
   input->textFile = (char**)malloc(input->numOfFile * sizeof(char*));
   for (int i = 0; i < input->numOfFile; i++) {
      input->textFile[i] = (char*)malloc(BUFFER_SIZE * sizeof(char));
      strcpy(input->textFile[i], testName[i]);
   }
   input->min = 3;
   input->max = 20;
   input->order = 'n';
}

void getinput(struct user_input* input) {
   printf("Enter the number of text files: ");
   fflush(stdout);
   scanf("%d", &input->numOfFile);

   input->textFile = (char**)malloc(input->numOfFile * sizeof(char*));
   for (int i = 0; i < input->numOfFile; i++) {
      input->textFile[i] = (char*)malloc(BUFFER_SIZE * sizeof(char));
      printf("Enter the path of text file %d: ", i + 1);
      fflush(stdout);
      scanf("%s", buffer);
      strncpy(input->textFile[i], buffer, BUFFER_SIZE);
   }

   printf("Enter the minimum length of word: ");
   fflush(stdout);
   scanf("%d", &input->min);

   printf("Enter the maximum length of word: ");
   fflush(stdout);
   scanf("%d", &input->max);

   printf("Enter 'a' for alphabetical order or 'n' for number of words order: ");
   fflush(stdout);
   scanf(" %c", &input->order);
}

void slice(const char* src, char* dest, size_t start, size_t end) {
   strncpy(dest, src + start, end - start);
}

void openfile(MPI_File* fh, struct user_input* input, struct environment* env, int idx) {
   if (!env->process) {
      strcpy(buffer, input->textFile[idx]);
   }
   MPI_Bcast(buffer, BUFFER_SIZE, MPI_CHAR, 0, MPI_COMM_WORLD);
   if (MPI_File_open(MPI_COMM_WORLD, buffer, MPI_MODE_RDONLY, MPI_INFO_NULL, fh)) {
      if (!env->process) fprintf(stderr, "Couldn't open file %s\n", buffer);
      MPI_Finalize();
      exit(2);
   }
}

// modified version, source: https://stackoverflow.com/questions/12939279/mpi-reading-from-a-text-file
// UPDATE: this seems to cause issue where certain words gets skipped
// so we'll go with naive approach for now:
// process 0 read all the string, count text length by new line
// and distribute string by line count evenly
struct string_chunk* readfileanddistribute(MPI_File* fh, struct user_input* input, struct environment* env) {
   struct string_chunk* chunk = malloc(sizeof(struct string_chunk));
   MPI_Offset fileSize;
   char *str, *sliced;
   size_t *lineSize, localSize, size, part, leftover;
   int i = 0, textLength = 0, localStart, localEnd;

   if (!env->process) {
      MPI_File_get_size(*fh, &fileSize);
      str = (char*)malloc((fileSize) * sizeof(char));
      MPI_File_read(*fh, str, fileSize, MPI_CHAR, MPI_STATUS_IGNORE);

      while (str[i++])
         if (str[i] == '\n')
            textLength++;

      lineSize = malloc((textLength + 1) * sizeof(size_t));
      lineSize[0] = 0;
      i = 0;
      textLength = 1;
      while (str[i++])
         if (str[i] == '\n')
            lineSize[textLength++] = i;
      lineSize[textLength] = i - 1;
   }

   part = textLength / env->size;
   leftover = textLength % env->size;

   for (i = env->size - 1; i >= 0; i--) {
      if (!env->process) {
         localStart = part * i;
         localEnd = part * (i + 1);
         if (i == env->size - 1) localEnd += leftover;
         size = lineSize[localEnd] - lineSize[localStart];
         sliced = (char*)malloc(size * sizeof(char));
         slice(str, sliced, lineSize[localStart], lineSize[localEnd]);
         if (i) {
            MPI_Send(&size, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(sliced, size, MPI_CHAR, i, 0, MPI_COMM_WORLD);
         } else
            localSize = size;
      }
      if (i && i == env->process) {
         MPI_Recv(&localSize, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
         sliced = (char*)malloc(localSize * sizeof(char));
         MPI_Recv(sliced, localSize, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      }
   }
   chunk->str = sliced;
   chunk->size = localSize;

   return chunk;
}

void filterandcountwords(struct string_chunk* chunk, struct hash_map* hashmap, struct user_input* input) {
   char c;
   int i = 0, j = 0;
   memset(buffer, 0, BUFFER_SIZE);
   while (chunk->str[i]) {
      c = chunk->str[i++];
      if (isalpha(c))
         buffer[j++] = tolower(c);
      else if (j) {
         if (j >= input->min && j <= input->max) hashmap_add(hashmap, buffer, 1);
         memset(buffer, 0, j);
         j = 0;
      }
   }
}

void aggregateresults(struct hash_map* hashmap, struct environment* env) {
   int size;
   char key[BUFFER_SIZE];
   struct node* n;
   int val;
   for (int i = 1; i < env->size; i++) {
      if (env->process && env->process != i) continue;
      if (env->process) {
         size = hashmap_size(hashmap);
         MPI_Send(&size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

         for (int i = 0, j = 0; i < BUCKET_SIZE; i++) {
            n = hashmap->bucket[i];
            if (n != NULL) {
               do {
                  MPI_Send(&n->key, BUFFER_SIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
                  MPI_Send(&n->value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
               } while (n = n->next);
            }
         }
      } else {
         MPI_Recv(&size, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
         for (int j = 0; j < size; j++) {
            MPI_Recv(&key, BUFFER_SIZE, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(&val, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            hashmap_add(hashmap, key, val);
         }
      }
   }
}

void sortresults(struct node** nodes, struct user_input* input, size_t size) {
   switch (input->order) {
      case 'n':
         printf("Sorting by numerical\n");
         qsort(nodes, size, sizeof(struct node*), val_comparator);
         break;
      case 'a':
         printf("Sorting by alphabetical\n");
         qsort(nodes, size, sizeof(struct node*), alpha_comparator);
         break;
      default:
         printf("Unknown input, no sorting is done\n");
   }
}

void printresults(struct node** nodes) {
   struct node* n;
   int i = 0;
   FILE* outfile = fopen("output.txt", "w");
   if (!outfile) {
      fprintf(stderr, "Unable to open %s for writing.\n", "output.txt");
      exit(1);
   }
   while (n = nodes[i++])
      fprintf(outfile, "%s: %d\n", n->key, n->value);
   fclose(outfile);
}

void closefile(MPI_File* fh) {
   MPI_File_close(fh);
}

int main(int argc, char* argv[]) {
   struct user_input* input = malloc(sizeof(struct user_input));
   struct environment* env = malloc(sizeof(struct environment));
   MPI_File fh;

   struct string_chunk* chunk;
   struct hash_map* hashmap = malloc(sizeof(struct hash_map));
   struct node** nodes;

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &env->process);
   MPI_Comm_size(MPI_COMM_WORLD, &env->size);
   if (!env->process) {
      if (argc == 2 && !strcmp(argv[1], "test")) {
         getinputtest(input);
         // strcpy(input->textFile[0], "lorem.txt");
         // input->numOfFile = 1;
      } else {
         getinput(input);
      }
   }

   MPI_Bcast(&input->numOfFile, 1, MPI_INT, 0, MPI_COMM_WORLD);
   MPI_Bcast(&input->min, 1, MPI_INT, 0, MPI_COMM_WORLD);
   MPI_Bcast(&input->max, 1, MPI_INT, 0, MPI_COMM_WORLD);
   if (input->min > input->max) {
      if (!env->process) fprintf(stderr, "Minimum should be lower than or equal to maximum, min:%d max:%d\n", input->min, input->max);
      MPI_Finalize();
      exit(1);
   }

   for (int i = 0; i < input->numOfFile; i++) {
      if (!env->process) printf("Opening file input %s\n", input->textFile[i]);
      openfile(&fh, input, env, i);
      if (!env->process) printf("Reading and distributing string\n");
      chunk = readfileanddistribute(&fh, input, env);
      if (!env->process) printf("Finished reading file %s\n", input->textFile[i]);
      closefile(&fh);
      if (!env->process) printf("Filtering and counting words\n");
      filterandcountwords(chunk, hashmap, input);
   }

   if (!env->process) printf("Aggregating results\n");
   aggregateresults(hashmap, env);
   if (!env->process) {
      printf("Converting hashmap to array results\n");
      nodes = hashmap_to_array(hashmap);
      printf("Sorting results\n");
      sortresults(nodes, input, hashmap_size(hashmap));
      printf("Printing results\n");
      printresults(nodes);
   }

   MPI_Finalize();
}
