# FIXME: these are fake translations, can be keept up to date
# with the updateFakeTranslations.sh script. They are used to
# be able to demonstrate the on the fly language change, and
# are going in to the package duicontrolpanel-l10n-fake
#
# Remove them once we get real translations.

LANGUAGES = ar de fi hu ur zh_CN
# LANGUAGES =
CATALOGNAME = duicontrolpanel
SOURCEDIR = $$PWD/..
TRANSLATIONDIR = $$PWD
TRANSLATION_INSTALLDIR = /usr/share/l10n/meegotouch
include(../../translations.pri)

