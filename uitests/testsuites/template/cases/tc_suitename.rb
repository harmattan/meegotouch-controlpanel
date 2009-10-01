#  Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
#  All rights reserved.
#
#  * Description: SuiteName test suite functional cases for Awidget
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

class TC_SuiteName < Dui::TestCase

    # method called before any test case
    def setup
    # get the application
      @app = @sut.application(:name => 'ta_suitename')
    end

    # method called after any test case for cleanup purposes
    def teardown
    end

    #Test case documentation one liner to include objectives
    #
    #* Pre-conditions
    #  * ta_suitename started
    #* Test steps
    #  * tap on xxx then zzzz has changed to AAA
    #  * tap on xxx then ssss has changed to BBB
    #* Post-conditions
    #  * None
    #* References
    #  * DUI-123
    def test_suitename0_fail
      verify_true(1, "Implement your testcases here, this is just a placeholder that will always fail!") {
        false
      }
    end

end
