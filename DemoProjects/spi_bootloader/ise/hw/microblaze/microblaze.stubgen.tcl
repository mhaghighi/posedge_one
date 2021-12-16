cd C:/Users/Mahdi/Desktop/spi_bootloader/hw/microblaze/
if { [ catch { xload xmp microblaze.xmp } result ] } {
  exit 10
}
xset hdl verilog
run stubgen
exit 0
