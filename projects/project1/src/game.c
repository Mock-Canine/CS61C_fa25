#include "game.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snake_utils.h"

/* Helper function definitions */
static void set_board_at(game_t *game, unsigned int row, unsigned int col, char ch);
static bool is_tail(char c);
static bool is_head(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static char head_to_body(char c);
static unsigned int get_next_row(unsigned int cur_row, char c);
static unsigned int get_next_col(unsigned int cur_col, char c);
static void find_head(game_t *game, unsigned int snum);
static char next_square(game_t *game, unsigned int snum);
static void update_tail(game_t *game, unsigned int snum);
static void update_head(game_t *game, unsigned int snum);

/* Task 1 */
game_t *create_default_game() {
  // TODO: Implement this function.
    game_t *gameptr = calloc(1, sizeof(game_t));
    if (!gameptr)
        return NULL;

    gameptr->num_snakes = 1;
    gameptr->snakes = malloc(gameptr->num_snakes * sizeof(snake_t));
    if (!gameptr->snakes)
    {
        free_game(gameptr);
        return NULL;
    }
    *(gameptr->snakes) = (snake_t){.tail_row = 2, .tail_col = 2, .head_row = 2, .head_col = 4, .live = true};

    unsigned int rows = 18;
    gameptr->board = malloc(rows * sizeof(char *));
    char **bptr = gameptr->board;
    if (!bptr)
    {
        free_game(gameptr);
        return NULL;
    }
    gameptr->num_rows = rows;
    for (int i = 0; i < rows; i++, bptr++)
    {
        *bptr = malloc(22 * sizeof(char));
        if (!*bptr)
        {
            gameptr->num_rows = (unsigned int)i;
            free_game(gameptr);
            return NULL;
        }
        char *str = (i == 0 || i == 17) ? "####################\n" :\
                    (i == 2)            ? "# d>D    *         #\n" :\
                                          "#                  #\n"; 
        strcpy(*bptr, str);
    }
    return gameptr;
}

/* Task 2 */
void free_game(game_t *game) {
  // TODO: Implement this function.
  if (game == NULL)
      return;
  free(game->snakes);
  for (int i = 0; i < game->num_rows; i++)
  {
      free(*(game->board+i));
  }
  free(game->board);
  free(game);
  return;
}

/* Task 3 */
void print_board(game_t *game, FILE *fp) {
  // TODO: Implement this function.
  char **arr = game->board;
  for (int i = 0; i < game->num_rows; i++)
  {
     fprintf(fp, "%s", *arr++); 
  }
  return;
}

/*
  Saves the current game into filename. Does not modify the game object.
  (already implemented for you).
*/
void save_board(game_t *game, char *filename) {
  FILE *f = fopen(filename, "w");
  print_board(game, f);
  fclose(f);
}

/* Task 4.1 */

/*
  Helper function to get a character from the board
  (already implemented for you).
*/
char get_board_at(game_t *game, unsigned int row, unsigned int col) { return game->board[row][col]; }

/*
  Helper function to set a character on the board
  (already implemented for you).
*/
static void set_board_at(game_t *game, unsigned int row, unsigned int col, char ch) {
  game->board[row][col] = ch;
}

/*
  Returns true if c is part of the snake's tail.
  The snake consists of these characters: "wasd"
  Returns false otherwise.
*/
static bool is_tail(char c) {
  // TODO: Implement this function.
  // note that strchr compare the '\0'
  return (bool)strchr("wasd", c);
}

/*
  Returns true if c is part of the snake's head.
  The snake consists of these characters: "WASDx"
  Returns false otherwise.
*/
static bool is_head(char c) {
  // TODO: Implement this function.
  return (bool)strchr("WASDx", c);
}

/*
  Returns true if c is part of the snake.
  The snake consists of these characters: "wasd^<v>WASDx"
*/
static bool is_snake(char c) {
  // TODO: Implement this function.
  return (bool)strchr("wasd^<v>WASDx", c);
}

/*
  Converts a character in the snake's body ("^<v>")
  to the matching character representing the snake's
  tail ("wasd").
*/
static char body_to_tail(char c) {
  // TODO: Implement this function.
  char *tail = "wasd";
  char *body = "^<v>";
  char *place = strchr(body, c);
  return tail[place - body];
}

/*
  Converts a character in the snake's head ("WASD")
  to the matching character representing the snake's
  body ("^<v>").
*/
static char head_to_body(char c) {
  // TODO: Implement this function.
  char *head = "WASD";
  char *body = "^<v>";
  char *place = strchr(head, c);
  return body[place - head];
}

/*
  Returns cur_row + 1 if c is 'v' or 's' or 'S'.
  Returns cur_row - 1 if c is '^' or 'w' or 'W'.
  Returns cur_row otherwise.
*/
static unsigned int get_next_row(unsigned int cur_row, char c) {
  // TODO: Implement this function.
  bool increase = (c == 'v' || c == 's' || c == 'S') ? true : false;
  bool decrease = (c == '^' || c == 'w' || c == 'W') ? true : false;
  cur_row = increase ? cur_row + 1 : decrease ? cur_row - 1: cur_row;
  return cur_row;
}

/*
  Returns cur_col + 1 if c is '>' or 'd' or 'D'.
  Returns cur_col - 1 if c is '<' or 'a' or 'A'.
  Returns cur_col otherwise.
*/
static unsigned int get_next_col(unsigned int cur_col, char c) {
  // TODO: Implement this function.
  bool increase = (c == '>' || c == 'd' || c == 'D') ? true : false;
  bool decrease = (c == '<' || c == 'a' || c == 'A') ? true : false;
  cur_col = increase ? cur_col + 1 : decrease ? cur_col - 1: cur_col;
  return cur_col;
}

/*
  Task 4.2

  Helper function for update_game. Return the character in the cell the snake is moving into.

  This function should not modify anything.
*/
static char next_square(game_t *game, unsigned int snum) {
  // TODO: Implement this function.
  snake_t *ptr = game->snakes + snum;
  unsigned int row = get_next_row(ptr->head_row, get_board_at(game, ptr->head_row, ptr->head_col));
  unsigned int col = get_next_col(ptr->head_col, get_board_at(game, ptr->head_row, ptr->head_col));
  return get_board_at(game, row, col);
}

/*
  Task 4.3

  Helper function for update_game. Update the head...

  ...on the board: add a character where the snake is moving

  ...in the snake struct: update the row and col of the head

  Note that this function ignores food, walls, and snake bodies when moving the head.
*/
static void update_head(game_t *game, unsigned int snum) {
  // TODO: Implement this function.
  snake_t *ptr = game->snakes + snum;
  char head = get_board_at(game, ptr->head_row, ptr->head_col);
  unsigned int row = get_next_row(ptr->head_row, head);
  unsigned int col = get_next_col(ptr->head_col, head);
  set_board_at(game, row, col, head);

  char new_head = head_to_body(head);
  set_board_at(game, ptr->head_row, ptr->head_col, new_head);

  ptr->head_row = row; 
  ptr->head_col = col; 
}

/*
  Task 4.4

  Helper function for update_game. Update the tail...

  ...on the board: blank out the current tail, and change the new
  tail from a body character (^<v>) into a tail character (wasd)

  ...in the snake struct: update the row and col of the tail
*/
static void update_tail(game_t *game, unsigned int snum) {
  // TODO: Implement this function.
  snake_t *ptr = game->snakes + snum;
  char tail = get_board_at(game, ptr->tail_row, ptr->tail_col);
  unsigned int row = get_next_row(ptr->tail_row, tail);
  unsigned int col = get_next_col(ptr->tail_col, tail);
  char new_tail = body_to_tail(get_board_at(game, row, col));
  set_board_at(game, row, col, new_tail);

  set_board_at(game, ptr->tail_row, ptr->tail_col, ' ');

  ptr->tail_row = row; 
  ptr->tail_col = col; 
  return;
}

/* Task 4.5 */
void update_game(game_t *game, int (*add_food)(game_t *game)) {
  // TODO: Implement this function.
  // snakes, *, # or space  
  snake_t *ptr = game->snakes;
  for (unsigned int i = 0; i < game->num_snakes; i++, ptr++)
  {
      if (!ptr->live)
          continue;
      char next = next_square(game, i);
      if (is_snake(next) || next == '#')
      {
          set_board_at(game, ptr->head_row, ptr->head_col, 'x');
          ptr->live = false;
      }
      else 
      {
          update_head(game, i);
          if (next == ' ')
          {
             update_tail(game, i);
          }
          else
          {
              add_food(game);
          }
      } 
  }
  return;
}

/* Task 5.1 */
char *read_line(FILE *fp) {
  // TODO: Implement this function.
  // Must support stdin
  // allocate significantly enough memory for the board
  size_t buffer_size = 10;
  char *buffer = malloc(buffer_size);
  if (!buffer) 
      return NULL;
  // read from fp, check if \n inside it using strchr
  // if in, strlen the size and shrink the size plus 1 of buffer and return
  // else, realloc the double size, loop to read 
  // Add error handle to fgets later
  size_t initial_size = buffer_size;
  char *end_ptr = buffer;
  while(true)
  {
      if (fgets(end_ptr, (int)initial_size, fp) == NULL)
      {
          free(buffer);
          return NULL; 
      }
      if (strchr(buffer, '\n') == NULL)
      {
          buffer_size += initial_size;
          char *tmp = buffer;
          buffer = realloc(tmp, buffer_size);
          if (buffer == NULL)
          {
              free(tmp);
              return NULL;
          }
          end_ptr = strchr(buffer, '\0');
      }
      else
      {
          size_t length = strlen(buffer);
          char *tmp = buffer;
          buffer = realloc(tmp, length + 1);
          if (buffer == NULL)
          {
              free(tmp);
              return NULL;
          }
          return buffer;
      }
  }
}

/* Task 5.2 */
game_t *load_board(FILE *fp) {
  // TODO: Implement this function.
  // set num_snakes to 0 and snakes to NULL
  // for loop, allocate initial size, create a pointer keep track of the 
  // position, if i larger than the size, double it, 
  // read one line and create tmp buffer to store, if NULL:
  // if feof, note the i and shrink the size of buffer, update the row numbers
  // else -> error, free the memory and return NULL
  // else: malloc for char * and copy the tmp -> free all memory if NULL
  // add the memory handle later
  game_t *game = calloc(1, sizeof(game_t));
  if (game == NULL)
      return NULL;
  unsigned int rows = 10;
  unsigned int initial_rows = rows;
  game->board = malloc(rows * sizeof(char *));
  if (game->board == NULL)
  {
      free_game(game);
      return NULL;
  }
  char **end_ptr = game->board;
  for (int i = 0;; i++, end_ptr++)
  {
     game->num_rows = (unsigned int)i;
     if (i == rows)
     {
        rows += initial_rows;
        char **tmp = realloc(game->board, rows * sizeof(char *));
        if (tmp == NULL)
        {
            free_game(game);
            return NULL;
        }
        game->board = tmp;
        end_ptr = tmp + i;
     }
     char *tmp = read_line(fp);
     if (tmp == NULL)
     {
         // I did not know to free tmp!!
         free(tmp);
         if (feof(fp))
         {
             char **temp = realloc(game->board, (unsigned int)i * sizeof(char *));
             if (temp == NULL)
             {
                 free_game(game);
                 return NULL;
             }
             game->board = temp; 
             return game;
         }
         else
         {
             free_game(game);
             return NULL;
         }
     }
     *end_ptr = malloc(strlen(tmp) + 1);
     if (*end_ptr == NULL)
     {
         free(tmp);
         free_game(game);
         return NULL;
     }
     strcpy(*end_ptr, tmp); 
     free(tmp);
  }
}

/*
  Task 6.1

  Helper function for initialize_snakes.
  Given a snake struct with the tail row and col filled in,
  trace through the board to find the head row and col, and
  fill in the head row and col in the struct.
*/
static void find_head(game_t *game, unsigned int snum) {
  // TODO: Implement this function.
  // is_head and get_board_at
  snake_t *sptr = game->snakes + snum;
  unsigned int cur_row = sptr->tail_row;
  unsigned int cur_col = sptr->tail_col;
  char symbol = get_board_at(game, cur_row, cur_col);
  while(true)
  {
      cur_row = get_next_row(cur_row, symbol);
      cur_col = get_next_col(cur_col, symbol);
      symbol = get_board_at(game, cur_row, cur_col);
      if (is_head(symbol))
      {
          sptr->head_row = cur_row;
          sptr->head_col = cur_col;
          return;
      }
  }
}

/* Task 6.2 */
game_t *initialize_snakes(game_t *game) {
  // TODO: Implement this function.
  // create the snum to keep track the snake num
  // make a pointer to the board attrubute, for loop, iterate through the 
  // content and if char is tail, realloc snum + 1 space for snakes and pass
  // to the find_head(populate the tail first), then snum++, 
  // if outside for, update the snake_num, return 
  // handle memory error later
  unsigned int snum = 0;
  char **board = game->board;
  for (int i = 0; i < game->num_rows; i++, board++)
  {
      char *arr = *board;
      for (int j = 0; *arr; j++, arr++)
      {
          if (is_tail(*arr))
          {
              snake_t *tmp = realloc(game->snakes, (snum + 1) * sizeof(snake_t));
              if (tmp == NULL)
              {
                  free_game(game);
                  return NULL;
              }
              game->snakes = tmp;
              tmp += snum;
              tmp->tail_row = (unsigned int)i;
              tmp->tail_col = (unsigned int)j; 
              // I forgot to update live initially
              tmp->live = true;
              find_head(game, snum);
              snum++;
          }
      }
  }
  game->num_snakes = snum;
  return game;
}
