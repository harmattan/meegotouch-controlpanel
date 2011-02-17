HOST_ARCH=$$system(dpkg-architecture -qDEB_HOST_GNU_TYPE || echo "meego")
contains($$HOST_ARCH,meego){
  CONFIG += meego
  DEFINES += MEEGO
}

meego {
  message("MEEGO")
} else {
message("NON-MEEGO")
}
