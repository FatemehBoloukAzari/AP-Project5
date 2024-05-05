#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

int main(int argc, char const *argv[])
{
    RenderWindow window(VideoMode(300,200), "Hello From SFML");
    CircleShape shape(100.f);
    shape.setFillColor(Color::Magenta);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if(event.type == Event::Closed){
                window.close();
            }
        }
        window.clear();
        window.draw(shape);
        window.display();
        
    }

    return 0;
}