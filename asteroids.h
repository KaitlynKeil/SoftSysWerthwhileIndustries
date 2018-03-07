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
Asteroid *make_asteroid();
void free_asteroid(Asteroid *ast);
int update_asteroid(Asteroid *ast);