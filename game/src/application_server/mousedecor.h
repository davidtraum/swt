#ifndef MOUSEDECOR_H
#define MOUSEDECOR_H


class MouseDecor
{
public:
    MouseDecor();
    enum TYPE {
        NONE,
        RADIUS
    };
    void setType(TYPE);
    void setValue(int);
    TYPE getType();
    int getValue();

private:
    TYPE type{NONE};
    int value{0};
};

#endif // MOUSEDECOR_H
