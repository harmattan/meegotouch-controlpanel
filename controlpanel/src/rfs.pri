
rfs.files += controlpanel-rfs.sh
rfs.path += $$system(pkg-config --variable rfs_scripts_dir clean-device)

INSTALLS += rfs


