#ifndef RENDERER_TRANSFORMABLE_H
#define RENDERER_TRANSFORMABLE_H

// Interfaces que dizem se uma classe pode ser movida, rotacionada e escalonada

// ToDo: Adicionar parâmetros na assinatura

// Nomes péssimos

struct Translatable{
    ~Translatable() = default;
    virtual void translate() = 0;
};

struct Rotatable{
    ~Rotatable() = default;
    virtual void rotate() = 0;
};

struct Escalable{
    ~Escalable() = default;
    virtual void escale() = 0;
};

struct Skewable{
    ~Skewable() = default;
    virtual void skew() = 0;
};

struct Mirrorable{
    ~Mirrorable() = default;
    virtual void mirror() = 0;
};

#endif // RENDERER_TRANSFORMABLE_H