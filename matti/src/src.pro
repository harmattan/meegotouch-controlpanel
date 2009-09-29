CONFIG+=ordered
TEMPLATE = subdirs

TESTAPPS+=  \
        ta_duianimatedicon \
        ta_duibutton \
        ta_duibuttongroup \
        ta_duicontainer \
        ta_duiimage \ 
        ta_duiseparator \ 
        ta_duigriditem \
        ta_duislider \
        ta_duilist \
        ta_duiinfobanner \
        ta_duiobjectmenu \
#        ta_duitoolbar \
        ta_duipopuplist \
        ta_duimashupcanvas \ 
        ta_duivideowidget \ 
#        ta_duigrid \
        ta_duilabel \
        ta_virtualkeyboard \
        ta_duiaction \
        ta_duiviewmenu \
        ta_rotation \
        ta_duiservicetester \

SUBDIRS += \
        mtestapp \
        fixture_duipopuplist \
#        fixture_duigrid \
        weatherapplet \
        $$TESTAPPS


check.target = check
check.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check

