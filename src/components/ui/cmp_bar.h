include <SFML/Graphics.hpp>

class cmp_bar {
public:


    void update(double dt) {}

    cmp_bar(Entity* p) : Component(p), _value(100.0f), _maxValue(100.0f) {}

    float getValue() const { return _value; }

    float setValue(float value) { _value = value; }


private:
    float _value;
    float _maxValue;
    float sf::RectangleShape;

};
