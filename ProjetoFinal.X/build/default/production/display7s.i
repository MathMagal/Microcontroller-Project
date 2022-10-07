# 1 "display7s.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.35/packs/Microchip/PIC18Fxxxx_DFP/1.2.26/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "display7s.c" 2
# 35 "display7s.c"
unsigned char display7s(unsigned char v)
{
  switch(v)
  {
    case 0:
      return 0x3F;
    case 1:
      return 0x06;
    case 2:
      return 0x5B;
    case 3:
      return 0x4F;
    case 4:
      return 0x66;
    case 5:
      return 0x6D;
    case 6:
      return 0x7D;
    case 7:
      return 0x07;
    case 8:
      return 0x7F;
    case 9:
      return 0x6F;
    case 10:
      return 0x77;
    case 11:
      return 0x7c;
    case 12:
      return 0x58;
    case 13:
      return 0x5E;
    case 14:
      return 0x79;
    case 15:
      return 0x71;
    default:
      return 0;
  }
}
