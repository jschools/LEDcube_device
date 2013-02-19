
void setPixel(byte* buffer, int x, int y, int z, boolean value) {
  int index = z * CUBE_DIM + y;

  byte writeMask = 1 << x;
  if (value) {
    buffer[index] |= writeMask;
  }
  else {
    buffer[index] &= ~(writeMask);
  }
}

boolean getPixel(byte* buffer, int x, int y, int z) {
  int index = z * CUBE_DIM + y;
  return buffer[index] & (1 << x);
}
