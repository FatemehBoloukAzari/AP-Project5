#include "global_stuff.h"

class Progress_Bar{
public: 
    Progress_Bar(); 
    
private:
    Texture bar_texture ; 
    Texture head_texture ; 
    Texture flag_texture ; 
    Texture progress_texture ; 
    Sprite bar_sprite ;
    Sprite head_sprite ; 
    Sprite flag_sprite ; 
    Sprite progress_sprite ;  
}; 