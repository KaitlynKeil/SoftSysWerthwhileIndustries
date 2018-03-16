float float_rand( float min, float max );

typedef struct {
  // Asteroid life
  int alive; // Is it still around?
  float life; // Health

  // position
  float xpos;
  float ypos;

  // velocity
  float xvel;
  float yvel;
} Asteroid;

typedef struct {
	int x;
	int y;
} Point;

/* Node containing an asteroid and a position. Position
should be asteroid point converted to non-float coordinates */
typedef struct 
{
	Point *pos;
	Asteroid *ast;
} Node;

Asteroid *make_asteroid();
Point *make_point(int x, int y);
void print_point(Point *p);
void print_ast(Asteroid *a);
Node *make_node(Point *center, Asteroid *ob);
void print_node(Node *n);
int ast_collision(Asteroid *ast, Point *p);
void free_asteroid(Asteroid *ast);
int update_asteroid(Asteroid *ast);
Point *convert_coords(float x, float y);
Node *ast_to_node(Asteroid *ast);