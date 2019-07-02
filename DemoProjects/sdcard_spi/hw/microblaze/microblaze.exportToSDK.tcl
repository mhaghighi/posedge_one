proc exportToSDK {} {
  cd C:/Users/Mahdi/Desktop/sd_new_spi/hw/microblaze
  if { [ catch { xload xmp microblaze.xmp } result ] } {
    exit 10
  }
  if { [run exporttosdk] != 0 } {
    return -1
  }
  return 0
}

if { [catch {exportToSDK} result] } {
  exit -1
}

set sExportDir [ xget sdk_export_dir ]
set sExportDir [ file join "C:/Users/Mahdi/Desktop/sd_new_spi/hw/microblaze" "$sExportDir" "hw" ] 
if { [ file exists C:/Users/Mahdi/Desktop/sd_new_spi/hw/edkBmmFile_bd.bmm ] } {
   puts "Copying placed bmm file C:/Users/Mahdi/Desktop/sd_new_spi/hw/edkBmmFile_bd.bmm to $sExportDir" 
   file copy -force "C:/Users/Mahdi/Desktop/sd_new_spi/hw/edkBmmFile_bd.bmm" $sExportDir
}
if { [ file exists C:/Users/Mahdi/Desktop/sd_new_spi/hw/microblaze_top.bit ] } {
   puts "Copying bit file C:/Users/Mahdi/Desktop/sd_new_spi/hw/microblaze_top.bit to $sExportDir" 
   file copy -force "C:/Users/Mahdi/Desktop/sd_new_spi/hw/microblaze_top.bit" $sExportDir
}
exit $result
