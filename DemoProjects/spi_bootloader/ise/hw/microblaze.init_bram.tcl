cd C:/Users/Mahdi/Desktop/spi_bootloader/hw/microblaze
if { [ catch { xload xmp microblaze.xmp } result ] } {
  exit 10
}

if { [catch {run init_bram} result] } {
  exit -1
}

exit 0
