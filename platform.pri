HOST_ARCH=$$system(dpkg-architecture -qDEB_HOST_GNU_TYPE || echo)
isEmpty($$HOST_ARCH){
  message("preparing for MEEGO")
  CONFIG += meego
  DEFINES += MEEGO
}

meego {
  message("MEEGO")
} else {
message("NON-MEEGO")
}
