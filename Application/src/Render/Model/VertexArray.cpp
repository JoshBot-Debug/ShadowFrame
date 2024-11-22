#include "VertexArray.h"

VertexArray::~VertexArray()
{
  if (vao)
    glDeleteVertexArrays(1, &vao);
}

void VertexArray::generate()
{
  if (!vao)
    glGenVertexArrays(1, &vao);
}

void VertexArray::setVertexAttribPointer(unsigned int index, unsigned int size, VertexDataType type, bool normalized, size_t stride, const void *pointer) const
{
  glVertexAttribPointer(index, size, dataTypeToGLenum(type), normalized ? GL_TRUE : GL_FALSE, stride, pointer);
  glEnableVertexAttribArray(index);
}

void VertexArray::setVertexAttribPointer(unsigned int index, unsigned int size, VertexDataType type, bool normalized, size_t stride, const void *pointer, unsigned int divisor) const
{
  glVertexAttribPointer(index, size, dataTypeToGLenum(type), normalized ? GL_TRUE : GL_FALSE, stride, pointer);
  glEnableVertexAttribArray(index);
  glVertexAttribDivisor(index, divisor);
}

  void VertexArray::bind() const { glBindVertexArray(vao); }
  void VertexArray::unbind() const { glBindVertexArray(0); }

  unsigned int VertexArray::get() const { return vao; }