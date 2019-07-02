proc pnsynth {} {
  cd C:/Users/Mahdi/Desktop/sd_new_spi/hw/microblaze
  if { [ catch { xload xmp microblaze.xmp } result ] } {
    exit 10
  }
  if { [catch {run netlist} result] } {
    return -1
  }
  return $result
}
if { [catch {pnsynth} result] } {
  exit -1
}
exit $result
