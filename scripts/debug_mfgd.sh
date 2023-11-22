#!/bin/bash

ln -s lib/libglfw.3.dylib libglfw.3.dylib
install_name_tool -add_rpath @executable_path/ mfgd
cd content
lldb ../mfgd
