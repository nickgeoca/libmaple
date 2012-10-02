MEMORY
{
  ram (rwx) : ORIGIN = 0x20000000, LENGTH = 32K
  rom (rx)  : ORIGIN = 0x1400, LENGTH = 256K - 0x1400
}
