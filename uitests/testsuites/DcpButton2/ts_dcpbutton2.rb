#!/usr/bin/ruby 

#  Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
#  All rights reserved.
#
#  DcpButton2 test suite 
#  Author:: Jani Mikkonen <ext-jani.3.mikkonen@nokia.com>
#
#  This software, including documentation, is protected by copyright
#  controlled by Nokia Corporation. All rights are reserved. Copying,
#  including reproducing, storing, adapting or translating, any or all of
#  this material requires the prior written consent of Nokia Corporation.
#  This material also contains confidential information which may not be
#  disclosed to others without the prior written consent of Nokia.

$_MATTI_DISABLE_STATS_REPORTING = true
PATH=File.dirname(__FILE__)
CASES=File.join(PATH,"cases")
$LOAD_PATH << "/usr/share/duifw-tests/lib"
require "dui.rb"

# Loads all the testcase files
# TODO: Move to lib/dui.rb ?
Dir.entries(CASES).each do |file|
  require File.join(CASES,file)  if file =~ /^tc_.*\.rb$/
end


suite = Dui::Runner.new
# NOTICE: Dont pass -hardware or -software anymore unless you explicitly
# require either of them, hw acceleration will be automatically probed
# at runtime via dui.rb library
suite.start('/usr/lib/dcp-ui-tests/ta_dcpbutton2','')

