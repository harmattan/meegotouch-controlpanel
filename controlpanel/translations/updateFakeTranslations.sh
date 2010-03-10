#! /bin/bash

# this little script creates fake .ts files which can be used by the
# translation.pri to create fake .qm files which will go to the
# package xxx-l10n-fake
#
# It is used to be able to demonstrate that the on the fly language
# change is working until we get the real translations.

# configure these: --
langs="ar de fi hu ur zh_CN"
pkgName="duicontrolpanel"
# --


engineering="$pkgName.ts"

createTranslation() {
    lang="$1"
    echo "Creating fake translation for $lang" >&2
    i=0
    lastWord=
    cat "$engineering" | while read line; do
        if [[ "$line" =~ '<source>' ]]
        then
            lastWord=$(echo "$line" | sed -e 's_<source>__' -e 's_</source>__')
        fi
        if [[ "$line" =~ '<translation type="unfinished"></translation>' ]]
        then
            let i++
            if [ "x$lastWord" = "x" ]; then
                echo "<translation>Fake $lang $i</translation>"
            else
                echo "<translation>(${lang}) $lastWord</translation>"
            fi
            lastWord=
        else
            echo "$line"
        fi
    done
}

for i in $langs; do
    createTranslation "$i" >"${pkgName}_${i}.ts"
done

