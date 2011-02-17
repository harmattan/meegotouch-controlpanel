HOST_ARCH=$$system(dpkg-architecture -qDEB_HOST_GNU_TYPE || echo meego)
message("arch $$HOST_ARCH")
contains(HOST_ARCH,meego){
  message("preparing for MEEGO")
  CONFIG += meego
  DEFINES += MEEGO
}

meego {
  message("MEEGO")
} else {
message("NON-MEEGO")
}
