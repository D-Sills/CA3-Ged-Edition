#include <SFML/Graphics.hpp>

class Interactable {
public:
    virtual ~Interactable() = default;
    virtual void interact() = 0;

    void setBoundingBox(const sf::FloatRect& box) {
        boundingBox = box;
    }

    const sf::FloatRect& getBoundingBox() const {
        return boundingBox;
    }

protected:
    sf::FloatRect boundingBox;
};