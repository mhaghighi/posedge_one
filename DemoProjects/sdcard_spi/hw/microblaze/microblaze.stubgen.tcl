cd C:/Users/Mahdi/Desktop/sd_new_spi/sd/microblaze/
if { [ catch { xload xmp microblaze.xmp } result ] } {
  exit 10
}
xset hdl verilog
run stubgen
exit 0
