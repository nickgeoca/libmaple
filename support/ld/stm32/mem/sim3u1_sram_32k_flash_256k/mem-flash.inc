MEMORY
{
  ram (rwx) : ORIGIN = 0x20000000, LENGTH = 32K
  rom (rx)  : ORIGIN = 2048, LENGTH = 256K - 2048
}
