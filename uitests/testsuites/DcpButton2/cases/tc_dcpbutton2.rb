#  Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
#  All rights reserved.
#
#  * Description: DcpButton2 test suite functional cases for Awidget
#  * Objectives: test the functionality of Awidget
#
#  Author:: Your Name (mailto:your.name@nokia.com)
#
#  This software, including documentation, is protected by copyright
#  controlled by Nokia Corporation. All rights are reserved. Copying,
#  including reproducing, storing, adapting or translating, any or all of
#  this material requires the prior written consent of Nokia Corporation.
#  This material also contains confidential information which may not be
#  disclosed to others without the prior written consent of Nokia.

require 'test/unit'
require 'matti'
include MattiVerify

class TC_DcpButton2 < Dui::TestCase

    # method called before any test case
    def setup
    # get the application
      @app = @sut.application(:name => 'ta_dcpbutton2')
      @dcpButton2 = { :name => 'DcpButton2-0' }
      @text1ToggleBtn = { :name => 'ToolBarbutton0' }
      @text2ToggleBtn = { :name => 'ToolBarbutton1' }
      @clickCounterLbl = { :name => 'ClickCounter' }
      @sleepTime = 30
    end

    # method called after any test case for cleanup purposes
    def teardown
    end

    # Verifies that the button can be found and tapped
    #
    #* Pre-conditions
    #  * ta_dcpbutton2 started
    #* Test steps
    #  * tap on DcpButton2
    #* Post-conditions
    #  * None
    #* References
    #  * None
    def test_dcpbutton2_tap
        btn = nil
        verify(sleepTime, "Couldn't tap on DcpButton2") {
               btn = @app.DcpButton2(@dcpButton2)
               btn.tap
        }
    end

    #Test case documentation one liner to include objectives
    #
    #* Pre-conditions
    #  * ta_dcpbutton2 started
    #* Test steps
    #  * tap on xxx then zzzz has changed to AAA
    #  * tap on xxx then ssss has changed to BBB
    #* Post-conditions
    #  * None
    #* References
    #  * DUI-123
=begin    
    def test_dcpbutton20_fail
      verify_true(1, "Implement your testcases here, this is just a placeholder that will always fail!") {
        false
      }
    end
=end

end
