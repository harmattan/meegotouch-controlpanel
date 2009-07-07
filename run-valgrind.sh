#!/bin/sh
G_SLICE=always-malloc G_DEBUG=gc-friendly valgrind --log-file=logfile --trace-children=yes --num-callers=50 --tool=callgrind duicontrolpanel --software
